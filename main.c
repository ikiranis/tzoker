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
#define COLUMN_LENGTH 5

typedef struct column {
    int array[COLUMN_LENGTH];
} Column;

typedef struct node {
    Column column;
    struct node * next;
} Node;

int generatedNumbers[MAX_NUMBER], generatedTzokers[MAX_TZOKER];

int numbers, tzokers, columns;
double cost;
int combinations;

Node *ColumnsList;

/**
 * And column to columns List
 *
 * @param column
 */
void insertNodeToColumnsList(Column column)
{
    Node *new = (Node *) malloc(sizeof(Node));

    if (new == NULL)
    {
        printf("Δεν υπάρχει διαθέσιμη Μνήμη\n");
        exit(1);
    }

    new->column = column;
    new->next = ColumnsList;
    ColumnsList = new;
}

/**
 * Display columns of Columns List
 */
void displayColumnsList()
{
    int i;
    Node *current = ColumnsList;

    while(current != NULL) {
        for(i=0; i<COLUMN_LENGTH; i++) {
            printf("%d ", current->column.array[i]);
        }

        printf("\n");

        current = current->next;
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

/**
 * Calculate factorial
 *
 * @param number
 * @return
 */
long int factorial(long int number)
{
    if(number==0) {
        return 1; // Επιστρέφει 1 και τερματίζεται την αναδρομή
    } else {
        return number * factorial(number-1); // n!=n*(n-1)!
    }
}

/**
 * Get the data from user
 */
void getUserData()
{
    printf("\n");
    do {
        printf("Πόσους τυχαίους αριθμούς θέλεις να δημιουργήσεις? ");
        scanf("%d", &numbers);

        if( (numbers < 1) || (numbers > MAX_NUMBER) ) {
            printf("\nΠρέπει να επιλέξεις μεταξύ 1-%d\n", MAX_NUMBER);
        }
    } while ( (numbers < 1) || (numbers > MAX_NUMBER) );

    printf("\n");
    do {
        printf("Πόσους τυχαίους αριθμούς ΤΖΟΚΕΡ θέλεις να δημιουργήσεις? ");
        scanf("%d", &tzokers);

        if( (tzokers < 1) || (tzokers > MAX_TZOKER) ) {
            printf("\nΠρέπει να επιλέξεις μεταξύ 1-%d\n", MAX_TZOKER);
        }
    } while ( (tzokers < 1) || (tzokers > MAX_TZOKER) );

    printf("\n");
    do {
        printf("Ποιο θέλεις να είναι το μέγιστο κόστος? ");
        scanf("%lf", &cost);

        if((cost < COLUMN_COST)) {
            printf("\nΤο ποσό πρέπει να είναι τουλάχιστον %3.2lf\n", COLUMN_COST);
        }
    } while (cost < COLUMN_COST);
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
int isInArray(int hay, const int array[], int elements)
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
 * Gererate random numbers for array
 *
 * @param elements
 * @param limit
 * @param array
 */
void gererateRandomNumbers(int array[], int elements, int limit)
{
    int i;
    int randomNumber;

    for (i=0; i<elements; i++) {
        do {
            randomNumber = getRandomNumber(1, limit);
        } while (isInArray(randomNumber, array, elements));

        array[i] = randomNumber;
    }
}

/**
 * Calculate how many columns can pick at this cost
 *
 * @return
 */
int calculateColumnsNumber()
{
    return (int) (cost / COLUMN_COST);
}

/**
 * Create columns combinations
 *
 * @param elements
 */
int createCombinations(int elements)
{
    int countCombinations = 0;
    int a, b, c, d, e;
    Column column;

    // TODO refactor this with recursive function
    for (a=0; a<elements; a++) {
        for (b=a+1; b<elements; b++) {
            for (c=b+1; c<elements; c++) {
                for (d=c+1; d<elements; d++) {
                    for (e=d+1; e<elements; e++) {

                        column.array[0] = generatedNumbers[a];
                        column.array[1] = generatedNumbers[b];
                        column.array[2] = generatedNumbers[c];
                        column.array[3] = generatedNumbers[d];
                        column.array[4] = generatedNumbers[e];

                        insertNodeToColumnsList(column);

                        countCombinations++;
                    }
                }
            }
        }
    }

    return countCombinations;
}

/**
 * Get random column from columns list
 *
 * @param randomColumn
 * @return
 */
Node * getRandomColumn(int randomColumn)
{
    int i;
    Node * current = ColumnsList;

    for(i=0; i<randomColumn; i++) {
        current = current->next;
    }

    return current;
}

/**
 * Sort column numbers
 *
 * @param column
 */
void sortColumn(Column *column)
{
    int i, j, temp;

    // Ascending Bubble sort
    for (i=0; i<COLUMN_LENGTH-1; i++) {
        for (j=COLUMN_LENGTH-1; j>=i+1; j--) {
            if (column->array[j]<column->array[j-1]) {
                temp = column->array[j-1];
                column->array[j-1] = column->array[j];
                column->array[j] = temp;
            }
        }
    }
}

/**
 * Print a column
 *
 * @param column
 */
void printColumn(Column column)
{
    int i;

    sortColumn(&column);

    for(i=0; i<COLUMN_LENGTH; i++) {
        printf("%3d", column.array[i]);
    }
}

/**
 * Display random columns from columns list
 */
void printRandomColumns()
{
    int i;
    int randomNumbers[columns];
    int randomTzoker;
    Node * randomColumn;

    for(i=0; i<columns; i++) {
        do {
            randomNumbers[i] = getRandomNumber(0, combinations);
        } while (!isInArray(randomNumbers[i], randomNumbers, columns));

        randomColumn = getRandomColumn(randomNumbers[i]);
        randomTzoker = getRandomNumber(0, tzokers);

        printColumn(randomColumn->column);

        printf("\t| %d\n", generatedTzokers[randomTzoker]);
    }
}

int main()
{
    srandom(time(NULL));

    getUserData(&numbers, &tzokers, &cost);

//    numbers = 10;
//    tzokers = 3;
//    cost = 5.50;

    gererateRandomNumbers(generatedNumbers, numbers, MAX_NUMBER);
    gererateRandomNumbers(generatedTzokers, tzokers, MAX_TZOKER);

    printf("\n");

    printf("Επιλεγμένοι αριθμοί: ");
    printArray(generatedNumbers, numbers); printf("\n");

    printf("Επιλεγμένα τζόκερ: ");
    printArray(generatedTzokers, tzokers); printf("\n");

    columns = calculateColumnsNumber(cost);
    printf("Σύνολο στηλών: %d\n", columns);

    combinations = createCombinations(numbers);

    printf("\n%d επιλεγμένες τυχαίες στήλες από %d συνολικά συνδυασμούς\n", columns, combinations);
    printRandomColumns();

    return 0;
}