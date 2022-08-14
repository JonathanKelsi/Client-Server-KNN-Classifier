#ifndef Classified_H
#define Classified_H
#include <vector>
#include <string>
#include <memory>

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

    /**
     * Given a classified object, return it's CSV representation.
     * @param classified a classified object
     * @return the object's CSV representation
     */
    std::string ClassifiedToLine(const Classified& classified);

    /**
     * Given a classified object represented in a CSV format, return a pointer to the object.
     * @param line the classified object in a CSV format
     * @return the classified object
     */
    static std::unique_ptr<Classified> fromLine(const std::string& line);
};

#endif
