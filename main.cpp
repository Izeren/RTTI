#include <iostream>
#include <cstddef>
#include "RTTI.h"

#include "Globals.h"

class D {
public:
    int value;
    D(int value = 0) : value(value) {}
};

class E {
public:
    int anotherValue;
    E(int anotherValue = 0) : anotherValue(anotherValue) {}
};

class C {
public:
    std::string branchName;
    C(std::string branchName = "") : branchName(branchName) {}
};

class B : public D, public E {
public:
    B(int value = 1, int anotherValue = 2) : D(value), E(anotherValue) {}
};

class A : public B, public C {
public:
    A(int value = 3, int anotherValue = 4, std::string branchName="right") : B(value, anotherValue), C(branchName) {}
};

int main( ) {
    DECLARE_CLASS(A);
    DECLARE_CLASS(B);
    DECLARE_CLASS(C);
    DECLARE_CLASS(D);
    DECLARE_CLASS(E);

    DERIVED(B, D);
    DERIVED(B, E);
    DERIVED(A, B);
    DERIVED(A, C);


    B* ba = NEW_RTTI(A);
    E* ea = NEW_RTTI(A);
    C* ca = NEW_RTTI(A);
    D* db = NEW_RTTI(B);
    std::cout << TYPEID(ba).ToString() << "\n";
    std::cout << TYPEID(ea).ToString() << "\n";
    std::cout << TYPEID(ca).ToString() << "\n";
    std::cout << TYPEID(db).ToString() << "\n";
    std::cout << EQUALS(ba, ea) << "\n";
    std::cout << EQUALS(ba, db) << "\n";

//    B* bb = DYNAMIC_CAST(A, B, b);
//    std::cout << EQUALS(d, bb) << "\n";

    return 0;
}
