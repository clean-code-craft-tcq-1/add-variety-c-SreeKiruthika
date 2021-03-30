#include "breach.h"
#include <stdio.h>


/*alert functions declared for available alert types*/
tempAlerter_funcPtr tempAlertFunc[]= {sendToController,sendToEmail};

/****************************************************************************************
*Func desc : This function check for the temperature breach does appropriate alert actions
*Param     : alertTarget      - the alerting target type
             batteryCharacter - The battery characteristing defining strcuture
			 temperatureInC   - the measured temperature value                         
*Return    : None
*****************************************************************************************/
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  tempAlertFunc[alertTarget](breachType);

}

/****************************************************************************************
*Func desc : This function does controller alert based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : None
*****************************************************************************************/
void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

/****************************************************************************************
*Func desc : This function does email alert based on passed breach type
*Param     : breachType  - the type of breach occured in the system                
*Return    : None
*****************************************************************************************/
void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  switch(breachType) 
  {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
    break;
  }
}
