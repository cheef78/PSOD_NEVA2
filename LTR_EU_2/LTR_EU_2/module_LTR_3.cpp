#include "module_LTR_3.h"
#include "general_const.h"
#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>
#include <string>
#include <clocale>
#include <ctime>
#pragma hdrstop
#include "ltr\\include\\ltr212api.h"
#include "lib\\INIReader.h"
/* ��������� ������������ ����� */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "bd_mysql.h"

static  INIReader reader("C:\\PSOD_NEVA2\\LTR_EU_2\\Debug\\settings.ini");

static  std::string  NAME_SYSTEM = reader.Get("SYSTEM", "NAME_SYSTEM", "UNKNOWN"); // ��� �������
static  std::string  CREAT_SN = reader.Get("MODULE_3", "CREAT_SN", "UNKNOWN"); // �������� ����� ������ 
static  const int SLOT_NUMBER = reader.GetInteger("MODULE_3", "SLOT_NUMBER", -1); // ����� ����� � ������
static  const int ACQ_BLOCKS_QNT = reader.GetInteger("MODULE_3", "ACQ_BLOCKS_QNT", -1); // ����������� ������ � ������ ����� �����
static  const int TOTAL_BLOCKS_QNT = reader.GetInteger("MODULE_3", "TOTAL_BLOCKS_QNT", -1); // �� ������ 
static  const int POINTS_PER_CHANNEL = reader.GetInteger("MODULE_3", "POINTS_PER_CHANNEL", -1); // 
static  const int CHANNELS_QNT = reader.GetInteger("MODULE_3", "CHANNELS_QNT", -1);; // ���������� ������� 
static  double SLOT_RATE = reader.GetInteger("MODULE_3", "SLOT_RATE", -1); // ������� ���������� ������ ��
static  double limit_DPK = reader.GetReal("MODULE_3", "Limit_DPK", -1); // ������ ������������ ��� mV
static  volatile int limit_time = reader.GetInteger("MODULE_3", "Limit_time", -1); //600���
static  volatile int Time_stop = reader.GetInteger("MODULE_3", "Time_stop", -1); // ����� �����
static  volatile int Chanel_DPK = reader.GetInteger("MODULE_3", "Chanel_DPK", -1); // ����� ���
static  volatile int Filter_ON_OFF = reader.GetInteger("MODULE_3", "Filter_ON_OFF", -1); // ��� ���� ������
static  std::string  file_way = reader.Get("MODULE_3", "File_way", "UNKNOWN");  // ���� � ������ �������� ������


static  volatile int CHANNELS_QNT_UNPACK = POINTS_PER_CHANNEL * CHANNELS_QNT; // ���������� ������� � ����� 
static  double limit_time_buff = 0; // ����� ����������� ���������� �����
static  volatile int flag_delete_file = 0; // ���� �������� �����
static  TLTR212 hltr212; // ��������� ��������� �������� ������
static  HANDLE AcqThreadHnd1; // ����� ����� ������
static  CHAR ErrorString[255] = {}; // ������ ��� ������ �������� ������
static  CHAR MsgString[255] = {}; // ������ ��� ������ ��������� �� �������
static  volatile int flag_before_DPK = 0; // ���� ��� ����������� ��� ���� ���� ������ �� ��� � ����� ���
static  volatile int flag_ok_dpk_block = 0; // ���� ������� ��� � ������ 
static  double** voltage; // ����� ����� 1 �����
static  double** BUFF; // ����� ��� ������ �� ��� � ����� ���
static  double** BUFF_ok_DPK; // ����� ��� ������ ������ ����� ������������ ���
static  double BUFF1[1150][100];
static  double BUFF2[600][100];
static  double BUFF_time_read[1][4];
static  double BUFF_time_read_reserve[1][4];
static  char time_read[255] = {};
static  char time_read_console[255] = {};
static  char time_read_buff[255] = {};
static  SYSTEMTIME st;
static  volatile int RunFlag = 0; // ����, �����������, ��� ���� ���� ������
static  volatile int Flag_ok_DPK = 0; // ���� ��� ����������� ��� ���� ���� ������ � ���
static  volatile int* BlockReady; // ���� ��� ���� ������
static FILE* DataFile;



static DWORD WINAPI AcqThread(LPVOID param);

