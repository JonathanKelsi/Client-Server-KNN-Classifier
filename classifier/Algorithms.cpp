#include "Algorithms.h"
#include <random>
#include <stdexcept>
#include <cmath>

// Vector utility functions

std::vector<double> operator-(const std::vector<double>& v) {
    std::vector<double> res = v;
    auto size = res.size();

    for (int i = 0; i < size; ++i) {
        res[i] *= -1;
    }

    return res;
}

std::vector<double> operator+(const std::vector<double>& v, const std::vector<double>& u) {
    auto size = v.size();

    if (size != u.size()) {
        throw std::invalid_argument("The vectors aren't of the same dimension");
    }

    std::vector<double> res = v;

    for (int i = 0; i < size; ++i) {
        res[i] += u[i];
    }

    return res;
}

std::vector<double> operator-(const std::vector<double>& u, const std::vector<double>& v) {
    return v + (-u);
}

std::vector<double> operator*(double t, const std::vector<double>& v) {
    std::vector<double> res = v;
    auto size = res.size();

    for (int i = 0; i < size; ++i) {
        res[i] *= t;
    }

    return res;
}

std::vector<double> operator*(const std::vector<double>& v, double t) {
    return t * v;
}

std::vector<double> operator/(const std::vector<double>& v, double t) {
    return v * (1 / t);
}

double len(const std::vector<double>& v) {
    double lenSqrd = 0;
    auto size = v.size();

    for (int i = 0; i < size; ++i) {
        lenSqrd += v[i] * v[i];
    }

    return sqrt(lenSqrd);
}

// Other utility functions

bool isDouble(const std::string& str) {
    char* end = nullptr;
    double val = strtod(str.c_str(), &end);
    return end != str.c_str() && *end == '\0' && val != HUGE_VAL;
}

std::string maxKey(const std::map<std::string, int>& map) {
    auto handleIterator = map.begin();
    std::string mostCommonString;
    int maxTimes = 0;

    while (handleIterator != map.end()) {
        if (handleIterator->second > maxTimes) {
            mostCommonString = handleIterator->first;
            maxTimes = handleIterator->second;
        }

        handleIterator = std::next(handleIterator);
    }

    return mostCommonString;
}

std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> subStrings;
    std::string currentSubString;

    for (char c : str) {
        if (c == delim) {
            subStrings.push_back(currentSubString);
            currentSubString.clear();
        } else {
            currentSubString.push_back(c);
        }
    }

    // Add the last substring
    subStrings.push_back(currentSubString);

    return subStrings;
}

int random(int a, int b) {
    // Obtain a random number from hardware
    std::random_device rand;

    // Seed the generator
    std::mt19937 gen(rand());

    // Define the range
    std::uniform_int_distribution<> distr(a, b);

    return distr(gen);
}

void swap(std::pair<double,int>& p1, std::pair<double,int>& p2) {
    std::pair<double,int> temp = p1;
    p1 = p2;
    p2 = temp;
}

// Algorithms

static int partition(std::vector<std::pair<double,int>>& v, int left, int right, int pivot) {
    double pivotVal = v[pivot].first;

    // Move the pivot to the end
    swap(v[pivot], v[right]);

    int index = left;
    for (int i = left; i < right; ++i) {
        if (v[i].first < pivotVal) {
            swap(v[index], v[i]);
            index++;
        }
    }

    // Move pivot to its final place
    swap(v[right], v[index]);

    return index;
}

static double quickSelect(std::vector<std::pair<double,int>>& v, int left, int right, int k) {
    // If the vector contains only one element
    if (left == right) {
        return v[left].first;
    }

    // Select an index between left and right
    int pivot = random(left, right);
    pivot = partition(v, left, right, pivot);

    // If we've found the desired element
    if (k == pivot) {
        return v[k].first;
    } else if (k < pivot) {
        return quickSelect(v, left, pivot -1, k);
    }

    // Edge case
    if (pivot + 1 >= right) {
        return v[right].first;
    }

    return quickSelect(v, pivot + 1, right, k);
}

std::vector<int> kSmallestElements(const std::vector<double>& v, int k) {
    auto size = v.size();

    if (k <= 0 || k > size) {
        throw std::runtime_error("k out of bounds");
    }

    std::vector<std::pair<double,int>> valuesAndIndices;

    for (int i = 0; i < size; ++i) {
        valuesAndIndices.emplace_back(v[i], i);
    }

    // Use the quickSelect algorithm to find the k-th smallest element, and partition the vector accordingly.
    quickSelect(valuesAndIndices, 0, size - 1, k);

    // Find the indices of the k-th smallest elements
    std::vector<int> indices;

    for (int i = 0; i < k; ++i) {
        indices.push_back(valuesAndIndices[i].second);
    }

    return indices;
}