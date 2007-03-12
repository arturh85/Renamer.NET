#include <iostream>
#include <boost/test/included/unit_test_framework.hpp>
#include "globals.h"
#include "ruleset.h"

using namespace std;
using boost::unit_test::test_suite;

void free_test_function();

test_suite*
init_unit_test_suite( int, char* [] ) {

  //PathObjekte validieren. Damit sie dass auch "sinnvoll" tun:
  using namespace boost::filesystem;
  path::default_name_check(native);

  //Zufallsgenerator initialisieren
  srand(time(NULL));

  //  init tests
  test_suite* test= BOOST_TEST_SUITE( "distributedBackup" );

  test->add( BOOST_TEST_CASE( &Ruleset::unitTest ), 0 /* expected one error */ );
  test->add( BOOST_TEST_CASE( &free_test_function ), 0 /* expected one error */ );
//  test->add( BOOST_TEST_CASE( &free_test_function2 ), 0 /* expected no error */ );

  return test;
}

void dummy()
{
    // reports 'error in "free_test_function": test 2 == 1 failed'
    BOOST_CHECK(1 == 1); // non-critical test => continue after failure
//    int* p = (int*)0;
//    *p = 0;
}

// most frequently you implement test cases as a free functions
void free_test_function()
{
    dummy();
}

