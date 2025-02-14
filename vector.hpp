#include <iostream>
#include <memory>
#include <stdexcept>

template<class T>
class Iterator {
    public:
        explicit Iterator(T* ptr) : current(ptr) {}
        
        bool operator!=(const Iterator<T>& rhs) {
            return current != rhs.current;
        }
        
        T& operator*() {
            return *current;
        }
        
        Iterator<T>& operator++() {
            ++current;
            return *this;
        }
    private:
        T* current;
};

template<class T>
class Vector {
    private:
        T* vector = nullptr;
        size_t maxsize = 0;
        size_t capacity = 0;
        void resize(const size_t capacity);
    public:
        Vector() = default();
        Vector(size_t capacity, const T& init);
        Vector(size_t count);

        Vector(const Vector<T>& rhs);
        Vector<T>& operator = (const Vector<T>& rhs)
        ~Vector() {delete[] vector};

        size_t size() const;
        size_t capacity() const;
        bool empty() const;
        T& operator[] (const size_t index);
        T& front() const;
        T& back() const;

        void emplace_back(const T& elem);
        T pop_back();

        Iterator<T> begin();
        Iterator<T> end();

        void erase(Iterator<T> position);
};

template<class T>
T& Vector<T>::operator[] (const size_t index) {
    if (index >= capacity) {
        throw std::invalid_argument("index is bigger that current capacity of the vector");
    }
    else {
        return vector[index];
    }
}

template<class T>
Vector<T>::Vector(size_t capacity, const T& init)  {
    this->capacity = capacity;
    maxsize = capacity;
    vector = new T[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        vector[i] = init;
    }
}

template<class T>
Vector<T>::Vector(size_t count): capacity(count), maxsize(count) {
    vector = new T[capacity];
    for (size_t i = 0; i < capacity; ++i)
    {
        vector[i] = T();
    }
}

template<class T>
Vector<T>::Vector(const Vector<T>& rhs) {
    detete[] vector;

    capacity = rhs.capacity;
    maxsize = rhs.maxsize;
    vector = new T[capacity];
    for (size_t i = 0; i < capacity; i++) {
        vector[i] = rhs[i];

    }
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    if (this== &rhs) return *this;

    if (rhs.capacity <= maxsize) {
        for (size_t i = 0; i < rhs.capacity; i++) {
            vector[i] = rhs.vector[i];
        }
        capacity = rhs.capacity;
        return *this;
    }
    T* p = new T[rhs.capacity];
    for (size_t i = 0; i < rhs.capacity; i++) {
        p[i] = rhs.vector[i];
    }
    delete[] vector;
    capacity = rhs.capacity;
    maxsize = rhs.maxsize;
    vector = p;
    return *this;
}

template<class T>
size_t Vector<T>::size() const {return size;}

template<class T>
size_t Vector<T>::capacity() const {return capacity;}

template<class T>
bool Vector<T>::empty() const {return capacity == 0;}

template<class T>
T& Vector<T>::front() {
    if (capacity > 0)
    {
        return vector[0];
    }
}

template<class T>
T& Vector<T>::back() {
    if (capacity > 0)
    {
        return vector[capacity - 1];
    }
}

template<class T>
void Vector<T>::resize(const size_t capacity)
{
    if (capacity > maxsize)
    {
        T *temp = new T[capacity];
        for (size_t i = 0; i < capacity; ++i)
        {
            temp[i] = vector[i];
        }
        delete[] vector;
        vector = temp;
        maxsize = capacity;
    }
}

template<class T>
void Vector<T>::emplace_back(const T& elem) {
    if (capasity == maxsize) {
        if (capacity == 0) {
            resize(8);
        }
        else {
            resize(capacity + capacity);
        }
    }
    else {
        vector[capacity] = elem;
        capacity++;
    }
}

template<class T>
T Vector<t>::pop_back() {
    if (capacity > 0) {
        T to_return = vector[capacity - 1];
        capacity--;
        return to_return;
    }
    else {
        throw std::out_of_range("Nothing to pop");
    }
}

template<class T>
Iterator<T> Vector<T>::begin() {
    return Iterator<T>(&vector[0]);
}

template<class T>
Iterator<T> Vector<T>::end() {
    return Iterator<T>(&vector[capacity]);
}

template<class T>
void Vector<T>::erase(Iterator<T> position) {
    T* pos = &(*position);
    size_t index = pos - vector;
    
    if (index >= capacity) {
        throw std::out_of_range("Iterator out of range");
    }
    
    for (size_t i = index; i < capacity - 1; ++i) {
        vector[i] = std::move(vector[i + 1]);
    }
    
    --capacity;
}
