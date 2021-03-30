#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach Passive cooling - normal")
{
	BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_CONTROLLER,batteryChar, 30);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("infers the breach medium active cooling - low")
{
	BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_SIEMENS"};
	checkAndAlert(TO_CONTROLLER,batteryChar, -5);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
}

TEST_CASE("infers the breach High active cooling - low")
{
	BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BOSCH_RBEI"};
	checkAndAlert(TO_EMAIL,batteryChar, -1);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 41) == TOO_LOW);
}

TEST_CASE("infers the breach medium active cooling - high")
{
	BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_SIEMENS"};
	checkAndAlert(TO_CONTROLLER ,batteryChar, 60);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 60) == TOO_HIGH);
}

TEST_CASE("infers the breach High active cooling - high")
{
	BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BOSCH_RBEI"};
	checkAndAlert(TO_EMAIL,batteryChar, 41);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 41) == TOO_HIGH);
}
