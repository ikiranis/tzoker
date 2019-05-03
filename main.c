/**
 *
 * File: main.c
 *
 * Created by Yiannis Kiranis <std138327@ac.eap.gr>
 *
 * Date: 2019-05-03
 * Time: 16:12
 *
 * Experimental program to create random systems for tzoker
 *
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NUMBER 45
#define MAX_TZOKER 20
#define COLUMN_COST 0.50

typedef struct node {
    int number;
    struct node *next;
} RandomNumbers;

RandomNumbers *randomNumbersList;

/**
 * Get the data from user
 *
 * @param numbers
 * @param tzokers
 * @param cost
 */
void getUserData(int *numbers, int *tzokers, double *cost)
{
    printf("\n");
    do {
        printf("Πόσους τυχαίους αριθμούς θέλεις να δημιουργήσεις? ");
        scanf("%d", numbers);

        if( (*numbers < 1) || (*numbers > MAX_NUMBER) ) {
            printf("\nΠρέπει να επιλέξεις μεταξύ 1-%d\n", MAX_NUMBER);
        }
    } while ( (*numbers < 1) || (*numbers > MAX_NUMBER) );

    printf("\n");
    do {
        printf("Πόσους τυχαίους αριθμούς ΤΖΟΚΕΡ θέλεις να δημιουργήσεις? ");
        scanf("%d", tzokers);

        if( (*tzokers < 1) || (*tzokers > MAX_TZOKER) ) {
            printf("\nΠρέπει να επιλέξεις μεταξύ 1-%d\n", MAX_TZOKER);
        }
    } while ( (*tzokers < 1) || (*tzokers > MAX_TZOKER) );

    printf("\n");
    do {
        printf("Ποιο θέλεις να είναι το μέγιστο κόστος? ");
        scanf("%lf", cost);

        if((*cost < COLUMN_COST)) {
            printf("\nΤο ποσό πρέπει να είναι τουλάχιστον %3.2lf\n", COLUMN_COST);
        }
    } while (*cost < COLUMN_COST);
}

/**
 * Get a random integer, in range start-limit
 *
 * @param start
 * @param limit
 * @return
 */
int getRandomNumber(int start, int limit)
{
    return (int) (random() %limit + start);
}

/**
 * Search hay in array
 *
 * @param hay
 * @param array
 * @param elements
 * @return
 */
int isInArray(int hay, int array[], int elements)
{
    int i;

    for (i=0; i<elements; i++) {
        if (array[i] == hay) {
            return 1;
        }
    }

    return 0;
}

/**
 * Gererate random numbers and tzokers
 *
 * @param numbers
 * @param tzokers
 * @param generatedNumbers
 * @param generatedTzokers
 */
void gererateRandomNumbers(int numbers, int tzokers, int generatedNumbers[], int generatedTzokers[])
{
    int i;
    int randomNumber;

    for (i=0; i<numbers; i++) {
        do {
            randomNumber = getRandomNumber(1, MAX_NUMBER);
        } while (isInArray(randomNumber, generatedNumbers, numbers));

        generatedNumbers[i] = randomNumber;
    }

    for (i=0; i<tzokers; i++) {
        do {
            randomNumber = getRandomNumber(1, MAX_TZOKER);
        } while (isInArray(randomNumber, generatedTzokers, tzokers));

        generatedTzokers[i] = randomNumber;
    }
}

/**
 * Print array elements
 *
 * @param array
 * @param numbers
 */
void printArray(int array[], int elements)
{
    int i;

    for (i=0; i<elements; i++) {
        printf("%d ", array[i]);
    }
}

int main()
{
    int numbers, tzokers;
    double cost;

    int generatedNumbers[MAX_NUMBER], generatedTzokers[MAX_TZOKER];

    srandom(time(NULL));

//    getUserData(&numbers, &tzokers, &cost);

    numbers = 10;
    tzokers = 3;
    cost = 5.0;

    gererateRandomNumbers(numbers, tzokers, generatedNumbers, generatedTzokers);

    printf("Επιλεγμένοι αριθμοί: ");
    printArray(generatedNumbers, numbers); printf("\n");

    printf("Επιλεγμένα τζόκερ: ");
    printArray(generatedTzokers, tzokers); printf("\n");

    return 0;
}