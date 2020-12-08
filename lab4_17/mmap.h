//
//  mmap.h
//  Lab_4
//
//  Created by Alyona Borushnova on 08.12.2020.
//

#ifndef mmap_h
#define mmap_h

#include <stdio.h>
#include<iostream>
#include <cmath>
namespace mmap {

template <typename T1, typename T2>
struct T
{
    T1 first;
    T2 second;
};

template<typename T1, typename T2>
class Mymap{
private:
    unsigned int _current_size;
    unsigned int _size;
    T<T1, T2>* buff;
    
public:

    typedef T<T1, T2> Iterator;
    
    Mymap() {
        _current_size=0;
        _size=0;
        buff = nullptr;
    }

    Mymap(int size){
        _current_size=size;
        _size=0;
        buff = new T<T1, T2>[_size];
    }
    
    ~Mymap(){
        delete [] buff;
    }
    
    Iterator* begin(){
        return this->buff;
    }
    
    Iterator* end(){
        return (this->buff + this->_size);
    }
    
    bool empty(){
        if (this->_current_size == 0)
            return true;
        else
            return false;
    }
    
    void clear(){
        _size = 0;
        _current_size = 0;
        delete [] buff;
    }
    
    Iterator* find(int kkey){
        for (Iterator* i = begin(); i != end(); ++i){
            if (i->first == kkey){
                return i;
            }
        }
        return nullptr;
    }
    
    void allocate(){
        int n = 1 + _current_size;
//        if (_current_size <=2){
//            n = 2;
//        }
//        else
//            n = _current_size + std::round(log(_current_size)/log(2.0)) + 1;
        Iterator* buff = new Iterator[n];
        Iterator* count = buff;
        for (Iterator* i = begin(); i != end(); ++i, ++count) {
            count->second = i->second;
            count->first = i->first;
        }
        delete this->buff;
        this->buff = buff;
        _current_size = n;
    }
    
    std::pair<Iterator*, bool> insert(std::pair<T1, T2> elem){
        if (find(elem.first)){
            return std::pair<Iterator*, bool>(nullptr, false);
        }
        if (_size == _current_size){
            allocate();
        }
        (this->buff+_size)->first = elem.first;
        (this->buff+_size)->second = elem.second;
        ++_size;
        return std::pair<Iterator*, bool>((this->buff+_size), true);
    }
    
    void reallocate(){
        int n = 1;
//        if (_current_size <=2){
//            n = 2;
//        }
//        else
//            n = _current_size + std::round(log(_current_size)/log(2.0)) + 1;
        Iterator* buff = new Iterator[n];
        Iterator* count = buff;
        for (Iterator* i = begin(); i != end(); ++i, ++count) {
            count->second = i->second;
            count->first = i->first;
        }
        delete this->buff;
        this->buff = buff;
        _current_size += n;
    }
    
    std::pair<Iterator*, bool> erase(Iterator* elem){
        Iterator* er = find(elem->first);
        if (er != nullptr){
            if (_size != 1) {
                er->second = (this->end()-1)->second;
                er->first = (this->end()-1)->first;
            }
            --_size;
            return std::pair<Iterator*, bool>(er, true);
        }
        
        return std::pair<Iterator*, bool>(nullptr, false);
    }
    
};

}

#endif /* mmap_h */
