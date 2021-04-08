#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "breach.h"

/*test cases for breach check along with different cooling types*/
TEST_CASE("infers the breach Passive cooling - normal")
{
   REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
}

TEST_CASE("infers the breach medium active cooling - low")
{
   REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
}

TEST_CASE("infers the breach High active cooling - high")
{
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 47) == TOO_HIGH);
}

/*Test cases for alert functions */
TEST_CASE("When INVALID target is sent")
{
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(NUM_OF_TARGETS, batteryChar, 47) == INVALID_TARGET);
}

TEST_CASE("When breach infered is NORMAL and no alert is needed")
{
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 30) == NO_BREACH);
}

TEST_CASE("When breach infered is TOO_LOW and EMAIL alert triggered")
{
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, -1) == BREACH_ALERTED);
}

TEST_CASE("When breach infered is TOO_HIGH and EMAIL alert triggered")
{
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 70) == BREACH_ALERTED);
}

TEST_CASE("When breach infered is TOO_LOW and CONSOLE alert triggered")
{
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_CONSOLE, batteryChar, -5) == BREACH_ALERTED);
}

TEST_CASE("When breach infered is TOO_HIGH and CONSOLE alert triggered")
{
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_CONSOLE, batteryChar, 70) == BREACH_ALERTED);
}

TEST_CASE("When breach infered is TOO_LOW and CONTROLLER alert triggered")
{
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, -100) == BREACH_ALERTED);
}

TEST_CASE("When breach infered is TOO_HIGH and CONTROLLER alert triggered")
{
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "BOSCH_RBEI"};	
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 60) == BREACH_ALERTED);
}

/*To validate invalid breach type passed to ALERT via mail and console */
TEST_CASE("When breach infered is NORMAL (this is used as invalid alert value) and alert is  triggered")
{
  REQUIRE(sendToConsole(NORMAL) == BREACH_ALERTFAIL);	
  REQUIRE(sendToEmail(NORMAL) == BREACH_ALERTFAIL);
}