from cs50 import SQL
from sys import argv, exit

# open database
db = SQL("sqlite:///students.db")

# check command-line arguments
if len(argv) != 2:
    print("Compulsory command-line argument missing")
    exit(1)

# query database for all students in house
# students should be sorted alphabetically by last name, then first name
database = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])

# print out each student's full name and birth year
for n in range(len(database)):
    if database[n]['middle'] != None:
        print(f'{database[n]["first"]} {database[n]["middle"]} {database[n]["last"]}, born {database[n]["birth"]}')
    else:
        print(f'{database[n]["first"]} {database[n]["last"]}, born {database[n]["birth"]}')
