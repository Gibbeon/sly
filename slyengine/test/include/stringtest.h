#include "gtest/gtest.h"
#include "sly/string.h"


using namespace sly;

class CollectionsStringTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  CollectionsStringTest() {
    // You can do set-up work for each test here.
  }

  virtual ~CollectionsStringTest() {
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

TEST_F(CollectionsStringTest, ctor) 
{
    constexpr const char_t* HAP_STRING = "hap";
    constexpr const char_t* HAPPY_STRING = "happy";
    constexpr const char_t* HAPPY_STRING2 = "happy";

    String<> stringOne = "Hello String";                     // using a constant String
    String<> stringTwo =  String<>("This is a string");        // converting a constant string into a String object

    String<> happy = String<>(HAPPY_STRING);
    String<> happy2 = String<>(HAPPY_STRING2);
    String<> cutoff = String<>(HAPPY_STRING, 3);
    String<> copy = String<>(happy);

    for(int i = 0; i < happy.count(); i++)
    {
        EXPECT_EQ(happy[i], HAPPY_STRING[i]);
    }

    EXPECT_EQ(cutoff, HAP_STRING);
    EXPECT_EQ(happy, HAPPY_STRING);
    EXPECT_NE(cutoff, happy);
    EXPECT_EQ(happy, happy2);
    EXPECT_EQ(cutoff, HAP_STRING);

    EXPECT_EQ(String<>::compare(happy, HAPPY_STRING), 0);
}

