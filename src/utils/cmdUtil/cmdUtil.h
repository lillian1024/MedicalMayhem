#ifndef CMD_UTIL_H
#define CMD_UTIL_H

#define TTYRED      "\x1B[31m"
#define TTYGRN      "\x1B[32m"
#define TTYYEL      "\x1B[33m"
#define TTYBLU      "\x1B[34m"
#define TTYMAG      "\x1B[35m"
#define TTYCYN      "\x1B[36m"
#define TTYWHT      "\x1B[37m"
#define TTYDEF      "\x1B[0m"

#define TTYBOLD     "\e[1m"
#define TTYFAINT    "\e[2m"
#define TTYNORMINT  "\e[22m"
#define TTYITA      "\e[3m"
#define TTYUNDER    "\e[4m"
#define TTYCONC     "\e[8m"
#define TTYCROS     "\e[9m"
#define TTYDUBUNDER "\e[21m"
#define TTYNITA     "\e[23m"
#define TTYNUND     "\e[24m"
#define TTYNCRO     "\e[29m"
#define TTYOVER     "\e[53m"
#define TTYNOVR     "\e[55m"

#define APP_FLAG_QUIT 0b01
#define APP_FLAG_ERROR 0b10

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void CmdLaunch(int* appFlags);

void DisplayTitle();
void DisplayLine(char* s, int nb);
int AskIntChoice(int minChoice, int maxChoice);
void AskStr(char* stringStart, int minLength, int maxLength);
int flushSTDIN();

#endif