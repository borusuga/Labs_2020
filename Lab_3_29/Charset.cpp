//
//  Charset.cpp
//  Lab_3_29
//
//  Created by Alyona Borushnova on 15.10.2020.
//

#include "Charset.hpp"
#include <iostream>

namespace ThirdLab3{
    CharSet::CharSet(int cardinal){     //работает
        // констпуктор по мощности
        if (cardinal <= 100){
            char* nw = new char[cardinal];
            this->cardinality = cardinal;
            for (int i = 0; i <= cardinal; i++){
                nw[i] = '\0';
            }
            for (int i = 0; i < cardinal; i++){
                nw[i] = 32+i;
            }
            this->value=nw;
            delete[] nw;
        }
        else throw std::invalid_argument ("Input cardinality is bigger than possible one");
    }
    

    char* DeleteIdenticalChar(char* line){  //работает
        // удаление повторяющихся
        int n = (int)strlen(line);
        char* ptr1 = &line[0];
        char* ptr2 = &line[0] + 1;
        char* a = new char[n];
        for (int i = 0; i <= n; i++){
            a[i] = '\0';
        }
        bool b = true;
        int i = 0;
        if (n <= 1){
            delete [] a;
            return line;
        }
        while (*(ptr1) != '\0') {
            while (*(ptr2) != '\0' && b) {
                if (*(ptr1) == *(ptr2))
                    b = false;
                ptr2++;
            }
            if (b){
                a[i] = *(ptr1);
                i++;
            }
            b = true;
            ptr1++;
            ptr2 = ptr1 + 1;
        }
        line = a;
        delete [] a;
        return line;
    }

    CharSet::CharSet(char* line){   // работает
        // конструктор по строке
        line = DeleteIdenticalChar(line);
        //char* ptr = &line[0];
        int cardinal = (int)strlen(line);
        if (cardinal <= 100){
            this->cardinality = cardinal;
            this->value = line;
        }
        else throw std::invalid_argument ("Input char set is bigger than possible one");
    }

    CharSet::CharSet(char line){   // работает
        // конструктор по символу
        //char* ptr = &line[0];
        int cardinal = 1;
        this->cardinality = cardinal;
        this->value = &line;
    }

//    std::istream& operator >> (std::istream& c, CharSet& charset){    // работает
//        int k = 0;
//        std::cout << "cordinality(1) : value(2) ?" << std::endl;
//        c >> k;
//        if (k == 1){
//            std::cout << "Enter cordinality -> ";
//            c >> k;
//            charset = ThirdLab3::CharSet(k);
//        }
//        else{
//            std::cout << "Enter value -> ";
//            char* nw = new char[MAX_SIZE];
//            c >> nw;
//            charset = ThirdLab3::CharSet(nw);
//        }
//        return c;
//    }



    std::ostream& operator << (std::ostream& s, const CharSet& charset){    // работает
        if (charset.cardinality){
            s << "Set: ";
            for (int i = 0; i < charset.cardinality; i++){
                s << charset.value[i];
            }
            s << std::endl;
            s << "Cardinality: " << charset.cardinality;
        }
        else s << "The char set is empty";
        return s;
    }


    bool CharSet::Existence (char symbol[1]) const {  // работает
    // проверяет, есть ли данный символ в множестве
        bool flag = false;
        for (int i = 0; i < this->cardinality; i++){
            if (this->value[i] == *symbol){
                flag = true;
                break;
            }
        }
        return flag;
    }

    bool CharSet::Equality(const CharSet &charset){     // не надо, но работает
    // проверяет равенство множеств
        bool flag = true;
        if (this->cardinality != charset.cardinality)
            flag = false;
        for (int i = 0; (i < this->cardinality) && flag; ++i) {
            if (this->Existence(&charset.value[i])){
                flag = false;
            }
        }
        return flag;
    }

