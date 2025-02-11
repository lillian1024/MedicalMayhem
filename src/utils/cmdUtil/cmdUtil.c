#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include "cmdUtil.h"
#include "../../config.h"
#include "menus/mainMenu/mainMenu.h"

#define TITLE_LR_PADDING 5
#define TITLE_UD_PADDING 1

void CmdLaunch(int* appFlags)
{
    clrscr();

    DisplayTitle();
    ShowMainMenu(0, appFlags);
}

void DisplayTitleEmptyLine(int titleLineLen)
{
    for (int i = 0; i < TITLE_UD_PADDING; i++)
    {
        printf("⎹");
        DisplayLine(" ", titleLineLen-2);
        printf("⎹\n");
    }
}

void DisplayTitleMiddleLine()
{
    printf("⎹");
    for (int i = 1; i < TITLE_LR_PADDING; i++)
    {
        printf(" ");
    }
    printf("%s%s%s", TTYUNDER, PROJECT_NAME, TTYNUND);
    for (int i = 1; i < TITLE_LR_PADDING; i++)
    {
        printf(" ");
    }
    printf("⎹\n");
}

void DisplayTitle()
{
    int titleLen = strlen(PROJECT_NAME);
    int titleLineLen = titleLen + (2 * TITLE_LR_PADDING);

    printf("%s", TTYGRN);

    printf("⎾");
    DisplayLine("⎺", titleLineLen-2);
    printf("⏋");

    printf("\n");

    DisplayTitleEmptyLine(titleLineLen);

    DisplayTitleMiddleLine();
    
    DisplayTitleEmptyLine(titleLineLen);

    printf("⎿");
    DisplayLine("⎽", titleLineLen-2);
    printf("⏌");

    printf("%s", TTYDEF);

    printf("\n");
}

void DisplayLine(char* s, int nb)
{
    for (int i = 0; i < nb; i++)
    {
        printf("%s", s);
    }
}

int AskIntChoice(int minChoice, int maxChoice)
{
    int choice;

    scanf("%d", &choice);
    flushSTDIN();

    while (choice < minChoice || choice > maxChoice)
    {
        printf("Invalid choice (%d-%d)! \nPlease try again: ", minChoice, maxChoice);
        scanf("%d", &choice);
        flushSTDIN();
    }

    return choice;
}

void getString(char* stringStart, size_t maxLength)
{
    //Get string from user
    fgets(stringStart, maxLength, stdin);

    //Get end of string position
    size_t len = strcspn(stringStart, "\n");

    //Flush STDIN and check if characters were left in it
    if (flushSTDIN() > 0)
    {
        //Reset end of string position if more than maxLength
        len = maxLength - 1;

        char choice;

        printf("Inputed text is too long (max: %ld characters) and will be truncated, do you want to (t) truncate or (a) input again: ", maxLength);

        scanf("%c", &choice);
        getchar();

        while (choice != 't' && choice != 'a')
        {
            printf("Invalid choice (t/a), try again: ");
            scanf("%c", &choice);
            getchar();
        }

        if (choice == 'a')
        {
            getString(stringStart, maxLength);
            return;
        }
    }

    //Put end of string character at the correct place
    stringStart[len] = '\0';

    //Flush input buffer to prevent excess data to remain
}

void AskStr(char* stringStart, int minLength, int maxLength)
{
    if (minLength >= maxLength)
        errx(EXIT_FAILURE, "AskStr: minLength >= maxLength!");

    //Get the string from the user
    getString(stringStart, maxLength);

    //The length of the inputed string
    int len = strlen(stringStart);

    //If the string is too short ask for the string again
    while (len < minLength)
    {
        printf("The inputed string is too short! The minimum length is %d characters\nPlease try again: ", minLength);

        getString(stringStart, maxLength);

        len = strlen(stringStart);
    }
}

int flushSTDIN()
{
    size_t readChar = 0;
    char c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        readChar++;
    }

    return readChar;
}
