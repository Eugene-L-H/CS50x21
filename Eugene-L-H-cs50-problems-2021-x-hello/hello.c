#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    // Asks user to input their name and prints a unique greeting to them.
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}