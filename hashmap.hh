/*
 *  Source code written by Gabriel Correia
*/

#include <iostream>
#include <cassert>

class hashmap {
public:
    hashmap ()
    {
        buckets_array = new bucket[255];
    }

    ~hashmap ()
    {
        delete[] buckets_array;
    }

    template<typename T>
    bool insert (T key, T value)
    {
        auto bucket = select_bucket (key);
        bucket->key = key;
        bucket->value = value;
        return true;
    }

    std::string search (const std::string& key) 
    {
        auto bucket = select_bucket (key);
        /* Duplicating the string at retrun (Isn't a good idea) */
        if (bucket->key == key) {
            return bucket->value;
        }
        return "Undefined";
    }

    auto operator[] (const std::string& key) 
    {
        //auto value = search (key);
        //std::cout << "Founded value: " << value << std::endl;
        return search (key);
    }

private:
    class bucket {
    public:
        /* Duplicating each value */
        std::string key, value;    
    };

    bucket* buckets_array;

    bucket* select_bucket (const std::string& key)
    {
        bucket *selected_bucket;
        selected_bucket = &buckets_array[hash (key)];
        assert (selected_bucket);
        return selected_bucket;
    }

    int hash (const std::string& key) 
    {
        int digest(0);
        for (auto caracter : key) {
            digest += caracter;
        }
        digest %= 100;
        //std::cout << digest << std::endl;
        return digest;
    }
};
