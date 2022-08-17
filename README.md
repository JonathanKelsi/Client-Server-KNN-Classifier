# KNN Classifier

This repository provides a server-side and a client-side system that
implements the  [k-nearest neighbors algorithm](https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm), 
using different metrics to classify new data, based on given data.

## Table Of Contents

## Getting Started

### Dependencies

This project uses CMake to generate and build. In a Debian-based system you can install it via:
```bash
sudo apt install cmake
```

### Installation

Clone the repository:
```bash
git clone 'https://github.com/JonathanKelsi/Server-Client-KNN-Classifier'
```

### Executing The Program

To build the program, the standard CMake workflow can be used:
```bash
mkdir -p build && cd build
cmake ..
make -j && make
```

Running the server can be achieved by:
```bash
./Server
```
Running the client:
```bash
./Client [UNCLASSIFIED-DATA-PATH] [OUTPUT-PATH]
```

## Design

### Distance

In order get another level of abstraction, we've created
the pure virtual class *Distance*, and gave it some concrete
subclasses, such as *EuclideanDistance*, *ManhattanDistance*
and *ChebyshevDistance*.
```c++
class Distance {
public:
    virtual double distance(const std::vector<double>& v1, const std::vector<double>& v2) const = 0;
     virtual ~Distance() = default;
};
```
The class represents an abstract metric, and is used
to achieve generality through polymorphism at the KNN classifier.

### Classified and Classifier

**classified**: for

## Authors
[Jonathan Kelsi](https://github.com/JonathanKelsi)  
[Ido Katzav](https://github.com/idokatzav)

## Acknowledgments

In order to better understand C/C++, and implement some of the
algorithms we used, we've relied on the following sources:

* [Wikipedia](https://www.wikipedia.org/)
* [Stackoverflow](https://stackoverflow.com/questions)
* [die.net](https://linux.die.net/)
* [man7.org](https://man7.org/linux/man-pages/)
* Hemi Leibowitch and Areal Shtusel
