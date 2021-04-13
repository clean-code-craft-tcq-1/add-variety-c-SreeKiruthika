#include "breach.h"
#include <stdio.h>


/*Declaration for low and high limits along with types of cooling*/
BatteryCoolingTypeLimit tempLimits[]={{PASSIVE_COOLING,0,35},{HI_ACTIVE_COOLING,0,45},{MED_ACTIVE_COOLING,0,40}};


/****************************************************************************************
*Func desc : This function check if the passed value  value is within the specified range of lower and upper limit
*Param     : value      - The measured  value, whose limits are to be verified         - double type
			 lowerLimit - the lower limit against which value breach is to be verified - double type
			 upperLimit - the upper limit against which value breach is to be verified - double type
*Return    : Returns the status of value breach - enum BreachType
*****************************************************************************************/
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) 
  {
    return TOO_LOW;
  }
  if(value > upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

/****************************************************************************************
*Func desc : This function check for the cooling type and evaluates breach type for the value passed 
*Param     : coolingType    - The type of cooling which occurs in the system         - CoolingType type
			 temperatureInC - the measured temperature value                         - double type
*Return    : Returns the status of value breach - enum BreachType
*****************************************************************************************/
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  return inferBreach(temperatureInC, tempLimits[coolingType].lowerLimit, tempLimits[coolingType].upperLimit);
}
