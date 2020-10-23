//
//  Charset.hpp
//  Lab_3_29
//
//  Created by Alyona Borushnova on 15.10.2020.
//

#ifndef Charset_hpp
#define Charset_hpp

#include <stdio.h>
#include <iostream>

namespace ThirdLab3{
    
 //   #define MAX_SIZE 1000

    class CharSet{
    private:
        char* value;
        int cardinality;
    public:
        CharSet(int cardinal = 0); // конструктор по умолчанию
//        char* DeleteIdenticalChar (char* line, int &);
        CharSet(char* line);
        friend std::istream& operator >> (std::istream& c, CharSet&);
        friend std::ostream& operator << (std::ostream& s, const CharSet& charset);
        bool Equality(const CharSet& charset);
        CharSet* Subtraction (CharSet& charset);//вычитание множеств
        CharSet* intersection (CharSet& charset);//пересечение
        CharSet& Injection(char symbol[1]);//вставка нового элемента
        CharSet* Addition(CharSet& charset);//объединение множеств
        //~CharSet();

        bool Existence (char symbol[1]) const;
        
        //перегрузка операторов
        CharSet& operator= (const CharSet& charset);
        CharSet operator- (CharSet& charset);
        CharSet* operator+= (CharSet& charset);
        CharSet* operator* (CharSet& charset){
            return this->intersection(charset);
        }
        CharSet operator+ (CharSet& charset1);
        
    };

    char* DeleteIdenticalChar (char* line);
}
#endif /* Charset_hpp */
