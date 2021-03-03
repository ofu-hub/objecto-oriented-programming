#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Array
{
public:
    // Types
    using size_type = size_t;
    using value_type = uint8_t;
    using referense = value_type&;
    using const_referense = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    // Exceptions
    class zero_array_size_exception {};

    // Constructors
    Array() = default;
    explicit Array(size_type n, value_type t = 0);
    Array(const std::initializer_list<value_type> &t);
    explicit Array(const std::string &str);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    virtual ~Array() noexcept;

    std::string toString() const noexcept;
    inline size_type size() const noexcept { return current_size; }
    inline iterator getData() const noexcept { return iterator(data); }
    inline iterator begin() const noexcept { return iterator(data); }
    inline iterator end() const noexcept { return iterator(data + current_size); }

    referense operator[](size_type n);
    const_referense operator[](size_type n) const;
    void push_back(const value_type& v);
    void pop_back() noexcept;
    iterator erase(iterator first, iterator last);

    friend bool operator<(const Array &var1, const Array &var2);
    friend bool operator>(const Array &var1, const Array &var2);
    friend bool operator<=(const Array &var1, const Array &var2);
    friend bool operator>=(const Array &var1, const Array &var2);
    friend bool operator==(const Array &var1, const Array &var2);
    friend bool operator!=(const Array &var1, const Array &var2);

    friend std::istream &operator>>(std::istream &strm, Array &arr);
    friend std::ostream &operator<<(std::ostream &strm, const Array &arr);

private:
    size_type current_size{0};
    value_type *data{nullptr};

    void verifyZeroSize(size_type _n) const;
    void verifyIndex(size_type _index) const;
};


#endif //ARRAY_H
