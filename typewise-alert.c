#include "typewise-alert.h"
#include <stdio.h>

int limits[NUMBEROFCOOLINGTYPES][NUMBEROFTEMPLIMITS] = {{0,35}, {0,45}, {0,40}};
char alertMsgForEmail[NUMBEROFBREACHTYPES][100] = {"Hi, the temperature is Normal\n"
                                                   "Hi, the temperature is too low\n",
                                                   "Hi, the temperature is too High\n"};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

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

void printRecepientAndAlertMsg(const char* receiver, char alertMsg[]){
  printf("To: %s\n", receiver);
  printf("%s", alertMsg[breachType]);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printRecepientAndAlertMsg(recepient, alertMsgForEmail[breachType]);
}
