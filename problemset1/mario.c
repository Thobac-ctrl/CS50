#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int userinput = 0;

    // Asks user for a positiv Number which is bigger than 0 and smaller than 8
    while (userinput < 1 || userinput > 8)
    {
        userinput = get_int("Enter a positiv Number!\n");
    }


    // Print n lines (n = userinput)
    for (int i = 0; i < userinput; i++)
    {
        //indent (whitespace) to align # to the right
        for (int k = userinput - i - 1; k > 0; k--)
        {
            printf(" ");
        }
        //Print as many hastags as linenumber
        // LINE(1) #
        // LINE(2)##
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}