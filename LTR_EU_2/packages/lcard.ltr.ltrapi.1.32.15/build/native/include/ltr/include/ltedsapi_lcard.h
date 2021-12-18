#ifndef LTEDSAPI_LCARD_H
#define LTEDSAPI_LCARD_H

#include "ltedsapi_base.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#pragma pack(4)

/***************************************************************************//**
  @addtogroup lcard_base_types ���� � �����������, ����������� ��� ������������� "� ����"
  @{
  *****************************************************************************/


/** ������ � ����� �������������� ������� �������� ��� "� ����" */
#define LTEDS_LCARD_TEMPLATE_ID_BITSIZE 8

/** ������������� �������������, ��������������� �������� ��� "� ����" */
#define LTEDS_LCARD_MANUFACTURER_ID   2614


/** @brief �������������� ������� ���������������� �������� "� ����" � TEDS

   ������ ���� ����������, ������ ���� ��������������� "� ����"
   ������������� ������ TEDS.
   � ������ �������������� ���������������� (��� LPW25-U-2-230) ������� ���������
   �������������� ������ ��� ������� ������ ��� ����������� �����������,
   ����� ������ ����� ��������������� ������������. */
typedef enum {
    /** ������ ����� ��������������� LPW25-U-2-230 */
    LTEDS_LCARD_MODEL_ID_LPW25_U_2_230_CH1 = 2500,
    /** ������ ����� ��������������� LPW25-U-2-230 */
    LTEDS_LCARD_MODEL_ID_LPW25_U_2_230_CH2 = 2501,
    /** ��������������� LPW25-I-1-5-1 */
    LTEDS_LCARD_MODEL_ID_LPW25_I_1_5_1     = 2502,
    /** ��������������� LPW25-I-1-5-2 */
    LTEDS_LCARD_MODEL_ID_LPW25_I_1_5_2     = 2503,
} e_LTEDS_LCARD_MODEL_ID;


/** �������������� �������� ������������� "� ����" */
typedef enum {
    /** ������� ����������� ��������� ������������� ������� �� ���� �������
        ������� (������ @ref lcard_tmpl_curimp). */
    LTEDS_LCARD_TEMPLATE_ID_CUR_IMP_TABLE = 100,
    /** ������� � ���� ��������� ��������������� ������. ��������� ��������
        ���� ������������ �������� ��� ������ ������ (������ @ref lcard_tmpl_phafreqtbl). */
    LTEDS_LCARD_TEMPLATE_ID_PHASE_FREQ_TABLE = 101
} e_LTEDS_LCARD_TEMPLATE_ID;


/***************************************************************************//**
    @brief ��������, ��������� �� ������ ������������� ������������� � �������� "� ����".

    ������� ��������� �������� ���� ManufacturerID �� TEDS ������ � ���������,
    ��������� �� ������ ������������� � �������� "� ����".

    @brief manid ������������ �������������, ������� ����� ���������.
    @return ������� ���������� TRUE, ���� ������������� ��������� � �������� "� ����",
            ����� --- FALSE.
*******************************************************************************/
LTEDSAPI_DllExport(BOOL) LTEDS_IsLCardManufacturerID(WORD manid);

/** @} */




/***************************************************************************//**
    @addtogroup lcard_tmpl_curimp ������ Current Impendance Table (1)
    @{
*******************************************************************************/

/** ������������ ���������� ��������� � ������� ������������ �����
    ����� ������� � �������� �������������� */
#define LTEDS_LCARD_INFO_CUR_IMP_DATASET_MAX  127

/** @brief ������������ ������������� ����

    ��������� ������ ������������ ����� ������������ ����� ������� ���������������
    � ��� �������� ��������������. */
typedef struct {
    double SourceCurrent; /**< �������� ��������� ���� � ������� */
    double OutputImpedance; /**< �������� ��������� ������������� � ���� */
} TLTEDS_LCARD_INFO_CUR_IMP_DATASET;


/** @brief ���������� ����������� ��������� ������������� ������� �� ���� �������
        �������

   ��������� �������� ���������� �� ������� "� ����" � ���������������
   #LTEDS_LCARD_TEMPLATE_ID_CUR_IMP_TABLE.

    � ��������� ���������� �������� ��������� ������������� ����������������
    ��� ��������� �������� ���� ������� ���������������.

    ��� ��������� ������������ ������� LTEDS_GetLCardTmpltInfoCurImpTable(). */
