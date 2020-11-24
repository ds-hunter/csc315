#ifndef SMART_POINTER_H
#define SMART_POINTER_H

template <class ptr>
class SmartPointer {
        ptr* pointer;
    public:
        
        // Class functions are defined here to avoid redundant use of 
        // template <class ptr> for all class definitions in a .cpp file
        SmartPointer(ptr* p = nullptr) : pointer(p) {}
    
        ~SmartPointer() { 
            delete pointer; 
        }

        ptr& operator*() { 
            return *pointer; 
        }

        ptr* operator->() {
            return pointer;
        }
};

#endif
