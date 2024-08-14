#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *formatNumber(char *input, char begin, char divider)
{
    int length = strlen(input);

    int formattedLength = length + length / 3 + 2;

    char *formattedNumber = (char *)malloc(formattedLength);

    int j = 0;
    int commaCount = length % 3;

    formattedNumber[0] = begin;
    j = j + 1;

    for (int i = 0; i < length; i++)
    {
        formattedNumber[j] = input[i];
        j = j + 1;

        if (commaCount > 0 && i < length - 1 && (i + 1) % 3 == commaCount)
        {
            formattedNumber[j++] = divider;
        }
        else if (commaCount == 0 && i < length - 1 && (i + 1) % 3 == 0)
        {
            formattedNumber[j++] = divider;
        }
    }

    formattedNumber[j] = '\0';

    return formattedNumber;
}

int main(int argc, char *argv[])
{
    // open file for writing
    FILE *outputFile = fopen(argv[1], "w");

    // allocate memory to save one complete number into
    char *number = (char *)malloc(10 * sizeof(char));
    int index = 0;

    // read one character form stdin
    int c = fgetc(stdin);

    // keep reading until the end of File sign(EOF)
    while (c != EOF)
    {
        if (c != ' ')
        {
            number[index] = c;
            index++;
        }

        if (c == ' ')
        {
            if (index > 0)
            {
                // end the stream number as we complete read the number
                number[index] = '\0';

                // format the number that we just read
                char *formattedNumber = formatNumber(number, argv[2][0], argv[3][0]);

                // write to our destination
                fprintf(outputFile, " %s ", formattedNumber);
                fflush(outputFile);

                // Resetting
                free(number);
                free(formattedNumber);
                number = (char *)malloc(10 * sizeof(char));
                index = 0;
            }
        }
        // instead of writing output to console(stdout)
        // we print it  in the file
        // fprintf(stdout, "%c", c);
        // fprintf(outputFile, "%c", c);

        // read another character from stdin
        c = fgetc(stdin);
    }

    // close the open file that we wrote to
    fclose(outputFile);
    exit(0);
}