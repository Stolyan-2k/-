#include <iostream>
#include <vector>
#include <memory>

class GenericCreature {
public:
    GenericCreature() {
        std::cout << "GenericCreature created." << std::endl;
    }
    virtual ~GenericCreature() {
        std::cout << "GenericCreature destroyed." << std::endl;
    }

    virtual void eat() const = 0;
};

class OceanCreature : virtual public GenericCreature {
public:
    OceanCreature() {
        std::cout << "OceanCreature created." << std::endl;
    }
    virtual ~OceanCreature() {
        std::cout << "OceanCreature destroyed." << std::endl;
    }

    void swim() const {
        std::cout << "Swimming in the ocean." << std::endl;
    }

    void eat() const override {
        std::cout << "OceanCreature is eating small fish." << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    TerrestrialCreature() {
        std::cout << "TerrestrialCreature created." << std::endl;
    }
    virtual ~TerrestrialCreature() {
        std::cout << "TerrestrialCreature destroyed." << std::endl;
    }

    void walk() const {
        std::cout << "Walking on land." << std::endl;
    }

    void eat() const override {
        std::cout << "TerrestrialCreature is eating plants." << std::endl;
    }
};

class Amphibious : public OceanCreature, public TerrestrialCreature {
public:
    Amphibious() {
        std::cout << "Amphibious created." << std::endl;
    }
    virtual ~Amphibious() {
        std::cout << "Amphibious destroyed." << std::endl;
    }

    void eat() const override {
        std::cout << "Amphibious is eating insects." << std::endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    Bird() {
        std::cout << "Bird created." << std::endl;
    }
    virtual ~Bird() {
        std::cout << "Bird destroyed." << std::endl;
    }

    void fly() const {
        std::cout << "Flying in the sky." << std::endl;
    }

    void eat() const override {
        std::cout << "Bird is eating seeds." << std::endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    Waterfowl() {
        std::cout << "Waterfowl created." << std::endl;
    }
    virtual ~Waterfowl() {
        std::cout << "Waterfowl destroyed." << std::endl;
    }

    void eat() const override {
        std::cout << "Waterfowl is eating aquatic plants." << std::endl;
    }
};

int main() {
    std::vector<std::shared_ptr<GenericCreature>> creatures;

    creatures.push_back(std::make_shared<OceanCreature>());
    creatures.push_back(std::make_shared<TerrestrialCreature>());
    creatures.push_back(std::make_shared<Amphibious>());
    creatures.push_back(std::make_shared<Bird>());
    creatures.push_back(std::make_shared<Waterfowl>());

    std::cout << "\nPolymorphic behavior demonstration:\n";
    for (const auto& creature : creatures) {
        creature->eat();
    }

    return 0;
}
