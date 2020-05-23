#ifndef HASH_TABLE_LIST_H
#define HASH_TABLE_LIST_H

#include "Config.h"
#include "Errors.h"

namespace mm {
    template <class T>
    class List;
}

template <class T>
class mm::List
{
private:
    int* prev{};
    T* data{};
    int* next{};

    int first{NULLPOINTER};
    int last{NULLPOINTER};
    int free{};

    size_t size{};
    size_t maxsize{INIT_SIZE};
    void ResizeUp();

public:
    List();

    T front();
    T back();

    void push_back(T value);
    T pop_back();

    int begin();
    int end();

    void push_front(T value);
    T pop_front();

    void insert_after(T value, const int num);
    void insert_before(T value, const int num);

    T delete_elem(const int num);
    int list_size();

    void Dump();

    ~List();
};

template<class T>
mm::List<T>::List()
{
    this->data = new T[INIT_SIZE];
    this->prev = new int[INIT_SIZE];
    this->next = new int[INIT_SIZE];

    for (int i = 0; i < this->maxsize; i++)
        this->prev[i] = NULLPOINTER;

    this->next[INIT_SIZE-1] = NULLPOINTER;

    for (int i = 0; i < this->maxsize - 1; i++)
        this->next[i] = i + 1;
}

template<class T>
mm::List<T>::~List()
{
    delete[] this->data;
    this->data = nullptr;

    delete (this->prev);
    this->prev = nullptr;

    delete (this->next);
    this->next = nullptr;
}


template <class data>
void Reallocate(data*& array, size_t old_size, size_t new_size)
{
    try {
        data* temp = new data[new_size];
        for (int i = 0; i < old_size; i++)
            temp[i] = array[i];
        array = temp;
    } catch (std::bad_alloc& exception) {
        std::cout << "Error occured: " << exception.what();
    }

}


template<class T>
void mm::List<T>::ResizeUp()
{
    this->maxsize *= MULTIPLY;

    Reallocate<int>(this->prev, this->size, this->maxsize);
    Reallocate<T>(this->data, this->size, this->maxsize);
    Reallocate<int>(this->next, this->size, this->maxsize);

    for (int i = this->size; i < this->maxsize; i++) {
        this->prev[i] = NULLPOINTER;
        this->data[i] = {};
    }

    for (int i = this->size; i < this->maxsize - 1; i++)
        this->next[i] = i + 1;
    this->next[this->maxsize - 1] = NULLPOINTER;

    this->free = this->size;
}

///----------------------------------------------------------------------------------------------------
template<class T>
T mm::List<T>::front() {
    try {
        if (this->size == 0)
            throw std::underflow_error(EMPTY_STR);

        return this->data[this->first];
    } catch (std::underflow_error str) {
        std::cout << "Error: " << str.what() << std::endl;
    }

    return 0;
}

///----------------------------------------------------------------------------------------------------
template<class T>
T mm::List<T>::back() {
    try {
        if (this->size == 0)
            throw std::underflow_error(EMPTY_STR);

        return this->data[this->last];
    }
    catch (std::underflow_error& str) {
        std::cout << "Error: " << str.what() << std::endl;
    }

    return 0;
}

///----------------------------------------------------------------------------------------------------
template<class T>
void mm::List<T>::push_back(T value) {
    if (this->size == this->maxsize)
        this->ResizeUp();

    this->size++;

    int temp = this->free;
    this->free = this->next[temp];

    this->prev[temp] = this->last;
    this->data[temp] = value;
    this->next[temp] = NULLPOINTER;

    if (this->size == 1)
        this->first = temp;
    else
        this->next[this->last] = temp;

    this->last = temp;
}

template<class T>
void mm::List<T>::Dump() {
    for (int i = 0; i < this->maxsize; i++)
        std::cout << "\t" << this->prev[i] << "\t" << this->data[i] << "\t" << this->next[i] << std::endl;

    std::cout << "Size:\t" << this->size << std::endl;
    std::cout << "Maxsize:\t" << this->maxsize << std::endl;
    std::cout << "First:\t" << this->first << std::endl;
    std::cout << "Last:\t" << this->last << std::endl;
    std::cout << "Free:\t" << this->free << std::endl;
}


template<class T>
T mm::List<T>::pop_back() {
    try {
        if (this->size == 0)
            throw std::underflow_error(EMPTY_STR);

        this->size--;
        int temp = this->prev[this->last];

        std::cout << "FREE\t" << this->free << std::endl;

        this->next[this->last] = this->free;
        this->prev[this->last] = NULLPOINTER;

        T ret = this->data[this->last];
        this->data[this->last] = {};

        this->free = this->last;

        this->last = temp;

        if (this->size == 0)
            this->first = NULLPOINTER;
        else
            this->next[temp] = NULLPOINTER;

        return ret;
    }
    catch (std::underflow_error str) {
        std::cout << "Error: " << str.what() << std::endl;
    }

    return 0;
}

