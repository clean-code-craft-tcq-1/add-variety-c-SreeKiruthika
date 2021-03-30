#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct
{
	CoolingType coolingType;
	int lowerLimit;
	int upperLimit;
}BatteryCoolingTypeLimit;

BatteryCoolingTypeLimit tempLimits[]={{PASSIVE_COOLING,0,35},{HI_ACTIVE_COOLING,0,45},{MED_ACTIVE_COOLING,0,40}};

	

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void (*tempAlerter_funcPtr)();
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
