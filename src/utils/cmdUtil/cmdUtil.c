#include <stdio.h>
#include <string.h>
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