static int roundUp(int numToRound, int multiple) // ������� ���������� ����� ����� �� 100.....500.....1000
{
	if (multiple == 0)
	{
		return numToRound;
	}

	int roundDown = ((int)(numToRound) / multiple) * multiple;
	int roundUp = roundDown + multiple;
	int roundCalc = roundUp;
	return (roundCalc);
}

static  volatile int BLOCKS_UNPACK_1 = roundUp((Time_stop / ((CHANNELS_QNT_UNPACK / CHANNELS_QNT) / SLOT_RATE)) * 2, 100); // ����������� ������ ��� ������� �� ��� � ����� ���
static  volatile int BLOCKS_UNPACK_2 = BLOCKS_UNPACK_1 / 2; // ����������� ������ ��� ������ ���������� ����� � ���


static int* mass_x(int m) // ������� �������� ������������� ����������� ������� 
{
	int* array = new int[m];

	for (int i = 0; i < m; i++) {
		array[i] = 0;
	}
	return array;
}


static double** mass_x_x(int m, int n) // ������� �������� ������������� ����������� ������� 
{
	double** array = new double* [m];
	//array = new double* [m]; 
	for (int i = 0; i < m; i++) {
		array[i] = new double[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			array[i][j] = 0;
		}
	}
	return array;
}


static void  mass_x_x_zero_BUFF() // ������� ��������� ������������� ����������� ������� �� ��� � ����� ���
{

	for (int i = 0; i < CHANNELS_QNT_UNPACK; i++) {
		BUFF[ACQ_BLOCKS_QNT][i] = 0;
	}
}

static void  mass_x_x_zero_BUFF_ok_DPK() // ������� ��������� ������������� ����������� ������� � ���
{

	for (int i = 0; i < BLOCKS_UNPACK_2; i++) {
		for (int j = 0; j < CHANNELS_QNT_UNPACK; j++) {
			BUFF_ok_DPK[i][j] = 0;
		}
	}
}


