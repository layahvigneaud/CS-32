#ifndef HashMap_h
#define HashMap_h

#include <stdio.h>
#include <list>
#include <iostream>
#include <string>

template<typename T>
//Private
class HashMap
{
public:
    HashMap(double max_load = 0.75 );
    ~HashMap();
    void insert(const std::string& key, const T& value);
    int size() const;
    const T* find(const std::string& key) const;
    T& operator[](const std::string& key);
    T* find(const std::string& key) {
     const auto& hm = *this;
     return const_cast< T*>(hm.find(key));
     }
    
private:
    int m_numItems;
    int m_numBuckets;
    
    double m_maxLoad;
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;

    
    struct KeyValue{
        std::string key;
        T value;
        
       
    };
    std::list<KeyValue>* m_map;
    unsigned int getBucket(const std::string& key) const;
    void resize();
    
};

//Constructor
template<typename ValueType>
HashMap<ValueType>:: HashMap(double max_load)
{
    m_numItems = 0;
    m_numBuckets = 10;
    m_maxLoad = max_load;
    m_map = new std::list<KeyValue> [m_numBuckets];
}

//Delete function

template <typename ValueType>
HashMap<ValueType>::~HashMap()
{
    delete[] m_map;
}



//Gets size
template <typename ValueType>
int HashMap<ValueType>::size() const
{
    return m_numItems;
}


//Insert in the hash map
template< typename ValueType>
void HashMap<ValueType>:: insert(const std::string &key, const ValueType& value)
{
    ValueType* currVal = find(key);
    if(currVal != nullptr){
        *currVal = value;
        return;
    }
    
    KeyValue kv;
    kv.key = key;
    kv.value = value;
    
    
    
    unsigned int bucketValue = getBucket(key);
    m_map[bucketValue].push_back(kv);
    m_numItems++;
    
    if(m_numItems/static_cast<double>(m_numBuckets) > m_maxLoad){
        resize();
    }
}
//Resizes the hash map
template<typename ValueType>
void HashMap<ValueType>:: resize()
{
    int oldBucketNum = m_numBuckets;
    m_numBuckets *=2;
    std::list<KeyValue>* newMap = new std::list<KeyValue>[m_numBuckets];
    for(int i = 0; i < oldBucketNum; i++){
        while(m_map[i].size() > 0){
            auto it = m_map[i].begin();
            unsigned int newBucketNum = getBucket(it->key);
            newMap[newBucketNum].splice(newMap[newBucketNum].begin(), m_map[i], it);
        }
    }
    delete[] m_map;
    m_map = newMap;
    
}
//Finds items in the hash map
template <typename ValueType>
const ValueType* HashMap<ValueType>::find(const std::string & key) const
{
    unsigned int bucketNum = getBucket(key);
    for (auto it = m_map[bucketNum].begin(); it != m_map[bucketNum].end(); it++) {
        if ((*it).key == key)
            return &it->value;
    }

    return nullptr;
}


template <typename ValueType>
unsigned int HashMap<ValueType>::getBucket(const std:: string& key) const
{
    size_t hash = std::hash<std::string>()(key);
    return hash % m_numBuckets;
}

//Operator function
template<typename T>
T& HashMap<T>::operator[](const std::string& key) {
    T* keyinMap = find(key);
    if(keyinMap != nullptr){
        return *keyinMap;
    }
    else{
        insert(key, T());
        return *(find(key));
    }
}


#endif /* HashMap_h */
