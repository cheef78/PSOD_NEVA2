#ifndef LTEDSAPI_STDTMPL_H
#define LTEDSAPI_STDTMPL_H

#include "ltedsapi_base.h"

#ifdef __cplusplus
extern "C" {                                 // only need to export C interface if
                                             // used by C++ source code
#endif

#pragma pack(4)

/***************************************************************************//**
  @addtogroup std_tmpl_general ���� ������ ��� ������������� ����� ����������
                               �� ����������� ��������
  @{
  *****************************************************************************/

/** @brief ������� ���������� � ���������� ����������

   ��������� �������� ���������� � ��������� ����������� ����������
   � ������� ����� �� ������������.
   ������ � ����������� ����������� ��������, ����������� ������. */
typedef struct {
    TLTEDS_INFO_DATE Date; /**< ���� ���������� ���������� */
    WORD PeriodDays;   /**< ������ ����� ����������� ���������� � ���� */
    CHAR  Initials[4];  /**< �������� ����������� ����������. 3 ��������� ���������� 
                                                   ����� � ����������� ������� �������� */
} TLTEDS_INFO_BASE_CAL;

/** @brief ���������� ���������� ��������.

  ������������ ������������ � ���������� ����������� �������� ��� ��������,
  ����� ���������� �������� �������� ������, � ����� � ����� �����������
  ������ � ��������������� ���������� �� �������� */
typedef  enum {
    LTEDS_PHYSMEAS_TEMP_K           = 0, /**< ����������� � ��������� */
    LTEDS_PHYSMEAS_TEMP_CELSIUS     = 1, /**< ����������� � �������� ������� (K - 273.15) */
    LTEDS_PHYSMEAS_STRAIN           = 2, /**< ����������, ��������� (�/�) */
    LTEDS_PHYSMEAS_MICROSTRAIN      = 3, /**< ���������������, �������������� */
    LTEDS_PHYSMEAS_FORCE_WEIGHT_N   = 4, /**< ���� ��� ��� � �������� (�) */
    LTEDS_PHYSMEAS_FORCE_WEIGHT_LB  = 5, /**< ���� ��� ��� � ������ (4.44822 ��������) */
    LTEDS_PHYSMEAS_FORCE_WEIGHT_KGF = 6, /**< ���� ��� ��� � ��� (���������-����) */
    LTEDS_PHYSMEAS_ACCEL_M_S2       = 7, /**< ��������� � \f$ \textup{�}/\textup{�}^2 \f$ */
    LTEDS_PHYSMEAS_ACCEL_G          = 8, /**< ��������� � g (9.80665 \f$\textup{�}/\textup{�}^2\f$) */
    LTEDS_PHYSMEAS_TORQUE_NM_RADIAN = 9, /**< �������� ������ � \f$ \textup{�}*\textup{�}/\textup{���} \f$ */
    LTEDS_PHYSMEAS_TORQUE_NM        = 10,/**< �������� ������ � \f$ \textup{�}*\textup{�} \f$
                                             (��� �������� ������ � ������������) */
    LTEDS_PHYSMEAS_TORQUE_OZ_IN     = 11,/**< �������� ������ � "oz-in" (0.00706155 �*�) */
    LTEDS_PHYSMEAS_PRESSURE_PASCAL  = 12,/**< �������� � �������� */
    LTEDS_PHYSMEAS_PRESSURE_PSI     = 13,/**< �������� � ������ �� ����������
                                              ���� (6894.757 ��������) */
    LTEDS_PHYSMEAS_MASS_KG          = 14,/**< ����� � ����������� */
    LTEDS_PHYSMEAS_MASS_G           = 15,/**< ����� � ������� */
    LTEDS_PHYSMEAS_DISTANCE_M       = 16,/**< ��������� � ������ */
    LTEDS_PHYSMEAS_DISTANCE_MM      = 17,/**< ��������� � ����������� */
    LTEDS_PHYSMEAS_DISTANCE_INCHES  = 18,/**< ��������� � ������ (0.0254 �����) */
    LTEDS_PHYSMEAS_VELOCITY_M_S     = 19,/**< �������� � ������ � ������� */
    LTEDS_PHYSMEAS_VELOCITY_MPH     = 20,/**< �������� � ����� � ��� (0.44704 �/�) */
    LTEDS_PHYSMEAS_VELOCITY_FPS     = 21,/**< �������� � ����� � ������� (0.3048 �/�) */
    LTEDS_PHYSMEAS_ANGPOS_RADIAN    = 22,/**< ���� � �������� */
    LTEDS_PHYSMEAS_ANGPOS_DEGREES   = 23,/**< ���� � �������� (0.0174533 ������) */
    LTEDS_PHYSMEAS_ROT_VEL_RADIAN_S = 24,/**< ������� �������� � �������� � ������� */
    LTEDS_PHYSMEAS_ROT_VEL_RPM      = 25,/**< ������� �������� � �������� � ������
                                           (0.104720 ������ � �������) */
    LTEDS_PHYSMEAS_FREQ_HZ          = 26,/**< ������� � �� */
    LTEDS_PHYSMEAS_CONCENT_KG_M3    = 27,/**< ��������� � \f$ \textup{��}/\textup{�}^3 \f$ */
    LTEDS_PHYSMEAS_CONCENT_UNIT_G_L = 28,/**< ��������� � \f$ \textup{�}/\textup{�}^3 \f$
                                            (������������ \f$ \textup{��}/\textup{�}^3\f$)*/
    LTEDS_PHYSMEAS_CONCENT_MOLE_M3  = 29,/**< �������� ������������ � \f$ \textup{����}/\textup{�}^3 \f$ */
    LTEDS_PHYSMEAS_CONCENT_MOLE_L   = 30,/**< ���� �� ���� (\f$1000 *\textup{����}/\textup{�}^3 \f$) */
    LTEDS_PHYSMEAS_VOL_CONCENT_M3_M3= 31,/**< �������� �������� ������������ �
                                            \f$ \textup{�}^3/\textup{�}^3 \f$ */
    LTEDS_PHYSMEAS_VOL_CONCENT_L_L  = 32,/**< �������� �������� ������������ � ������
                                          �� ���� */
    LTEDS_PHYSMEAS_MASS_FLOW_KG_S   = 33,/**< �������� ������ � ��/� */
    LTEDS_PHYSMEAS_VOL_FLOW_M3_S    = 34,/**< �������� ������ � \f$ \textup{�}^3/\textup{c} \f$ */
    LTEDS_PHYSMEAS_VOL_FLOW_M3_HR   = 35,/**< �������� ������ � \f$ \textup{�}^3\f$ � ��� */
    LTEDS_PHYSMEAS_VOL_FLOW_GPM     = 36,/**< �������� ������ � �������� � ������
                                          = \f$ 6.30902e^{-5} * \textup{�}^3/\textup{c}\f$)*/
    LTEDS_PHYSMEAS_VOL_FLOW_CFM     = 37,/**< �������� ������ � ���������� ����� � ������
                                          = \f$ 4.71947e^{-4} * \textup{�}^3/\textup{c}\f$)*/
    LTEDS_PHYSMEAS_VOL_FLOW_L_M     = 38,/**< �������� ������ � ������ � ������
                                          = \f$ 1.66667e^{-5} * \textup{�}^3/\textup{c}\f$)*/
    LTEDS_PHYSMEAS_REL_HUMIDITY     = 39,/**< ������������� ��������� �
                                          \f$ (\textup{��}/\textup{�}^3)/(\textup{��}/\textup{�}^3)\f$)*/
    LTEDS_PHYSMEAS_RATIO_PERCENT    = 40,/**< ������������ ��������� � ��������� */
    LTEDS_PHYSMEAS_VOLTAGE          = 41,/**< ���������� � ������� */
    LTEDS_PHYSMEAS_RMS_VOLTAGE      = 42,/**< RMS ���������� � ������� */
    LTEDS_PHYSMEAS_CURRENT          = 43,/**< ���� ���� � ������� */
    LTEDS_PHYSMEAS_RMS_CURRENT      = 44,/**< RMS ���� ���� � �������  */
    LTEDS_PHYSMEAS_POWER_WATTS      = 45,/**< �������� � ������  */
}  e_LTEDS_INFO_PHYSICAL_MEASURAND;

/** @brief ��� �������������� ���������� ���������������

   ������ ������������ ���������� ����� ��� �������� �������� �������������� ����������
   ��������������� (��� ����� ����������� ����������).
*/
typedef enum {
    LTEDS_INFO_ELECSIGTYPE_VOLTAGE_SENSOR    = 0, /**< ������ � ������� �� ���������� */
    LTEDS_INFO_ELECSIGTYPE_CURRENT_SENSOR    = 1, /**< ������ � ������� �� ���� */
    LTEDS_INFO_ELECSIGTYPE_RESISTANCE_SENSOR = 2, /**< ������ � ������� � ���� ������������� */
    LTEDS_INFO_ELECSIGTYPE_BRIDGE_SENSOR     = 3, /**< ������  � ������� � ���� ����� */
    LTEDS_INFO_ELECSIGTYPE_LVDT_SENSOR       = 4, /**< LVDT ������ */
    LTEDS_INFO_ELECSIGTYPE_POTENT_VDIV_SENSOR= 5, /**< ������������������� �������� ���������� */
    LTEDS_INFO_ELECSIGTYPE_PULSE_SENSOR      = 6, /**< ������ � ���������� ������� */
    LTEDS_INFO_ELECSIGTYPE_VOLTAGE_ACTUATOR  = 7, /**< �������� �����������, ����������� ����������� */
    LTEDS_INFO_ELECSIGTYPE_CURRENT_ACTUATOR  = 8, /**< �������� �����������, ����������� ����� */
    LTEDS_INFO_ELECSIGTYPE_PULSE_ACTUATOR    = 9, /**< �������� �����������, ����������� ���������� */
} e_LTEDS_INFO_ELECSIGTYPE;

/** ���� (����������) ��������� ������� ������������ �������� */
typedef enum {
    LTEDS_INFO_OUTSIG_SIGN_POSITIVE = 0, /**< �������� ������ ������������� ����������
                                              (� ���� � �������) */
    LTEDS_INFO_OUTSIG_SIGN_NEGATIVE = 1, /**< �������� ������ ������������� ����������
                                              (� ����������� � �������) */
} e_LTEDS_INFO_OUTSIG_SIGN;

/** ��� ��������� ������� */
typedef  enum {
    LTEDS_INFO_SENS_DIRECTION_X = 0, /**< ��� X */
    LTEDS_INFO_SENS_DIRECTION_Y = 1, /**< ��� Y */
    LTEDS_INFO_SENS_DIRECTION_Z = 2, /**< ��� Z */
    LTEDS_INFO_SENS_DIRECTION_NA = 3, /**< ��� ������ */
} e_LTEDS_INFO_SENS_DIRECTION;

/** ����� ����������� ������� ����������� ������� (PV) �� �������� �������������� ������� (EV) */
typedef enum {
    LTEDS_INFO_MAPMETH_LINEAR       = 0, /**< �������� �����������: \f$ PV = m*EV + b \f$ */
    LTEDS_INFO_MAPMETH_INVERSE_1    = 1, /**< ��������� �������� ����������� ���� 1:
                                           \f$ PV = m/(EV + b) \f$ */
    LTEDS_INFO_MAPMETH_INVERSE_2    = 2, /**< ��������� �������� ����������� ���� 2:
                                           \f$ PV = b + m/EV \f$ */
    LTEDS_INFO_MAPMETH_INVERSE_3    = 3, /**< ��������� �������� ����������� ���� 3:
                                           \f$ PV = 1/(b + m/EV)\f$ */
    LTEDS_INFO_MAPMETH_THERMOCOUPLE = 4, /**< ����������� ��� ��������� */
    LTEDS_INFO_MAPMETH_THERMISTOR   = 5, /**< ����������� ��� ���������� */
    LTEDS_INFO_MAPMETH_RTD          = 6, /**< ����������� ��� ������������������ */
    LTEDS_INFO_MAPMETH_BRIDGE       = 7, /**< ����������� ��� ����� (� ��������������
                                              ������� ������������) */
} e_LTEDS_INFO_MAPMETH;


/** @brief ���������� � ��������� ���������� �������, ���������� ��������

    ��������� �������� ����������, ����� ���������� �������� �������� ������,
    � ����� ������� �������� ��������� ���������� �������.
    ��� �������� � �������� ��������������� ������ �������� ������ � ����������
    ������������� ������� (#TLTEDS_INFO_ELECTRICAL_RANGE) ����� ����������
    ����������� �������������� (����������������) �������.

    ������ � ������ ������ ����������� ��������. */
typedef struct {
    BYTE   Measurand; /**< ���������� ���������� �������� � ������� �� ���������.
                           �������� �� #e_LTEDS_INFO_PHYSICAL_MEASURAND. */
    double MinValue; /**< ����������� ���������� �������� � ��������, ������������
                          [Units](@ref TLTEDS_INFO_PHYSMEAS_RANGE::Measurand). */
    double MaxValue; /**< ������������ ���������� �������� � ��������, ������������
                          [Units](@ref TLTEDS_INFO_PHYSMEAS_RANGE::Measurand). */
} TLTEDS_INFO_PHYSMEAS_RANGE;

/** @brief ���������� � ��������� ������������� �������� �� ������ �������

    ��������� ���������� ������� ������������� �������� �������� �������.
    ��� �������� � �������� ��������������� ������ �������� ������ � ����������
    ���������� ������� (#TLTEDS_INFO_PHYSMEAS_RANGE) ����� ����������
    ����������� �������������� (����������������) �������.

    ������ � ������ ������ ����������� ��������. */
typedef struct {
    BYTE PrecType; /**< ������ ���� ����������, ����� �������� � � ����� ���������
                       ���� ������������ �������� � TEDS. ����� ����� ������� ��
                       ���� �������. */
    double MinValue; /**< ����������� �������� ��������� �������������� �������. */
    double MaxValue; /**< ������������ �������� ��������� �������������� �������. */
} TLTEDS_INFO_ELECTRICAL_RANGE;

/** ���������� �  ������� ���������� ����������� ��� ������� ������� */
typedef struct {
    double NominalValue;  /**< ����������� �������� � ������� */
    double MinValue; /**< ����������� �������� � ������� */
    double MaxValue; /**< ����������� �������� � ������� */
} TLTEDS_INFO_EXCITATION_LEVELS;


/** @brief ��� ���������� ������� ��� �����������.

     ������������ ���������� ��� ���������� ������� ��� ����������� �
     ����������, ��� ���������������� �������� ������, �������� � ���������
     #TLTEDS_INFO_EXCITATION_LEVELS. */
typedef  enum {
    /** ������� ���������� ������������ �������. */
    LTEDS_INFO_EXCITETYPE_DC         = 0,
    /** ������� ���������� ����������� �������, �.�. ��������� ������  ��������������
     *  � �������������� ����������� ������ �������� ��������. */
    LTEDS_INFO_REXCITETYPE_BIPOLAR_DC = 1,
    /** ���������� �������. ������ ����������� � RMS. */
    LTEDS_INFO_EXCITETYPE_AC         = 2,
} e_LTEDS_INFO_EXCITE_TYPE;

/** @} */


/***************************************************************************//**
    @addtogroup std_tmpl_25 ������ Accelerometer/Force transducer (25)
    @{
*******************************************************************************/

/** ��� ��������������� ��� ������� �������������/������� ���� */
typedef enum {
    LTEDS_INFO_ACCF_TRANS_TYPE_ACC = 0, /**< ������������ */
    LTEDS_INFO_ACCF_TRANS_TYPE_FORCE = 1, /**< ������ ���� */
} e_LTEDS_INFO_ACCF_TRANS_TYPE;

/** ��������� ���������������� �� ��������� */
typedef enum {
    LTEDS_INFO_ACCF_DEFSENS_NO = 0, /**< ��������� ����� */
    LTEDS_INFO_ACCF_DEFSENS_LOW = 1, /**< ������ ���������������� */
    LTEDS_INFO_ACCF_DEFSENS_HIGH = 2 /**< ������� ���������������� */
} e_LTEDS_INFO_ACCF_DEFSENS;


/** ��������� ������ �������� ���������������� �������������/������� ���� */
typedef struct {
    double Sens; /**< ���������������� ��������������� */
    double Fhp; /**< ������� ����� ��� �� ������ -3dB, ������������� ����� ������������
                     �������������� ���

                     \f$ H(f, F_{hp}) = 1 + \frac{i*f}{F_{hp}} \f$. */
} TLTEDS_INFO_ACCF_SENS_HP;

/** ��������� ���������������� �������������/������� ���� ��� ����������� ���������� */
typedef struct {
    BYTE DefaultSens; /**< �������� ������������� ���������������� �� ���������.
                           �������� �� #e_LTEDS_INFO_ACCF_DEFSENS. */
    BOOLEAN SupportPassiveMode; /**< ������������ �� ������ ��������� �����,
                                     � ������� �� �� �������� �������� ������,
                                     ��� ��������� ���������� ���������
                                     �������������������� �������� �� ���� �����. */
    TLTEDS_INFO_ACCF_SENS_HP Low; /**< ��������� ��� ��������� ������ ����������������. */
    TLTEDS_INFO_ACCF_SENS_HP High; /**< ��������� ��� ��������� ������� ����������������. */
} TLTEDS_INFO_ACCF_PROG_SENS;

/** ��������� ��������� ���������� ��������, ����������� ��� ������� ���� */
typedef struct {
    double Stiffness; /**< ��������� � �������� �� ����. */
    double MassBelow; /**< ����� ���� ��������������� �������� � �������. */
    double PhaseCorrection; /**< ��������� ���� � ��������, ����������� ��� ����������� ������
                                 �� ������� �������. ������������ ������
                                 ��� ��������� ������������ ���������� �����������������. */
} TLTEDS_INFO_ACCF_FORCE;


/** ��������� ��������� ���������� �������� ��������������/�������� ���� */
typedef struct {
    BYTE TransducerType; /**< ��� ��������������� �� #e_LTEDS_INFO_ACCF_TRANS_TYPE */
    BOOLEAN HasProgrSens; /**< �������, ������������ �� ������ ����������� ���������� ����������������� */
    union {
        TLTEDS_INFO_ACCF_SENS_HP SensInfo; /**< ������������� ��������� ����������������
                                                (���� @structref{TLTEDS_INFO_ACCF_MEAS,HasProgrSens} ����� �������� "����") */
        TLTEDS_INFO_ACCF_PROG_SENS ProgrSensInfo; /**< ��������� ���������������� ��� ����������� ����������
                                                  (���� @structref{TLTEDS_INFO_ACCF_MEAS,HasProgrSens}  ����� �������� "������") */
    };
    TLTEDS_INFO_ACCF_FORCE Force; /**< ���������, ����������� ��� ������� ����
                                       (��� ������������� �� ����� ��������) */
    BYTE SensDirection; /**< ��� ��������� �������. �������� �� #e_LTEDS_INFO_SENS_DIRECTION */
    double Weight; /**< ��� ������� � ������� */
} TLTEDS_INFO_ACCF_MEAS;


/** ��������� �������������� ���������� �������������/������� ���� */
typedef struct {
    BYTE SigType; /**< ��� �������� �������������� ����������. ������ �����
                       #LTEDS_INFO_ELECSIGTYPE_VOLTAGE_SENSOR ��� ������� ������� */
    BOOLEAN AcCoupling; /**< �������, ��������� �� ������� ���������� ������������
                             ��� ��������� ��������� �������.
                             ������ ������ ��� ������� �������. */
    BYTE MapMeth; /**< ����� ����������� ���������� �������� �� �������������.
                       ������ ����� #LTEDS_INFO_MAPMETH_LINEAR ��� ������� �������. */
    BYTE Sign; /**< ���������� ��������� �������. �������� �� #e_LTEDS_INFO_OUTSIG_SIGN */
} TLTEDS_INFO_ACCF_ELEC;

/** ��������� ������������ ������� �������������/������� ���� */
typedef struct {
    BOOLEAN IsSpecified; /**< ���������� �� ���������� �������������� � �������.
                              ���� ����, �� ��������� ���� �� ����� �������� */
    double Flp; /**< ������� ����� ��� �� ����� -3dB, ������������� ����� ������������
                     �������������� ���

                     \f$ H(f, F_{lp}) = \frac{1}{1 + \frac{i*f}{F_{lp}}} \f$. */
    double Fpres; /**< ����������� ������� ��� ������������ ������, �������������
                       ����� ������������ �������������� ���

                       \f$ H(f, F_{pres}, Q_p) = \frac{1}{1 + \frac{i*f}{Q_p * F_{pres}} + (\frac{i*f}{F_{pres}})^2} \f$.

                       �������� \f$ Q_p \f$ ������� �� ��������� @structref{TLTEDS_INFO_ACCF_TF,Qp}.*/
    double Qp; /**< ����������� ��� ������������ ������. ������������ � ������� ��
                    �������� ��������� @structref{TLTEDS_INFO_ACCF_TF,Fpres}.*/
    double AmpSlope; /**< ������������� ������ ��� � ��������� �� ������.
                          ������� ����������� �� �������
                          \f$ H(f,a,F_{ref}) = (\frac{i*f}{F_{ref}})^{\frac{a}{ln(10)}}\f$,
                          ��� ������ ���� ������ �������� a. */
    double TempCoef; /**< ������������� �����������, ����������� �������
                          ����������� �� ������������ �������������� �� �������

                          \f$ H(T) = (1 + TempCoef * (T - RefTemp)) \f$ */
} TLTEDS_INFO_ACCF_TF;

/** ���������� � ���������� �������������/������� ���� */
typedef struct {
    double RefFreq; /**< �������� ������� � ��, �� ������� �������� ���������������� �������
                         � ������������ ������� ����� ���������� ������������ �������������� */
    double RefTemp; /**< �������� ����������� � �������� �������, ��� ������� ��������
                         ���������������� ������� � ������������ ������� ����� ����������
                         ������������� ����������� ��������� */
    TLTEDS_INFO_BASE_CAL Base; /**< ������� ���������� � ������� ���������� ���������� */
} TLTEDS_INFO_ACCF_CALINFO;


/** @brief ���������� � �������������/������� ����

    ��������� �������� ��� ���������� � �������, ������� �������������
    ������������ ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_ACCFORCE. */
typedef struct {
    TLTEDS_INFO_ACCF_MEAS Meas; /**< �������� ��������� ���������� �������� */
    TLTEDS_INFO_ACCF_ELEC ElecSigOut; /**< �������� �������������� ���������� */
    TLTEDS_INFO_ACCF_TF TransfFunc; /**< �������� ������������ ������� */
    TLTEDS_INFO_ACCF_CALINFO CalInfo; /**< ���������� � ���������� */
    WORD MeasLocationID; /**< ���������������� ������������� ����� ���������. */
} TLTEDS_INFO_TMPLT_ACCFORCE;




/***************************************************************************//**
    @brief ���������� ���������� � �������������/������� ���� �� ������ TEDS

    ������� ��������� �������� �� TEDS ����������, ��������������� ������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_ACCFORCE.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_INFO_TMPLT_ACCFORCE.

    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetTmpltInfoAccForce(TLTEDS_DECODE_CONTEXT *ctx,
                                                 TLTEDS_INFO_TMPLT_ACCFORCE *info);

/***************************************************************************//**
    @brief ������ ���������� � �������������/������� ���� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ��������������� ������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_ACCFORCE.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutTmpltInfoAccForce(TLTEDS_ENCODE_CONTEXT *ctx,
                                       const TLTEDS_INFO_TMPLT_ACCFORCE *info);


/** @} */

/***************************************************************************//**
    @addtogroup std_tmpl_hlvout ������ High Level Voltage (30)
    @{
*******************************************************************************/

/** ������ ����������� ��������� ������������� �������� ������� � ������� �� ���������� */
typedef enum {
    LTEDS_INFO_HLV_ELEC_PREC_STD_0_10V = 0, /**< ����������� ������������� ��������
                                                 �������� 0-10 ����� */
    LTEDS_INFO_HLV_ELEC_PREC_STD_PM10V = 1, /**< ����������� ������������� ��������
                                                 �������� \f$\pm10\f$ �����. */
    LTEDS_INFO_HLV_ELEC_PREC_20MV      = 2, /**< �������� ������������ � ����
                                                 ������ ����� � ����� 20 ��. */
    LTEDS_INFO_HLV_ELEC_PREC_FULL      = 3, /**< �������� ������������ ���
                                                 ������������ �����. */
} e_LTEDS_INFO_HLV_ELEC_PRECTYPE;



/** ���������� �� ������������� ��������������� ��������� ���������� �������
    � ������� �� ���������� */
typedef struct {   
    BYTE SigType; /**< ��� �������� �������������� ����������. ������ �����
                       #LTEDS_INFO_ELECSIGTYPE_VOLTAGE_SENSOR ��� ������� ������� */
    TLTEDS_INFO_ELECTRICAL_RANGE Range; /**< �������� ��������� �������������� �������. */    
    BYTE MapMeth; /**< ����� ����������� ���������� �������� �� �������������.
                       ������ ����� #LTEDS_INFO_MAPMETH_LINEAR ��� ������� �������. */
    BOOLEAN AcCoupling; /**< �������, ��������� �� ������� ���������� ������������
                             ��� ��������� ��������� �������. */
    double OutputImpedance; /**< �������� ������������� ������� ��� �����������
                               ������� � ������� � ����. */
    double ResponseTime; /**< ����� ������� � ��������.
                              ���������� �������, � ������� �����
                              �������� �������� ������.
                              �������� ������������� ��� �������� ������ ���������
                              ������� � �� ����������� ������������� ������� ��������
                              ��������� �������������� ������� ������������
                              �����������. */
} TLTEDS_INFO_HLV_ELECTRICAL;



/** ���������� � ������� ������� � ������� �� ���������� */
typedef struct {
    BOOLEAN IsRequired; /**< �������, ��������� �� ������� ��������� �������.
                             ���� ���, �� ��������� ���� �� ����� ��������. */
    BYTE   Type;        /**< ��� ���������� �������. �������� �� #e_LTEDS_INFO_EXCITE_TYPE. */
    TLTEDS_INFO_EXCITATION_LEVELS Levels; /**< ������ ���������� ������� �������. */
    double CurrentDraw; /**< ��������� ���� ���� (������������ ������������ ���)
                             ��� ��������� ������� ��� ����������� ������ �
                             ���������� ��������. */
} TLTEDS_INFO_HLV_POWSUPPLY;

/** @brief ���������� � ������� � ������� �� ����������

    ��������� �������� ��� ���������� � �������, ������� �������������
    ������������ ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_HL_VOLTAGE_OUTPUT. */
typedef struct {
    TLTEDS_INFO_PHYSMEAS_RANGE Meas; /**< ���������� ���������� �������� � ������� ��������. */
    TLTEDS_INFO_HLV_ELECTRICAL ElecSigOut; /**< ��������� ��������� �������������� �������. */
    TLTEDS_INFO_HLV_POWSUPPLY  PowerSupply; /**< ��������� ���������� ������� (���� ���������). */
    TLTEDS_INFO_BASE_CAL       CalInfo; /**< ���������� � ���������� ����������. */
    WORD MeasLocationID; /**< ���������������� ������������� ����� ���������. */
} TLTEDS_INFO_TMPLT_HLVOUT;



/***************************************************************************//**
    @brief ���������� ���������� � ������� � ������� �� ���������� �� ������ TEDS

    ������� ��������� �������� �� TEDS ����������, ��������������� ������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_HL_VOLTAGE_OUTPUT.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_INFO_TMPLT_HLVOUT.

    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetTmpltInfoHLVOut(TLTEDS_DECODE_CONTEXT *ctx,
                                                 TLTEDS_INFO_TMPLT_HLVOUT *info);

/***************************************************************************//**
    @brief ������ ���������� � ������� � ������� �� ���������� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ��������������� ������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_HL_VOLTAGE_OUTPUT.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutTmpltInfoHLVOut(TLTEDS_ENCODE_CONTEXT *ctx,
                                       const TLTEDS_INFO_TMPLT_HLVOUT *info);
/** @} */




/***************************************************************************//**
    @addtogroup std_tmpl_bridge ������ Bridge Sensors (33)
    @{
*******************************************************************************/

/** ��� ����� */
typedef enum {
    LTEDS_INFO_BRIDGE_TYPE_QUARTER = 0, /**< ������������ */
    LTEDS_INFO_BRIDGE_TYPE_HALF    = 1, /**< �������� */
    LTEDS_INFO_BRIDGE_TYPE_FULL    = 2  /**< ������ ���� */
} e_LTEDS_INFO_BRIDGE_TYPE;


/** ������ ����������� ��������� ������������� �������� ��� ������� ��������� ������� */
typedef enum {
    LTEDS_INFO_BRIDGE_ELEC_PREC_11BIT = 0, /**< �� -1 �� +1 � �����  0.001 */
    LTEDS_INFO_BRIDGE_ELEC_PREC_19BIT = 1, /**< �� -6.55E-3 �� 6.55E-3 � ����� 25E-9 */
    LTEDS_INFO_BRIDGE_ELEC_PREC_FULL  = 2, /**< ���������� ������������ ������ � ��������� ������ */
} e_LTEDS_INFO_BRIDGE_ELEC_PRECTYPE;


/** ���������� � ������������� ��������������� ��������� ���������� �������
    � ������� � ���� ����� */
typedef struct {
    BYTE SigType; /**< ��� �������� �������������� ����������. ������ �����
                       #LTEDS_INFO_ELECSIGTYPE_BRIDGE_SENSOR ��� ������� ������� */
    TLTEDS_INFO_ELECTRICAL_RANGE Range; /**< �������� ��������� �������������� �������. */
    BYTE MapMeth; /**< ����� ����������� ���������� �������� �� �������������.
                       ������ ����� #LTEDS_INFO_MAPMETH_LINEAR ��� ������� �������. */
    BYTE BridgeType; /**< ��� �����. �������� �� #e_LTEDS_INFO_BRIDGE_TYPE. */
    double BridgeImpedance; /**< �������� �������������  ������� �������� ����� � ����. */
    double ResponseTime; /**< ����� ������� � ��������.
                              �������� ��������� ������������ ���� �� [TLTEDS_INFO_HLV_ELECTRICAL]
                              (@ref TLTEDS_INFO_HLV_ELECTRICAL::ResponseTime). */
} TLTEDS_INFO_BRIDGE_ELECTRICAL;




/** @brief ���������� ������� ��������� �������.

   ��������� �������� ���������� �� ������� � ���������������
   #LTEDS_STD_TEMPLATE_ID_BRIDGE_SENSOR, ������������ �������� ��������� �������.
   
   ��� ��������� ������������ ������� LTEDS_GetTmpltInfoBridge(). */
typedef struct {
    TLTEDS_INFO_PHYSMEAS_RANGE    Meas; /**< ���������� � ���������� ���������� ��������. */
    TLTEDS_INFO_BRIDGE_ELECTRICAL ElecSigOut; /**< ���������� � �������� ������������� ���������� �������. */
    TLTEDS_INFO_EXCITATION_LEVELS ExcitationLevels; /**< ���������� � ���������� ����������� (�������) �����. */
    TLTEDS_INFO_BASE_CAL CalInfo; /**< ���������� � ���������� ����������. */
    WORD MeasLocationID; /**< ���������������� ������������� ����� ���������. */
} TLTEDS_INFO_TMPLT_BRIDGE;



/***************************************************************************//**
    @brief ���������� ���������� � �������� ������� �� TEDS ������

    ������� ��������� �������� �� TEDS ����������, ������� �������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_BRIDGE_SENSOR � ��������� ��������
    ������� � ������� � ���� ����� �������������.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_INFO_TMPLT_BRIDGE.

    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
    ****************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetTmpltInfoBridge(TLTEDS_DECODE_CONTEXT *ctx,
                                                TLTEDS_INFO_TMPLT_BRIDGE *info);


/***************************************************************************//**
    @brief ������ ���������� � �������� ������� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ���������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_BRIDGE_SENSOR.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
    ****************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutTmpltInfoBridge(TLTEDS_ENCODE_CONTEXT *ctx,
                                                 const TLTEDS_INFO_TMPLT_BRIDGE *info);
/** @} */




/***************************************************************************//**
    @addtogroup std_tmpl_caltbl ������ Calibration Table (40)
    @{
*******************************************************************************/

/** ������������ ���������� ��������� � ������� ���������� */
#define LTEDS_INFO_CALTABLE_DATASET_MAX 127

/** ����� ��������� ��� ������� ����� ���������� */
typedef enum {
    LTEDS_INFO_CAL_DOMAIN_ELECTRICAL = 0, /**< �������� ������������� �������� */
    LTEDS_INFO_CAL_DOMAIN_PHYSICAL   = 1  /**< �������� ���������� �������� */
} e_LTEDS_CAL_DOMAIN;


/** @brief ����� �� ������� ����������

    ���������, ���������� ����� �� ���� ��������, ������������ ����������
    �������������� �������� �� ������������ � ��������� �����. */
typedef struct {
    double DomainValue; /**< �������� �������� (���������� ��� �������������, �
                            ����������� �� ���������� ������), ��� ������� �������
                            ������������� ��������. �������� � ��������� ��
                            ������� ���������. */
    double RangeDeviation; /**< ���������� �� ����������� �������� ������������
                            ������� � ��������� �� �����. */
} TLTEDS_INFO_CALTABLE_DATASET;


/** @brief ���������� ������� ������� ����������

   ��������� �������� ���������� �� ������� � ���������������
   #LTEDS_STD_TEMPLATE_ID_CAL_TABLE.

    � ��������� ������������ ������ ������������� �������, ����������� ������������
    ������� �������������� ����� �������������� � ����������� ����������.
    ������ ����� ������� ��������� ��� ������������� �������� �������� ����������
    �� ����������� �������� �������������� � ��������� �����.

    ��� ��������� ������������ ������� LTEDS_GetTmpltInfoCalTable(). */
typedef struct {
    BYTE Domain; /**< �����, ������������ ����� �������� ������������ ��� �������
                      �����, ��� ������������� ����������. �������� ��
                      #e_LTEDS_CAL_DOMAIN. */
    BYTE DataSetCount; /**< ���������� ����� ����������. ���������� ����������
                            �������������� ��������� � �������
                            [DataSets](@ref TLTEDS_INFO_TMPLT_CAL_TABLE::DataSets). */
    /** ����� ����� ����������. ������������� ������
       [DataSetCount](@ref TLTEDS_INFO_TMPLT_CAL_TABLE::DataSetCount) ���������. */
    TLTEDS_INFO_CALTABLE_DATASET DataSets[LTEDS_INFO_CALTABLE_DATASET_MAX];
} TLTEDS_INFO_TMPLT_CAL_TABLE;



/***************************************************************************//**
    @brief ����������  ������������� ������� �� ������ TEDS

    ������� ��������� �������� �� TEDS ����������, ��������������� ������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_CAL_TABLE.

    ���������� ������������ � ���� ��������� ���� #TLTEDS_INFO_TMPLT_CAL_TABLE
    @param[in]   ctx      �������� ������� ������ TEDS.
    @param[out]  info     ���������, � ������� ������������ ���������� ����������.
    @return               ��� ������.
********************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_GetTmpltInfoCalTable(TLTEDS_DECODE_CONTEXT *ctx,
                                                   TLTEDS_INFO_TMPLT_CAL_TABLE *info);

/***************************************************************************//**
    @brief ������ ���������� � �������� ������� � ������ TEDS

    ������� ��������� ������������ � TEDS ����������, ���������������
    ������� � ��������������� #LTEDS_STD_TEMPLATE_ID_CAL_TABLE.

    @param[in]   ctx      �������� ����������� ������ TEDS.
    @param[in]   info     ���������, ���������� ������������ ����������.
    @return               ��� ������.
    ****************************************************************************/
LTEDSAPI_DllExport(INT) LTEDS_PutTmpltInfoCalTable(TLTEDS_ENCODE_CONTEXT *ctx,
                                                   const TLTEDS_INFO_TMPLT_CAL_TABLE *info);
/** @} */

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif // LTEDSAPI_STDTMPL_H
