#include <map>
#include <stdexcept>

#include "IndexedSet.h"

IndexedSet::IndexedSet() : valuesSet(), valuesArray(nullptr) {}
IndexedSet::IndexedSet(const IndexedSet& other) : valuesSet(other.valuesSet) {
    valuesArray = new Value[other.size()];
    if (other.valuesArray != nullptr)
    {
        for (size_t i = 0; i < other.size(); i++)
        {
            valuesArray[i] = other.valuesArray[i];
        }
    }
    else
    {
        valuesArray = nullptr;
    }
}

void IndexedSet::add(const Value& v){
    valuesSet.insert(v);
    clearIndex();
}

size_t IndexedSet::size() const { return valuesSet.size(); }

const Value& IndexedSet::operator[](size_t index){
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index out of range");
    }

    if (valuesArray == nullptr)
    {
        buildIndex();
    }
    return valuesArray[index];
}

IndexedSet& IndexedSet::operator=(const IndexedSet& other){
    if (this != &other)
    {
        clearIndex();
        valuesSet = other.valuesSet;

        if (other.valuesArray != nullptr)
        {
            valuesArray = new Value[other.size()];
            for (size_t i = 0; i < other.size(); i++)
            {
                valuesArray[i] = other.valuesArray[i];
            }
        }
    }
    return *this;

}

IndexedSet::~IndexedSet() { clearIndex(); }

    void IndexedSet::buildIndex(){
        clearIndex();
        valuesArray = new Value[size()];
        int index = 0;
        for (std::set<Value>::iterator it = valuesSet.begin(); it != valuesSet.end();it++)
        {
            valuesArray[index] = *it;
            index++;
        }
    }
    void IndexedSet::clearIndex(){
        delete[] valuesArray;
        valuesArray = nullptr;
    }