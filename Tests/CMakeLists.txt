find_package (Boost COMPONENTS unit_test_framework REQUIRED)
#include(CTest)

set(COMPILE_OPTIONS
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo

    -Wno-unused-variable
    
    -fPIC
)

set(SOURCES
    MainTests.cpp
)

add_executable(TestMasMatrix ${SOURCES})
target_link_libraries(TestMasMatrix
    PRIVATE LibMasMatrix ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
target_compile_options(TestMasMatrix PRIVATE ${COMPILE_OPTIONS})

#add_test(NAME UnitTests COMMAND TestMasMatrix)