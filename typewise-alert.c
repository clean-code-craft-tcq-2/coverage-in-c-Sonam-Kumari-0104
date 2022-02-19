#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

Limits PASSIVE_COOLING(CoolingType coolingType){
  Limits limit;
  limit.lowerlimit = 0;
  limit.upperLimit = 35;
}

Limits HI_ACTIVE_COOLING(CoolingType coolingType){
  Limits limit;
  limit.lowerlimit = 0;
  limit.upperLimit = 45;
}

Limits MED_ACTIVE_COOLING(CoolingType coolingType){
  Limits limit;
  limit.lowerlimit = 0;
  limit.upperLimit = 40;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  Limits getLimit = coolingType();
  return inferBreach(temperatureInC, getLimit.lowerLimit, getLimit.upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
