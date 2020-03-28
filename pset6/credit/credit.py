import math


def main():
    # input the credit card number
    card_number = int(input("Number: "))
    print(is_valid(card_number))


def is_valid(card_number):
    # converting the card number to a list
    li = [int(n) for n in str(card_number)]

    # reversing the list
    li.reverse()

    # multiply every other digit by 2, starting from the second-to-last
    li[1::2] = [n * 2 for n in li[1::2]]

    # add the products' digits
    products = li[1::2]
    product_digits_total = 0
    for i in range(len(products)):
        product_digits_total += sum_digits(products[i])

    # add the sum to the sum of the digits that weren't multiplied by 2
    checksum = product_digits_total + sum(li[::2])

    # if the total's last digit is 0, the number is valid
    if checksum % 10 == 0:
        # AMEX starts with 34 or 37, uses 15-digit numbers
        if len(str(card_number)) == 15:
            first_digit = math.floor(card_number / 10000000000000)
            if first_digit == 34 or first_digit == 37:
                return "AMEX"
            else:
                return "INVALID"
        # MasterCard starts with 51, 52, 53, 54 or 55, uses 16-digit numbers
        elif len(str(card_number)) == 16:
            first_digit = math.floor(card_number / 100000000000000)
            if first_digit in [51, 52, 53, 54, 55]:
                return "MASTERCARD"
            elif (math.floor(first_digit / 10) == 4):
                return "VISA"
            else:
                return "INVALID"
        # Visa starts with 4, uses 13- and 16-digit numbers
        elif len(str(card_number)) == 13:
            first_digit = math.floor(card_number / 100000000000)
            if first_digit == 4:
                return "VISA"
            else:
                return "INVALID"
    else:
        return "INVALID"


def sum_digits(number):
    result = 0
    while(number > 0):
        digit = number % 10
        result = result + digit
        number = int(number / 10)
    return int(result)


main()
