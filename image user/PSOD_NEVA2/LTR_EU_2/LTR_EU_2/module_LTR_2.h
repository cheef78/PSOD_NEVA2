#pragma once
#ifndef module_LTR_2_H
#define module_LTR_2_H

#include <windows.h>

extern volatile int Flag_not_DPK_module_LTR_2;

DWORD WINAPI AcquireThread(LPVOID param);
DWORD WINAPI POTOK_2(LPVOID param);

#endif // !module_LTR_2_H
