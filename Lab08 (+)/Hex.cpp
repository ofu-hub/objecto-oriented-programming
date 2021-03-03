#include "Hex.h"

Hex &Hex::toAdditionalCode(Array::size_type _n) {
    size_type diff = _n - size();
    Hex temp(_n, num_sys-1);

    for (size_type i = diff; i < _n; ++i)
    {
        temp[i] = num_sys-1 - (*this)[i-diff];
    }
    temp[_n-1]++;
    *this = std::move(temp);
    return *this;

}

void Hex::verifyHexFold(const Array &arr) const {
    bool verify = all_of(arr.begin(), arr.end(),
                         [] (value_type t) { return (t < num_sys); });
    if (!verify) throw not_Hexfold_exception();
}

Hex &Hex::operator+=(const Hex &var2) {
    Hex max, min;
    if (size() < var2.size()) {
        max = var2;
        min = *this;
    } else {
        max = *this;
        min = var2;
    }

    reverse(max.begin(), max.end());
    reverse(min.begin(), min.end());

    Array::size_type j = 0;
    for (Array::size_type i = 0; i < max.size(); i++) {
        if (j < min.size()) {
            max[i] += min[j];
            ++j;
        }

        if (max[i] >= Hex::num_sys) {
            if (i == max.size()-1) {
                max.push_back(0);
            }
            max[i] -= Hex::num_sys;
            ++max[i+1];
        }
    }

    reverse(max.begin(), max.end());
    *this = std::move(max);
    return *this;
}

Hex &Hex::operator-=(const Hex &var2) {
    if (*this < var2) {
        throw left_is_less_than_right_when_subtracted();
    }

    Array::size_type  _n = var2.size();
    if (size() > _n) {
        _n = size();
    }
    Hex var2_add_code(var2);
    var2_add_code.toAdditionalCode(_n);

    *this += var2_add_code;

    auto it = begin()+1;
    while (*it == 0 && it != end()-1) ++it;
    erase(begin(), it);
    return *this;
}

Hex &Hex::operator*=(const Hex &var2) {
    Hex max, min;
    if (size() < var2.size()) {
        max = var2;
        min = *this;
    } else {
        max = *this;
        min = var2;
    }

    reverse(max.begin(), max.end());
    reverse(min.begin(), min.end());

    Hex result(max.size());
    for (size_type i = 0; i < min.size(); ++i) {
        Hex temp(max);
        value_type v_ume = 0;
        for (size_type j = 0; j < max.size(); ++j) {
            temp[j] *= min[i];
            temp[j] += v_ume;
            if (temp[j] >= num_sys) {
                v_ume = temp[j] / num_sys;
                if (j == max.size()-1) {
                    temp.push_back(v_ume);
                }
                temp[j] %= num_sys;
            } else {
                v_ume = 0;
            }
        }

        Hex temp_res(temp.size()+i);
        std::reverse_copy(temp.begin(), temp.end(), temp_res.begin());
        result += temp_res;
    }

    *this = std::move(result);
    return *this;
}

Hex &Hex::operator/=(const Hex &var2) {
    if (var2.size() == 1 && var2[0] == 0) {
        throw zero_devided_exception();
    }

    Hex result;
    if (*this == var2) {
        result = {1};
    } else if(*this < var2) {
        result = {0};
    } else {
        Hex init(1, 1);
        while (*this >= var2) {
            *this -= var2;
            result += init;
        }
    }

    *this = std::move(result);
    return *this;
}

Hex operator+(const Hex &var1, const Hex &var2) {
    Hex max, min;
    if (var1.size() < var2.size()) {
        max = var2;
        min = var1;
    } else {
        max = var1;
        min = var2;
    }

    reverse(max.begin(), max.end());
    reverse(min.begin(), min.end());

    Array::size_type j = 0;
    for (Array::size_type i = 0; i < max.size(); i++) {
        if (j < min.size()) {
            max[i] += min[j];
            j++;
        }

        if (max[i] >= Hex::num_sys) {
            if (i == max.size()-1) {
                max.push_back(0);
            }
            max[i] -= Hex::num_sys;
            max[i+1]++;
        }
    }

    reverse(max.begin(), max.end());
    return Hex(max);
}

Hex operator-(const Hex &var1, const Hex &var2) {
    Hex temp(var1);
    temp -= var2;
    return temp;
}

Hex operator*(const Hex &var1, const Hex &var2) {
    Hex temp(var1);
    temp *= var2;
    return temp;
}

Hex operator/(const Hex &var1, const Hex &var2) {
    Hex temp(var1);
    temp /= var2;
    return temp;
}
