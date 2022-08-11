#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H

#include "Distance.h"

class EuclideanDistance : public Distance {
public:
    /**
     * @param v1 a vector
     * @param v2 another vector
     * @return the euclidean distance between the two
     */
    double distance(const std::vector<double>& v1, const std::vector<double>& v2) const override;
};

#endif
