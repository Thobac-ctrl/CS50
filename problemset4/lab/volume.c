// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header //
const int HEADER_SIZE = 44;
const int FILE_SIZE = 352844;

int main(int argc, char *argv[])
{
    int16_t sample_buffer;
    uint8_t header_buffer[HEADER_SIZE];


    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // atof converts a  numeric string into its equivalent integers (int,float,long ...)
    float factor = atof(argv[3]);
    //Read header from input file and copy it to output file
    fread(header_buffer, HEADER_SIZE, 1, input);
    fwrite(header_buffer, HEADER_SIZE, 1, output);


    //Read in sample in buffer
    //Loop through buffer and manipulted the samples by the given factor
    // write updated_sample to the output file
    while (fread(&sample_buffer, 2, 1, input))
    {
        sample_buffer = sample_buffer * factor;
        fwrite(&sample_buffer, 2, 1, output);
    }


    //Close Files
    fclose(input);
    fclose(output);

}
