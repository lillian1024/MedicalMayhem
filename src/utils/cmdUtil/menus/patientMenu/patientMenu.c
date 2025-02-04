#include <stdio.h>
#include "patientMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../doctorMenu/doctorMenu.h"
#include "../scheduleMenu/scheduleMenu.h"

void ShowPatientMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayPatientMenu();
    ProcessPatientMenuAction(appFlags);
}

void DisplayPatientMenu()
{
    printf("%s%sPatient Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Schedule Management\n");
    printf("4. Back\n");
    printf("Select menu: ");
}

void ProcessPatientMenuAction(int* appFlags)
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
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s", TTYRED, TTYDEF);
            break;
    }
}