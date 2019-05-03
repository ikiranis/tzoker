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

int main()
{
    int numbers, tzokers;
    double cost;

    getUserData(&numbers, &tzokers, &cost);

    printf("\nUser Data: %d, %d, %3.2lf \n", numbers, tzokers, cost);

    return 0;
}