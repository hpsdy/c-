//
// Created by qinhan on 2018/6/29.
//

#ifndef C_PLUS_1612_H
#define C_PLUS_1612_H

#include <vector>
#include <initializer_list>
#include <memory>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <set>

template<typename T>
class Blob {
public:
    typedef typename std::vector<T>::size_type size_type;

    Blob();

    Blob(const std::initializer_list <T> &il);

    size_type size() {
        printf("%s\n", "size_type");
        return data->size();
    }

    size_type size() const {
        printf("%s\n", "const size_type");
        return data->size();
    }

    bool empty() {
        printf("%s\n", "empty");
        return data->empty();
    }

    bool empty() const {
        printf("%s\n", "const empty");
        return data->empty();
    }

    void push_back(const T &t) {
        data->push_back(t);
    }

    void push_back(T &&t) {
        data->push_back(std::move(t));
    }

    void pop_back();

    T &back();

    T &back() const;

    T &operator[](size_type i);

    T &operator[](size_type i) const;

private:
    std::shared_ptr <std::vector<T>> data;

    void check(size_type i, const std::string &msg = "default error") const;
};

template<typename T>
Blob<T>::Blob():data(new std::vector<T>()) {}

template<typename T>
Blob<T>::Blob(const std::initializer_list <T> &il):data(new std::vector<T>(il)) {}

template<typename T>
void Blob<T>::pop_back() {
    data->pop_back();
}

template<typename T>
T &Blob<T>::back() {
    printf("%s\n", "back");
    return data->back();
}

template<typename T>
T &Blob<T>::back() const {
    printf("%s\n", "const back");
    return data->back();
}

template<typename T>
T &Blob<T>::operator[](size_type i) {
    check(i, "index out range");
    return data->at(i);
}

template<typename T>
T &Blob<T>::operator[](size_type i) const {
    check(i, "index out range");
    return data->at(i);
}

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i < size()) {
        return;
    } else {
        throw std::range_error(msg);
    }
}

#endif //C_PLUS_1612_H
