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
//class Fence {
//public:
//    virtual void Describe() const = 0;
//    virtual ~Fence() = default;
//};
//
//class WoodFence : public Fence {
//public:
//    void Describe() const override {
//        std::cout << "Fence type: Wooden." << std::endl;
//    }
//};
//
//class BrickFence : public Fence {
//public:
//    void Describe() const override {
//        std::cout << "Fence type: Brick." << std::endl;
//    }
//};
//
//class ConcreteFence : public Fence {
//public:
//    void Describe() const override {
//        std::cout << "Fence type: Concrete." << std::endl;
//    }
//};
//
//class Barn {
//public:
//    virtual void Describe() const = 0;
//    virtual ~Barn() = default;
//};
//
//class WoodBarn : public Barn {
//public:
//    void Describe() const override {
//        std::cout << "Shed type: Wooden." << std::endl;
//    }
//};
//
//class BrickBarn : public Barn {
//public:
//    void Describe() const override {
//        std::cout << "Barn type: Brick." << std::endl;
//    }
//};
//
//class ConcreteBarn : public Barn {
//public:
//    void Describe() const override {
//        std::cout << "Barn type: Concrete." << std::endl;
//    }
//};
//
//class Developer {
//public:
//    virtual std::unique_ptr<House> BuildHouse() const = 0;
//    virtual std::unique_ptr<Fence> BuildFence() const = 0;
//    virtual std::unique_ptr<Barn> BuildBarn() const = 0;
//    virtual ~Developer() = default;
//};
//
//class WoodDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<WoodHouse>();
//    }
//    std::unique_ptr<Fence> BuildFence() const override {
//        return std::make_unique<WoodFence>();
//    }
//    std::unique_ptr<Barn> BuildBarn() const override {
//        return std::make_unique<WoodBarn>();
//    }
//};
//
//class BrickDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<BrickHouse>();
//    }
//    std::unique_ptr<Fence> BuildFence() const override {
//        return std::make_unique<BrickFence>();
//    }
//    std::unique_ptr<Barn> BuildBarn() const override {
//        return std::make_unique<BrickBarn>();
//    }
//};
//
//class ConcreteDeveloper : public Developer {
//public:
//    std::unique_ptr<House> BuildHouse() const override {
//        return std::make_unique<ConcreteHouse>();
//    }
//    std::unique_ptr<Fence> BuildFence() const override {
//        return std::make_unique<ConcreteFence>();
//    }
//    std::unique_ptr<Barn> BuildBarn() const override {
//        return std::make_unique<ConcreteBarn>();
//    }
//};
//
//void ConstructNeighborhood(const Developer& developer) {
//    auto house = developer.BuildHouse();
//    auto fence = developer.BuildFence();
//    auto barn = developer.BuildBarn();
//    house->Describe();
//    fence->Describe();
//    barn->Describe();
//}
//
//int main() {
//    WoodDeveloper woodDev;
//    BrickDeveloper brickDev;
//    ConcreteDeveloper concreteDev;
//    ConstructNeighborhood(woodDev);
//    ConstructNeighborhood(brickDev);
//    ConstructNeighborhood(concreteDev);
//    return 0;
//}

//12.2

#include <iostream>
#include <vector>
#include <memory>

// Абстрактный базовый класс для существ
class GenericCreature {
public:
    virtual ~GenericCreature() = default;
    virtual void eat() const = 0;
    virtual void ability() const = 0;
};

// OceanCreature
class OceanCreature : public GenericCreature {
public:
    void eat() const override {
        std::cout << "OceanCreature is eating fish." << std::endl;
    }

    void ability() const override {
        swim();
    }

    void swim() const {
        std::cout << "Swimming in the ocean." << std::endl;
    }
};

class Shark : public OceanCreature {
public:
    void eat() const override {
        std::cout << "Shark is eating smaller fish." << std::endl;
    }
};

class Dolphin : public OceanCreature {
public:
    void eat() const override {
        std::cout << "Dolphin is eating squid." << std::endl;
    }
};

