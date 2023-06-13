/*
 * DistanceSensor.c
*/

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include "IfxPort.h"
#include "Bsp.h"
#include "Ifx_Types.h"
#include "IfxGtm_Tim_In.h"
#include "IfxGtm_Tom_Pwm.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define TRIGGER     &MODULE_P21,2              /* Trigger Pin of HCSR04 sensor  */
#define ECHO        IfxGtm_TIM0_1_P21_3_IN     /* Echo Pin of HCSR04 sensor in input for GTM Timer  */

/* Numeric constants  */
#define TICK2PERIOD     3.33e-9
#define SOUNDSPEED      343.1/2.0

/*********************************************************************************************************************/
/*------------------------------------------------------Variables-------------------------------------------------------*/
/*********************************************************************************************************************/
sint32 measuredTicks = 0.0;             /* Variable for ticks counting     */
IfxGtm_Tim_In g_driverTIM;              /* TIM driver structure            */
float distance = 0.0;                   /* Variable for measured distance  */

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

/* This function initializes the TRIGGER and ECHO pin of HCSR04 along with the GTM Timer */
void initPins(void)
{

    IfxPort_setPinMode(TRIGGER, IfxPort_Mode_outputPushPullGeneral);    /* Initialization of TRIGGER pin            */

    IfxGtm_enable(&MODULE_GTM);                                         /* Enable the GTM                           */
    IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);        /* Enable the CMU clock 0                   */

    IfxGtm_Tim_In_Config configTIM;

    IfxGtm_Tim_In_initConfig(&configTIM, &MODULE_GTM);                  /* Initialize default parameters            */
    configTIM.filter.inputPin = &ECHO;                                  /* Select input port pin                    */
    configTIM.filter.inputPinMode = IfxPort_InputMode_pullDown;         /* Select input port pin mode               */
    IfxGtm_Tim_In_init(&g_driverTIM, &configTIM);                       /* Initialize the TIM                       */
}


/* This function toggles the trigger pin and wait 500 milliseconds */
int triggerSensor(void)
{
    //______________10us burst____________________________________
    /* Trigger pin is initially low */
    IfxPort_setPinState(TRIGGER, IfxPort_State_low);

    /* Wait 2 microseconds */
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER,2));

    /* In order to generate the ultrasound the Trigger pin is set high for 10 microseconds */
    IfxPort_setPinState(TRIGGER, IfxPort_State_high);

    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER,10));

    IfxPort_setPinState(TRIGGER, IfxPort_State_low);


//_____________________________Measure time____________________________________

    /* update measured data */
    IfxGtm_Tim_In_update(&g_driverTIM);

    /* get the elapsed time in number of ticks */
    measuredTicks =  IfxGtm_Tim_In_getPulseLengthTick(&g_driverTIM);

    /* find distance in meters as speed*time */
    distance = (TICK2PERIOD*measuredTicks)*SOUNDSPEED*3;

    /* return distance as int for the print on the led matrix,
     * multiplication by 5 to match matrix functions ranges*/
    return (int)(distance*5) ;


}


