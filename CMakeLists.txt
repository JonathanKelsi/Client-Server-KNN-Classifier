cmake_minimum_required(VERSION 3.22)
project(KNN-Classifier)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_SOURCES
    "classifier/Classified.cpp"
    "classifier/distance/EuclideanDistance.cpp"
    "classifier/distance/ManhattanDistance.cpp"
    "classifier/Algorithms.cpp"
    "classifier/distance/ChebyshevDistance.cpp"
    "classifier/Classifier.cpp"
)

set(PROJECT_HEADERS
    "classifier/Classified.h"
    "classifier/distance/Distance.h"
    "classifier/distance/EuclideanDistance.h"
    "classifier/distance/ManhattanDistance.h"
    "classifier/Algorithms.h"
    "classifier/distance/ChebyshevDistance.h"
    "classifier/Classifier.h"
)

add_executable(Server ${PROJECT_SOURCES} ${PROJECT_HEADERS} server/server.cpp)
add_executable(Client client/client.cpp)


