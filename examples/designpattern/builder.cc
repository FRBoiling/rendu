//
// Created by boil on 18-10-30.
//

class Product
{
public:
    void ShowProduct()
    {
    }
    void SetPartA()
    {
    }
    void SetPartB()
    {
    }
};

class Builder
{
public:
    virtual void BuildPartA() = 0;

    virtual void BuildPartB() = 0;

    virtual Product GetProduct() = 0;

protected:
    Product product_;
};


class ConcreteBuilder : public Builder
{
public:
    void BuildPartA() override
    {
        product_.SetPartA();
    }

    void BuildPartB() override
    {
        product_.SetPartB();
    }

    Product GetProduct() override
    {
        return product_;
    }
};

class Director
{
public:
    void ConstructProduct(Builder *builder)
    {
        builder->BuildPartA();
        builder->BuildPartB();
    }
};

int main(){
    Director director ;
    ConcreteBuilder b;

    director.ConstructProduct(&b);
    Product p = b.GetProduct();
    p.ShowProduct();
}