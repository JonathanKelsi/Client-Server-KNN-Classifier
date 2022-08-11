#include "Classified.h"

Classified::Classified() {
    m_handle = "";
}

Classified::Classified(std::string handle, std::vector<double>& data) {
    m_handle = std::move(handle);
    m_data = data;
}

Classified::Classified(const Classified& classified) {
    m_handle = classified.m_handle;
    m_data = classified.data();
}

const std::string& Classified::handle() const {
    return m_handle;
}

const std::vector<double>& Classified::data() const {
    return m_data;
}

void Classified::handle(std::string handle) {
    m_handle = std::move(handle);
}

