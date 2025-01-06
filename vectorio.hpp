#ifndef VECTORIO_HPP
#define VECTORIO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << *it;
        if (it != v.end() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& input, std::vector<int>& v) {
    v.clear();
    std::string s;
    std::getline(input, s);
    std::stringstream ss(s);
    int x;
    while (ss >> x) {
        v.push_back(x);
    }
    return input;
}

#endif // VECTORIO_HPP