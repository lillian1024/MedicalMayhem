#include <stdio.h>
#include "mainMenu.h"
#include "../../cmdUtil.h"
#include "../patientMenu/patientMenu.h"
#include "../doctorMenu/doctorMenu.h"
#include "../scheduleMenu/scheduleMenu.h"

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
    printf("4. Quit\n");
    printf("Select menu: ");
}

void ProcessMainMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 4);
    
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
            *appFlags = (*appFlags) | 1;
            return;
        default:
            printf("%sError in program!%s", TTYRED, TTYDEF);
            break;
    }
}
