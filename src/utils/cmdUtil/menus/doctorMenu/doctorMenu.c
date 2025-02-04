#include <stdio.h>
#include "doctorMenu.h"
#include "../../cmdUtil.h"
#include "../patientMenu/patientMenu.h"
#include "../mainMenu/mainMenu.h"
#include "../scheduleMenu/scheduleMenu.h"

void ShowDoctorMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayDoctorMenu();
    ProcessDoctorMenuAction(appFlags);
}

void DisplayDoctorMenu()
{
    printf("%s%sDoctor Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Schedule Management\n");
    printf("4. Back\n");
    printf("Select menu: ");
}

void ProcessDoctorMenuAction(int* appFlags)
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