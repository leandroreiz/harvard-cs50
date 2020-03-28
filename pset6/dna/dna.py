from sys import argv, exit
import csv


def main():
    # check the number of command-line arguments
    if len(argv) != 3:
        print("Missing one or more command-line arguments")
        exit(1)  # failure
    else:
        # pass the command-line arguments as parameters for the function
        dna_test(str(argv[1]), str(argv[2]))
        exit(0)  # success


def dna_test(csv_filename, txt_filename):
    # open csv file and read its content into memory
    with open(csv_filename, "r") as csv_file:
        csv_reader = csv.reader(csv_file)

        # create a list with all the candidates and their respectives STR counts
        list_of_candidates = []
        for row in csv_reader:
            list_of_candidates.append(row)

    # open the dna sequence file
    with open(txt_filename, "r") as txt_file:
        dna_sequence = txt_file.read()

    # create substring list with all the STRs
    substr_list = []
    for i in list_of_candidates[0][1::]:
        substr_list.append(i)

    # for each STR, compute the longest run for consecutive repeats
    # declare the variables to control
    str_count = []
    for substr in substr_list:
        str_lenght = len(dna_sequence)
        start_index = 0
        end_index = str_lenght
        tmp_count = 0
        count = 0
        end_of_file = False

        # run this block until is the end of the file or no results were found
        while(not end_of_file):
            # look for the substring inside the string obtained from file
            if dna_sequence.find(substr, start_index, end_index) != -1:
                start_index = dna_sequence.find(substr, start_index, end_index) + len(substr)
                end_index = start_index + len(substr)
                tmp_count += 1

                # keep couting until the sequence remains
                while dna_sequence.find(substr, start_index, end_index) != -1:
                    start_index += len(substr)
                    end_index = start_index + len(substr)
                    tmp_count += 1

                # update the counters
                if count < tmp_count:
                    count = tmp_count
                tmp_count = 0

                # check if the string still have any sequence of the substring
                if dna_sequence.find(substr, start_index, str_lenght) != -1 and end_index < str_lenght:
                    start_index = dna_sequence.find(substr, start_index, str_lenght)
                    end_index = str_lenght
                # if not, set set the end of file and update the list of strs
                else:
                    end_of_file = True
                    str_count.append(str(count))
            else:
                str_count.append(str(count))
                end_of_file = True

    # compare the STR counts against each row in the csv file
    for row in list_of_candidates[1::]:
        if str_count == row[1::]:
            print("".join(row[0:1]))
            exit(0)
    print("No match")
    exit(1)


main()