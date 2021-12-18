/** @file ltr210api.h
    Файл содержит определение функций для получения дополнительно идентификатора
    тестового модуля, который виден как LTR01. Все тестовые модули используют
    общий MID равный MID_LTR01. Узнать, какой тестовый модуль реально установлен,
    можно с помощью дополнительно идентификатора.

    В библиотеке введен как набор функций для установки соединения и последующиего
    получения дополнительно ID (в первую очередь для использования в API
    самих тестовых модулей), так и упрощенная функция, выполняющая все
    за один вызов (для удобного вызова из внешних программ при определении
    состава модулей).

    Библиотека не использует дополнительного типа для определения описателя
    модуля LTR01, а использует напрямую описатель соединения TLTR. Это сделано
    для более удобного встраивания в API непосредственно тестовых модулей. */

#ifndef LTR01API_H_
#define LTR01API_H_


#include "ltrapi.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#ifdef _WIN32
    #ifdef LTR01API_EXPORTS
      #define LTR01API_DllExport(type) __declspec(dllexport) type APIENTRY
    #else
      #define LTR01API_DllExport(type) __declspec(dllimport) type APIENTRY
    #endif
#elif defined __GNUC__
    #define LTR01API_DllExport(type) __attribute__ ((visibility("default"))) type
#else
    #define LTR01API_DllExport(type)  type
#endif

/** Коды дополнительных идентификаторов, позволяющие определить, что за тестовый
    модуль, видимый как LTR01, реально установлен */
typedef enum
{
    LTR01_SUBID_INVALID = 0,
    LTR01_SUBID_LTRS511 = 1, /**< Идентификатор модуля LTRS-511 */
    LTR01_SUBID_LTRS411 = 2, /**< Идентификатор модуля LTRS-411 */
    LTR01_SUBID_LTRS412 = 3, /**< Идентификатор модуля LTRS-412 */
    LTR01_SUBID_LTRT10  = 4  /**< Идентификатор модуля LTRT-10 */
} e_LTR01_SUBID;



/*============================================================================*/

/**  @brief Открытие соединения с модулем.

    Функция устанавливает соединение с одним из тестовых модулей, видимых как LTR01
    в соответствии с переданными параметрами, проверяет наличие модуля и при
    необходимости проверяет дополнительный идентификатор.

    После завершения работы необходимо закрыть соединение с помощью LTR01_Close().
 *
 *Установка соедининия
    Выполняет соединение, сброс модуля и проверку, что это именно LTR01.
    @param[in] hnd         Описатель для установки соединения с сервером,
                           предварительно проинициализированный с помощью LTR_Init()
    @param[in] net_addr    IP-Адрес LTR-Сервера
    @param[in] net_port    TCP-порт для установления связи с сервером
    @param[in] crate_sn    Серийный номер крейта
    @param[in] slot_num    Слот модуля (от CC_MODULE1 до CC_MODULE16)
    @param[in] subid       Если не равен #LTR01_SUBID_INVALID, то функция выполняет
                           проверку на соответствия дополнительного идентификатора
                           указанному в данном параметре
    @param[out] cpld_ver   Если не NULL, то в данную переменную сохраняется
                           версия CPLD, полученная в ответе на сброс модуля.
    @return                Код ошибки */
LTR01API_DllExport(INT) LTR01_Open(TLTR *hnd, DWORD net_addr, WORD net_port,
                                   const CHAR *crate_sn, INT slot_num, WORD subid, BYTE* cpld_ver);

/** Закрытие ранее открытого с помощью LTR01_Open() соединения.
    @param[in] hnd         Описатель соединения с сервером
    @return                Код ошибки */
LTR01API_DllExport(INT) LTR01_Close(TLTR *hnd);

/** Получение дополнительного ID для модуля LTR01, с которым была установлена
    до этого связь с помощью LTR01_Open().
    Дополнительный ID позволяет узнать, какой реально модуль тестовый модуль
    установлен.
    @param[in] hnd         Описатель соединения с сервером.
    @param[out] subid      При успехе возвращается дополнительный ID-модуля
                           из #e_LTR01_SUBID.
    @return                Код ошибки */
LTR01API_DllExport(INT) LTR01_GetModuleSubID(TLTR *hnd, WORD *subid);

/** Вспомогательная функция для получения дополнительного ID модуля за один вызов.
    Функция устанавливает соединение с модулем, получает ID модуля и закрывает
    установленное соединение.

    Аналогична последовательности вызовов LTR_Init(), LTR01_Open(),
    LTR01_GetModuleSubID() и LTR01_Close().

    @param[in] net_addr    IP-Адрес LTR-Сервера
    @param[in] net_port    TCP-порт для установления связи с сервером
    @param[in] csn         Серийный номер крейта
    @param[in] slot        Слот модуля (от CC_MODULE1 до CC_MODULE16)
    @param[out] subid      При успехе возвращается дополнительный ID-модуля
                           из #e_LTR01_SUBID.
    @return                Код ошибки */
LTR01API_DllExport(INT) LTR01_GetSubID(DWORD net_addr, WORD net_port, const CHAR *csn,
                                       INT slot, WORD *subid);

/** Получение имени модуля по его дополнительному идентификатору
    @param[out] subid      Дополнительный идентификатор из #e_LTR01_SUBID.
    @return                Строка с именем модуля */
LTR01API_DllExport(LPCSTR) LTR01_GetModuleName(WORD subid);

/*============================================================================*/

#ifdef __cplusplus
}                                          // only need to export C interface if
                                           // used by C++ source code
#endif

#endif                      /* #ifndef LTR11API_H_ */
