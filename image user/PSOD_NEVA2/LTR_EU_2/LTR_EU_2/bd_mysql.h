#pragma once
#ifndef bd_mysql_H
#define bd_mysql_H

#include <windows.h>
#include <tchar.h>


int init_bd();
int sending_data_db(std::string DataTime, std::string FileName);
int disconnect_bd();
int connect_bd();

#endif // !bd_mysql_H