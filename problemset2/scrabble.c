#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Prototype func
int calculate_score(string input, int a, int  b, int arr1[], int arr2[]);

//Main body
int main(void)
{
    // Variabls
    int x = 0;
    int counted = 0;
    int totalscore = 0;
    // Arrays to collect important data
    int count[26] = {0};
    int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    // Get input from user
    string word1 = get_string("Word Player1 :");
    string word2 = get_string("Word Player2 :");
    // Call func
    int score1 = calculate_score(word1, x, totalscore, count, score);
    int score2 = calculate_score(word2, x, totalscore, count, score);
    // Print endresult
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    //printf("%i......%i", score1, score2);
}
//Main func to check input , convert it in uniform lowercase,..
//count occurence and store them in array
//compute totalscore by multiplying the 2 Arrays
int calculate_score(string word, int x, int totalscore, int count[], int score[])
{
    for (int i = 0; strlen(word) > i; i++)
    {
        if (isupper(word[i]) > 0)
        {
            word[i] = word[i] + 32;
        }
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            x = word[i] - 97;
            count[x]++;
        }
        //printf("%c      %i      \n", word[i], word[i]);
    }
    //26 lenght of the alphabet
    for (int j = 0; j < 26; j++)
    {
        if (count[j] >= 1)
        {
            totalscore += count[j] * score[j];
            count[j] = 0;
        }
    }
    return totalscore;
}