#include <iostream>

constexpr unsigned max_hero_name = 256;

enum Division {
    ASSASSIN,
    MEDIC,
    MAGE,
    TANK
};

enum Combat {
    UNKNOWN = -1,
    RANGE,
    MELEE,
    BOTH,
};

struct Hero {
    char* name;
    Division division;
    Combat combat;
};

const char* get_division_str(const Division division) {
    switch (division) {
        case ASSASSIN:
            return "Assassin";
        case MEDIC:
            return "Medic";
        case MAGE:
            return "Mage";
        case TANK:
            return "Tank";
        default:
            return nullptr;
    }
}

const char* get_combat_str(const Combat combat) {

    switch (combat) {
        case RANGE:
            return "Range";
        case MELEE:
            return "Melee";
        case BOTH:
            return "Both";
        case UNKNOWN:
            return "Unknown";
        default:
            return nullptr;
    }
}

void init_hero(Hero* hero, char* name, Division division, Combat combat) {
    hero->name = name;
    hero->division = division;
    hero->combat = combat;
}

void print_hero(const Hero* hero) {
    const char* division = get_division_str(hero->division);
    const char* combat = get_combat_str(hero->combat);

    if (division == nullptr || combat == nullptr || hero->name == nullptr) {
        std::cout << "Hero data is invalid!" << std::endl;
        return;
    }

    std::cout << "Name: " << hero->name << std::endl;
    std::cout << "Division: " << division << std::endl;
    std::cout << "Combat: " << combat << std::endl;
}

void deinit_hero(Hero* hero) {
    delete[] hero->name;
    hero->name = nullptr;
}

int main() {
    Hero hero {};

    char* hero_name = new char[max_hero_name];
    std::cin.getline(hero_name, max_hero_name);

    init_hero(&hero, hero_name, MAGE, RANGE);
    print_hero(&hero);
    deinit_hero(&hero);

    return 0;
}