template<class T>
void mm::List<T>::push_front(T value) {
    if (this->size == this->maxsize)
        this->ResizeUp();

    this->size++;

    int temp = this->free;
    this->data[temp] = value;
    this->free = this->next[temp];

    this->next[temp] = this->first;
    this->prev[this->first] = temp;
    this->first = temp;

    if (this->size == 1)
        this->last = temp;

    this->prev[temp] = NULLPOINTER;
}

template<class T>
T mm::List<T>::pop_front() {
    try {
        if (this->size == 0)
            throw std::underflow_error(EMPTY_STR);

        this->size--;
        T ret = this->data[this->first];

        int temp = this->first;
        this->first = this->next[this->first];

        if (this->size == 0)
            this->last = NULLPOINTER;
        else
            this->prev[this->next[temp]] = NULLPOINTER;

        this->data[temp] = {};
        this->next[temp] = this->free;
        this->free = temp;

        return ret;

    } catch (std::underflow_error str) {
        std::cout << "Error: " << str.what() << std::endl;

        return 0;
    }
}

template<class T>
int mm::List<T>::begin() {
    return this->first;
}

template<class T>
int mm::List<T>::end() {
    return this->last;
}

template<class T>
T mm::List<T>::delete_elem(const int num) {
    try {
        if (num < 0 || num >= this->maxsize)
            throw std::out_of_range(OUT_OF_RANGE);

        if (this->prev[num] == NULLPOINTER && num != this->first)
            throw std::out_of_range(OUT_OF_RANGE);

        this->size--;

        T value = this->data[num];

        if (this->size == 0) {
            this->data[num] = {};
            this->next[num] = this->free;
            this->free = num;

            this->first = NULLPOINTER;
            this->last = NULLPOINTER;

            return value;
        }

        if (this->next[num] == NULLPOINTER) {
            int temp = this->prev[num];

            this->next[num] = this->free;
            this->prev[num] = NULLPOINTER;
            this->data[num] = {};

            this->free = num;
            this->last = temp;
            this->next[temp] = NULLPOINTER;

            return value;
        }

        if (this->prev[num] == NULLPOINTER) {
            int temp = this->next[num];

            this->next[num] = this->free;
            this->data[num] = {};

            this->free = num;
            this->first = temp;
            this->prev[temp] = NULLPOINTER;

            return value;
        }

        int nxt = this->next[num];
        int prv = this->prev[num];

        this->prev[nxt] = prv;
        this->next[prv] = nxt;

        this->next[num] = this->free;
        this->prev[num] = NULLPOINTER;
        this->data[num] = {};

        this->free = num;

        return value;

    } catch (std::out_of_range& str) {
        std::cout << "Error: " << str.what() << std::endl;

        return {};
    }
}

template<class T>
void mm::List<T>::insert_before(T value, const int num) {
    try {
        if (num < 0 || num >= this->maxsize)
            throw std::out_of_range(OUT_OF_RANGE);

        if (this->prev[num] == NULLPOINTER && num != this->first)
            throw std::out_of_range(OUT_OF_RANGE);

        if (this->size == this->maxsize)
            this->ResizeUp();

        if (num == this->first) {
            this->push_front(value);
            return;
        }

        this->size++;

        int temp = this->free;
        this->free = this->next[temp];

        this->prev[temp] = this->prev[num];
        this->next[temp] = num;

        this->prev[num] = temp;
        this->next[this->prev[temp]] = temp;

        this->data[temp] = value;

    } catch (std::out_of_range str) {
        std::cout << "Error: " << str.what() << std::endl;
    }
}

template<class T>
void mm::List<T>::insert_after(T value, const int num) {
    try {
        if (num < 0 || num >= this->maxsize)
            throw std::out_of_range(OUT_OF_RANGE);

        if (this->prev[num] == NULLPOINTER && num != this->first)
            throw std::out_of_range(OUT_OF_RANGE);

        if (this->size == this->maxsize)
            this->ResizeUp();

        if (num == this->last) {
            this->push_back(value);
            return;
        }

        this->size++;

        int temp = this->free;
        this->free = this->next[temp];

        this->next[temp] = this->next[num];
        this->prev[temp] = num;

        this->next[num] = temp;
        this->prev[this->next[temp]] = temp;

        this->data[temp] = value;

    } catch (std::out_of_range str) {
        std::cout << "Error: " << str.what() << std::endl;
    }
}

template<class T>
int mm::List<T>::list_size() {
    return this->size;
}




///----------------------------------------------------------------------------------------------------


#endif //HASH_TABLE_LIST_H
