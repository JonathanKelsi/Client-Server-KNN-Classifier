#include "Classifier.h"
#include "distance/EuclideanDistance.h"
#include "distance/ChebyshevDistance.h"
#include "distance/ManhattanDistance.h"
#include "Algorithms.h"
#include <map>
#include <fstream>
#include <sstream>

Classifier::Classifier(int k) : m_isInit(false), m_k(k) {}

void Classifier::classify(Classified& unclassified, const Distance& metric) const {
    if (!m_isInit) {
        throw std::runtime_error("Classifier uninitialized");
    }

    // Measure the distances from the unclassified vector to the gathered data
    std::vector<double> distances;
    auto dataSize = m_classifiedData.size();

    for (int i = 0; i < dataSize; ++i) {
        distances.push_back(metric.distance(unclassified.data(), m_classifiedData[i]->data()));
    }

    // Find the K nearest neighbours, and the most common handle among them
    std::map<std::string, int> map;
    std::vector<int> indices = kSmallestElements(distances, m_k);

    for (int i = 0; i < m_k; ++i) {
        std::string handle = m_classifiedData[indices[i]]->handle();

        if (map.find(handle) == map.end()) {
            map[handle] = 1;
        } else {
            map[handle]++;
        }
    }

    // Classify the object
    unclassified.handle(maxKey(map));
}

void Classifier::addClassifiedData(std::unique_ptr<Classified>& classified) {
    m_classifiedData.push_back(std::move(classified));
}

void Classifier::init(const std::string& dataPath) {
    // Read from given csv files and create classified objects
    std::string line;
    std::ifstream inFile(dataPath);

    // Iterate through the csv file lines
    while (std::getline(inFile, line)) {
        // Read the columns and gather the classified object's data
        std::vector<std::string> columns = split(line, ',');
        auto size = columns.size();

        std::string handle = columns[size - 1];
        std::vector<double> vData;

        for (int i = 0; i < size - 1; ++i) {
            vData.push_back(std::stod(columns[i]));
        }

        std::unique_ptr<Classified> uniquePtr(new Classified(handle, vData));
        m_classifiedData.push_back(std::move(uniquePtr));
    }

    // Close the stream, and update the initialization has completed
    inFile.close();
    m_isInit = true;
}

void Classifier::write(const std::string& dataPath, const std::string& outputPath) const {
    if (!m_isInit) {
        throw std::runtime_error("Classifier uninitialized");
    }

    // Create unclassified objects from the unclassified data
    std::string line;
    std::ifstream inFile(dataPath);

    std::vector<std::unique_ptr<Classified>> unclassifiedData;

    while (std::getline(inFile, line)) {
        std::vector<std::string> columns = split(line, ',');
        auto size = columns.size();

        std::vector<double> vData;

        for (int i = 0; i < size; ++i) {
            vData.push_back(std::stod(columns[i]));
        }

        std::unique_ptr<Classified> uniquePtr(new Classified("", vData));
        unclassifiedData.push_back(std::move(uniquePtr));
    }

    inFile.close();

    // Create a vector of the metrics used
    std::vector<Distance*> metrics = {new EuclideanDistance(), new ChebyshevDistance(), new ManhattanDistance()};
    auto numOfDistances = metrics.size();

    //Create vector with the output path names, corresponding to the metrics
    std::vector<std::string> files = {"euclidean_output.csv", "chebyshev_output.csv", "manhattan_output.csv"};

    // For each distance, print the classifications by the relevant metric
    auto classificationSize = unclassifiedData.size();

    for (int i = 0; i < numOfDistances; ++i) {
        std::ofstream ostream(outputPath + "/" + files[i]);

        for (int j = 0; j < classificationSize; ++j) {
            classify(*unclassifiedData[j], *metrics[i]);
            ostream << unclassifiedData[j]->handle() << std::endl;
        }

        ostream.close();
        delete metrics[i];
    }

    metrics.clear();
}
