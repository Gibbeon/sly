#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/list.h"


using namespace sly;

class CollectionsListTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsListTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsListTest() {
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

TEST_F(CollectionsListTest, add) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list[0]);
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsListTest, addRange)
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    
    List<s32> list;

    list.addRange(ITEM_RANGE, ITEM_ADD_COUNT);
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());

    for(s32 index = 0; index < ITEM_ADD_COUNT; index++)
        EXPECT_EQ(ITEM_RANGE[index], list.get(index));

    list.addRange(ITEM_RANGE, ITEM_ADD_COUNT);    
    for(s32 index = ITEM_ADD_COUNT; index < ITEM_ADD_COUNT * 2; index++)
        EXPECT_EQ(ITEM_RANGE[index - ITEM_ADD_COUNT], list.get(index));
}

TEST_F(CollectionsListTest, remove) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    // remove head
    list.remove(0);
    EXPECT_EQ(4, list.count());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(4, list[list.count()-1]);

    // remove mid
    list.remove(2);
    EXPECT_EQ(3, list.count());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(4, list[list.count()-1]);

    // remove tail
    list.remove(list.count() - 1);
    EXPECT_EQ(2, list.count());
    EXPECT_EQ(1, list[0]);
    EXPECT_EQ(2, list[list.count()-1]);

    for(int i = 0; i < list.count();)
        list.remove(0);

    EXPECT_EQ(0, list.count());
}

TEST_F(CollectionsListTest, insert) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;

    List<s32> list;

    list.insert(0, ITEM_TO_INSERT);
    EXPECT_EQ(ITEM_TO_INSERT, list.get(0));

    list.clear();
    EXPECT_EQ(0, list.count());
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    //head
    list.insert(0, ITEM_TO_INSERT);
    EXPECT_EQ(ITEM_TO_INSERT, list.get(0));

    //mid
    list.insert(5, ITEM_TO_INSERT2);
    EXPECT_EQ(ITEM_TO_INSERT2, list.get(5));

    //tail
    list.insert(list.count(), ITEM_TO_INSERT3);
    EXPECT_EQ(ITEM_TO_INSERT3, list.get(list.count() - 1));
}

TEST_F(CollectionsListTest, get) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(ITEM_TO_INSERT3);

    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        EXPECT_EQ(ITEM_TO_INSERT3, list.get(i));
}

TEST_F(CollectionsListTest, set) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT1 = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list.set(0, ITEM_TO_INSERT1);
    list.set(2, ITEM_TO_INSERT2);
    list.set(list.count()-1, ITEM_TO_INSERT3);

    EXPECT_EQ(ITEM_TO_INSERT1, list.get(0));
    EXPECT_EQ(ITEM_TO_INSERT2, list.get(2));
    EXPECT_EQ(ITEM_TO_INSERT3, list.get(list.count()-1));
}

TEST_F(CollectionsListTest, clear) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list.clear();

    EXPECT_EQ(0, list.count());
}

TEST_F(CollectionsListTest, ensure) 
{
    constexpr int ITEM_ENSURE_COUNT1 = 497;
    constexpr int ITEM_ENSURE_COUNT2 = 5;
    constexpr int ITEM_ENSURE_COUNT3 = 1002;
    constexpr int ITEM_ENSURE_COUNT4 = 87;

    List<s32> list;

    list.ensure(ITEM_ENSURE_COUNT1);
    EXPECT_LE(ITEM_ENSURE_COUNT1, list.capacity());
    EXPECT_EQ(0, list.count());

    list.ensure(ITEM_ENSURE_COUNT2);
    EXPECT_LE(ITEM_ENSURE_COUNT2, list.capacity());
    EXPECT_EQ(0, list.count());

    list.ensure(ITEM_ENSURE_COUNT3);
    EXPECT_LE(ITEM_ENSURE_COUNT3, list.capacity());
    EXPECT_EQ(0, list.count());

    list.ensure(ITEM_ENSURE_COUNT4);    
    EXPECT_LE(ITEM_ENSURE_COUNT4, list.capacity());
    EXPECT_EQ(0, list.count());
}

TEST_F(CollectionsListTest, operatorAssignment) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr int ITEM_SET_VALUE = 32;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    EXPECT_EQ(3, list[3]);

    list[3] = ITEM_SET_VALUE;
    EXPECT_EQ(ITEM_SET_VALUE, list.get(3));
    EXPECT_EQ(ITEM_SET_VALUE, list[3]);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsListTest, count) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsListTest, capacity) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr int ITEM_ENSURE_VALUE = 500;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    EXPECT_LT(0, list.capacity());

    list.ensure(ITEM_ENSURE_VALUE);
    EXPECT_LE(ITEM_ENSURE_VALUE, list.capacity());
}

TEST_F(CollectionsListTest, getIterator) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    List<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    Iterator<s32> iter = list.getIterator();
}


TEST_F(CollectionsListTest, iternatorMoveNext) 
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

TEST_F(CollectionsListTest, iteratorCurrent) 
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

    EXPECT_EQ(count, list.count());
}