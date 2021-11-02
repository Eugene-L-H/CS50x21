def main():
    # Prompt user for a credit card number.
    while True:
        credit_num = input("Number: ")
        try:
            int(credit_num)
            break
        except ValueError:
            continue

    credit_list = []

    for i in credit_num[::-1]:  # append individual integers to list in reverse order
        credit_list.append(int(i))

    # This will hold the number of digits in the user's credit number.
    length = len(credit_num)

    # Variable to hold value of each digit as credit_number is iterated through.
    digits = []
    # Applies Luhn's algorithm
    double = False
    for i in credit_list:
        num = i
        if double:
            num = num * 2
            if len(str(num)) > 1:
                num = num - 9
            double = False
        else:
            double = True
        digits.append(num)

    # This will hold the sum of all the digits added up from the algorithm
    total = sum(digits)

    first_two = credit_num[0] + credit_num[1]

    if total % 10 == 0:

        if first_two == "51" or first_two == "52" or first_two == "53"\
                or first_two == "54" or first_two == "55":
            if length == 16:
                print("MASTERCARD")
                return 1

        elif first_two == "34" or first_two == "37":
            if length == 15:
                print("AMEX")
                return 2

        elif first_two[0] == "4":
            if length == 13 or length == 16:
                print("VISA")
                return 3


    print("INVALID")
    return 4


main()