#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/array.h"

using namespace sly;

class CollectionsArrayTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsArrayTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsArrayTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
};

TEST_F(CollectionsArrayTest, get) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);
        
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        EXPECT_EQ(ITEM_RANGE[i], list.get(i));
}

TEST_F(CollectionsArrayTest, set) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);

    constexpr s32 ITEM_TO_INSERT1 = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;

    list.set(0, ITEM_TO_INSERT1);
    list.set(2, ITEM_TO_INSERT2);
    list.set(list.count()-1, ITEM_TO_INSERT3);

    EXPECT_EQ(ITEM_TO_INSERT1, list.get(0));
    EXPECT_EQ(ITEM_TO_INSERT2, list.get(2));
    EXPECT_EQ(ITEM_TO_INSERT3, list.get(list.count()-1));
    
    EXPECT_EQ(ITEM_TO_INSERT2, ITEM_RANGE[2]);
}

TEST_F(CollectionsArrayTest, operatorAssignment) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_SET_VALUE = 32;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);

    EXPECT_EQ(ITEM_RANGE[3], list[3]);

    list[3] = ITEM_SET_VALUE;
    EXPECT_EQ(ITEM_SET_VALUE, list.get(3));
    EXPECT_EQ(ITEM_SET_VALUE, list[3]);
    EXPECT_EQ(ITEM_SET_VALUE, ITEM_RANGE[3]);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsArrayTest, count) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsArrayTest, getIterator) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);

    Iterator<s32> iter = list.getIterator();
}


TEST_F(CollectionsArrayTest, iternatorMoveNext) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);
    
    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

TEST_F(CollectionsArrayTest, iteratorCurrent) 
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    Array<s32> list(ITEM_RANGE, ITEM_ADD_COUNT);

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        EXPECT_EQ(list[count], iter.current());
        EXPECT_EQ(list[count], *iter);
        count++;
    }

    EXPECT_EQ(count, list.count());
}
