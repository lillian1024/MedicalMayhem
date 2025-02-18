#include <stdio.h>
#include "doctorMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../../../doctorUtil/doctorUtil.h"

void ShowAddDoctor();

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
    printf("1. Add New Doctor\n");
    printf("2. Back\n");
    printf("Select menu: ");
}

void ProcessDoctorMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 2);
    
    switch (menu)
    {
        case 1:
            ShowAddDoctor();
            ShowDoctorMenu(1, appFlags);
            break;
        case 2:
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s\n", TTYRED, TTYDEF);
            break;
    }
}

void ShowAddDoctor()
{
    char name[MAX_NAME_LEN];

    clrscr();

    printf("Please input the name of the doctor: ");
    AskStr(name, 3, MAX_NAME_LEN);

    printf("Please input the number of morning shift: ");
    int morningShift = AskIntChoice(0, 7);

    printf("Please input the number of afternoon shift: ");
    int afternoonShift = AskIntChoice(0, 7);

    printf("Please input the number of evening shift: ");
    int eveningShift = AskIntChoice(0, 7);

    addDoctor(&doctorLL, name, morningShift, afternoonShift, eveningShift);
}