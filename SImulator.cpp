#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

// Ingredient class
// SRP is Implemented
class Ingredient {
private:
    std::string name;
    int quantity;

public:
    Ingredient(const std::string &name, int quantity) : name(name), quantity(quantity) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
};

// Abstract base class BakedGood
class BakedGood {
private:
    std::string name;
    static int totalBakedGoods;

public:
    // Constructor Overloading
    BakedGood() : name("Generic Baked Good") { ++totalBakedGoods; }
    BakedGood(const std::string &name) : name(name) { ++totalBakedGoods; }
    virtual ~BakedGood() {
        --totalBakedGoods;
        std::cout << "BakedGood [" << name << "] is being destroyed.\n";
    }

    std::string getName() const { return name; }
    static int getTotalBakedGoods() { return totalBakedGoods; }

    // Virtual function (Pure virtual function to make this class abstract)
    virtual void prepare() const = 0;  // Abstract method
    void bake(const std::vector<Ingredient> &ingredients) const
    {
        std::cout << "Baking " << name << " with:\n";
        for (const auto &ingredient : ingredients)
        {
            std::cout << "- " << ingredient.getQuantity() << "gms of " << ingredient.getName() << "\n";
        }
        std::cout << "Done baking " << name << "!\n";
    }
};

int BakedGood::totalBakedGoods = 0;

// Derived class Pastry
// LSP is Implemented
class Pastry : public BakedGood {
public:
    Pastry() : BakedGood("Pastry") {}

    // Overridden virtual function to provide specific implementation for Pastry
    void prepare() const override {
        std::cout << "Preparing Pastry with extra care!\n";
    }

    void bake(const std::vector<Ingredient> &ingredients) const
    {
        std::cout << "Baking a special " << getName() << " with extra care!\n";
        BakedGood::bake(ingredients);
    }
};

// Customer class
class Customer {
private:
    std::string name;
    static int totalOrders;

public:
    Customer() : name("Anonymous") {}
    Customer(const std::string &name) : name(name) {}

    virtual ~Customer()
    {
        std::cout << "Customer [" << name << "] is being destroyed.\n";
    }

    std::string getName() const { return name; }
    void placeOrder(const BakedGood &bakedGood) const
    {
        std::cout << name << " ordered a " << bakedGood.getName() << "\n";
        ++totalOrders;
    }

    static int getTotalOrders() { return totalOrders; }
};

int Customer::totalOrders = 0;

// Derived class BakedItemOrder demonstrating multiple inheritance
// OCP is Implemented
class BakedItemOrder : public Customer, public BakedGood {
public:
    BakedItemOrder(const std::string &customerName, const std::string &bakedGoodName)
        : Customer(customerName), BakedGood(bakedGoodName) {}

    void orderAndBake(const std::vector<Ingredient> &ingredients)
    {
        placeOrder(*this); // Customer places an order for baked good
        bake(ingredients); // Bake the item
        prepare(); // Prepare the baked item
    }

    // Overridden virtual function to provide specific implementation for BakedItemOrder
    void prepare() const override {
        std::cout << "Preparing BakedItemOrder with a special process!\n";
    }
};

int main() {
    // Ingredient vectors
    std::vector<Ingredient> Bingredients = {
        {"Flour", 500},
        {"Sugar", 250},
        {"Butter", 150}};

    std::vector<Ingredient> Pingredients = {
        {"Flour", 300},
        {"Eggs", 100},
        {"Chocolate", 150}};

    // Single inheritance: Pastry inherits from BakedGood
    Customer customer("Priya");
    // Multiple inheritance: BakedItemOrder inherits from both Customer and BakedGood
    BakedItemOrder order1("Priya", "Bread");
    BakedItemOrder order2("Priya", "Pastry");

    order1.orderAndBake(Bingredients); // Using multiple inheritance
    order2.orderAndBake(Pingredients);

    std::cout << "Total baked goods created: " << BakedGood::getTotalBakedGoods() << "\n";
    std::cout << "Total orders placed: " << Customer::getTotalOrders() << "\n";
    return 0;
}
