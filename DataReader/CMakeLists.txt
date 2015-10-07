#A. Guayaquil
#10.2015

file(GLOB_RECURSE CPP_SOURCE src/*.cpp)
file(GLOB_RECURSE CPP_HEADER src/*.h)

include_directories(inc)
add_executable(DataReader ${CPP_SOURCE} ${CPP_HEADER})

#link_directories(lib/${CMAKE_BUILD_TYPE})
target_link_libraries(DataReader debug freeglutd.lib)
target_link_libraries(DataReader optimized freeglut.lib)