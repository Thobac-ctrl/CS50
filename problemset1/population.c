#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int endsize = 0;
    int startsize = 0;
    int years = 0;

    //Prompt for start size
    do
    {
        startsize = get_int("Set start size:\n");

    }
    while (startsize < 9);
    //Prompt for end size
    do
    {
        endsize = get_int("Set end size:\n");
    }
    while (endsize < startsize);

    //Calculate number of years until we reach threshold
    while (endsize > startsize)
    {
        years++;
        startsize = startsize + (startsize / 3) - (startsize / 4);
        if (startsize > endsize)
        {
            break;
        }
        printf("%i+++%i\n", startsize, years);

    }
    printf("Years: %i\n", years);
    // Print number of years
}