import csv  # reader and DictReader
import sys  # sys.argv for command-line arguments


def main():

    if len(sys.argv) != 3:
        print("Please provide csv file and a DNA sequence.")
        sys.exit(1)

    # Open the CSV file and DNA sequence, read contents into memory.
    with open(sys.argv[2], 'r') as seq:
        sequence = seq.read()

    data_bank = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            data_bank.append(row)

    STR_name = []
    STR_count = {}  # Stores STR to be sequenced.

    # Pulls keys from first dict stored in database to be used as STR.
    for key in data_bank[0]:
        if key != "name":
            STR_name.append(key)
            STR_count[key] = 0

    # For each STR, compute the longest run of consecutive repeats in the DNA sequence.
    # *hint* s[i:j] in Python takes the string s, and returns the substring with all characters from the ith character up to (but not including) the jth.
    for STR in STR_name:

        length = len(sequence)

        run = 0  # Tally of current matches of STR in sequence.

        hi_run = 0  # Highest total run of STR in sequence.

        step = 0

        first_char = STR[0]

        for i in range(0, length):

            i = i + step

            cur_sequence = sequence[i: i + len(STR)]

            if cur_sequence == STR:

                run += 1

                if run > hi_run:

                    hi_run = run

                if step + len(STR) < length:

                    step += len(STR) - 1

            else:

                run = 0

        STR_count[STR] = hi_run  # Update STR sequence count in dictionary value.

    # Compare the STR counts against each row in the CSV file.
    for person in range(len(data_bank)):

        match = 0

        for STR in STR_name:

            if int(data_bank[person][STR]) == STR_count[STR]:
                match += 1

        if match == len(STR_name):

            print(data_bank[person]["name"])
            return 0

    print("No match")


main()
