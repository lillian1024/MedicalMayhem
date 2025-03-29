#include <stdio.h>
#include "scheduleMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../../../doctorUtil/doctorScheduleUtil.h"
#include "../../../doctorUtil/doctorUtil.h"

void ShowWeekSchedule();
void ShowCreateSchedule();
void ShowAssignDoctor();

void ShowScheduleMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayScheduleMenu();
    ProcessScheduleMenuAction(appFlags);
}

void DisplayScheduleMenu()
{
    printf("%s%sSchedule Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Display Week Schedule\n");
    printf("2. Create Schedule\n");
    printf("3. Assign Doctor\n");
    printf("4. Back\n");
    printf("Select menu: ");
}

void ProcessScheduleMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 4);
    
    switch (menu)
    {
        case 1:
            ShowWeekSchedule();
            ShowScheduleMenu(1, appFlags);
            break;
        case 2:
            ShowCreateSchedule();
            ShowScheduleMenu(1, appFlags);
            break;
        case 3:
            ShowAssignDoctor();
            ShowScheduleMenu(1, appFlags);
            break;
        case 4:
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s\n", TTYRED, TTYDEF);
            break;
    }
}

void ShowWeekSchedule()
{
    if (weekSchedule == NULL)
    {
        printf("%sWeek schedule has not been created yet!%s\n", TTYRED, TTYDEF);
        getchar();
    }
    else
    {
        displayWeekSchedule(weekSchedule);
        getchar();
    }
}

void ShowCreateSchedule()
{
    if (weekSchedule != NULL)
    {
        clrscr();
        printf("%sThe schedule already exist, you are about to override it!%s\n", TTYRED, TTYDEF);
        printf("0: Cancel, 1: Continue ");
        int choice = AskIntChoice(0, 1);

        if (choice == 0)
            return;
    }

    weekSchedule = createSchedule();
    printf("%sSchedule successfully created!%s", TTYGRN, TTYDEF);
    getchar();
}

void ShowAssignDoctor()
{
    if (weekSchedule == NULL)
    {
        printf("%sWeek schedule has not been created yet!%s\n", TTYRED, TTYDEF);
        getchar();
    }
    else
    {
        clrscr();
        assignDoctor(weekSchedule);
    }
}
