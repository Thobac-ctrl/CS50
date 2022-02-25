#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//declaration of func
int sort_input(string textinput);


int main(void)
{
    //userinput
    //function call and output of grade
    string textinput = get_string("Type in your Paragraph: ");




    if (sort_input(textinput) > 15)
    {
        printf("Grade 16+\n");
    }
    if (sort_input(textinput) < 1)
    {
        printf("Before Grade 1\n");
    }
    if (sort_input(textinput) >= 1 && sort_input(textinput) <= 15)
    {
        printf("Grade %i\n", sort_input(textinput));
    }
}
//function to calculate the grade level of the text
int sort_input(string textinput)
{
    //variables for calculation
    //word = 1 -> last word in sentence has no 'space'
    float letter = 0, words = 1, sentence = 0;
    for (int i = 0; i < strlen(textinput); i++)
    {
        //manipulates string to uppercase letters
        if (islower(textinput[i]) > 0)
        {
            textinput[i] = textinput[i] - 32;
        }
        //collects letters in sentences
        if (textinput[i] >= 'A' && textinput[i] <= 'Z')
        {
            letter++;
        }
        //collects words in sentences
        if (textinput[i] == ' ')
        {
            words++;
        }
        // collects sentences in the paragraph
        if (textinput[i] == '!' || textinput[i] == '.' || textinput[i] == '?')
        {
            sentence++;
        }
    }
    //printf("%f.......%f........%f\n", letter, words, sentence);
    // calculates text grade level
    float average_letter = (letter / words) * 100;
    float average_sentence = (sentence / words) * 100;
    float grade = (0.0588 * average_letter) - (0.296 * average_sentence) - 15.8;
    return round(grade);
}