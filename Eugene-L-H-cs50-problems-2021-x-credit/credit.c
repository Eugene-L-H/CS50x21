#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for a credit card number.
    long credit_number = get_long("Please enter your credit number: ");

    // This will hold the sum of all the digits added up from
    // the algorithm.
    int total = 0;

    // This will hold the number of digits in the user's credit number.
    int length = 0;

    // Counts the number of digits in the credit number.
    long cn_digit_count = credit_number; // Copy of credit_number for this loop
    while (cn_digit_count > 0)
    {
        cn_digit_count /= 10;
        length++;
    }


    // Determines how many times the loop will iterate though the number
    int count_back = length;
    // Alterates between true and false each iteration
    bool two = false;
    // Variable to hold value of each digit as credit_number is iterated through.
    int digit;
    // Applies Luhn's algorithm
    cn_digit_count = credit_number; // Copy of credit_number for this loop
    while (count_back != 0)
    {
        // Leaves the reaminder of credit_number dived by 10, which will be
        // the right-most digit in the number.
        digit = cn_digit_count % 10;

        // Each digit will be multiplied by 2 and added together if after
        // mulitplication there are two digits present.
        if (two == true)
        {
            // Multiply digit by two.
            digit *= 2;

            // if digit length is more than one, they are added together.
            if (digit / 10 == 1)
            {
                // The first number is the remainder when divided by 10 and the second
                // will always be 1.
                digit = (digit % 10) + 1;
            }
        }

        // Switches "two" to true in order alternate the multiplication.
        if (two == false)
        {
            two = true;
        }
        else if (two == true)
        {
            two = false;
        }
        // Add digit to total.
        total += digit;

        // Divides credit_number(copied to "cn_digit_count") by 10 to eliminate the furthest right
        // digit.
        cn_digit_count = cn_digit_count / 10;

        // Reduce count_back(wards) by 1. When at 0 the loop exits.
        count_back -= 1;

    }

    // Check length and starting digits.

    // Determines the starting two digits in credit_number
    int zeros = length - 2;
    long first_two = 1;

    while (zeros > 0)
    {
        first_two *= 10;
        zeros --;
    }

    first_two = credit_number / first_two;

    if (total % 10 > 0)
    {
        printf("INVALID\n");
    }

    else if (first_two == 34 || first_two == 37)
    {
        if (length == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (first_two == 51 || first_two == 52 || first_two == 53 || \
             first_two == 54 || first_two == 55)
    {
        if (length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (first_two / 10 == 4)
    {
        if (length == 13 || length == 16)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}