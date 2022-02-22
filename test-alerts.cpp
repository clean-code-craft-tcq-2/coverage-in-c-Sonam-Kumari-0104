#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(20, 10, 15) == TOO_HIGH);
  REQUIRE(inferBreach(15, 10, 20) == NORMAL);
}

TEST_CASE("Classify the cooling type and infer the breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -4) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 42) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -2) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 42) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 51) == TOO_HIGH);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -4) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 38) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
}

TEST_CASE("Evaluate the breach type and send alerts") {
  AlertTarget alert_target = TO_EMAIL;
  BatteryCharacter batteryChracteristics;
  batteryChracteristics.coolingType = PASSIVE_COOLING;
  checkAndAlert( alert_target, batteryChracteristics, 40);
  assert(emailAlertCntr==1);
   
  alert_target = TO_CONTROLLER;
  batteryChracteristics.coolingType = PASSIVE_COOLING;
  checkAndAlert( alert_target, batteryChracteristics, -2);
  assert(controllerAlertCntr==1);
  
  alert_target = TO_EMAIL;
  batteryChracteristics.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChracteristics, 20);
  assert(emailAlertCntr==2);
  
  alert_target = TO_CONTROLLER;
  batteryChracteristics.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChracteristics, 50);
  assert(controllerAlertCntr==2);
}
