#include <boost/test/included/unit_test_framework.hpp>
//#include <boost/test/unit_test_log.hpp>
#include "globals.h"
#include "ruleset.h"
#include "InputRule.h"
#include "replacements.h"
#include "gem.h"
#include "outputFormat.h"

using namespace std;
using boost::unit_test::test_suite;
using namespace boost::unit_test::log;

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
//  unit_test_log::instance().set_log_threshold_level(0);

  test->add( BOOST_TEST_CASE( &TableRow::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Replacement::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Replacements::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Gem::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &InputRule::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &OutputFormat::unitTest ), 0);
  test->add( BOOST_TEST_CASE( &Ruleset::unitTest ), 3);
//  test->add( BOOST_TEST_CASE( &free_test_function ), 0);

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
//    BOOST_CHECK(2==1);
    dummy();
}

