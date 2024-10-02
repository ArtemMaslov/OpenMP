#find_package (Boost COMPONENTS unit_test_framework REQUIRED)

###################################################################################################

function(add_my_executable TestSrcFile)
    set(Target "Test${TestSrcFile}")

    add_executable(${Target} "${TestSrcFile}.cpp")
    target_link_libraries(${Target} PRIVATE LibMasMatrix)

    target_compile_options(${Target} PRIVATE ${COMPILE_DEBUG_OPTIONS})
    target_link_options(${Target} PRIVATE ${LINK_DEBUG_OPTIONS})
endfunction()

function(add_my_test TestSrcFile)
    set(Target "Test${TestSrcFile}")
    add_my_executable(${TestSrcFile})
    add_test(NAME ${TestSrcFile} COMMAND ${Target})
endfunction()

###################################################################################################

add_my_test(ReadMatrix)
add_my_test(ReadMatrix2)
add_my_test(WriteMatrix)
add_my_test(MulMatrix1)
add_my_test(MulMatrix2)
add_my_test(MulMatrix3)
add_my_test(CtorThrow)
add_my_test(MulMatrixPar)

add_my_executable(MulMatrixSpeedSeq)
add_my_executable(MulMatrixSpeedPar)

###################################################################################################