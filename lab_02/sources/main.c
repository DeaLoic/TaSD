#include <stdio.h>
#include <stdlib.h>
#include "errorCodes.h"
#include "subscriber.h"
#include "phoneBook.h"

#define RELEASE 1    // For information messages
#define DEBUG 0      // For debug messages

void printMenu();

int main(int argc, char** argv)
{
    int errorCode = SUCCES;

    int choose = 1;
    char filename[] = "phoneBook.txt";

    phoneBook_t phoneBook;
    phoneBookKeyTable_t keyTable;
    subscriber_t tempSubscriber;
    setPhoneBookEmpty(&phoneBook);
    setKeyTableEmpty(&keyTable);
    setSubscriberEmpty(&tempSubscriber);
    int temp = 0;

    while (!errorCode)
    {
        printMenu();
        scanf("%d", &choose);

        switch (choose)
        {
            case 1:
                setPhoneBookEmpty(&phoneBook);
                setKeyTableEmpty(&keyTable);
                FILE* source = fopen(filename, "r");
                if (source)
                {
                    errorCode = inputPhoneBookFile(&phoneBook, filename);
                    fclose(source);
                    if (!errorCode)
                    {
                        createKeyTable(&phoneBook, &keyTable)
                    }
                    else
                    {
                        setPhoneBookEmpty(&phoneBook);
                        printf("\nError while reading phone book. Pls, try again\n");
                    }
                }
                else
                {
                    printf("\nError while opening file\n");
                }
                errorCode = SUCCES;
                break;
            
            case 2:
                setPhoneBookEmpty(&phoneBook);
                setKeyTableEmpty(&keyTable);

                errorCode = inputPhoneBookConsole(&phoneBook);

                if (!errorCode)
                {
                    createKeyTable(&phoneBook, &keyTable)
                }
                else
                {
                    setPhoneBookEmpty(&phoneBook);
                    printf("\nError while reading phone book. Pls, try again\n");
                }

                break;

            case 3:
                if (phoneBook.subscribersCount)
                {
                    setSubscriberEmpty(&tempSubscriber);
                    errorCode = inputSubscriber(&tempSubscriber, stdin);
                    if (!errorCode)
                    {
                        errorCode = addRecord(&phoneBook, &tempSubscriber);
                        if (errorCode)
                        {
                            printf("\nError in memory");
                        }
                    }
                    else
                    {
                        printf("\nIncorrect input. Record doesnt add\n");
                        errorCode = SUCCES;
                    }
                    setSubscriberEmpty(&tempSubscriber);
                }
                else
                {
                    printf("\nPhone book doesnt exist\n");
                }
                break;

            case 4:
                if (phoneBook.subscribersCount > 1)
                {
                    printf("\nInput position to delete\n");

                    if ((scanf("%d", &temp) == 1) && temp >= 0 && temp < phoneBook.subscribersCount)
                    {
                        errorCode = deleteRecord(&phoneBook, temp);
                        if (errorCode)
                        {
                            printf("Memory error, panic exit\n");
                        }
                    }
                    else
                    {
                        printf("Incorrect position, try again\n");
                    }   
                }
                else
                {
                    printf("\nCount of records in phone book <= 1. Deleting impossible.\n");
                }
                break;
            
            case 5:
                if (phoneBook.subscribersCount)
                {
                    printPhoneBook(&phoneBook);
                }
                else
                {
                    printf("\nPhone book doesnt exist\n");
                }
                break;
            
            case 6:
                if (keyTable.keysCount)
                {
                    printKeyTable(keyTable);
                }
                else
                {
                    printf("\nKey table is empty\n");
                }
                break;

            case 7:
                if (phoneBook.subscribersCount)
                {
                    printPhoneBookByKeyTable(phoneBook, keyTable);
                }
                else
                {
                    printf("\nPhone book doesnt exist\n");
                }
                break;

            case 8:
                if (phoneBook.subscribersCount)
                {
                    sortPhoneBook(&phoneBook, &compareSubscribersBySurname);
                    sortKeyTable(&keyTable, &compareKeyBySurname);
                }
                else
                {
                    printf("\nPhone book is empty\n");
                }
                break;
            
            case 9:
                if (phoneBook.subscribersCount)
                {
                    compareSorting(&phoneBook, &keyTable);
                }
                else
                {
                    printf("\nPhone book is empty\n");
                }
                break;
            
            case 10:
                if (phoneBook.subscribersCount)
                {
                    findWeekBirthday(&phoneBook);
                }
                else
                {
                    printf("\nPhone book is empty\n");
                }
                break;

            case 11:
                if (phoneBook.subscribersCount)
                {
                    sortKeyTable(&keyTable, &compareKeyByPosition);
                    setPhoneBookByKeyTable(&phoneBook, &keyTable);
                }
                else
                {
                    printf("\nPhone book is empty\n");
                }
                break;

            default:
                printf("\nPls, choose point from menu\n")
                break;
            
        }
    }
    if (errorCode)
    {
        printf("\nFATAL ERROR");
    }
    else
    {
        printf("\nGoodbay");
    }
    
    getchar();
    return errorCode;
}

void printMenu()
{
    printf("\n------------------MENU------------------\n");
    printf("0.  Exit\n");
    printf("1.  Input data from file phoneBook.txt\n");
    printf("2.  Input data from console\n");
    printf("3.  Add data from console\n");
    printf("4.  Delete data from temp handler\n");
    printf("5.  Print phone book\n");
    printf("6.  Print key table\n");
    printf("7.  Print phone book by key table\n");
    printf("8.  Sort (qsort)\n");
    printf("9.  Compare sorting\n");
    printf("10. Find friends with birthday in week\n");
    printf("11. Unsort (reset to raw)\n");
    printf("\nYour choose: ");
}