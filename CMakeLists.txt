cmake_minimum_required(VERSION 3.15)
project(rw-cov LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

# json
find_package(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# openblas
find_package(BLAS REQUIRED)
if(BLAS_FOUND)
    message("OpenBLAS found.")
    include_directories(/usr/local/include/openblas/)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${BLAS_LIBRARIES})
else()
    message(FATAL_ERROR "OpenBLAS not found.")
endif()

# python
find_package(Python3 COMPONENTS Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python3_LIBRARIES})

# plot-cpp
find_package(plot-cpp REQUIRED) # find plot-cpp
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include/) # include to make header visible to main
target_link_libraries(${PROJECT_NAME} PRIVATE plot-cpp::plot-cpp) # link the plot-cpp .a