#include <stdio.h>
#include <cs50.h>

int main(void)
{
// Asks user for input
    string username = get_string("Whats your name?\n");

// Welcomes new user
    printf("Hello,%s\n", username);
}

