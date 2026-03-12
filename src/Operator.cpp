#include<WString.h>
#include "Operator.h"

Operator::Operator(int id, String name, String  weapon, String metalGear){
    this->id = id;
    this->name = name;
    this->weapon = weapon;
    this->metalGear = metalGear;
}

int Operator::getId() {
    return this->id;
}

String Operator::getName() {
    return this->name;
}

String Operator::getWeapon() {
    return this->weapon;
}

String Operator::getMetalGear() {
    return this->metalGear;
};
