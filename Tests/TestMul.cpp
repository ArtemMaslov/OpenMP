#include <stdio.h>

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "Test Mas::Matrix Multiplication algorithms"

#include <boost/test/unit_test.hpp>

#include <Matrix.h>

using namespace boost::unit_test;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

void 

test_suite* init_unit_test_suite( int, char* [] )
{
    framework::master_test_suite().p_name.value = "Unit test example 02";
    

    framework::master_test_suite().add( BOOST_TEST_CASE( free_test_function, numbers ) );

    return test;
}

// EOF