cmake_minimum_required (VERSION 3.0)
project(tests)

include_directories(.)

file( GLOB TESTS *.cpp )

include_directories(..)

#Later have each component as a library so I can easily link this here
include_directories(../Memory)
include_directories(../CPU)
include_directories(../PPU)
include_directories(../IO)
file(GLOB_RECURSE SOURCES ../Memory/*.cpp ../CPU/*.cpp ../PPU/*.cpp ../IO/*.cpp)

enable_testing()
foreach( testsourcefile ${TESTS} )
    get_filename_component(filename ${testsourcefile} NAME)
    string( REPLACE ".cpp" "_test" testname ${filename} )
    add_executable( ${testname} ${testsourcefile} ${SOURCES})
    add_test(NAME ${testname} COMMAND ${testname})
    set_target_properties(${testname} PROPERTIES
            CXX_STANDARD 17
            )
endforeach(testsourcefile ${TESTS})

