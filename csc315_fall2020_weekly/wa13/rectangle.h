#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>

class Rectangle{
    int _height;
    int _width;

    public:
    Rectangle(int height, int width): _height(height), _width(width){}
    ~Rectangle(){}

    void PrintInfo(){
        std::cout << "This is a " << _height << " x " << _width << " rectangle" << std::endl;
    }
};
#endif
