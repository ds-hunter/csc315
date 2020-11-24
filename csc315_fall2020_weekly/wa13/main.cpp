#include <iostream>
#include "smart_pointer.h"
#include "employee.h"
#include "rectangle.h"

using namespace std;

int main(){
    SmartPointer<Employee> employee(new Employee("John",1234));
    employee->PrintInfo();

    SmartPointer<Rectangle> rectangle(new Rectangle(10,20));
    rectangle->PrintInfo();
    return 0;
}
