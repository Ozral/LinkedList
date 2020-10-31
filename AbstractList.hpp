#pragma once

#include "functional"

template<typename T>
class AbstractList {
public:
    virtual const T& operator[](size_t index) const {
        return get(index);
    }

    virtual ~AbstractList() {};

public:
    // 增
    virtual AbstractList<T>& add(T elem) = 0;

    virtual AbstractList<T>& insert(T newElem, size_t pos) = 0;

    // 删
    virtual AbstractList<T>& remove(size_t pos) = 0;

    virtual AbstractList<T>& clear() = 0;

    // 改
    virtual AbstractList<T>& set(size_t index, T newElem) = 0;

    // 查
    virtual const T& get(size_t index) const = 0;

    virtual size_t indexOf(T target) const = 0;

    // 遍历
//    virtual AbstractList<T>& forEach(void(* fn)(const T&)) = 0;

    virtual AbstractList<T>& forEach(const std::function<void(T)>& fn) = 0;
};
