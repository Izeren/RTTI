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


    B* ba = NEW_RTTI(B, A);
    E* ea = NEW_RTTI(E, A);
    C* ca = NEW_RTTI(C, A);
    D* db = NEW_RTTI(D, B);
    std::cout << TYPEID(ba).ToString();                   // Name: A Hash: 0 [ B C ]
    std::cout << TYPEID(ea).ToString();                   // Name: A Hash: 0 [ B C ]
    std::cout << TYPEID(ca).ToString();                   // Name: A Hash: 0 [ B C ]
    std::cout << TYPEID(db).ToString();                   // Name: B Hash: 1 [ D E ]
    std::cout << EQUALS(ba, ea) << "\n";                  // true
    std::cout << EQUALS(ba, db) << "\n";                  // false

    B* bb = DYNAMIC_CAST(D, B, db);
    std::cout << TYPEID(bb).ToString();                   // Name: B Hash: 1 [ D E ]
    std::cout <<"Value: " <<  bb->value << "\n";          // Value: 1
    std::cout << EQUALS(db, bb) << "\n";                  // true

    B* eba = DYNAMIC_CAST(E, B, ea);
    std::cout << TYPEID(eba).ToString();                  // Name: A Hash: 0 [ B C ]
    std::cout << "value: " << eba->value << "\n";         // value: 3
    std::cout << EQUALS(eba, ea) << "\n";                 // true

    return 0;
}
