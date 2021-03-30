#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "breach.h"

TEST_CASE("infers the breach Passive cooling - normal")
{
	BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_CONTROLLER,batteryChar, 30);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("infers the breach medium active cooling - normal")
{
	BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_CONTROLLER,batteryChar, 15);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 15) == NORMAL);
}

TEST_CASE("infers the breach high active cooling - normal")
{
	BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_CONTROLLER,batteryChar, 10);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 10) == NORMAL);
}

TEST_CASE("infers the breach Passive cooling - low")
{
	BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_CONTROLLER,batteryChar, -100);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -100) == TOO_LOW);
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
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1) == TOO_LOW);
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
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 41) == TOO_HIGH);
}

TEST_CASE("infers the breach Passive cooling - high")
{
	BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH"};
	checkAndAlert(TO_EMAIL,batteryChar, 100);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 100) == TOO_HIGH);
}
