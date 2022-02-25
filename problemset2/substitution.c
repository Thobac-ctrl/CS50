#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validation(string arr[], int argc);
int sort_key(string arr1[], char arr2[][150], string user_plaintext);

//mainbody
int main(int argc, string argv[])
{
    //pre defined 2D array
    char key[2][150] =
    {
        {},
        {},
    };
    int z = validation(argv, argc);
    //Calls functions to validate and compute input
    //If input Key is OK asks for plaintext and encrypte it
    if (z == 0)
    {
        string user_plaintext  = get_string("plaintext:");
        sort_key(argv, key, user_plaintext);
        if (sort_key(argv, key, user_plaintext) < 1)
        {
            printf("ciphertext:");
            for (int i = 0; strlen(user_plaintext) > i; i++)
            {
                if (user_plaintext[i] >= 'A' && user_plaintext[i] <= 'Z')
                {
                    int j = user_plaintext[i];
                    user_plaintext[i] = key[0][j];
                    printf("%c", user_plaintext[i]);
                }
                else if (user_plaintext[i] >= 'a' && user_plaintext[i] <= 'z')
                {
                    int j = user_plaintext[i];
                    user_plaintext[i] = key[1][j];
                    printf("%c", user_plaintext[i]);
                }
                else
                {
                    printf("%c", user_plaintext[i]);
                }
            }
            printf("\n");
            return 0;
        }
    }
    return 1;
}

//Function to determine if Key is legit
int validation(string argv[], int argc)
{
    int count[120] = {0};
    int x = 0;
    //checks if user gave an argument
    if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //checks if Key is 26 characters long
    if (argc == 2 && strlen(argv[1]) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; strlen(argv[1]) > i; i++)
    {
        //manipulates string to a uniform case
        if (islower(argv[1][i]) > 0)
        {
            argv[1][i] = argv[1][i] - 32;
        }
        //checks if Key contains only letters
        //checks if letters repeat
        if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
        {
            x = argv[1][i];
            if (count[x] == 2)
            {
                printf("Key must not contain repeated characters.\n");
                return 0;
            }
            count[x]++;
        }
        //checks if Key contains non-alphabetic signs
        if (argv[1][i] >= '0' && argv[1][i] <= '9')
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    return 0;
}
//Function to sort Key in array
int sort_key(string argv[], char key[][150], string user_plaintext)
{

    int x = 97;
    int y = 65;
    //loop through Key and sort it in 2D Array.
    //manipulates string to a uniform uppercase
    for (int i = 0; strlen(argv[1]) > i; i++)
    {

        if (islower(argv[1][i]) > 0)
        {
            argv[1][i] = argv[1][i] - 32;
        }
        key[0][y] = argv[1][i];
        y++;
        //manipulates string to a uniform lowercase
        for (int j = 0; strlen(argv[1]) > j; j++)
        {
            if (isupper(argv[1][i]) > 0)
            {
                argv[1][i] = argv[1][i] + 32;
            }
            key[1][x] = argv[1][i];
            x++;
            break;
        }
        //printf("%c...",key[1][x - 1]);
        //printf("%c",key[0][y - 1]);
        //printf("\n");
    }
    return 0;
}