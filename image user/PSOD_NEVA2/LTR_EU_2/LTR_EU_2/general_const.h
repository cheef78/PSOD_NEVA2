#pragma once
#ifndef general_const_H
#define general_const_H

#include <windows.h>
#include <string>

extern volatile int START_write;
extern volatile int START_write_1;
extern volatile int START_write_2;
extern volatile int START_write_3;
extern volatile int START_write_4;
extern volatile int START_potok_1;
extern volatile int START_potok_2;
extern volatile int START_potok_3;
extern volatile int START_potok_4;
extern volatile int TotalBlockCntr_mod1;
extern volatile int TotalBlockCntr_mod2;
extern volatile int TotalBlockCntr_mod3;
extern volatile int TotalBlockCntr_mod4;

extern std::string FileName2;
int INIT_LTR_EU_2();

#endif // !general_const_H
