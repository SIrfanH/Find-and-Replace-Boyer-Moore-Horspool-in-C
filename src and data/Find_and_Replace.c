#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <windows.h>
#define Size 256

void shifttable(char pattern[], int table[Size], int selection)
{
    int i,j, patternLength;
    patternLength = strlen(pattern);

    if ( selection == 1)                             // case sensitive durumu icin tablo
    {
        for(i = 0; i < 256; i++)
            table[i] = patternLength;

        for(j=0; j < patternLength-1; j++)
            table[(int)pattern[j]] = patternLength-1-j;
    }
    else
    {
        for(i = 0; i < 256; i++)
        {
            table[i] = patternLength;              //   case insensitive durumu icin tablo
        }
        for(j=0; j < patternLength-1; j++)
        {
            table[(int)pattern[j]] = patternLength-1-j;
            table[(int)pattern[j]+32] = patternLength-1-j;  // ASCII karakter aritmatigi ex. T nin kucuk hali T+32
            table[(int)pattern[j]-32] = patternLength-1-j;
        }
    }
}

void replace(char string[], char oldWord[], char newWord[], int index)
{
    int oldWordLength = strlen(oldWord);
    int newWordLenth = strlen(newWord);
    int stringLength = strlen(string);

    int i,j,k;

    for( i = index; i < index+oldWordLength; i++){
			for( j = index; string[j]; j++){                // eski kelimeyi textten siler
				string[j]=string[j+1];
			}
    }

    i = newWordLenth;

    for(i=i-1;i>=0;i--)
    {
        for( k = stringLength; k >= index; k--)      // indexten yeni kelimeyi ekler
            string[k+1] = string[k];
        stringLength++;
        string[index]=newWord[i];
    }
}

int BMHorspool(char text[],char pattern[], int index, int selection) {
	int i, k, m, n; int table[Size];

    shifttable( pattern, table, selection );
	n = strlen(text);
	m = strlen(pattern);
	i = index;
	if( selection == 1 )                              //   Case sensitive durumu icin arama
    {
        while( i <= n-1 )
        {
            k = 0;
            while( ( k <= m-1 ) && ( pattern[m-1-k] == text[i-k] ) )
                k++;
            if( k == m )
                return(i-m+1);
            else
                i += table[(int)text[i]];
        }
    }
    else
    {
        while( i <= n-1 )                             // case insensitive durumu icin arama
        {
            k = 0;
            while((k <= m-1) && (( pattern[m-1-k] == text[i-k] ) || (pattern[m-1-k] == (text[i-k]+32)) || (pattern[m-1-k] == (text[i-k]-32))) )
            {                //  ex. T textte degil diyelim o zaman T+32sini kontrol eder, veya kucuk t yok o zaman t-32yi kontrol eder
                k++;
            }

            if( k == m )
                return(i-m+1);
            else
                i += table[(int)text[i]];
        }
    }


	return -1;

}

void horspool_repetetive(char text[],char pattern[], char newWord[], int selection)
{
    int i = strlen(pattern)-1;
    int j = strlen(text);
    int k = 0;;
    int counter = 0;

    while(i <= j-1 && k != -1)
    {
        int index = BMHorspool(text,pattern, i, selection);  // kelimeynin indisini bulur ve index'e atar
        i = strlen(pattern) + index;       // ex. "Truth is Truth" diyelim ilk Truth bulundu, diger aramada ilk Truth'tan sonraki elemanlara bakar.
        k = i - strlen(pattern);

        if( k != -1 )
        {
            counter++;
            replace(text,pattern,newWord,index);
        }
    }
    printf("FOUND AND REPLACED: %d\n\n", counter);

}

void main_program_file(int selection)
{
    char text[500], filename[100], pattern[100], newWord[100];
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    printf("Enter the File path WITH .txt at the End\n");
    gets(filename);

    FILE *fp;
    fp = fopen(filename,"r+");

    if ( fp == NULL)
    {
        printf("Could not Open\n");
        return ;
    }
    printf("File Successfuly Opened\n");

    fgets( text, 500, fp);


    int len = strlen(text);
    if (text[len-1] == '\n')
    {
        text[len-1] = '\0';
    }
    printf("%s\n\n",text);


    printf("Enter the Pattern\n");
    gets(pattern);


    printf("Enter the Word You Want To Replace instead of Pattern\n");
    gets(newWord);

    printf("\nFIND : %s\n", pattern);
    printf("REPLACE : %s\n", newWord);

    if(selection == 1)
    {
        printf("OPTION : CASE SENSITIVE\n");
    }
    else
    {
        printf("OPTION : NOT CASE SENSITIVE\n");
    }
    printf("TEXT : %s\n", text);

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    horspool_repetetive(text,pattern,newWord,selection);

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("NEW TEXT : %s\n",text);
    printf("Running Time in Seconds %f   in Milliseconds %f\n", interval, interval*1000);


    fprintf(fp,"\n");
    fprintf(fp,"%s", text);



    fclose(fp);
}

int main()
{

    int selection;
    printf("Please Select an Option\n");
    printf("    1. For Case Sensitive \n");
    printf("    2. For Case InSensitive \n");
    scanf ("%d", &selection);
    getchar();
    printf("\n\n");

    if (selection == 1 || selection == 2)
    {
        main_program_file(selection);
    }
    else
    {
        printf("Please Enter a Valid Key\n");
        return main();
    }


    return 0;
}
