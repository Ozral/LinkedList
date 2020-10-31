#pragma once

#include "AbstractList.hpp"
#include "initializer_list"
#include "iostream"

template<typename T>
class LinkedList;

/**
 * ������ڵ���
 */
template<typename T>
class LinkedListNode {
    friend class LinkedList<T>;

private:
    T _value;
    LinkedListNode<T>* next;
public:
    LinkedListNode(T value, LinkedListNode<T>* next) : _value(value), next(next) {
    }

    virtual ~LinkedListNode() {}
};


/**
 * ��������
 */
template<typename T>
class LinkedList final : public AbstractList<T> {
    friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& list) {
        list.forEach([](const T& item) {
            cout << item << '\t';
        });
        cout << endl;
        return os;
    }

private:
    LinkedListNode<T>* _head = nullptr;
    LinkedListNode<T>* _tail = nullptr;
    size_t _length = 0;
public:
    LinkedList() {}

    LinkedList(std::initializer_list<T> initializerList) {
        for (auto item:initializerList) {
            add(item);
        }
    }

    LinkedList(const LinkedList<T>& src) {
        for (LinkedListNode<T>* ptr = src._head->next; ptr; ptr = ptr->next) {
            add(ptr->_value);
        }
    }

    LinkedList& operator=(const LinkedList<T>& src) {
        if (&src == this) {
            return *this;
        }
        clear();
        for (LinkedListNode<T>* ptr = src._head->next; ptr; ptr = ptr->next) {
            add(ptr->_value);
        }
        return *this;
    }

    ~LinkedList() override { clear(); }

    friend LinkedList<T>& operator<<(LinkedList<T>& list, T elem) {
        return list.add(elem);
    }


    const T& get(size_t index) const override {
        if (_length == 0)throw exception("get:������!");
        else if (index >= _length) throw exception("get:���!");
        int i = 0;
        for (LinkedListNode<T>* ptr = _head->next; ptr; ptr = ptr->next) {
            if (i++ == index) {
                return ptr->_value;
            }
        }
        throw exception("get:δ֪����!");
    }


    LinkedList<T>& set(size_t index, T newElem) override {
        if (index > _length - 1) {
            throw exception("set:���!");
        }
        int i = 0;
        for (LinkedListNode<T>* ptr = _head->next; ptr; ptr = ptr->next) {
            if (i++ == index) {
                ptr->_value = newElem;
                return *this;
            }
        }
        throw exception("set:δ֪����!");
    }

    size_t length() const {
        return _length;
    }

public:

    LinkedList<T>& add(T data) override {
        // �����ɽ��
        LinkedListNode<T>* pNode = new LinkedListNode<T>(data, nullptr);
        // ����ǵ�һ�����
        if (_length == 0) {
            if (_head != nullptr)delete _head;
            _head = new LinkedListNode<T>(data, pNode);
            _tail = pNode;
        } else {
            _tail->next = pNode;
            // β���ָ�������ɵĽ��
            _tail = pNode;
        }
        _length++;
        return *this;
    }

    LinkedList<T>& insert(T newElem, size_t pos) override {
        if (pos >= _length) {
            return add(newElem);
        }
        LinkedListNode<T>* pNode = new LinkedListNode<T>(newElem, nullptr);
        int i = -1;
        for (LinkedListNode<T>* ptr = _head; ptr; ptr = ptr->next) {
            if (i == pos - 1) {
                pNode->next = ptr->next;
                ptr->next = pNode;
                break;
            }
            i++;
        }
        _length++;
        return *this;
    }


    size_t indexOf(T target) const override {
        int i = 0;
        for (LinkedListNode<T>* ptr = _head->next; ptr; ptr = ptr->next) {
            if (ptr->_value == target) {
                return i;
            }
            i++;
        }
        throw exception("indexOf:δ�ҵ���Ԫ��!");
    }


    LinkedList<T>& remove(size_t index) override {
        if (index > _length - 1) {
            throw exception("remove:���!");
        }
        int i = -1;
        for (LinkedListNode<T>* ptr = _head; ptr; ptr = ptr->next, i++) {
            if (i + 1 == index) {
                auto temp = ptr->next;
                ptr->next = ptr->next->next;
                delete temp;
                // �����β���
                if (index == _length - 1) {
                    _tail = ptr;
                }
                break;
            }
        }
        _length--;
        if (_length == 0) {
            delete _head;
            _head = _tail = nullptr;
        }
        return *this;
    }

    LinkedList<T>& clear() override {
        if (!_length)return *this;
        LinkedListNode<T>* ptr = _head;
        while (ptr) {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
        _head = _tail = nullptr;
        _length = 0;
        return *this;
    }

    LinkedList<T>& forEach(const std::function<void(T)>& fn) override {
        if (_length == 0)throw exception("forEach:������!");
        for (LinkedListNode<T>* ptr = _head->next; ptr; ptr = ptr->next) {
            fn(ptr->_value);
        }
        return *this;
    }
};
