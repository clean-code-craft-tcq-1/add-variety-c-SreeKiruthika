#include "breach.h"
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
*Return    : None
*****************************************************************************************/
int sendToController(BreachType breachType) 
{
  int retval;
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  retval = BREACH_ALERTED;
  return retval;
}

/****************************************************************************************
*Func desc : This function does email alert based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : None
*****************************************************************************************/
int sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  int retval = BREACH_ALERTFAIL;
  switch(breachType) 
  {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
	  retval = BREACH_ALERTED;
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
	  retval = BREACH_ALERTED;
    break;
  }
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