// TerrestrialCreature
class TerrestrialCreature : public GenericCreature {
public:
    void eat() const override {
        std::cout << "TerrestrialCreature is eating grass." << std::endl;
    }

    void ability() const override {
        walk();
    }

    void walk() const {
        std::cout << "Walking on land." << std::endl;
    }
};

class Elephant : public TerrestrialCreature {
public:
    void eat() const override {
        std::cout << "Elephant is eating plants." << std::endl;
    }
};

class Lion : public TerrestrialCreature {
public:
    void eat() const override {
        std::cout << "Lion is eating meat." << std::endl;
    }
};

// Amphibious
class Amphibious : public GenericCreature {
public:
    void eat() const override {
        std::cout << "Amphibious is eating insects." << std::endl;
    }

    void ability() const override {
        swim();
        walk();
    }

    void swim() const {
        std::cout << "Swimming in water." << std::endl;
    }

    void walk() const {
        std::cout << "Walking on land." << std::endl;
    }
};

class Crocodile : public Amphibious {
public:
    void eat() const override {
        std::cout << "Crocodile is eating large prey." << std::endl;
    }
};

class Frog : public Amphibious {
public:
    void eat() const override {
        std::cout << "Frog is eating flies." << std::endl;
    }
};

// Bird
class Bird : public GenericCreature {
public:
    void eat() const override {
        std::cout << "Bird is eating seeds." << std::endl;
    }

    void ability() const override {
        fly();
        walk();
    }

    void fly() const {
        std::cout << "Flying in the sky." << std::endl;
    }

    void walk() const {
        std::cout << "Walking on land." << std::endl;
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

// Waterfowl
class Waterfowl : public Bird {
public:
    void eat() const override {
        std::cout << "Waterfowl is eating aquatic plants." << std::endl;
    }

    void ability() const override {
        fly();
        swim();
        walk();
    }

    void swim() const {
        std::cout << "Swimming in lakes and ponds." << std::endl;
    }
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

// Фабрика существ (абстрактная)
class CreatureFactory {
public:
    virtual ~CreatureFactory() = default;
    virtual std::shared_ptr<GenericCreature> createCreature() const = 0;
};

// Конкретные фабрики для каждого типа
class OceanCreatureFactory : public CreatureFactory {
public:
    std::shared_ptr<GenericCreature> createCreature() const override {
        return std::make_shared<Shark>();
    }
};

class TerrestrialCreatureFactory : public CreatureFactory {
public:
    std::shared_ptr<GenericCreature> createCreature() const override {
        return std::make_shared<Lion>();
    }
};

class AmphibiousFactory : public CreatureFactory {
public:
    std::shared_ptr<GenericCreature> createCreature() const override {
        return std::make_shared<Frog>();
    }
};

class BirdFactory : public CreatureFactory {
public:
    std::shared_ptr<GenericCreature> createCreature() const override {
        return std::make_shared<Parrot>();
    }
};

class WaterfowlFactory : public CreatureFactory {
public:
    std::shared_ptr<GenericCreature> createCreature() const override {
        return std::make_shared<Duck>();
    }
};

// Демонстрация зоопарка
void createZoo(const std::vector<std::shared_ptr<CreatureFactory>>& factories) {
    std::vector<std::shared_ptr<GenericCreature>> zoo;
    for (const auto& factory : factories) {
        zoo.push_back(factory->createCreature());
    }

    std::cout << "\nFeeding and demonstrating abilities in the zoo:\n";
    for (const auto& creature : zoo) {
        creature->eat();
        creature->ability();
        std::cout << "------------------\n";
    }
}

int main() {
    // Создание фабрик
    std::vector<std::shared_ptr<CreatureFactory>> factories = {
        std::make_shared<OceanCreatureFactory>(),
        std::make_shared<TerrestrialCreatureFactory>(),
        std::make_shared<AmphibiousFactory>(),
        std::make_shared<BirdFactory>(),
        std::make_shared<WaterfowlFactory>()
    };

    createZoo(factories);

    return 0;
}

