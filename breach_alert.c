#include "breach.h"
#include "libfunc.h"
#include <stdio.h>


/*alert functions declared for available alert types*/
tempAlerter_funcPtr tempAlertFunc[]= {sendToController,sendToEmail,sendToConsole};

/****************************************************************************************
*Func desc : This function check for the temperature breach does appropriate alert actions
*Param     : alertTarget      - the alerting target type
             batteryCharacter - The battery characteristing defining strcuture
			 temperatureInC   - the measured temperature value                         
*Return    : Returns alert check status (BREACH_ALERTFAIL by default if not evaluated)
*****************************************************************************************/
int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{

  int retval = BREACH_ALERTFAIL;

  if(alertTarget >= NUM_OF_TARGETS)
  {
	  retval = INVALID_TARGET;
  }
  else
  {
	BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    
    if(breachType != NORMAL)
    {	  
	   retval = tempAlertFunc[alertTarget](breachType);
    }
    else
    {
    	retval = NO_BREACH;
    }
  }
  return retval;

}

/****************************************************************************************
*Func desc : This function does controller alert based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : Returns if alert is success or not
*****************************************************************************************/
int sendToController(BreachType breachType) 
{
  float alert_voltage[NUM_BREACH]={0,3.2,5};
  
  const unsigned short pin_number = TEMP_ALERT_OUTPIN;
  
  pin_status = DigitalPin_Set(TEMP_ALERT_OUTPIN, alert_voltage[breachtype]);
  
  if(pin_status == OUTPIN_SET)
  {
     return BREACH_ALERTED;
  }
  else
  {
	 return BREACH_ALERTFAIL;
  }
}

/****************************************************************************************
*Func desc : This function does email alert based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : Returns if alert is success or not
*****************************************************************************************/
int sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  const char* sender = "z.y@x.com";
  int retval;
  int mail_status = MAIL_NOTSENT;
  switch(breachType) 
  {
    case TOO_LOW:
	  mail_status = email_send(sender, recepient, "Hi, the temperature is too low\n");      
      break;
    case TOO_HIGH:
      mail_status =  email_send(sender, recepient, "Hi, the temperature is too high\n");
    break;
  }
  
  retval = (mail_status == MAIL_SENT) ? BREACH_ALERTED : BREACH_ALERTFAIL;
  
  return retval;
}

/****************************************************************************************
*Func desc : This function does passess alert messages to console based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : Returns if alert is success or not
*****************************************************************************************/
int sendToConsole(BreachType breachType) 
{
  int retval = BREACH_ALERTFAIL;
  switch(breachType) 
  {
    case TOO_LOW:
      printf("Hi, the temperature is too low\n");
	  retval = BREACH_ALERTED;
      break;
    case TOO_HIGH:
      printf("Hi, the temperature is too high\n");
	  retval = BREACH_ALERTED;
    break;
  }
  return retval;
}