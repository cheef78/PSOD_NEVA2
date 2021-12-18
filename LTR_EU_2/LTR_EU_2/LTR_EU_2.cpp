// LTR_EU_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>
#include <ctime>
#pragma hdrstop
#include "module_LTR_1.h"
#include "module_LTR_2.h"
#include "module_LTR_3.h"
#include "module_LTR_4.h"
#include "general_const.h"
#include "bd_mysql.h"
#include <windows.h>



void main() // Основная функция
{
	DWORD dwThreadId, dwThrdParam;
	HANDLE h1, h2, h3, h4;

	INIT_LTR_EU_2();
	//connect_bd();
	//sending_data_db("2021-07-19 12-29-19", "C:\\PSOD_NEVA2_DATA\\PSOD_NEVA2_12-29-19 19-07-2021_LTR212_2D881683.dat");
	//disconnect_bd();

	while (1) { // Создание бесконечный цикл
		connect_bd();
		h1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)POTOK_1,
			NULL, CREATE_SUSPENDED, (LPDWORD)&dwThreadId); // Обьявление потока инициализации и сбора данных 1 модуля

		h2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)POTOK_2,
			NULL, CREATE_SUSPENDED, (LPDWORD)&dwThreadId); // Обьявление потока инициализации и сбора данных 2 модуля

		h3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)POTOK_3,
			NULL, CREATE_SUSPENDED, (LPDWORD)&dwThreadId); // Обьявление потока инициализации и сбора данных 3 модуля

		h4 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)POTOK_4,
			NULL, CREATE_SUSPENDED, (LPDWORD)&dwThreadId); // Обьявление потока инициализации и сбора данных 4 модуля


		if (h1 == NULL) // Обработка ошибки создания потока
		{
			setlocale(LC_ALL, "Russian");
			printf("%s\n", "Невозможно создать поток 1!");
			Sleep(3000);
			return;
		}

		if (h2 == NULL) // Обработка ошибки создания потока
		{
			setlocale(LC_ALL, "Russian");
			printf("%s\n", "Невозможно создать поток 2!");
			Sleep(3000);
			return;
		}

		if (h3 == NULL) // Обработка ошибки создания потока
		{
			setlocale(LC_ALL, "Russian");
			printf("%s\n", "Невозможно создать поток 3!");
			Sleep(3000);
			return;
		}

		if (h4 == NULL) // Обработка ошибки создания потока
		{
			setlocale(LC_ALL, "Russian");
			printf("%s\n", "Невозможно создать поток 4!");
			Sleep(3000);
			return;
		}


		ResumeThread(h1); // Запуск потока инициализации и сбора данных 1 модуля
		setlocale(LC_ALL, "Russian");
		printf("%s\n", "Поток создан 1!");

		ResumeThread(h2); // Запуск потока инициализации и сбора данных 2 модуля
		setlocale(LC_ALL, "Russian");
		printf("%s\n", "Поток создан 2!");

		ResumeThread(h3); // Запуск потока инициализации и сбора данных 3 модуля
		setlocale(LC_ALL, "Russian");
		printf("%s\n", "Поток создан 3!");

		ResumeThread(h4); // Запуск потока инициализации и сбора данных 4 модуля
		setlocale(LC_ALL, "Russian");
		printf("%s\n", "Поток создан 4!");



		WaitForSingleObject(h1, INFINITE); // Отслеживание завершения потока инициализации и сбора данных 1 модуля
		WaitForSingleObject(h2, INFINITE); // Отслеживание завершения потока инициализации и сбора данных 2 модуля
		WaitForSingleObject(h3, INFINITE); // Отслеживание завершения потока инициализации и сбора данных 3 модуля
		WaitForSingleObject(h4, INFINITE); // Отслеживание завершения потока инициализации и сбора данных 4 модуля
		Sleep(1000);
		disconnect_bd();
		Sleep(1000);
	}


}




