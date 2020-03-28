from cs50 import SQL
from sys import argv, exit
import csv


def main():
    # open database
    db = SQL("sqlite:///students.db")

    # check command-line arguments
    if len(argv) != 2:
        print("Compulsory command-line argument missing")
        exit(1)

    # open the csv file given by command-line argument
    with open(argv[1], "r") as csv_file:
        reader = csv.DictReader(csv_file)
        list_of_names = []
        # for each row, parse name
        for row in reader:
            print(row)
            list_of_names = str(row['name']).split()
            if len(list_of_names) == 2:
                first_name = list_of_names[0]
                middle_name = None
                last_name = list_of_names[1]
            elif len(list_of_names) == 3:
                first_name = list_of_names[0]
                middle_name = list_of_names[1]
                last_name = list_of_names[2]
            house = row['house']
            birth = row['birth']
            # insert each student into the students table of students.db
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       first_name, middle_name, last_name, house, birth)


main()
