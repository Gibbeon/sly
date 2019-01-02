#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/map.h"


using namespace sly;

class CollectionsMapTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsMapTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsMapTest() {
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

TEST_F(CollectionsMapTest, add) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list[0]);
    EXPECT_EQ(ITEM_TO_ADD, list[ITEM_ADD_COUNT / 2]);
    EXPECT_EQ(ITEM_TO_ADD, list[ITEM_ADD_COUNT - 1]);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsMapTest, remove) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    // remove head
    list.remove(0);
    EXPECT_EQ(ITEM_ADD_COUNT-1, list.count());

    EXPECT_EQ(4, list[4]);
    EXPECT_EQ(1, list[1]);

    // remove mid
    list.remove(2);
    EXPECT_EQ(ITEM_ADD_COUNT-2, list.count());
    
    EXPECT_EQ(4, list[4]);
    EXPECT_EQ(1, list[1]);

    // remove tail
    list.remove(4);
    EXPECT_EQ(ITEM_ADD_COUNT-3, list.count());
    EXPECT_EQ(1, list[1]);

    list.remove(1);
    list.remove(3);

    EXPECT_EQ(0, list.count());
}

TEST_F(CollectionsMapTest, get) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, ITEM_TO_INSERT3);

    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        EXPECT_EQ(ITEM_TO_INSERT3, list.get(i));
}

TEST_F(CollectionsMapTest, set) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT1 = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    list.set(0, ITEM_TO_INSERT1);
    list.set(2, ITEM_TO_INSERT2);
    list.set(list.count()-1, ITEM_TO_INSERT3);

    EXPECT_EQ(ITEM_TO_INSERT1, list.get(0));
    EXPECT_EQ(ITEM_TO_INSERT2, list.get(2));
    EXPECT_EQ(ITEM_TO_INSERT3, list.get(list.count()-1));
}

TEST_F(CollectionsMapTest, clear) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    list.clear();

    EXPECT_EQ(0, list.count());
}

TEST_F(CollectionsMapTest, operatorAssignment) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr int ITEM_SET_VALUE = 32;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    EXPECT_EQ(3, list[3]);

    list[3] = ITEM_SET_VALUE;
    EXPECT_EQ(ITEM_SET_VALUE, list.get(3));
    EXPECT_EQ(ITEM_SET_VALUE, list[3]);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsMapTest, count) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsMapTest, getIterator) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    Iterator<Pair<s32, s32>> iter = list.getIterator();
}

TEST_F(CollectionsMapTest, iteratorMoveNext) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

TEST_F(CollectionsMapTest, iteratorCurrent) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Map<s32, s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(i, list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        EXPECT_EQ(list[count], iter.current().value);
        EXPECT_EQ(list[count], (*iter).value);
        count++;
    }

    EXPECT_EQ(count, list.count());
}
