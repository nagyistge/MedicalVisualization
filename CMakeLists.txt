#A. Guayaquil
#10.2015

cmake_minimum_required(VERSION 3.3)
project (MedicalVisualization)

#Check which system we are running\
message(STATUS "CMAKE_CXX_COMPILER_ID :" ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_SYSTEM_VERSION :" ${CMAKE_SYSTEM_VERSION})
message(STATUS "CMAKE_C_COMPILER_ID :" ${CMAKE_C_COMPILER_ID})

#Add flag of C math
add_definitions(-D_USE_MATH_DEFINES)

#Some flags for the C++ compiler
if(WIN32)
	set(CMAKE_CXX_FLAGS "-MP8 /EHsc /W3")
else()
	set (CMAKE_INCLUDE_CURRENT_DIR ON)
	set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
endif()

#Requirement for the project
find_package(OpenGL REQUIRED)

#Add all projects
add_subdirectory(DataReader)