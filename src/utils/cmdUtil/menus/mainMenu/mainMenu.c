#include <stdio.h>
#include "mainMenu.h"
#include "../../cmdUtil.h"
#include "../patientMenu/patientMenu.h"
#include "../doctorMenu/doctorMenu.h"
#include "../scheduleMenu/scheduleMenu.h"
#include "../managmentMenu/managmentMenu.h"

void ShowMainMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayMainMenu();
    ProcessMainMenuAction(appFlags);
}

void DisplayMainMenu()
{
    printf("%s%sMain Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Schedule Management\n");
    printf("4. Management Menu\n");
    printf("5. Quit\n");
    printf("Select menu: ");
}

void ProcessMainMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 5);
    
    switch (menu)
    {
        case 1:
            ShowPatientMenu(1, appFlags);
            break;
        case 2:
            ShowDoctorMenu(1, appFlags);
            break;
        case 3:
            ShowScheduleMenu(1, appFlags);
            break;
        case 4:
            ShowManagmentMenu(1, appFlags);
            break;
        case 5:
            *appFlags = (*appFlags) | APP_FLAG_QUIT;
            *appFlags = (*appFlags) & ~ APP_FLAG_ERROR;
            return;
        default:
            *appFlags = (*appFlags) | APP_FLAG_QUIT;
            *appFlags = (*appFlags) | APP_FLAG_ERROR;
            printf("%sError in program!%s\n", TTYRED, TTYDEF);
            return;
    }
}
