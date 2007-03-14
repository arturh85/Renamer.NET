#include <iostream>
#include <boost/test/included/unit_test_framework.hpp>
#include "globals.h"
#include "ruleset.h"
#include "InputRule.h"
#include "replacement.h"
#include "replacements.h"
#include "tableRow.h"

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
  test_suite* test= BOOST_TEST_SUITE( "renamer" );

  test->add( BOOST_TEST_CASE( &free_test_function ), 0);
  test->add( BOOST_TEST_CASE( &TableRow::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Replacement::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Replacements::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &InputRule::unitTest ), 1);
  //test->add( BOOST_TEST_CASE( &Ruleset::unitTest ));

  return test;
}

void dummy()
{
    BOOST_CHECK(1==1);
    BOOST_CHECK_THROW ( throw(runtime_error("Test")), exception );
}

// most frequently you implement test cases as a free functions
void free_test_function()
{
    dummy();
}

