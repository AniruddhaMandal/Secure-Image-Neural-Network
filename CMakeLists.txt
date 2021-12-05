cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 11)
PROJECT(NeuralNetwork VERSION 0.0.1) 


IF(NOT CMAKE_BUILD_TYPE) 
set(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")


add_executable(Main "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp")
target_include_directories(Main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")
target_link_libraries(Main Matrix MathCal ImRead NeuralNetworks)

add_library(Matrix SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/Math/Matrix.cpp")
target_include_directories(Matrix PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")

add_library(MathCal STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/Math/MathCal.cpp")
target_include_directories(MathCal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")

add_library(ImRead SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/NeuralNetworks/ImRead.cpp")
target_include_directories(ImRead PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")

add_library(NeuralNetworks SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/NeuralNetworks/NeuralNetworks.cpp")
target_include_directories(NeuralNetworks PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")

add_library(Encryption SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/Encryption/EncryptionAlgorithm.cpp")
target_include_directories(Encryption PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes/")