static DWORD WINAPI AcquireThread(LPVOID param) // ������� ����� ������ � ������ 
{
	int i;
	int err = 0;
	INT DataCntr = 0;
	int p = 0;
	int k = 0;
	DWORD* data = new DWORD[2 * POINTS_PER_CHANNEL * CHANNELS_QNT];
	DWORD to; // �������
	INT AcqBlockCntr = 0;
	int BlockCntr = 0;
	DWORD size; // ������ ������ ������
	DWORD ExitCode;
	/* �������, ����������� � �������� ������ ����� ������. */
	for (i = 0; i < ACQ_BLOCKS_QNT; i++)
		BlockReady[i] = 0;
	err = LTR212_Start(&hltr212);
	if (err)
	{
		strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
		CharToOem((wchar_t*)ErrorString, ErrorString);
		setlocale(LC_ALL, "Russian");
		printf("%s", ErrorString);
		LTR212_Stop(&hltr212);
		RunFlag = 0;
	}
	char* end;
	size = 2 * POINTS_PER_CHANNEL * CHANNELS_QNT; // ������ ���������� ������ ������
	to = LTR212_CalcTimeOut(&hltr212, POINTS_PER_CHANNEL);
	while (RunFlag) // ���� ������� ���� ������...
	{
		size = 2 * POINTS_PER_CHANNEL * CHANNELS_QNT;
		START_potok_3 = 1;
		while ((START_potok_3 == 0) and (START_potok_4 == 0)) {}
		time_t t_unix = time(NULL);
		//struct tm tm = *localtime(&t_unix);
		unsigned t_ms = (t_unix % 1000) * 100 / 512;

		GetLocalTime(&st);
		sprintf(time_read_console, "%d-%d-%d %d:%d:%d.%d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		sprintf(time_read, "%04d%02d%02d%02d%02d%02d,%03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		printf("%s\n", time_read_console);
		BUFF_time_read[0][0] = strtod(time_read, NULL);
		BUFF_time_read[0][1] = strtod(time_read, NULL);
		BUFF_time_read[0][2] = strtod(time_read, NULL);
		BUFF_time_read[0][3] = strtod(time_read, NULL);
		DataCntr = LTR212_Recv(&hltr212, data, NULL, size, to);
		if (DataCntr != size)
		{
			RunFlag = 0;
			if (DataCntr >= 0)
			{
				sprintf(MsgString, "%s", "������! �������� ������ �������, ��� ���� ��������!\n");
				CharToOem((wchar_t*)MsgString, MsgString);
				setlocale(LC_ALL, "Russian");
				printf("%s\n", MsgString);
			}
			else
			{
				err = DataCntr;
				strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
				CharToOem((wchar_t*)ErrorString, ErrorString);
				setlocale(LC_ALL, "Russian");
				printf("%s", ErrorString);
			}
			break;
		} // � if(DataCntr!=size)
		START_potok_3 = 0;
		err = LTR212_ProcessData(&hltr212, data, voltage[BlockCntr], &size, 1);
		if (err)
		{
			strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
			CharToOem((wchar_t*)ErrorString, ErrorString);
			setlocale(LC_ALL, "Russian");
			printf("%s", ErrorString);
			RunFlag = 0;
			break;
		}

		AcqBlockCntr++;
		sprintf(MsgString, "�������� %d-� ������ ������", AcqBlockCntr);
		CharToOem((wchar_t*)MsgString, MsgString);
		setlocale(LC_ALL, "Russian");
		printf("%s\n", MsgString);

		/* ��� ������������� � ������� � ����, ������������ � �������� ������,
		���������� ����������� ������ */
		BlockReady[BlockCntr] = 1;
		BlockCntr++;
		if (BlockCntr >= ACQ_BLOCKS_QNT)
			BlockCntr = 0;
		//printf("% u\n", RunFlag);
	} // � while(RunFlag)
	RunFlag = 0;
	err = LTR212_Stop(&hltr212); if (err)
	{
		strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
		CharToOem((wchar_t*)ErrorString, ErrorString);
		setlocale(LC_ALL, "Russian");
		printf("%s", ErrorString);
	}
	ExitThread(0);
	return 0;
}


DWORD WINAPI POTOK_3(LPVOID param) // ������� ������ ������ � ����
{
	static  TLTR ltr;
	int ltr_result;
	BUFF = mass_x_x(ACQ_BLOCKS_QNT, CHANNELS_QNT_UNPACK); // �������� ����������� ������������� ������� ��� ������ ������ �� ��� � ����� ���
	BUFF_ok_DPK = mass_x_x(BLOCKS_UNPACK_2, CHANNELS_QNT_UNPACK); // �������� ����������� ������������� ������� ��� ������ ������ � ���
	voltage = mass_x_x(ACQ_BLOCKS_QNT, CHANNELS_QNT * POINTS_PER_CHANNEL);
	BlockReady = mass_x(ACQ_BLOCKS_QNT);
	DWORD AcqThreadId1;
	DWORD ThreadSatus;
	//const char FileName[] = "ltr212_data_1.bin";
	INT TotalBlockCntr = 0; // ������� ������, ���������� � ����
	INT err; // ���������� ��� �������� ���� ������
	INT i; // ������������ ��� ��������� �������� � ������
	DWORD data[2 * 5000]; /* ������, � ������� ��������� ������, ���������� ��
	 ������*/

	int BlockCntr = 0;
	int BlockNumber;
	int dop_chanel_dpk = 4;
	START_potok_3 = 0;


	err = LTR212_Open(&hltr212, SADDR_DEFAULT, SPORT_DEFAULT, CREAT_SN.c_str(), SLOT_NUMBER, "");
	if (err)
	{
		if (err == LTR_WARNING_MODULE_IN_USE)
		{
			strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
			CharToOem((wchar_t*)ErrorString, ErrorString);
			setlocale(LC_ALL, "Russian");
			printf("%s", ErrorString);
		}
		else
		{
			strcpy(ErrorString, (char*)LTR212_GetErrorString(err));
			CharToOem((wchar_t*)ErrorString, ErrorString);
			setlocale(LC_ALL, "Russian");
			printf("%s", ErrorString);
			Sleep(3000);
			return 0;
		}
	}
	/* ���������� ����� ��� ����������. ����� ������� ������ ��� ������������ */
	sprintf(MsgString, "��� ������: %s", hltr212.ModuleInfo.Name);
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	sprintf(MsgString, "������ �����: %s", hltr212.ModuleInfo.BiosVersion);
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	sprintf(MsgString, "���� �������� �����: %s", hltr212.ModuleInfo.BiosDate);
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	sprintf(MsgString, "�������� ����� ������: %s", hltr212.ModuleInfo.Serial);
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	// ��������� ���������� ����� ��������� �������� ������ ���������� ����������
	hltr212.size = sizeof(TLTR212); // ������ ���������
	hltr212.AcqMode = reader.GetInteger("MODULE_3", "AcqMode", -1); // 4-��������� ����� ������� �������� - "1" 4-��������� ����� ������� �������� - "0"
	hltr212.UseClb = reader.GetInteger("MODULE_3", "UseClb", -1); //  �� ���������� ���������������� ������������� �����. "1" ��� AcqMode = 0 ,"0" ��� AcqMode = 1 
	hltr212.UseFabricClb = reader.GetInteger("MODULE_3", "UseFabricClb", -1); // ���������� ��������� ������. �����. "1" ��� AcqMode = 1 ,"0" ��� AcqMode = 0
	hltr212.LChQnt = reader.GetInteger("MODULE_3", "LChQnt", -1); // ���������� ���������� ������� - 4


	for (i = 0; i < hltr212.LChQnt; i++)
		hltr212.LChTbl[i] = LTR212_CreateLChannel(i + 1, reader.GetInteger("MODULE_3", "LChTbl", -1));

	if (Filter_ON_OFF == 0) {

		hltr212.filter.IIR = 0;
		hltr212.filter.FIR = 0;
	}
	else
	{
		hltr212.filter.IIR = 1;
		hltr212.filter.FIR = 1;
		hltr212.filter.Decimation = reader.GetInteger("MODULE_3", "Decimation", -1);
		hltr212.filter.TAP = reader.GetInteger("MODULE_3", "TAP", -1);
		strcpy(hltr212.filter.IIR_Name, reader.Get("MODULE_3", "Filter_IIR", "UNKNOWN").c_str());
		strcpy(hltr212.filter.FIR_Name, reader.Get("MODULE_3", "Filter_FIR", "UNKNOWN").c_str());
	}

	hltr212.REF = reader.GetInteger("MODULE_3", "REF", -1); // ������� ���������� 5 �.
	hltr212.AC = reader.GetInteger("MODULE_3", "AC", -1);; // ���������� ������� ����������

	// �������� ��������� ��� ����������� ��������� ������
	err = LTR212_SetADC(&hltr212);
	if (err)
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

	RunFlag = 1;
	// ������� ����� ����� ������
	AcqThreadHnd1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AcquireThread,
		NULL, CREATE_SUSPENDED, (LPDWORD)&AcqThreadId1);
	if (AcqThreadHnd1 == NULL)
	{
		strcpy(MsgString, "���������� ������� ����� ����� ������!");
		CharToOem((wchar_t*)MsgString, MsgString);
		setlocale(LC_ALL, "Russian");
		printf("%s\n", MsgString);
		LTR212_Close(&hltr212);
		Sleep(3000);
		return 0;
	}
	// ��������� �����
	ResumeThread(AcqThreadHnd1);
	strcpy(MsgString, "����� ����� ������ ������� ------ MODULE_3!\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	int flag = 0;
	TotalBlockCntr_mod1 = 0;
	float time1 = 0;
	float time_DPK = 0;
	float time_DPK_minus = 0;
	printf("FLAGS START POTOK MODULE 3\n");
	printf("START_write: %u\n", START_write);
	printf("START_write_1: %u\n", START_write_1);
	printf("START_write_2: %u\n", START_write_2);
	printf("START_write_3: %u\n", START_write_3);
	printf("START_write_4: %u\n", START_write_4);

	while (RunFlag)
	{

		if (BlockReady[BlockCntr]) // ���� ��������� ���� ������
		{
			if (START_write_3 == 0)
			{
				for (i = Chanel_DPK; i < CHANNELS_QNT_UNPACK; i = i + dop_chanel_dpk) {
					//BUFF1[BLOCKS_UNPACK_2][i] = voltage[BlockCntr][i];
					if ((voltage[BlockCntr][i] > limit_DPK))
					{
						flag_ok_dpk_block = 1;
					}
				}
				if (flag_ok_dpk_block == 0)
				{
					for (i = 0; i < CHANNELS_QNT_UNPACK; i++) {
						BUFF[BlockCntr][i] = voltage[BlockCntr][i];
					}
					BUFF_time_read_reserve[0][0] = BUFF_time_read[0][3];
					BUFF_time_read_reserve[0][1] = BUFF_time_read[0][3];
					BUFF_time_read_reserve[0][2] = BUFF_time_read[0][3];
					BUFF_time_read_reserve[0][3] = BUFF_time_read[0][3];
					//strcpy(time_read_buff,time_read);
					sprintf(MsgString, "%s:%s\n", "��� � ����� ���", hltr212.ModuleInfo.Serial);
					CharToOem((wchar_t*)MsgString, MsgString);
					setlocale(LC_ALL, "Russian");
					printf("%s\n", MsgString);
					flag_ok_dpk_block = 0;
				}
				if (flag_ok_dpk_block == 1) {
					time_t rawtime = time(NULL);
					struct tm* timeinfo;
					char buffer_timeinfo[80];
					timeinfo = localtime(&rawtime);
					strftime(buffer_timeinfo, 80, "%Y-%m-%d %H-%M-%S", timeinfo);

					std::string FileName5 = hltr212.ModuleInfo.Name;
					std::string FileName6 = hltr212.ModuleInfo.Serial;
					std::string FileName1 = "_" + FileName5 + "_" + FileName6 + ".dat";
					if (FileName2 == "") {
						FileName2 = buffer_timeinfo;
					}
					//std::replace(FileName2.begin(), FileName2.end(), ' ', '_');
					//std::replace(FileName2.begin(), FileName2.end(), ':', '-');
					std::string FileName3 = file_way + NAME_SYSTEM + '_' + FileName2 + FileName1;
					std::string FileNamedb = file_way + NAME_SYSTEM + '_' + FileName2 + "_" + FileName5 + "_";
					//if ((START_write_1 == 1) and (START_write_2 == 0) and (START_write_3 == 0) and (START_write_4 == 0)) {
					//sending_data_db(FileName2, FileNamedb);
					//}
					const char* FileName = FileName3.c_str();
					printf("FILE NAME:  %s \n", FileName);
					DataFile = fopen(FileName, "wb"); if (DataFile == NULL)
					{
						strcpy(MsgString, "���������� ������� ����!");
						CharToOem((wchar_t*)MsgString, MsgString);
						setlocale(LC_ALL, "Russian");
						printf("%s\n", MsgString);
						LTR212_Close(&hltr212);
						Sleep(3000);
						return 0;
					}
					START_write_3 = 1;
					flag_ok_dpk_block = 0;

					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, time_read_buff);
					//fwrite(time_read, sizeof time_read,
						//sizeof time_read, DataFile);
					fwrite(BUFF_time_read_reserve[0], sizeof BUFF[0][0],
						4, DataFile);
					fwrite(BUFF[BlockCntr], sizeof BUFF[0][0],
						CHANNELS_QNT* POINTS_PER_CHANNEL, DataFile);

					fprintf(DataFile, "22222222");
					fprintf(DataFile, "22222222");
					fprintf(DataFile, "22222222");
					fprintf(DataFile, "22222222");
					//fprintf(DataFile, time_read);
					fwrite(voltage[BlockCntr], sizeof voltage[0][0],
						CHANNELS_QNT* POINTS_PER_CHANNEL, DataFile);

					TotalBlockCntr++; // ������� ������
					sprintf(MsgString, "%d-� %s\n", TotalBlockCntr, "������ �������� � ����");
					CharToOem((wchar_t*)MsgString, MsgString);
					setlocale(LC_ALL, "Russian");
					printf("%s\n", MsgString);
					BlockReady[BlockCntr] = 0;
					if (BlockCntr >= ACQ_BLOCKS_QNT)
						BlockCntr = 0;
					if (TotalBlockCntr >= TOTAL_BLOCKS_QNT)
					{
						strcpy(MsgString, ">> ���� ������ ������� ��������.\n");
						CharToOem((wchar_t*)MsgString, MsgString);
						setlocale(LC_ALL, "Russian");
						printf("%s\n", MsgString);
						RunFlag = 1;

					}

				}
				BlockReady[BlockCntr] = 0;
				if (BlockCntr >= ACQ_BLOCKS_QNT)
					BlockCntr = 0;
			}
			else
			{
				for (i = Chanel_DPK; i < CHANNELS_QNT_UNPACK; i = i + dop_chanel_dpk) {
					//BUFF1[BLOCKS_UNPACK_2][i] = voltage[BlockCntr][i];
					if ((voltage[BlockCntr][i] > limit_DPK))
					{
						flag_ok_dpk_block = 1;
					}

				}
				if (flag_ok_dpk_block == 0)
				{
					sprintf(MsgString, "%s\n", "��� � ����� �������");
					CharToOem((wchar_t*)MsgString, MsgString);
					setlocale(LC_ALL, "Russian");
					printf("%s\n", MsgString);
					flag_ok_dpk_block = 0;
				}
				if (flag_ok_dpk_block == 1) {
					START_write_3 = 1;
					flag_ok_dpk_block = 0;

					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, time_read);
					fwrite(BUFF_time_read[0], sizeof BUFF[0][0],
						4, DataFile);
					fwrite(voltage[BlockCntr], sizeof voltage[0][0],
						CHANNELS_QNT* POINTS_PER_CHANNEL, DataFile);

					TotalBlockCntr++; // ������� ������
					sprintf(MsgString, "%d-� %s\n", TotalBlockCntr, "������ �������� � ����");
					CharToOem((wchar_t*)MsgString, MsgString);
					setlocale(LC_ALL, "Russian");
					printf("%s\n", MsgString);
					BlockReady[BlockCntr] = 0;
					if (BlockCntr >= ACQ_BLOCKS_QNT)
						BlockCntr = 0;
					if (TotalBlockCntr >= TOTAL_BLOCKS_QNT)
					{
						strcpy(MsgString, ">> ���� ������ ������� ��������.\n");
						CharToOem((wchar_t*)MsgString, MsgString);
						setlocale(LC_ALL, "Russian");
						printf("%s\n", MsgString);
						RunFlag = 1;

					}
					limit_time_buff = limit_time_buff + ((CHANNELS_QNT_UNPACK / CHANNELS_QNT) / SLOT_RATE);
					if (limit_time_buff > limit_time)
					{
						RunFlag = 0;
					}

				}
				else
				{
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, "22222222");
					//fprintf(DataFile, time_read);
					fwrite(BUFF_time_read[0], sizeof BUFF[0][0],
						4, DataFile);
					fwrite(voltage[BlockCntr], sizeof voltage[0][0],
						CHANNELS_QNT* POINTS_PER_CHANNEL, DataFile);

					strcpy(MsgString, ">> ����� ������� ������\n");
					CharToOem((wchar_t*)MsgString, MsgString);
					setlocale(LC_ALL, "Russian");
					printf("%s\n", MsgString);
					RunFlag = 0;
				}
				BlockReady[BlockCntr] = 0;
				if (BlockCntr >= ACQ_BLOCKS_QNT)
					BlockCntr = 0;

			}

		} // � if(BlockReady[BlockCntr]...)
	} // � while(RunFlag)
	strcpy(MsgString, "�����\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	limit_time_buff = 0;
	//����������� ���������� ������
	WaitForSingleObject(AcqThreadHnd1, INFINITE);
	GetExitCodeThread(AcqThreadHnd1, &ThreadSatus);
	CloseHandle(AcqThreadHnd1);
	strcpy(MsgString, "����� ����� ������ ������ ------ MODULE_3\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	fclose(DataFile);
	if (flag_delete_file == 1)
	{
		//remove(FileName);
	}

	flag_delete_file = 0;
	strcpy(MsgString, "���� ��� ������ ������ ������ ------ MODULE_3\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	RunFlag = 1;
	setlocale(LC_ALL, "Russian");
	printf("   value                channel       time\n");
	strcpy(MsgString, ">> ��� ������ ������� ����� �������\n");
	CharToOem((wchar_t*)MsgString, MsgString);
	setlocale(LC_ALL, "Russian");
	printf("%s\n", MsgString);
	for (i = 0; i < 24; i++)
	{
		float time = i / SLOT_RATE;
		printf("%u  ", i);
		if (voltage[0][i] < 0)
		{
			printf("%10.10f       ", voltage[0][i]);

		}
		else
		{
			printf("%10.10f        ", voltage[0][i]);
		}
		printf("%u        ", CHANNELS_QNT_UNPACK);
		printf("%f  \n", time);
	}
	Flag_ok_DPK = 0;
	flag_before_DPK = 0;
	START_write = 0;
	START_write_3 = 0;
	FileName2 = "";
	mass_x_x_zero_BUFF_ok_DPK();
	//mass_x_x_zero_BUFF();
	//while (!getch()) //��������� ������� ������ ����������
		//continue;
	return 1;


}