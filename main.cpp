#include <iostream>
#include <cstddef>
#include "RTTI.h"

#include "Globals.h"

class A {
public:
    int a;
    A(int a = 0) {
        CLASS_COUNTER = 10;
        this->a = CLASS_COUNTER;
        globalTest.push_back(0);
        std::cout << globalTest.size() << "\n";
//        registeredClasses["test"] = nullptr;
    }
};

A a(0);
int main( ) {
    std::cout << a.a << "\n";
    std::cout << "CLASS counter: " << CLASS_COUNTER << "\n";
    std::cout << globalTest.size() << "\n";
//    __Register test("A");
//    std::cout << registeredClasses.size();
//    std::cout << CLASS_COUNTER << "\n";
//    std::string name = "A";
//    std::cout << registeredClasses.size() << "\n";
//    registeredClasses["A"] = nullptr;
//    std::cout << registeredClasses.size() << "\n";
//    __TypeInfoPtr infoPtr = std::make_shared<__TypeInfo>(name, 0);
//    registeredClasses[name] = infoPtr;

//    __TypeInfoPtr info = TYPEID(A);
//    std::cout << info->ToString();
    return 0;
}
