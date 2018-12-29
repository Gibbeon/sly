#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/list.h"


using namespace sly;

class CollectionsIteratorTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsIteratorTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsIteratorTest() {
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

TEST_F(CollectionsIteratorTest, moveNext) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

TEST_F(CollectionsIteratorTest, current) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        EXPECT_EQ(list[count], iter.current());
        EXPECT_EQ(list[count], *iter);
        count++;
    }
}

TEST_F(CollectionsIteratorTest, operatorIncrement) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(++iter)
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

