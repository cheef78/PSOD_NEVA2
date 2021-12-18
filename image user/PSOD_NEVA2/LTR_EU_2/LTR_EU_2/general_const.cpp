#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>
#include <string>
#include <clocale>
#include <ctime>
#pragma hdrstop
#include "ltr\\include\\ltr212api.h"
#include "ltr\\include\\ltrapi.h"
#include "lib\\INIReader.h"
/* остальные заголовочные файлы */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>

static  CHAR ErrorString[255] = {}; // Строка для вывода описания ошибки
static  CHAR MsgString[255] = {}; // Строка для вывода сообщений на консоль
static  TLTR212 hltr212; // Экземпляр структуры описания модуля
static  TLTR ltr;
volatile int START_write = 0;
volatile int START_write_1 = 0;
volatile int START_write_2 = 0;
volatile int START_write_3 = 0;
volatile int START_write_4 = 0;
extern volatile int START_potok_1 = 0;
extern volatile int START_potok_2 = 0;
extern volatile int START_potok_3 = 0;
extern volatile int START_potok_4 = 0;
volatile int TotalBlockCntr_mod1 = 0;
volatile int TotalBlockCntr_mod2 = 0;
volatile int TotalBlockCntr_mod3 = 0;
volatile int TotalBlockCntr_mod4 = 0;
std::string FileName2 = "";

int INIT_LTR_EU_2() // Функция записи данных в файл
{

	INT err; // Переменная для хранения кода ошибки
	int ltr_result;
	sprintf(MsgString, "%s", "Инициализация структуры описания модуля LTR_EU_2\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	Sleep(200);
	err = LTR212_Init(&hltr212);
	if (err)
	{
		strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
		CharToOem((wchar_t*)ErrorString, ErrorString);
		setlocale(LC_ALL, "Russian");
		printf("%s", ErrorString);
		LTR212_Close(&hltr212);
		Sleep(3000);
		return 0;
	}
	//LTR_Init(&ltr);
	//ltr.cc = CC_MODULE2;
	//LTR_Open(&ltr);
	////if ((ltr_result = LTR_StartSecondMark(&ltr, LTR_MARK_INTERNAL)) != LTR_OK)
	////{
	////	strcpy(ErrorString, (char*)LTR_GetErrorString(ltr_result));
	////	CharToOem((wchar_t*)ErrorString, ErrorString);
	////	setlocale(LC_ALL, "Russian");
	////	printf("%s", ErrorString);
	////	LTR_Close(&ltr);
	////	Sleep(3000);
	////	return 0;
	////}
	return 1;
}