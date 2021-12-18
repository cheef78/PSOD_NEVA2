#pragma once
#ifndef module_LTR_1_H
#define module_LTR_1_H

#include <windows.h>
extern volatile int Flag_not_DPK_module_LTR_1;

DWORD WINAPI AcquireThread(LPVOID param);
DWORD WINAPI POTOK_1(LPVOID param);

#endif // !module_LTR_1_H

