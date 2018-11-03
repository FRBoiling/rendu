//
// Created by boil on 18-10-15.
//
#include <rendu/log/Logger.h>

using namespace rendu;
using namespace rendu::log;

class AbstractClass {
public:
    AbstractClass() {
        LOG_DEBUG << " AbstractClass()";
    }

    ~AbstractClass() {
        LOG_DEBUG << " ~AbstractClass()";
    }

public:
    virtual string helloWorld() {
        LOG_DEBUG << " AbstractClass helloWorld()";
    };

    void printHelloWorld() {
        LOG_DEBUG << helloWorld();
    }
};

class ConcreteClass : public AbstractClass {
public:
    ConcreteClass() {
        LOG_DEBUG << " ConcreteClass()";
    }

    ~ConcreteClass() {
        LOG_DEBUG << " ~ConcreteClass()";
    }

private:
    string helloWorld() override {
        LOG_DEBUG << " helloWorld()";
        return "hello world";
    }
};

int main() {
    Logger::setLogLevel(DEBUG);
//    AbstractClass *c = new ConcreteClass();
//    std::shared_ptr<AbstractClass> spC(new ConcreteClass);
//    spC->printHelloWorld();

//   AbstractClass* b1 =new ConcreteClass();
    std::shared_ptr<AbstractClass> spB1(new ConcreteClass());
//     AbstractClass b2;

//    delete b1;

}