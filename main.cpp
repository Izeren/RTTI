#include <iostream>
#include <cstddef>
#include "RTTI.h"

#include "Globals.h"

class A {
};

class B : public A {

};

class D {};

class C : public D, public B {

};

//A a(0);
int main( ) {
    DECLARE_CLASS(A);
    DECLARE_CLASS(B);
    DECLARE_CLASS(C);
    DECLARE_CLASS(D);

    DERIVED(B, A);
    DERIVED(C, D);
    DERIVED(C, B);


    A* a = NEW_RTTI(B);
    std::cout << TYPEID(a).ToString() << "\n";
//    std::cout << a.a << "\n";
//    std::cout << "CLASS counter: " << CLASS_COUNTER << "\n";
//    std::cout << globalTest.size() << "\n";
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
