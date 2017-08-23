#include <iostream>

using namespace std;

class ProductPart {
public:
    ProductPart(const string &param) : param_(param) {}

    virtual string getType() = 0;

protected:
    string param_;
};

class ProductPart1 : public ProductPart {
public:
    ProductPart1(const string &param = string()) : ProductPart(param) {}

    string getType() {
        return "ProductPart1(" + param_ + ")";
    }
};

class ProductPart2 : public ProductPart {
public:
    ProductPart2(const string &param = string()) : ProductPart(param) {}

    string getType() {
        return "ProductPart2(" + param_ + ")";
    }
};

class Product {
public:
    Product(ProductPart *part = nullptr) : part_(part) {}

    ~Product() {}

    void show() {
        cout << "This product has " << (part_ ? part_->getType() : "no part") << endl;
    }

private:
    ProductPart *part_;
};

class Builder {
public:
    virtual ProductPart *buildPart() = 0;

    virtual Product *getProduct() = 0;
};

class Builder1 : public Builder {
public:
    ProductPart *buildPart() {
        return new ProductPart1("PRE_DEFINED1");
    }

    Product *getProduct() {
        return new Product(buildPart());
    }
};

class Builder2 : public Builder {
public:
    ProductPart *buildPart() {
        return new ProductPart2("PRE_DEFINED2");
    }

    Product *getProduct() {
        return new Product(buildPart());
    }
};

class Director {
public:
    Director(Builder *builder = nullptr) : builder_(builder) {}

    void setBuilder(Builder *builder) {
        builder_ = builder;
    }

    Product *construct() {
        if (builder_ == nullptr) {
            throw runtime_error("Builder not set");
        }
        return builder_->getProduct();
    }

private:
    Builder *builder_;
};

int main() {
    Director *director = new Director();

    Builder *builder1 = new Builder1();
    director->setBuilder(builder1);
    Product *product1 = director->construct();
    product1->show();

    Builder *builder2 = new Builder2();
    director->setBuilder(builder2);
    Product *product2 = director->construct();
    product2->show();

    delete director;
    delete builder1;
    delete product1;
    delete builder2;
    delete product2;
}