    CharSet CharSet::Intersection (CharSet& charset){  // работает вроде
    // находит пересечение множеств
        int cardinal = 0;
        char* sub = new char[cardinal];
        int j = 0;
        for (int i = 0; i < this->cardinality; ++i){
            if (charset.Existence(&this->value[i])){
                sub[j] = this->value[i];
                ++j;
                ++cardinal;
            }
        }
        ThirdLab3::CharSet ncs(sub);
        //ncs->value = sub;
        //ncs->cardinality = cardinal;
        delete [] sub;
        return ncs;
    }


    CharSet* CharSet::Subtraction (CharSet& charset){ // работает
    // множество = разность множеств
        int cardinal = this->cardinality;
        char* sub = new char[cardinal];
        for (int i = 0; i < this->cardinality; i++){
            sub[i] = '\0';
        }
        int j = 0;
        for (int i = 0; i < this->cardinality; i++){
            bool b = this->Existence(&charset.value[i]);
            if (!b){
                sub[j] = this->value[i];
                j++;
                cardinal++;
            }
        }
        ThirdLab3::CharSet * ncs = new ThirdLab3::CharSet(sub);
        //this->value = sub;
        delete [] sub;
        return ncs;
    }
    
    CharSet CharSet::Addition(CharSet& charset){   // работает
        // множество = объединение множеств
        int cardinal = this->cardinality;
        for (int i = 0; i < charset.cardinality; ++i) {
            if (!this->Existence(&charset.value[i])) {
                cardinal++;
            }
        }
        char* sub = new char[cardinal];
        int i = 0;
        for (i = 0; i < this->cardinality; ++i) {
            sub[i] = this->value[i];
        }
        
        for (int j = 0; j < charset.cardinality; ++j) {
            if (!this->Existence(&charset.value[j])) {
                sub[i] = charset.value[j];
                ++i;
            }
        }
        ThirdLab3::CharSet ncs(sub);
        //this->value = sub;
        delete [] sub;
        return ncs;
    }

//перегрузка операторов

    CharSet CharSet::operator= (const CharSet& charset){
        this->cardinality = charset.cardinality;
        for (int i = 0; i < this->cardinality; i++){
            this->value[i] = charset.value[i];
        }
        return *this;
    }

    CharSet CharSet::operator+= (char ch){
        ThirdLab3::CharSet ncs(ch);
        *this = *this + ncs;
        return *this;
    }

    CharSet operator- (const CharSet& charset1, const CharSet& charset2){ //работает
        int cardinal = charset1.cardinality;
        char* sub = new char[cardinal];
        for (int i = 0; i < charset1.cardinality; i++){
            sub[i] = '\0';
        }
        int j = 0;
        for (int i = 0; i < charset1.cardinality; i++){
            bool b = charset1.Existence(&charset2.value[i]);
            if (!b){
                sub[j] = charset1.value[i];
                j++;
                cardinal++;
            }
        }
        ThirdLab3::CharSet ncs(sub);
        //this->value = sub;
        delete [] sub;
        return ncs;
    }


    CharSet operator+ (const CharSet& charset1, const CharSet& charset2){   // работает
        int k = charset1.cardinality+charset2.cardinality;
        char* nc = new char[k];
        for (int i = 0; i < k; ++i){
            nc[i] = '\0';
        }
        for (int i = 0; i < charset1.cardinality; ++i){
            nc[i] = charset1.value[i];
        }
        for (int i = 0; i < charset2.cardinality; ++i){
            nc[charset1.cardinality + i] = charset2.value[i];
        }
        nc = DeleteIdenticalChar(nc);
        ThirdLab3::CharSet ncs(nc);
        delete [] nc;
        return ncs;
        //else throw std::invalid_argument("Total set is too big");
    }

    CharSet operator* (const CharSet& charset1, const CharSet& charset2){   // работает
        int cardinal = 0;
        char* sub = new char[cardinal];
        int j = 0;
        for (int i = 0; i < charset1.cardinality; ++i){
            if (charset2.Existence(&charset1.value[i])){
                sub[j] = charset1.value[i];
                ++j;
                ++cardinal;
            }
        }
        ThirdLab3::CharSet ncs(sub);
        //ncs->value = sub;
        //ncs->cardinality = cardinal;
        delete [] sub;
        return ncs;
    }

}
