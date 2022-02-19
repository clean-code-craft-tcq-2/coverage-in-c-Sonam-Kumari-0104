#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(20, 10, 15) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(15, 10, 20) == TOO_LOW);
}
