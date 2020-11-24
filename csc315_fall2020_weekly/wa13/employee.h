#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

class Employee{
    int _id;
    std::string _name;

    public:
    Employee(std::string name, int id): _name(name), _id(id){}
    ~Employee(){}

    void PrintInfo(){
        std::cout << "Hi I am " << _name << " and my id is " << _id << std::endl;
    }
};
#endif
