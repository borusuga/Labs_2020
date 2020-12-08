//
//  HRD.cpp
//  Lab_4
//
//  Created by Alyona Borushnova on 28.11.2020.
//

#include "HRD.hpp"

#include "mmap.h"

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <typeinfo>

namespace Org {

Worker::Worker(){
    this->fullname = "Full Name";
    this->birthdate = "??.??.????";
    this->position = "slave";
    this->education = "none";
    this->salary = 300;
}

Worker::Worker(std::string fullname, std::string birthdate, std::string position, std::string education, int salary){
    this->fullname = fullname;
    this->birthdate = birthdate;
    this->position = position;
    this->education = education;
    this->salary = salary;
}

Worker::~Worker(){
}

void Worker::get_info(){
    std::cout << "full name: " << this->fullname << std::endl;
    std::cout << "birth date: " << this->birthdate << std::endl;
    std::cout << "position: " << this->position << std::endl;
    std::cout << "education: " << this->education << std::endl;
    std::cout << "salary: " << this->salary << std::endl;
}

std::string Worker::get_name(){
    return this->fullname;
}

void Worker::change_name(std::string s){
    this->fullname = s;
}

std::string Worker::get_birthdate(){
    return this->birthdate;
}

void Worker::change_birthdate(std::string s){
    this->birthdate = s;
}

std::string Worker::get_education(){
    return this->education;
}

void Worker::change_education(std::string s){
    this->education = s;
}

int Worker::get_salary(){
    return this->salary;
}

void Worker::change_salary(int new_salary){
    this->salary = new_salary;
}

std::string Worker::get_position(){
    return this->position;
}

void Worker::change_position(std::string new_pos){
    if (new_pos == this->get_position()) {
        std::cout << "This position is already set " << std::endl;
    }
    else {
        this->position = new_pos;
    }
}

std::string Worker::get_type(){
    return "Type::Worker";
}


/*-------------*/

Master::Master(){
    this->change_name("Full Name");
    this->change_birthdate("??.??.????");
    this->change_position("master");
    this->change_education("higher");
    this->change_salary(600);
}

Master::Master(std::string fullname, std::string birthdate, std::string position, std::string education, int salary, Department* dep){
    this->change_name(fullname);
    this->change_birthdate(birthdate);
    this->change_position(position);
    this->change_education(education);
    this->change_salary(salary);
    this->dep = dep;
}

std::string Master::get_type(){
    return "Type::Master";
}

Department* Master::get_dep(){
    return this->dep;
}

void Master::change_dep(Department* dp){
    this->dep = dp;
}

Slave* Master::make_slave(){
    Slave* news = new Slave(this->get_name(), this->get_birthdate(), this->get_position(), this->get_education(), this->get_salary());
    return news;
}

/*-------------*/

Slave::Slave(std::string fullname, std::string birthdate, std::string position, std::string education, int salary){
    this->change_name(fullname);
    this->change_birthdate(birthdate);
    this->change_position(position);
    this->change_education(education);
    this->change_salary(salary);
}

Slave::Slave(){
    this->change_name("Full Name");
    this->change_birthdate("??.??.????");
    this->change_position("slave");
    this->change_education("none");
    this->change_salary(300);
}

Master* Slave::make_master(Department* dp){
    Master* newm = new Master(this->get_name(), this->get_birthdate(), this->get_position(), this->get_education(), this->get_salary(), dp);
    return newm;
}

std::string Slave::get_type(){
    return "Type::Slave";
}


/*-------------*/


Department::Department(std::string name){
    this->name = name;
    //инициализация map
    if (this->workers.empty())
        this->workers.clear();
}

Department::Department(std::string name, std::map <int, Worker*> work){
    this->name = name;
    for (auto& it : work) {
        this->workers.insert(std::pair<int, Worker*>(it.first, it.second));
    }
}

Department* Department::find_dep(std::string depname){
    if (this->name == depname){
        return this;
    }
    else{
        for (auto& it: this->workers) {
            if ((it.second != nullptr) && (it.second->get_type() == "Type::Master")) {
                Master* m = dynamic_cast<Master*>(it.second);
                return m->get_dep()->find_dep(depname);
            }
        }
    }
    return nullptr;
}

bool Department::add_worker(int shifr, Worker* w){
    mmap::Mymap<int,Worker*>::Iterator* it;
    it = this->workers.find(shifr);
    if (it == nullptr){
        this->workers.insert(std::pair<int, Worker*>(shifr, w));
        return true;
    }
    else{
        std::cout << "Worker with such shifr already exists\n";
        return false;
    }
}

void Department::add_slave(std::string depname, Worker* w, int sh){
    if (this->find_dep(depname) == nullptr) {
        std::cout << "In " << this->name << ": ";
        std::cout << "there are no such department\n";
    }
    else{
        if (w == nullptr){
            std::cout << "Enter shifr: ";
            std::cin >> sh;
            w = new Slave();
            std::cout << "Enter name: ";
            std::string name;
            std::cin >> name;
            w->change_name(name);
        }
        if(this->add_worker(sh, w)){
            for (auto& it: this->workers) {
                if ((it.second != nullptr) && (it.second->get_type() == "Type::Master")) {
                    Master* m = dynamic_cast<Master*>(it.second);
                    m->get_dep()->add_slave(depname, w, sh);
                }
            }
        }
    }
}

void Department::add_master(std::string depname){
    Department* dp = this->find_dep(depname);
    if (dp == nullptr) {
        std::cout << "In " << this->name << ": ";
        std::cout << "there are no such department\n";
    }
    else{
        std::cout << "Enter shifr: ";
        int sh;
        std::cin >> sh;
        Master* w = new Master();
        std::cout << "Enter name: ";
        std::string name;
        std::cin >> name;
        w->change_name(name);
        std::cout << "Enter the name of the subdepartment: ";
        std::cin >> name;
        Department* subdep = new Department(name);
        w->change_dep(subdep);
        this->add_worker(sh, w);
        for (auto& it: this->workers) {
            if ((it.second != nullptr) && (it.second->get_type() == "Type::Master")) {
                Master* m = dynamic_cast<Master*>(it.second);
                m->get_dep()->add_master(depname);
            }
        }
    }
}

Worker* Department::find_worker(int shifr){
//найти элемент по заданному шифру сотрудника
    mmap::Mymap<int,Worker*>::Iterator* it;
    it = this->workers.find(shifr);
    if ((it != this->workers.end()) && (it != nullptr))
        return it->second;
    return nullptr;
}


Master* Department::find_worker(std::string name){
//найти элемент по заданному названию подразделения (найти начальника заданного отдела)
    for (auto& it : this->workers) {
            Master* m = dynamic_cast<Master*>(it.second);
        if (m){
            Department* dp = m->get_dep();
            if (dp->getname_dep() == name){
                return m;
            }
        }
    }
    return nullptr;
}



void Department::delete_worker(int shifr){
    for (auto it = this->workers.begin(); it != this->workers.end();) {
        if (it->first == shifr) {
            this->workers.erase(it);
            break;
        }
        else{
            ++it;
        }
    }
}

void Department::show_info(){
    for (auto& it : this->workers) {
        std::cout << it.first << std::endl;
        it.second->get_info();
    }
}

void Department::lvlup(int shifr){
    Worker* s = this->find_worker(shifr);
    if(s != nullptr){
        Department* dp = this;
        Master* m = nullptr;
        int msh = -1;
        bool b = true;
        while (b) {
            int mkol = 0;
            for (auto& it : dp->workers) {//проходим по всем сотрудникам
                mkol = 0;
                if (it.second->get_type() == "Type::Master"){//ищем мастеров
                    Master* tmpm = dynamic_cast<Master*>(it.second);
                    if (tmpm->get_dep()->find_worker(shifr) != nullptr){
                        ++mkol;
                        m = tmpm;
                        msh = it.first;
                        dp = m->get_dep();
                        break;
                    }
                }
            }
            if (mkol == 0)
                b = false;
        }
        
        for (auto& it : this->workers) {//проходим по всем сотрудникам
            if (it.first == shifr){
                it.second = (dynamic_cast<Slave*>(s))->make_master(dp);
            }
            if ((it.first == msh) && (m !=nullptr)){
                it.second = m->make_slave();
            }
        }
    }
    else
        std::cout << "No slave with such shifr";
}

void Department::fire(int shifr){
    Worker* s = this->find_worker(shifr);
    Master* tmpm = dynamic_cast<Master*>(s);
    if (tmpm != nullptr){
        mmap::Mymap<int,Worker*>::Iterator* it = tmpm->get_dep()->workers.begin();
        this->lvlup(it->first);
    }
    if(s != nullptr){
        for (auto it = this->workers.begin(); it != this->workers.end();) {
            if (it->first == shifr) {
                it = (this->workers.erase(it)).first;
            }
            else{
                if (it->second->get_type() == "Type::Master"){
                    Master* tmpm = dynamic_cast<Master*>(it->second);
                    tmpm->get_dep()->fire(shifr);
                }
                ++it;
            }
        }
    }
    else
        std::cout << "No slave with such shifr";
}

void Department::show_workers(std::string depname){
    if (this->name == depname){
        std::cout << "Department:\t" << depname << "\n";
        std::cout << "Slaves of this department:\n";
//        for (auto& it2 : this->workers) {
//            std::cout << it2.second->get_name() << "\n";
//        }
        for (auto it2 = this->workers.begin(); it2 != this->workers.end(); it2++){
            std::cout << it2->second->get_name() << "\n";
        }
    }
    else{
        for (auto& it : this->workers) {//проходим по всем сотрудникам
            if (it.second->get_type() == "Type::Master"){//ищем мастеров
                Master* tmpm = dynamic_cast<Master*>(it.second);
                int msh = it.first;
                if (tmpm->get_dep()->name == depname){
                    std::cout << "Department:\t" << depname << "\n";
                    std::cout << "Master of this department:\t" << tmpm->get_name() << "\n";
                    std::cout << "Slaves of this department:\n";
                    for (auto& it2 : tmpm->get_dep()->workers) {
                        if (it2.first != msh)
                            std::cout << it2.second->get_name() << "\n";
                    }
                }
            }
        }
    }
}

Department::~Department(){
    this->workers.clear();
}

}
