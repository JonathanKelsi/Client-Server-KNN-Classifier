cmake_minimum_required(VERSION 3.22)
project(KNN-Classifier)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_HEADERS
    "classifier/Classified.h"
    "classifier/distance/Distance.h"
    "classifier/distance/EuclideanDistance.h"
    "classifier/distance/ManhattanDistance.h"
    "classifier/Algorithms.h"
    "classifier/distance/ChebyshevDistance.h"
    "classifier/Classifier.h"
    "client/client.cpp"
    "server/server.cpp"
    )

set(PROJECT_SOURCES
    "classifier/Classified.cpp"
    "classifier/distance/EuclideanDistance.cpp"
    "classifier/distance/ManhattanDistance.cpp"
    "classifier/Algorithms.cpp"
    "classifier/distance/ChebyshevDistance.cpp"
    "classifier/Classifier.cpp"
    "main.cpp"
    )

add_executable(KNN-Classifier ${PROJECT_SOURCES} ${PROJECT_HEADERS})


