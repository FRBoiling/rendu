//
// Created by boil on 18-10-30.
//

//
// Created by boil on 18-10-3.
//

#include <iostream>
#include <memory>

#include <iostream>

class AbstractProductA {
public:
    AbstractProductA() {
        std::cout << "AbstractProductA Constructor" << std::endl;
    }

    virtual ~AbstractProductA() {
        std::cout << "AbstractProductA Destructor" << std::endl;
    }

public:
    virtual void OperationA() = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
    ConcreteProductA1() {
        std::cout << "ConcreteProductA1 Constructor" << std::endl;
    }

    ~ConcreteProductA1() {
        std::cout << "ConcreteProductA1 Destructor" << std::endl;
    }

public:
    void OperationA() override {
//        std::cout << "ConcreteProductA1 OperationA" << std::endl;
    };
};

class ConcreteProductA2 : public AbstractProductA {
public:
    ConcreteProductA2() {
        std::cout << "ConcreteProductA2 Constructor" << std::endl;
    }

    ~ConcreteProductA2() {
        std::cout << "ConcreteProductA2 Destructor" << std::endl;
    }

public:
    void OperationA() override {
//        std::cout << "ConcreteProductA2 OperationA" << std::endl;
    };
};


class AbstractProductB {
public:
    AbstractProductB() {
        std::cout << "AbstractProductB Constructor" << std::endl;
    };

    virtual ~AbstractProductB() {
        std::cout << "AbstractProductB Destructor" << std::endl;
    };

public:
    virtual void OperationB() = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
    ConcreteProductB1() {
        std::cout << "ConcreteProductB1 Constructor" << std::endl;
    };

    ~ConcreteProductB1() {
        std::cout << "ConcreteProductB1 Destructor" << std::endl;
    };

public:
    void OperationB() override {
//        std::cout << "ConcreteProductB1 OperationB" << std::endl;
    };
};

class ConcreteProductB2 : public AbstractProductB {
public:
    ConcreteProductB2() {
        std::cout << "ConcreteProductB2 Constructor" << std::endl;
    };

    ~ConcreteProductB2() {
        std::cout << "ConcreteProductB2 Destructor" << std::endl;
    };

public:
    void OperationB() override {
//        std::cout << "ConcreteProductB2 OperationB" << std::endl;
    };
};

class AbstractFactory {
public:
    AbstractFactory() {
        std::cout << "AbstractFactory Constructor" << std::endl;
    }

    virtual  ~AbstractFactory() {
        std::cout << "AbstractFactory Destructor" << std::endl;
    }

public:
    virtual AbstractProductA *CreateProductA() = 0;

    virtual AbstractProductB *CreateProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    ConcreteFactory1() {
        std::cout << "ConcreteFactory1 Constructor" << std::endl;
    }

    ~ConcreteFactory1() {
        std::cout << "ConcreteFactory1 Destructor" << std::endl;
    }

public:
    AbstractProductA *CreateProductA() override {
        return new ConcreteProductA1();
    }

    AbstractProductB *CreateProductB() override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    ConcreteFactory2() {
        std::cout << "ConcreteFactory2 Constructor" << std::endl;
    }

    ~ConcreteFactory2() {
        std::cout << "ConcreteFactory2 Destructor" << std::endl;
    }

public:
    AbstractProductA *CreateProductA() override {
        return new ConcreteProductA2();
    }

    AbstractProductB *CreateProductB() override {
        return new ConcreteProductB2();
    }
};

int main() {
    {
        std::unique_ptr<AbstractFactory> factory(new ConcreteFactory1);
        std::unique_ptr<AbstractProductA> productA1(factory->CreateProductA());
        productA1->OperationA();
        std::unique_ptr<AbstractProductB> productB1(factory->CreateProductB());
        productB1->OperationB();

        factory.reset(new ConcreteFactory2());
        std::unique_ptr<AbstractProductA> productA2(factory->CreateProductA());
        productA2->OperationA();
        std::unique_ptr<AbstractProductB> productB2(factory->CreateProductB());
        productB2->OperationB();
    }
    std::cout << "------------end-----------" << std::endl;
    return 0;
}