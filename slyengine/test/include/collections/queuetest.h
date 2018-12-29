#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/queue.h"


using namespace sly;

class CollectionsQueueTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsQueueTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsQueueTest() {
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

TEST_F(CollectionsQueueTest, enqueue) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsQueueTest, dequeue) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list.dequeue());
    EXPECT_EQ(ITEM_ADD_COUNT - 1, list.count());
}

TEST_F(CollectionsQueueTest, peek) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list.peek());
}

TEST_F(CollectionsQueueTest, count) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(list.count());
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsQueueTest, getIterator) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(list.count());

    Iterator<s32> iter = list.getIterator();
}

TEST_F(CollectionsQueueTest, iternatorMoveNext) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        count++;
    }

    EXPECT_EQ(count, list.count());
}

TEST_F(CollectionsQueueTest, iteratorCurrent) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    Queue<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.enqueue(list.count());

    auto iter = list.getIterator();

    s32 count = 0;

    while(iter.moveNext())
    {
        EXPECT_EQ(count, iter.current());
        EXPECT_EQ(count, *iter);
        count++;
    }

    EXPECT_EQ(count, list.count());
}
