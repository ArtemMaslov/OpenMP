cmake_minimum_required(VERSION 3.22)
project(MasMatrix
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Должен быть в корневом CMakeLists.txt, иначе проблемы будут.
include(CTest)

###################################################################################################

if (PROJECT_IS_TOP_LEVEL AND UNIX)
    # Create symlink to compile_commands.json for IDE to pick it up
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()

###################################################################################################

set(SANITIZER_OPTIONS
    -fsanitize=address
)

set(SANITIZER_LINK_OPTIONS
    -fsanitize=address
    -static-libasan
)

set(COMPILE_OPTIONS
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
    -Wno-unused-parameter
    
    -fPIC
    -fopenmp
)

set(LINK_OPTIONS
    ${SANITIZER_LINK_OPTIONS}
    -fopenmp
)

set(COMPILE_DEBUG_OPTIONS
    ${COMPILE_OPTIONS}
    ${SANITIZER_OPTIONS}
)

set(COMPILE_RELEASE_OPTIONS
    ${COMPILE_OPTIONS}
)

set(LINK_DEBUG_OPTIONS
    ${LINK_OPTIONS}
    ${SANITIZER_OPTIONS}
)

set(LINK_RELEASE_OPTIONS
    ${LINK_OPTIONS}
)

###################################################################################################

set(MasUtilsSrcs
    Mas/Utils/StringBuilder.cpp
    Mas/Utils/UtilsIO.cpp
)

###################################################################################################

add_library(LibMasUtils SHARED ${MasUtilsSrcs})
target_include_directories(LibMasUtils PUBLIC ./)

target_compile_options(LibMasUtils PRIVATE ${COMPILE_DEBUG_OPTIONS})
target_link_options(LibMasUtils PRIVATE ${LINK_DEBUG_OPTIONS})

###################################################################################################

add_executable(matrixGen Mas/Matrix/MatrixGen.cpp)
target_link_libraries(matrixGen PRIVATE LibMasMatrix)

target_compile_options(matrixGen PRIVATE ${COMPILE_RELEASE_OPTIONS})
target_link_options(matrixGen PRIVATE ${LINK_RELEASE_OPTIONS})

###################################################################################################

add_library(LibMasMatrix INTERFACE)
target_link_libraries(LibMasMatrix INTERFACE LibMasUtils)
target_include_directories(LibMasMatrix INTERFACE ./)

add_subdirectory(Tests)

###################################################################################################