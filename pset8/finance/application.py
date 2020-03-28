import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # update rows dictionary
    update = db.execute("SELECT symbol, sum(CASE WHEN status = 1 THEN shares ELSE - shares END) AS net_shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING net_shares > 0",
                       user_id=session["user_id"])

    # get the updated prices into a dictionary
    for item in update:
        prices = lookup(item["symbol"])
        db.execute("UPDATE transactions SET current_price=:current_price, updated=:updated WHERE symbol=:symbol AND user_id=:user_id",
                    current_price=prices["price"], updated=datetime.datetime.now(), symbol=prices["symbol"], user_id=session["user_id"])

    # get table with all the shares the current user has
    rows = db.execute("SELECT symbol, name, sum(CASE WHEN status = 1 THEN shares ELSE - shares END) AS net_shares, price, current_price, updated, user_id FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING net_shares > 0",
                       user_id=session["user_id"])

    # get user's actual balance
    user_balance = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

    # get sum of all holding shares
    total = db.execute("SELECT SUM((CASE WHEN status=1 THEN shares ELSE -shares END) * current_price) AS total FROM transactions WHERE user_id=:user_id", user_id=session["user_id"])

    # render the index page with the table
    return render_template("index.html", rows=rows, user_balance=user_balance, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # check if the symbol is valid
        if not request.form.get("symbol"):
            return apology("must provide a valid symbol")

        # check if number of shares is a positive number
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("must provide a positive number")

        # get the stock's data
        result = lookup(request.form.get("symbol"))

        # get the current price for the symbol returned
        current_price = result["price"]

        # how much cash the user currently has
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

        # check if user has enough funds to buy the desired shares
        if user_cash[0]["cash"] < (current_price * shares):
            return apology("insufficient funds")

        # insert data into the transactions table / set status = 1 (buy)
        db.execute("INSERT INTO transactions (symbol, name, shares, price, status, time, user_id, current_price, updated) VALUES (:symbol, :name, :shares, :price, :status, :time, :user_id, :current_price, :updated)",
                    symbol=result["symbol"], name=result["name"], shares=shares, price=current_price, status=1, time=datetime.datetime.now(), user_id=session["user_id"], current_price=current_price, updated=datetime.datetime.now())

        # calculate new balance
        new_balance = user_cash[0]["cash"] - (current_price * shares)

        # update user's balance
        db.execute("UPDATE users SET cash=:new_balance WHERE id=:id", new_balance=new_balance, id=session["user_id"])

        # redirect to index
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT symbol, (CASE WHEN status=1 THEN shares ELSE -shares END) AS shares, price, time FROM transactions WHERE user_id=:user_id ORDER BY time", user_id=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # check if the symbol exists
        if lookup(request.form.get("symbol")) == None:
            return apology("invalid symbol")
        else:
            result = lookup(request.form.get("symbol"))
            return render_template("quoted.html", result=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check if username was informed
        if not username:
            return apology("must provide username")

        # check if the username already exist in the database
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if len(rows) == 1:
            return apology("this username is already taken")

        # check if password was provided
        if not password:
            return apology("must provide password")

        # check if password and confirmation matches
        if not (password == confirmation):
            return apology("the password does not match")
        else:
            hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=len(password))
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hash)
            return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        shares = int(request.form.get("shares"))

        # get the number of shares the user has to that specific symbol
        owned_shares = db.execute("SELECT SUM(CASE WHEN status=1 THEN shares ELSE -shares END) AS net_shares FROM transactions WHERE symbol=:symbol AND user_id=:user_id",
                                   symbol=request.form.get("symbol"), user_id=session["user_id"])

        # check if the number of sold shares is less or equal the number of owned shares
        if shares <= owned_shares[0]["net_shares"]:

            # check for the updated price
            result = lookup(request.form.get("symbol"));
            current_price = result["price"]

            # get user's balance
            user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])

            # update the table transactions adding a sell order / status = 2 (sell)
            db.execute("INSERT INTO transactions (symbol, name, shares, price, status, time, user_id, current_price, updated) VALUES (:symbol, :name, :shares, :price, :status, :time, :user_id, :current_price, :updated)",
                        symbol=result["symbol"], name=result["name"], shares=shares, price=current_price, status=2, time=datetime.datetime.now(), user_id=session["user_id"], current_price=current_price, updated=datetime.datetime.now())

            # update user's balance
            new_balance = user_cash[0]["cash"] + (current_price * shares)
            db.execute("UPDATE users SET cash=:new_balance WHERE id=:id", new_balance=new_balance, id=session["user_id"])

            # redirect to index
            return redirect("/")
        else:
            return apology("you have " + str(owned_shares[0]["net_shares"]) + " share(s) (" + request.form.get("symbol") + ") and you're trying to sell " + str(shares) + " share(s).")
    else:
        rows = db.execute("SELECT symbol, sum(CASE WHEN status = 1 THEN shares ELSE - shares END) AS net_shares FROM transactions WHERE user_id=:user_id GROUP BY symbol HAVING net_shares > 0", user_id=session["user_id"])
        return render_template("sell.html", rows=rows)


# personal touch to allow the user to change their password
@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    if request.method == "POST":
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")
        if new_password == confirmation:
            # hash password
            hash = generate_password_hash(new_password, method='pbkdf2:sha256', salt_length=len(new_password))
            # change password in database
            db.execute("UPDATE users SET hash=:hash WHERE id=:user_id", hash=hash, user_id=session["user_id"])
            return redirect("/")
        else:
            apology("the password does not match")
    else:
        return render_template("change.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
