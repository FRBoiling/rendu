//
// Created by boil on 18-10-31.
//

#include <cstring>

class IPrototype {
public:
    IPrototype() {}

    virtual ~IPrototype() {}

    virtual IPrototype *Clone() = 0;
};

class ConcretePrototype1 : public IPrototype {
public:
    IPrototype *Clone() override {
        return nullptr;
    }
};

class Client {
public:
    void Operation() {
        ConcretePrototype1 *p1 = new ConcretePrototype1();
        ConcretePrototype1 *c1 = (ConcretePrototype1 *) p1->Clone();

        delete p1;
        p1 = nullptr;
        delete c1;
        c1 = nullptr;
    }
};

int main() {


}