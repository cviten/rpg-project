#ifndef HUDTEST
#define HUDTEST

#include "commontest.h"
#include "../hud.h"

// #include <gtest/gtest.h>

TEST(HUDMeter, Construction) {
  Meter meterWithoutParams;
  EXPECT_EQ(meterWithoutParams.min, 0);
  EXPECT_EQ(meterWithoutParams.max, 100);
  EXPECT_EQ(meterWithoutParams.curr,100);

  Meter meterWithOneParams(50);
  EXPECT_EQ(meterWithOneParams.min, 0);
  EXPECT_EQ(meterWithOneParams.max, 50);
  EXPECT_EQ(meterWithOneParams.curr,50);

  Meter meterWithTwoParams(75,25);
  EXPECT_EQ(meterWithTwoParams.min, 25);
  EXPECT_EQ(meterWithTwoParams.max, 75);
  EXPECT_EQ(meterWithTwoParams.curr,75);

  Meter meterWithThreeParams(-100,100,0);
  EXPECT_EQ(meterWithThreeParams.min, -100);
  EXPECT_EQ(meterWithThreeParams.max, 100);
  EXPECT_EQ(meterWithThreeParams.curr,0);
}
// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest( &argc, argv );
//   return RUN_ALL_TESTS();
// }


#endif /* end of include guard: HUDTEST */
