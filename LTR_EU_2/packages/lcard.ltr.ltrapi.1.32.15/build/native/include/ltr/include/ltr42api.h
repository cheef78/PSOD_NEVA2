#ifndef LTR42API_H_
#define LTR42API_H_


#include "ltrapi.h"


/*================================================================================================*/
#ifdef _WIN32
    #ifdef LTR42API_EXPORTS
        #define LTR42API_DllExport(type)   __declspec(dllexport) type APIENTRY
    #else
        #define LTR42API_DllExport(type)   __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR42API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR42API_DllExport(type)   type
#endif


#define LTR42_ERR_DATA_TRANSMISSON_ERROR              (-8013)
#define LTR42_ERR_WRONG_SECOND_MARK_CONF              (-8017)
#define LTR42_ERR_WRONG_START_MARK_CONF               (-8018)

#define LTR42_MARK_MODE_INTERNAL         (0)
#define LTR42_MARK_MODE_MASTER           (1)
#define LTR42_MARK_MODE_EXTERNAL         (2)

#define LTR42_EEPROM_SIZE                (512)


/*================================================================================================*/
#pragma pack(4) 
/* Структура описания модуля */
typedef struct {
    CHAR Name[16];
    CHAR Serial[24];
    CHAR FirmwareVersion[8];            /* Версия БИОСа */
    CHAR FirmwareDate[16];              /* Дата создания данной версии БИОСа */
} TINFO_LTR42, *PTINFO_LTR42;

typedef struct {
    TLTR Channel;
    INT size;                           /* размер структуры */
    BOOLEAN AckEna;
    struct {
        INT SecondMark_Mode;            /* Режим меток. 0 - внутр., 1-внутр.+выход, 2-внешн */
        INT StartMark_Mode;
    } Marks;                            /* Структура для работы с временными метками */
    TINFO_LTR42 ModuleInfo;
} TLTR42, *PTLTR42;                     /* Структура описания модуля */
#pragma pack()


/*================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

LTR42API_DllExport(INT) LTR42_Init(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_Open(PTLTR42 hnd, INT net_addr, WORD net_port, const CHAR *crate_sn,
    INT slot_num);
LTR42API_DllExport(INT) LTR42_IsOpened(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_Close(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_Config(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_ConfigAndStart(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_WritePort(PTLTR42 hnd, WORD OutputData);
LTR42API_DllExport(INT) LTR42_WriteArray(PTLTR42 hnd, const WORD *OutputArray, INT ArraySize);

LTR42API_DllExport(INT) LTR42_WritePortSaved(PTLTR42 hnd, WORD OutputData);

LTR42API_DllExport(INT) LTR42_StartSecondMark(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_StopSecondMark(PTLTR42 hnd);
LTR42API_DllExport(INT) LTR42_MakeStartMark(PTLTR42 hnd);

LTR42API_DllExport(INT) LTR42_WriteEEPROM(PTLTR42 hnd, INT Address, BYTE val);
LTR42API_DllExport(INT) LTR42_ReadEEPROM(PTLTR42 hnd, INT Address, BYTE *val);

LTR42API_DllExport(INT) LTR42_StoreConfig(PTLTR42 hnd, TLTR_CARD_START_MODE start_mode);

LTR42API_DllExport(LPCSTR) LTR42_GetErrorString(INT Error_Code);


/***************************************************************************//**
  @brief Установка ширины импульса метки СТАРТ

  Данная функция позволяет задать время импульса, генерируемого модулем на
  выходе при генерации метки старт, если разрешена трансляция метки СТАРТ на
  выход (режим #LTR42_MARK_MODE_MASTER).
  По-умолчанию время импульса составляет порядка 200нс, что может быть
  недостаточно для запуска других устройств от данного импульса. Данная функция
  позволяет установить большее время импульса.
  Данная функция доступна только в прошивке, начиная с версии 2.0.

  @param[in] hnd        Описатель модуля
  @param[in] time_mks   Время импульса в мкс. Если 0 --- то используется вариант
                        по-умолчанию (~200нс).
  @return               Код ошибки
 ******************************************************************************/
LTR42API_DllExport (INT) LTR42_SetStartMarkPulseTime(TLTR42 *hnd, DWORD time_mks);


#ifdef __cplusplus 
}
#endif

#endif
















