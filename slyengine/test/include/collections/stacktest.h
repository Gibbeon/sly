#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/stack.h"


using namespace sly;

class CollectionsStackTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsStackTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsStackTest() {
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

TEST_F(CollectionsStackTest, push) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsStackTest, pop) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list.pop());
    EXPECT_EQ(ITEM_ADD_COUNT - 1, list.count());
}

TEST_F(CollectionsStackTest, peek) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_ADD = 10;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(ITEM_TO_ADD - i);

    EXPECT_EQ(ITEM_TO_ADD - ITEM_ADD_COUNT + 1, list.peek());
}

TEST_F(CollectionsStackTest, count) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(list.count());
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsStackTest, getIterator) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(list.count());

    Iterator<s32> iter = list.getIterator();
}

TEST_F(CollectionsStackTest, iternatorMoveNext) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

TEST_F(CollectionsStackTest, iteratorCurrent) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Stack<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.push(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        EXPECT_EQ(list.count() - count - 1, iter.current());
        EXPECT_EQ(list.count() - count - 1, *iter);
        count++;
    }

    EXPECT_EQ(count, list.count());
}