typedef struct {
    BYTE PrecFormat; /**< ��� ������� (�������������� ������ 0) */
    BYTE DataSetCount; /**< ���������� ����� ������������ ������������� � ���� �������. */
    /** ����� ����� ������������ ������������� � ���� �������. ������������� ������
       [DataSetCount](@ref TLTEDS_LCARD_INFO_TMPLT_CUR_IMP::DataSetCount) ���������. */
    TLTEDS_LCARD_INFO_CUR_IMP_DATASET DataSets[LTEDS_LCARD_INFO_CUR_IMP_DATASET_MAX];
} TLTEDS_LCARD_INFO_TMPLT_CUR_IMP;


/***************************************************************************//**
    @brief ���������� ������� ������������ ������������� ���� �� ������ TEDS

    ������� ��������� �������� �� TEDS ����������, ��������������� �������
    "� ����" � ��������������� #LTEDS_LCARD_TEMPLATE_ID_CUR_IMP_TABLE.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_LCARD_INFO_TMPLT_CUR_IMP.

    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetLCardTmpltInfoCurImpTable(
        TLTEDS_DECODE_CONTEXT *ctx, TLTEDS_LCARD_INFO_TMPLT_CUR_IMP *info);

/***************************************************************************//**
    @brief ������ ������� ������������ ������������� ���� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ��������������� �������
    "� ����" � ��������������� #LTEDS_LCARD_TEMPLATE_ID_CUR_IMP_TABLE.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutLCardTmpltInfoCurImpTable(
        TLTEDS_ENCODE_CONTEXT *ctx, const TLTEDS_LCARD_INFO_TMPLT_CUR_IMP *info);

/** @} */




/***************************************************************************//**
    @addtogroup lcard_tmpl_phafreqtbl ������ Phase Frequency Table (2)
    @{
*******************************************************************************/

/** ������������ ���������� ��������� � ������� ���� ��������� �������������� */
#define LTEDS_LCARD_INFO_PHASE_FREQ_DATASET_MAX 127


/** @brief ������������ �������� ���� �������

    ��������� ������ �������� ����, �������� ����������������, ��� ���������
    �������� ������� �������. */
typedef struct {
    double Frequency; /**< ������� ������� � �� */
    double PhaseShift; /**< ����� ���� � �������� */
} TLTEDS_LCARD_INFO_PHASE_FREQ_DATASET;


/** @brief ���������� � ���� ��������� �������������� ���������������

   ��������� �������� ���������� �� ������� "� ����" � ���������������
   #LTEDS_LCARD_TEMPLATE_ID_PHASE_FREQ_TABLE.

    � ��������� ����������� ����� �����, ������������ ����� ����, ��������
    ����������������, ��� ��������� �������� ������ �������.

    ��� ��������� ������������ ������� LTEDS_GetLCardTmpltInfoPhaseFreqTable(). */
typedef struct {
    BYTE DataSetCount; /**< ���������� ����� ������������ ������� � ����. */
    /** ����� ����� ������������ ������� � ����. ������������� ������
       [DataSetCount](@ref TLTEDS_LCARD_INFO_TMPLT_PHASE_FREQ::DataSetCount) ���������. */
    TLTEDS_LCARD_INFO_PHASE_FREQ_DATASET DataSets[LTEDS_LCARD_INFO_PHASE_FREQ_DATASET_MAX];
} TLTEDS_LCARD_INFO_TMPLT_PHASE_FREQ;

/***************************************************************************//**
    @brief ���������� ������� � ���� ��������� ��������������� �� ������ TEDS

    ������� ��������� �������� �� TEDS ����������, ��������������� �������
    "� ����" � ��������������� #LTEDS_LCARD_TEMPLATE_ID_PHASE_FREQ_TABLE.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_LCARD_INFO_TMPLT_PHASE_FREQ.

    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetLCardTmpltInfoPhaseFreqTable(
        TLTEDS_DECODE_CONTEXT *ctx, TLTEDS_LCARD_INFO_TMPLT_PHASE_FREQ *info);


/***************************************************************************//**
    @brief ������ ������� � ���� ��������� ��������������� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ��������������� �������
    "� ����" � ��������������� #LTEDS_LCARD_TEMPLATE_ID_PHASE_FREQ_TABLE.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutLCardTmpltInfoPhaseFreqTable(
        TLTEDS_ENCODE_CONTEXT *ctx, const TLTEDS_LCARD_INFO_TMPLT_PHASE_FREQ *info);


/** @} */

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif // LTEDSAPI_LCARD_H
