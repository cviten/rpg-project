#ifndef CHARACTERTEST
#define CHARACTERTEST

#include "commontest.h"
#include "../character.h"


TEST(ValueContainer, Construction) {
  Container oneParam(100);
  EXPECT_EQ(oneParam.getMax(), 100);
  EXPECT_EQ(oneParam.getCurrent(), 100);

  Container twoParams(75,25);
  EXPECT_EQ(twoParams.getMax(), 75);
  EXPECT_EQ(twoParams.getCurrent(), 25);
}

TEST(ValueContainer, simpleContainer) {
  Container simpleContainer(100, 50);
  EXPECT_EQ(simpleContainer.getCurrent(), 50);
  EXPECT_EQ(simpleContainer.getMax(), 100);
  simpleContainer.take(25);
  EXPECT_EQ(simpleContainer.getCurrent(), 25);
  simpleContainer.give(50);
  EXPECT_EQ(simpleContainer.getCurrent(), 75);
}

TEST(ValueContainer, notOverflowContainer) {
  Container notOverflowContainer(100, false);
  EXPECT_EQ(notOverflowContainer.getCurrent(), 100);
  EXPECT_EQ(notOverflowContainer.getMax(), 100);
  notOverflowContainer.take(50);
  EXPECT_EQ(notOverflowContainer.getCurrent(), 50);
  EXPECT_EQ(notOverflowContainer.getMax(), 100);
  notOverflowContainer.give(100);
  EXPECT_EQ(notOverflowContainer.getCurrent(), 100);
  EXPECT_EQ(notOverflowContainer.getMax(), 100);
}

TEST(ValueContainer, overflowContainer) {
  Container overflowContainer(100, true);
  EXPECT_EQ(overflowContainer.getCurrent(), 100);
  EXPECT_EQ(overflowContainer.getMax(), 100);
  overflowContainer.take(50);
  EXPECT_EQ(overflowContainer.getCurrent(), 50);
  EXPECT_EQ(overflowContainer.getMax(), 100);
  overflowContainer.give(100);
  EXPECT_EQ(overflowContainer.getCurrent(), 150);
  EXPECT_EQ(overflowContainer.getMax(), 100);
}

TEST(ValueContainer, notOverZeroContainer) {
  Container notOverZeroContainer(100, false);
  EXPECT_EQ(notOverZeroContainer.getCurrent(), 100);
  notOverZeroContainer.take(200);
  EXPECT_EQ(notOverZeroContainer.getCurrent(), 0);
}

TEST(ValueContainer, overZeroContainer) {
  Container overZeroContainer(100, true);
  EXPECT_EQ(overZeroContainer.getCurrent(), 100);
  overZeroContainer.take(200);
  EXPECT_EQ(overZeroContainer.getCurrent(), 0);
}

#endif /* end of include guard: CHARACTERTEST */
