#include "typewise-alert.h"
#include <stdio.h>

int limits[3][3] = {{0,35}, {0,45}, {0,40}};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

/*Limits PASSIVE_COOLING(){
  Limits limit;
  limit.lowerLimit = 0;
  limit.upperLimit = 35;
  return limit;
}

Limits HI_ACTIVE_COOLING(){
  Limits limit;
  limit.lowerLimit = 0;
  limit.upperLimit = 45;
  return limit;
}

Limits MED_ACTIVE_COOLING(){
  Limits limit;
  limit.lowerLimit = 0;
  limit.upperLimit = 40;
  return limit;
}*/

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = limits[coolingType][LOWERLIMITIDX];
  int upperLimit = limits[coolingType][UPPERLIMITIDX];
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
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
