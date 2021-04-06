#pragma once

#define ALERT_FAIL 0
#define ALERT_SUCCESS 1
#define ALERT_NOTNEEDED 2
#define INVALID_TARGET 255

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE,
  NUM_OF_TARGETS
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


int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

typedef int (*tempAlerter_funcPtr)(BreachType breachType);
int sendToController(BreachType breachType);
int sendToEmail(BreachType breachType);
int sendToConsole(BreachType breachType);

