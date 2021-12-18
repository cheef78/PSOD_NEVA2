#pragma warning(disable : 4996)
#include <winsock.h>
#include <stdio.h>
#include <mysql.h> 
#include <string>
#include "lib\\INIReader.h"

MYSQL conn;
static  INIReader reader("C:\\PSOD_NEVA2\\LTR_EU_2\\Debug\\settings.ini");
static  std::string  HOST_DB = reader.Get("DB_SETTINGS", "HOST_DB", "UNKNOWN");   // Хост базы данных
static  std::string  USER_DB = reader.Get("DB_SETTINGS", "USER_DB", "UNKNOWN");   // Имя пользователя базы данных
static  std::string  PASSWD_DB = reader.Get("DB_SETTINGS", "PASSWD_DB", "UNKNOWN"); // Пороль пользователя базы данных
static  std::string  NAME_DB = reader.Get("DB_SETTINGS", "NAME_DB", "UNKNOWN");  // Имя базы данных
using namespace std;


int sending_data_db(std::string DataTime, std::string FileName)
{
    MYSQL_RES* res_set;
    MYSQL_ROW row;
    std::string send_db;
   
    send_db = "INSERT INTO trains(DateTime,FileName) VALUES('" + DataTime + "','" + FileName + "')";
    mysql_query(&conn, send_db.c_str());
    fprintf(stderr, "Запись в базу данных.\n");
        if (mysql_error(&conn) == "") {
            fprintf(stderr, "Успешная запись.\n");
        }
        else {
            fprintf(stderr, "Ошибка Записи: %s\n",
                mysql_error(&conn));
        }

    return 0;
}
int connect_bd() {
    MYSQL_RES* res_set;
    MYSQL_ROW row;

    mysql_init(&conn);
    if (!mysql_real_connect(&conn, HOST_DB.c_str(), USER_DB.c_str(), PASSWD_DB.c_str(), NAME_DB.c_str(), 0, NULL, 0))
    {
        fprintf(stderr, "Ошибка подключения к базе данных: %s\n",
            mysql_error(&conn));
    }
    else {
        fprintf(stderr, "Успешное подключение к базе данных.\n");
    }
    return 0;
}

int disconnect_bd() {

    mysql_close(&conn);
    fprintf(stderr, "Закрытие соединения.\n");
    return 0;

}


int init_bd()
{
    MYSQL_RES* res_set;
    MYSQL_ROW row;
    int query_state;

    mysql_init(&conn);

    if (!mysql_real_connect(&conn, "localhost", "root", "Spider@19128", "controlsystembase_dus", 0, NULL, 0))
    {
        fprintf(stderr, "Ошибка подключения к базе данных: %s\n",
            mysql_error(&conn));
    }
    else {
        fprintf(stderr, "Успешное подключение к базе данных.\n");
    }

    mysql_close(&conn);
    return 0;
}

