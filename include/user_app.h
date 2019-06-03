#ifndef __USER_APP_H
#define __USER_APP_H

#include "main.h"
#include "user_uart.h"
#include "user_adc.h"
#include "user_dac.h"
#include "user_time.h"
#include "stm32f1xx_hal_flash_ex.h"
#include "stm32f1xx_hal_flash.h"


/* Private function prototypes -----------------------------------------------*/

#define LOG printf


extern I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);


#define PowerCh     DAC_CHANNEL_1
#define TiggerOUT1  xxxxx
#define TiggerOUT2  xxxxxx

typedef enum 
{
  SetVoltage=0x00U,
	SetCurrent,
	SetOutputON,
	SetOutputOFF,
	GetOutputVoltage,
	GetOutputCurrent,
	SetTtiggerON,
	SetTriggerOFF,
} PowerBoardCMD;

typedef enum 
{
  OutputCh1=0x00U,
	TriggerOUT1,
	TriggerOUT2,
}ChanneNameDef;


typedef enum
{
 CV=0x00U,
 CC,
 CM
}WorkMode;

typedef struct
{
  uint8_t CVchangeFlag;
	uint8_t CCchangeFLag;
	uint8_t DutyChangeFLag;
	uint8_t FreqencyChangeFLag;
	uint8_t DelayTimeChangeFLag;
}Statusdef;

typedef struct
{
	ChanneNameDef OutputChannel;
	WorkMode mode;
	uint16_t voltage;
	uint16_t Current;
	uint16_t Duty;
	uint16_t Frequency;
	uint16_t DelayTime;
	uint16_t OP1offset;
	uint16_t OP2offset;
	Statusdef Status;
}PowerSettingDef;

// load Flash saving data, setting default setting or last setting
ErrorStatus LoadDefaultSetting(void);

//Power board CMD support
ErrorStatus WorkingCmd(PowerBoardCMD cmd);

//CV and CC 
ErrorStatus VoltageSetting(uint32_t Data);
ErrorStatus CurrentSetting(uint16_t value);
uint16_t    GetOutputVol(ChanneNameDef ch);
uint16_t    GetOutputCur(ChanneNameDef ch);

//Measuring
uint16_t    MeasureVoltage(ADC_HandleTypeDef ADCname);
uint16_t    MeasureCurrent(ADC_HandleTypeDef ADCname);

//Calibration
uint16_t    VoltageCali(ChanneNameDef ch);
uint16_t    CurrentCali(ChanneNameDef ch);

ErrorStatus SetDuty(uint16_t duty);
ErrorStatus SetFrequency(uint16_t Freq);
uint16_t    GetDuty(ChanneNameDef ch);
uint16_t    GetFrequency(ChanneNameDef ch);

ErrorStatus    SetDelayTime(uint16_t Delaytime);

//Trigger out
ErrorStatus SetTiggerCmd(uint8_t ch,PowerBoardCMD cmd);
ErrorStatus SetTiggerOutDelay(uint16_t DelayTime);

void PowerSet(PowerSettingDef pra );
ErrorStatus ReadSettingFromFlash(void);
uint8_t SaveSettingToFlash(PowerSettingDef pra);
void PowerSettingCheck(void);
ErrorStatus LoadFlashSetting(PowerSettingDef pra);
void PowerMonitor(void);

#endif
