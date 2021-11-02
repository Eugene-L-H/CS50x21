def main():
    # Prompt user to enter the text that they would like to analyse.
    text = input("Please enter the text: ")

    # Count the number of letters, words and sentances in the text.
    words = len(text.split())

    letters = 0
    sentences = 0
    for char in text:
        if char.isalpha():
            letters += 1
        # Punctuation denotes the end of a sentence.
        if char == "!" or char == "?" or char == ".":
            sentences += 1
            # Punctuation is not counted as a letter.

        # Calculate average number of letters per 100 words.
        L = letters / words * 100

        # Calculate the average number of sentances per 100 words.
        S = sentences / words * 100

        # Running results through Coleman-Liau algorithm to determine grade
        # level of the text.
        grade = 0.0588 * L - 0.296 * S - 15.8

        # Display to user what reading level their text is.
    if grade < 1:
        print("Before Grade 1\n")

    elif grade > 16:
        print("Grade 16+")

    else:
        print(f"Grade {round(grade)}")


main()