//11.1

//#include <iostream>
//#include <vector>
//#include <memory>
//
//class House {
//public:
//    virtual void Describe() const = 0;
//    virtual ~House() = default;
//};
//
//class WoodHouse : public House {
//public:
//    void Describe() const override {
//        std::cout << "House type: Wooden." << std::endl;
//    }
//};
//
//class BrickHouse : public House {
//public:
//    void Describe() const override {
//        std::cout << "House type: Brick." << std::endl;
//    }
//};
//
//class ConcreteHouse : public House {
//public:
//    void Describe() const override {
//        std::cout << "House type: Concrete." << std::endl;
//    }
//};
//
//class Developer {
//public:
//    virtual std::unique_ptr<House> BuildHouse() const = 0;
//    virtual ~Developer() = default;
//};
//
//class WoodDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<WoodHouse>();
//    }
//};
//
//class BrickDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<BrickHouse>();
//    }
//};
//
//class ConcreteDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<ConcreteHouse>();
//    }
//};
//
//void BuildNeighborhood(const Developer& developer, int numberOfHouses) {
//    std::vector<std::unique_ptr<House>> neighborhood;
//    for (int i = 0; i < numberOfHouses; ++i) {
//        neighborhood.push_back(developer.BuildHouse());
//    }
//
// std::cout << "The block is built up with " << numberOfHouses << " houses:" << std::endl;
// 
//    for (const auto& house : neighborhood) {
//        house->Describe();
//    }
//    std::cout << std::endl;
//}
//
//int main() {
//    WoodDeveloper woodDeveloper;
//    BrickDeveloper brickDeveloper;
//    ConcreteDeveloper concreteDeveloper;
//
//    BuildNeighborhood(woodDeveloper, 4);
//    BuildNeighborhood(brickDeveloper, 8);
//    BuildNeighborhood(concreteDeveloper, 16);
//
//    return 0;
//}

//11.2

#include <iostream>
#include <vector>
#include <memory>
#include <string>

class GenericCreature {
public:
    virtual ~GenericCreature() = default;
    virtual void eat() const = 0;
};

class OceanCreature : virtual public GenericCreature {
public:
    void swim() const {
        std::cout << "Swimming in the ocean." << std::endl;
    }
};

class Shark : public OceanCreature {
public:
    void eat() const override {
        std::cout << "Shark is eating fish." << std::endl;
    }
};

class Dolphin : public OceanCreature {
public:
    void eat() const override {
        std::cout << "Dolphin is eating small squid." << std::endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature {
public:
    void walk() const {
        std::cout << "Walking on land." << std::endl;
    }
};

class Elephant : public TerrestrialCreature {
public:
    void eat() const override {
        std::cout << "Elephant is eating grass." << std::endl;
    }
};

class Lion : public TerrestrialCreature {
public:
    void eat() const override {
        std::cout << "Lion is eating meat." << std::endl;
    }
};

class Amphibious : public OceanCreature, public TerrestrialCreature {
};

class Crocodile : public Amphibious {
public:
    void eat() const override {
        std::cout << "Crocodile is eating a large prey." << std::endl;
    }
};

class Frog : public Amphibious {
public:
    void eat() const override {
        std::cout << "Frog is eating flies." << std::endl;
    }
};

class Bird : public TerrestrialCreature {
public:
    void fly() const {
        std::cout << "Flying in the sky." << std::endl;
    }
};

class Pigeon : public Bird {
public:
    void eat() const override {
        std::cout << "Pigeon is eating grains." << std::endl;
    }
};

class Parrot : public Bird {
public:
    void eat() const override {
        std::cout << "Parrot is eating fruits." << std::endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
};

class Duck : public Waterfowl {
public:
    void eat() const override {
        std::cout << "Duck is eating small aquatic creatures." << std::endl;
    }
};

class Swan : public Waterfowl {
public:
    void eat() const override {
        std::cout << "Swan is eating underwater vegetation." << std::endl;
    }
};

class Creator {
public:
    static std::shared_ptr<GenericCreature> createCreature(const std::string& type) {
        if (type == "Shark") return std::make_shared<Shark>();
        if (type == "Dolphin") return std::make_shared<Dolphin>();
        if (type == "Elephant") return std::make_shared<Elephant>();
        if (type == "Lion") return std::make_shared<Lion>();
        if (type == "Crocodile") return std::make_shared<Crocodile>();
        if (type == "Frog") return std::make_shared<Frog>();
        if (type == "Pigeon") return std::make_shared<Pigeon>();
        if (type == "Parrot") return std::make_shared<Parrot>();
        if (type == "Duck") return std::make_shared<Duck>();
        if (type == "Swan") return std::make_shared<Swan>();
        throw std::invalid_argument("Unknown creature type");
    }
};

int main() {
    std::vector<std::shared_ptr<GenericCreature>> zoo;

    zoo.push_back(Creator::createCreature("Shark"));
    zoo.push_back(Creator::createCreature("Dolphin"));
    zoo.push_back(Creator::createCreature("Elephant"));
    zoo.push_back(Creator::createCreature("Lion"));
    zoo.push_back(Creator::createCreature("Crocodile"));
    zoo.push_back(Creator::createCreature("Frog"));
    zoo.push_back(Creator::createCreature("Pigeon"));
    zoo.push_back(Creator::createCreature("Parrot"));
    zoo.push_back(Creator::createCreature("Duck"));
    zoo.push_back(Creator::createCreature("Swan"));

    // Накормить всех животных
    for (const auto& creature : zoo) {
        creature->eat();
    }

    return 0;
}

