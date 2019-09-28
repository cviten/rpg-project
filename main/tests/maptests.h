#ifndef MAPTEST
#define MAPTEST

#include "commontest.h"
#include "../map.h"

TEST(Map, Construction) {
  Map mapWithoutParams;
  GridSize size1 = mapWithoutParams.getMapSize();
  EXPECT_EQ(size1.x, 10);
  EXPECT_EQ(size1.y, 10);

  Map mapWithOneParams(GridSize(5,15));
  GridSize size2= mapWithOneParams.getMapSize();
  EXPECT_EQ(size2.x, 5);
  EXPECT_EQ(size2.y, 15);

  EXPECT_THROW({Map wrongMap1(GridSize(-1,2));}, std::bad_alloc);
  EXPECT_THROW({Map wrongMap2(GridSize(4,-7));}, std::bad_alloc);
  EXPECT_THROW({Map wrongMap3(GridSize(5,0));}, MapException);
}




#endif /* end of include guard: MAPTEST */
