#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "Classified.h"
#include "distance/Distance.h"
#include <string>
#include <memory>

class Classifier {
private:
    int m_k;
    bool m_isInit;
    std::vector<std::unique_ptr<Classified>> m_classifiedData;

public:
    /**
     * Constructor.
     * @param k the parameter used in the KNN algorithm
     */
    Classifier(int k);

    /**
     * Given unclassified data and a distance metric, this method uses
     * the KNN algorithm to classify the object.
     * @param unclassified an unclassified object.
     * @param distance a distance metric
     */
    void classify(Classified& unclassified, const Distance& metric) const;

    /**
     * Initialize the classified data the KNN algorithm will utilise, from a CSV file.
     * @param dataPath the path to the classified data
     */
    void initFromFile(const std::string& dataPath);

    /**
     * Use the KNN algorithm with every supported metric to classify the data stored in the dataPath,
     * and output the result to outputPath, in a CSV file.
     * @param dataPath the path to the unclassified data
     * @param outputPath the desired output path
     */
    void writeToFile(const std::string& dataPath, const std::string& outputPath) const;
};

#endif