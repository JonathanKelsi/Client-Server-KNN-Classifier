#ifndef Classified_H
#define Classified_H
#include <vector>
#include <string>

/**
 * This class represents an object that is classified by the KNN Classifier.
 */
class Classified {
private:
    std::vector<double> m_data;
    std::string m_handle;

public:
    /**
     * empty constructor.
     */
    Classified();

    /**
     * constructor.
     * @param handle the handle
     * @param data the data
     */
    Classified(std::string handle, std::vector<double>& data);

    /**
    * copy constructor.
    * @param classified another classified instance
    */
    Classified(const Classified& classified);

    /**
     * handle getter.
     */
    const std::string& handle() const;

    /**
     * data getter.
     */
    const std::vector<double>& data() const;

    /**
     * handle setter
     */
     void handle(std::string handle);
};

#endif
