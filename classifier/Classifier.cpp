#include "Classifier.h"
#include "distance/EuclideanDistance.h"
#include "Algorithms.h"
#include <map>
#include <fstream>
#include <sstream>

Classifier::Classifier(int k) : m_isInit(false), m_k(k) {}

void Classifier::initFromFile(const std::string& dataPath) {
    std::string line;
    std::ifstream inFile(dataPath);

    // Iterate through the csv file, and gather the classified objects' data and classifications
    while (std::getline(inFile, line)) {
        m_classifiedData.push_back(Classified::fromLine(line));
    }

    inFile.close();
    m_isInit = true;
}

void Classifier::classify(Classified& unclassified, const Distance& metric) const {
    if (!m_isInit) {
        throw std::runtime_error("Classifier uninitialized");
    }

    // Measure the distances from the unclassified data to the points in the dataset
    std::vector<double> distances;
    auto dataSize = m_classifiedData.size();

    for (int i = 0; i < dataSize; ++i) {
        try {
            distances.push_back(metric.distance(unclassified.data(), m_classifiedData[i]->data()));
        } catch (const std::invalid_argument& ia) {
            unclassified.handle("");
            return;
        }
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

    // Give the unclassified object the correct handle
    unclassified.handle(maxKey(map));
}

std::string Classifier::classify(const std::string& unclassifiedData, const Distance& metric) const {
    std::vector<std::string> lines = split(unclassifiedData, '\n');
    std::string res;

    for (int i = 0; i < lines.size(); ++i) {
        std::unique_ptr<Classified> unclassified = Classified::fromLine(lines[i]);
        classify(*unclassified, metric);
        res += unclassified->handle() + "\n";
    }

    return res;
}