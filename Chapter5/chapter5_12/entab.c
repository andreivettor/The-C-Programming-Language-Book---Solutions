/*
 *  Chapter 5, Exercise 12
 *  Title: Entab with arguments
 *  Author: Andrei Vettor
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000
#define DEFAULT_TAB_OFFSET 0
#define DEFAULT_TAB_LENGTH 8

#define START_INDEX tablen + tabofs
#define END_INDEX n - (n - tabofs) % tablen


int getln(char s[], int maxlines);
void convargs(int argc, char* argv[]);
void entab();


char line[MAXLEN];
char result[MAXLEN];
int n;
int tabofs = 0;
int tablen = 8;

int main(int argc, char* argv[])
{
    int i;
    int j;
    int index;
    char space;
    
    int resindex = 0;

    convargs(argc, argv);
    n = getln(line, MAXLEN) - 1;

    // Handle / Copy characters before upset
    for(i = 0; i < tabofs; ++i)
    {
        result[resindex++] = line[i];
    }

    for(i = START_INDEX; i <= END_INDEX; i += tablen)
    {
        // Reset spaces flag
        space = 0;

        for(j = i; j > i - tablen; --j)
        {
            if(line[j] == ' ')
            {
                space = 1;
            }
            else
            {
                // Copy the characters up to the space
                index = j + space;
                for(j = i - tablen; j < index; ++j)
                {
                    result[resindex++] = line[j];
                }

                // If any spaces were present add a tab character
                if(space)
                {
                    result[resindex++] = '\t';
                }

                break;
            }
        }
    }

    for(i = END_INDEX; i < n; ++i)
    {
        result[resindex++] = line[i];
    }
    result[resindex] = '\0';

    printf("%s", result);

    return 0;
}

int getln(char s[], int maxlines)
{
    char c;
    int i = 0;

    while((c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }

    if(c == '\n')
    {
        s[i++] = c;
    }

    s[i] = '\0';

    return i;
}

void convargs(int argc, char* argv[])
{
    int i;

    tabofs = DEFAULT_TAB_OFFSET;
    tablen = DEFAULT_TAB_LENGTH;

    for(i = 1; i < argc; ++i)
    {
        switch(argv[i][0])
        {
            case '-':
            {
                tabofs = -atoi(argv[i]);
                break;
            }
            case '+':
            {
                tablen = atoi(argv[i]);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}