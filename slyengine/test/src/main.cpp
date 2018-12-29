#include "gtest/gtest.h"

//sly tools
#include "sly/global.h"
#include "sly/diagnostics/perftest.h"

//tests
#include "collections/arraytest.h"
#include "collections/maptest.h"
#include "collections/listtest.h"
#include "collections/iteratortest.h"
#include "collections/linkedlisttest.h"
#include "collections/queuetest.h"
#include "collections/stacktest.h"
//#include "platform/win32/win32windowservicetest.h"
#include "stringtest.h"

using namespace sly;

int main(int argc, char **argv) {
  try
  {
    ::testing::InitGoogleTest(&argc, argv);
    auto result = RUN_ALL_TESTS();
    
    PAUSE();
    return result;
  }
  catch(Exception& ex)
  {
    std::cout << (const char_t*)ex.message() << std::endl;
  }
}

/*
int main() {
  try{

    PerfTest test(1 << 5, 30);

    test.add("Math::sqrt", []() {
      for(u32 i = 0; i < (1 << 24); i++)
        Math::sqrt(11237481.0);
    });

    test.add("Math::sqrt_appx", []() {
      for(u32 i = 0; i < (1 << 24); i++)
        Math::sqrt_appx(11237481.0);
    });

    test.run().foreach([](PerfResult x){ x.print(); });

  } 
  catch(std::runtime_error& ex)
  {
    std::cout << ex.what() << std::endl;
  }
  PAUSE();
}*/

