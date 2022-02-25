#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

int main(void)
{
    long userinput = 0;
    int validation = 0;
    int storage1[20];//even numbers
    int storage2[20];//uneven numbers
    int storage3[20];// backup of input
    int sumeven = 0;
    int sumuneven = 0;
    int i = 0;//index counter
    int j = 0;//storage1
    int l = 0;//storage2
    int o = 0;//storage3

    // Ask the user for a valid input (Cardnumber)
    while (userinput < 1)
    {
        userinput = get_long("Enter your valid number!\n");
    }
    // Start validation process to determine if number is valid
    while (!validation)
    {
        //Takes userinput and manipulat it by:
        //break up input in single digits and multiplying every second digit by 2
        while (userinput != 0)
        {
            int eventimes2 = 0;
            int uneven = 0;
            int backup = 0;
            // break up input
            int digit = userinput % 10;
            userinput = userinput / 10;
            i++;
            // sort out every second digit and multiply by 2
            // even numbers
            if (i % 2 == 0)
            {
                eventimes2 = digit * 2;
            }
            if (i % 2 != 0)
            {
                uneven = digit;
            }
            //store important digits for algorithmus in array
            storage1[j] = eventimes2;
            storage2[l] = uneven;
            storage3[o] = digit;
            //printf("%i           %i            %i          %i           %i\n", digit, i, storage1[j], storage2[l], storage3[o]);
            j++;
            l++;
            o++;
        }
        //Prompt if cardnumber is invalid
        if (i < 13 || i  > 16)
        {
            printf("INVALID\n");
            break;
        }
        // Loop to enter storage1 and manipulate numbers which are bigger than 9 and sum up numbers
        // Loop to enter storage2 and sum up numbers
        for (int k = 0; k < i; k++)
        {
            if (storage1[k] / 10 >= 1)
            {
                storage1[k] = storage1[k] % 10 + storage1[k] / 10;
            }
            sumeven += storage1[k];
            sumuneven += storage2[k];
        }

        // Validation algorithmus + prompt if invalid
        int checksum = sumeven + sumuneven;
        if (checksum % 10 != 0)
        {
            printf("INVALID\n");
            break;
        }
        //printf("####%i####%i####%i\n",checksum,storage3[i-1],storage3[i-2]);
        //Check for card company and prompt the result
        //Break if card is unkown
        if (storage3[i - 1] < 2 || storage3[i -  1] > 5)
        {
            printf("INVALID\n");
            break;
        }
        if (storage3[i - 1] == 4)
        {
            printf("VISA\n");
        }
        if (storage3[i - 1] == 3)
        {
            if (storage3[i - 2] == 4 || storage3[i - 2] == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
                break;
            }
        }
        if (storage3[i - 1] == 5)
        {
            if (storage3[i - 2] < 1 || storage3[i - 2] <= 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
                break;
            }
        }
        // Validation prompt end of loop
        //printf("VALIDATION SUCCEEDED\n");
        validation = 1;
    }
}
