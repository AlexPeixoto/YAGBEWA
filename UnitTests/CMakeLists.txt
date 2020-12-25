cmake_minimum_required (VERSION 3.0)
project(tests)

include_directories(.)

file( GLOB TESTS *.cpp )



enable_testing()
foreach( testsourcefile ${TESTS} )
    get_filename_component(filename ${testsourcefile} NAME_WE)
    string( REPLACE ".cpp" "" testname ${filename} )
    add_executable( ${testname} ${testsourcefile} )
    add_test(NAME ${testname} COMMAND ${testname})
    set_target_properties(${testname} PROPERTIES
            CXX_STANDARD 17
            )
endforeach(testsourcefile ${TESTS})

