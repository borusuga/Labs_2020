//
//  HRD.hpp
//  Lab_4
//
//  Created by Alyona Borushnova on 28.11.2020.
//

#ifndef HRD_hpp
#define HRD_hpp

#include "mmap.h"

#include <stdio.h>
#include <map>
#include <string>
#include <iostream>

///This is a Human resourses department namespace
///
///Within this namespace we have 4 classes:
///1. Worker
///     a) Master
///     b) Slave
///2. Department
namespace Org {

class Worker;
class Master;
class Slave;
class Department;


class Worker{
private:
    ///@param fullname describes name of the worker
    std::string fullname;
    ///@param birthdate describes name of the worker
    std::string birthdate;
    std::string position;
    std::string education;
    int salary;
public:
    Worker();
    Worker(std::string fullname, std::string birthdate, std::string position, std::string education, int salary);
    ~Worker();
    
    virtual std::string get_type();
    void get_info();
    std::string get_name();
    void change_name(std::string s);
    std::string get_birthdate();
    void change_birthdate(std::string s);
    std::string get_education();
    void change_education(std::string s);

    std::string get_position();

    void change_position(std::string new_pos);
    
    int get_salary();
    void change_salary(int new_salary);
};

/// This is Master class. This class is extention of Worker class. Besides the information
/// fields it also contains pointer to the subdepartment.
class Master : public Worker{
private:
    Department* dep;
public:
    Master(std::string fullname, std::string birthdate, std::string position, std::string education, int salary, Department* dep);
    Master();
    void change_dep(Department* dp);
    Department* get_dep();
    
    std::string get_type();
    
    Slave* make_slave();
};

/// This is Slave class. This class is extention of Worker class. Besides the information
/// fields it also contains the ability of promotion to the Master.
class Slave : public Worker {
public:
    Slave(std::string fullname, std::string birthdate, std::string position, std::string education, int salary);
    std::string get_type();
    Slave();
    
    Master* make_master(Department* dp);
};

/// This is Department class. This class contains name of the depsrtment
/// and information about its workers
class Department{
private:
    std::string name;
    //std::map <int, Worker*> workers;
    mmap::Mymap <int, Worker*> workers;
public:
    Department(): name("Defolt Department") {};
    Department(std::string name);
    Department(std::string name, std::map <int, Worker*> workers);
    ~Department();
    Department* find_dep(std::string depname);
    bool add_worker(int shifr, Worker* w);
    void add_slave(std::string depname, Worker* w, int sh);
    void add_master(std::string depname);
    Worker* find_worker(int shifr);
    Master* find_worker(std::string name);
    void delete_worker(int shifr);
    std::string getname_dep(){
        return name;
    };
    void show_info();
    
    void lvlup(int shifr);
    
    void fire(int shifr);
    
    void show_workers(std::string depname);
    
};


}

#endif /* HRD_hpp */
