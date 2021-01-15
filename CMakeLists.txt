cmake_minimum_required (VERSION 3.0)
project (GBEmulator)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")
endif ()
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


# Set Modules Dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(SFML_WINDOWS_ROOT "D:/Developer/SFML-2.5/SFML")

# Find source files
file(GLOB_RECURSE SOURCES Bus.cpp Gameboy.cpp  Memory/*.cpp CPU/*.cpp PPU/*.cpp APU/*.cpp IO/*.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET (CMAKE_OSX_ARCHITECTURES "x86_64") 
endif()

# Include header files
include_directories(.)
include_directories(debug)

include_directories(Memory)

include_directories(CPU)
include_directories(PPU)
include_directories(APU)

include_directories(IO)

#Rework the code to use add_library

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
          include_directories(${SFML_INCLUDE_DIR})
		  add_executable(${PROJECT_NAME} ${SOURCES})
		  #target_link_libraries(${PROJECT_NAME} ${SFML_AUDIO} ${SFML_GRAPHICS} ${SFML_MAIN} ${SFML_SYSTEM} ${SFML_WINDOW})
          target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

add_custom_target(WindowsCopyDLL	
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/openal32.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-audio-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-audio-d-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-graphics-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-graphics-d-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-network-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-network-d-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-system-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-system-d-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-window-2.dll ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy ${SFML_WINDOWS_ROOT}/bin/sfml-window-d-2.dll ${CMAKE_BINARY_DIR}
)

add_custom_target(WindowsCopyRom
	COMMAND ${CMAKE_COMMAND} -E copy "D:/Tetris.gb" ${CMAKE_BINARY_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 17
            )


add_subdirectory(UnitTests)