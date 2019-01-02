#include "gtest/gtest.h"
#include "sly/global.h"
#include "sly/collections/linkedlist.h"


using namespace sly;

class CollectionsLinkedListTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsLinkedListTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsLinkedListTest() {
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

TEST_F(CollectionsLinkedListTest, add) 
{
    constexpr int ITEM_ADD_COUNT = 255;
    constexpr s32 ITEM_TO_ADD = 10;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(ITEM_TO_ADD);

    EXPECT_EQ(ITEM_TO_ADD, list[0]);
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsLinkedListTest, addRange)
{
    const s32 ITEM_ADD_COUNT = 4;
    s32 ITEM_RANGE[ITEM_ADD_COUNT] = {1,2,3,4};
    
    LinkedList<s32> list;

    list.addRange(ITEM_RANGE, ITEM_ADD_COUNT);
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());

    for(s32 index = 0; index < ITEM_ADD_COUNT; index++)
        EXPECT_EQ(ITEM_RANGE[index], list.get(index));

    list.addRange(ITEM_RANGE, ITEM_ADD_COUNT);    
    for(s32 index = ITEM_ADD_COUNT; index < ITEM_ADD_COUNT * 2; index++)
        EXPECT_EQ(ITEM_RANGE[index - ITEM_ADD_COUNT], list.get(index));
}

TEST_F(CollectionsLinkedListTest, remove) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
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

TEST_F(CollectionsLinkedListTest, insert) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;

    LinkedList<s32> list;

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

TEST_F(CollectionsLinkedListTest, get) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(ITEM_TO_INSERT3);

    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        EXPECT_EQ(ITEM_TO_INSERT3, list.get(i));
}

TEST_F(CollectionsLinkedListTest, set) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr s32 ITEM_TO_INSERT1 = 10;
    constexpr s32 ITEM_TO_INSERT2 = 32;
    constexpr s32 ITEM_TO_INSERT3 = 64;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list.set(0, ITEM_TO_INSERT1);
    list.set(2, ITEM_TO_INSERT2);
    list.set(list.count()-1, ITEM_TO_INSERT3);

    EXPECT_EQ(ITEM_TO_INSERT1, list.get(0));
    EXPECT_EQ(ITEM_TO_INSERT2, list.get(2));
    EXPECT_EQ(ITEM_TO_INSERT3, list.get(list.count()-1));
}

TEST_F(CollectionsLinkedListTest, clear) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list.clear();

    EXPECT_EQ(0, list.count());
}

/*
TEST_F(CollectionsListTest, copy) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    s32 array[ITEM_ADD_COUNT];
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list.copy(array, 0, list.count());
    EXPECT_EQ(0, array[0]);

    list.copy(array, 2, list.count() - 2);
    EXPECT_EQ(2, array[0]);

    list.copy(array, 4, list.count() - 4);
    EXPECT_EQ(4, array[0]);
}

TEST_F(CollectionsListTest, appendTo) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    LinkedList<s32> list2;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    list2.add(32);
    list.appendTo(list2,0,list.count());

    EXPECT_EQ(32, list2.get(0));
    EXPECT_EQ(list.get(0), list2.get(1));
    EXPECT_EQ(list.count() + 1, list2.count());
}*/

TEST_F(CollectionsLinkedListTest, operatorAssignment) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    constexpr int ITEM_SET_VALUE = 32;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    EXPECT_EQ(3, list[3]);

    list[3] = ITEM_SET_VALUE;
    EXPECT_EQ(ITEM_SET_VALUE, list.get(3));
    EXPECT_EQ(ITEM_SET_VALUE, list[3]);

    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsLinkedListTest, count) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());
    
    EXPECT_EQ(ITEM_ADD_COUNT, list.count());
}

TEST_F(CollectionsLinkedListTest, getIterator) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
    for(int i = 0; i < ITEM_ADD_COUNT; i++)
        list.add(list.count());

    Iterator<s32> iter = list.getIterator();
}

TEST_F(CollectionsLinkedListTest, iternatorMoveNext) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
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

TEST_F(CollectionsLinkedListTest, iteratorCurrent) 
{
    constexpr int ITEM_ADD_COUNT = 5;
    LinkedList<s32> list;
    
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
