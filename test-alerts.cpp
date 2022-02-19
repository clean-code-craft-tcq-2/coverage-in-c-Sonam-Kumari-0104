#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(20, 10, 15) == TOO_HIGH);
  REQUIRE(inferBreach(15, 10, 20) == NORMAL);
}

TEST_CASE("Evaluate the breach type and send alerts") {
  AlertTarget a1 = TO_EMAIL;
  BatteryCharacter b;
  b.coolingType = PASSIVE_COOLING;
 REQUIRE(checkAndAlert( a1, b.coolingType, 40));
}
