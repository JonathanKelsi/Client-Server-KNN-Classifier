#include "ManhattanDistance.h"
#include "../Algorithms.h"

double ManhattanDistance::distance(const std::vector<double>& v1, const std::vector<double>& v2) const {
    std::vector<double> diff = v1 - v2;
    double res = 0;
    auto size = diff.size();

    for(int i = 0; i < size; ++i) {
        res += std::abs(diff[i]);
    }

    return res;
}