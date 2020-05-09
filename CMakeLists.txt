cmake_minimum_required (VERSION 3.0)
project (GBEmulator)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif ()

# Set Modules Dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(SFML_WINDOWS_ROOT "D:/Developer/SFML-2.1")

# Find source files
file(GLOB SOURCES *.cpp)

# Include header files
include_directories(.)
include_directories(debug)

include_directories(Memory)

include_directories(CPU)
include_directories(PPU)
include_directories(APU)

include_directories(IO)

# Create shared library
#add_library(${PROJECT_NAME} SHARED )

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
	  include_directories(${SFML_INCLUDE_DIR})
	  add_executable(${PROJECT_NAME} ${SOURCES})
	  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#target_link_libraries(${PROJECT_NAME} ${SFML_AUDIO} ${SFML_GRAPHICS} ${SFML_MAIN} ${SFML_SYSTEM} ${SFML_WINDOW})
