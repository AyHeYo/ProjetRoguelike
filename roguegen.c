#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20


void labgen(char lab[N][N]);

int main()
{
    char lab[N][N];
    srand((unsigned int)time(NULL));
    labgen(lab);
    return 0;
}
void labgen(char a[N][N])
{
    size_t rang,col = 0, r;

  //  Initialisation de toutes les positions partant du coté gauche du mur
    for ( rang = 0; rang < N; rang++ )
    {
	 for (col = 0; col < N; col++)
        {
            printf("%2c",a[rang][col]);
        }
        a[rang][col] = '#';
 	a[rang][N - 1] = '#';
    }

   
    rang = rand() % 19 + 1;
    a[rang][0] = '#';

   
    rang = rand() % 19 + 1;
    a[rang][N - 1] = '#';


    for (col = 1; col < N - 1; col++)
    {
        a[0][col] = '#';
	a[N - 1][col] = '#';
    }


    for (rang = 0; rang < N; rang++)
    {
        for (col = 0; col < N; col++)
        {
            printf("%2c",a[rang][col]);
        }
        puts("");
    }
    puts("");
}
