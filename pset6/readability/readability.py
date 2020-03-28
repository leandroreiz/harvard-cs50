from cs50 import get_string


def main():
    text = get_string("Text: ")
    # call function to calculate the grade
    grade = round(coleman_liau_index(text))

    # printing the results
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade", grade)


def coleman_liau_index(text):
    # count the number of letters
    number_of_letters = 0
    for x in text:
        if x.isalpha():
            number_of_letters += 1

    # count the number of words
    number_of_words = len(text.split(" "))

    # count the number of sentences
    number_of_sentences = 0
    for x in text:
        if x in [".", "!", "?"]:
            number_of_sentences += 1

    # calculate the index
    L = number_of_letters / number_of_words * 100
    S = number_of_sentences / number_of_words * 100
    return 0.0588 * L - 0.296 * S - 15.8


main()
