#include "Array.h"

void Array::verifyZeroSize(Array::size_type _n) const {
    if (!_n) throw zero_array_size_exception();
}

void Array::verifyIndex(Array::size_type _index) const {
    if (_index >= current_size) throw std::out_of_range{"bad index exception"};
}

Array::Array(size_type n, value_type t) {
    verifyZeroSize(n);
    current_size = n;
    data = new value_type[current_size];
    std::fill(begin(), end(), t);
}

Array::Array(const initializer_list<value_type> &t) : Array(t.size()) {
    std::copy(t.begin(), t.end(), begin());
}

Array::Array(const string &str) : Array(str.size()) {
    size_type i = 0;
    for (char var : str) {
        data[i++] = static_cast<value_type>(var - '0');
    }
}

Array::Array(const Array &other) {
    current_size = other.current_size;
    data = new value_type[current_size];
    std::copy(other.begin(), other.end(), begin());
}

Array::Array(Array &&other) noexcept {
    current_size = other.current_size;
    this->data = other.data;
    other.current_size = 0;
    other.data = nullptr;
}

Array &Array::operator=(const Array &other) {
    if (this != &other) {
        Array temp(other);
        std::swap(current_size, temp.current_size);
        std::swap(data, temp.data);
    }
    return *this;
}

Array &Array::operator=(Array &&other) noexcept {
    if (this != &other) {
        std::swap(current_size, other.current_size);
        std::swap(data, other.data);
    }
    return *this;
}

Array::~Array() noexcept {
    current_size = 0;
    delete[] data;
}

std::string Array::toString() const noexcept {
    std::string out;
    for (auto &i : *this) {
        out += std::to_string(i);
    }
    return out;
}

Array::referense Array::operator[](Array::size_type n) {
    verifyIndex(n);
    return referense(data[n]);
}

Array::const_referense Array::operator[](Array::size_type n) const {
    verifyIndex(n);
    return const_referense(data[n]);
}

void Array::push_back(const Array::value_type &v) {
    Array temp(current_size+1, v);
    std::move(begin(), end(), temp.begin());
    *this = std::move(temp);
}

void Array::pop_back() noexcept {
    current_size--;
}

Array::iterator Array::erase(Array::iterator first, Array::iterator last) {
    if (first >= begin() && last <= end() && last > first) {
        size_type dist = size_type(last-first);
        Array temp;
        if (current_size != dist) {
            temp = Array(current_size - dist);
        }
        size_type pos = temp.size();
        if (begin() != first) {
            std::move(begin(), first, temp.begin());
        }
        if (end() != last) {
            pos = size_type(first - begin());
            std::move(last, end(), temp.begin()+pos);
        }
        *this = std::move(temp);
        return (begin()+pos);
    }
    return nullptr;
}

bool operator<(const Array &var1, const Array &var2) {
    if (var1.size() == var2.size()) {
        return std::lexicographical_compare(var1.begin(), var1.end(), var2.begin(), var2.end());
    }
    return (var1.size() < var2.size());
}

bool operator>(const Array &var1, const Array &var2) {
    return !(var1 <= var2);
}

bool operator<=(const Array &var1, const Array &var2) {
    return (var1 < var2) || (var1 == var2);
}

bool operator>=(const Array &var1, const Array &var2) {
    return (var1 > var2) || (var1 == var2);
}

bool operator==(const Array &var1, const Array &var2) {
    if (var1.size() != var2.size()) return false;
    return std::equal(var1.begin(), var1.end(), var2.begin());
}

bool operator!=(const Array &var1, const Array &var2) {
    return !(var1 == var2);
}

std::istream &operator>>(std::istream &strm, Array &arr) {
    std::string line;
    strm >> line;
    arr = Array(line);
    return strm;
}

std::ostream &operator<<(std::ostream &strm, const Array &arr) {
    return (strm << arr.toString());
}
