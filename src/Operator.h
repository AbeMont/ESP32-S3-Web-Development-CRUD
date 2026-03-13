// This fixes the error: redefinition of 'class Operator' 
#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <WString.h>

class Operator {
    private:
        /* data */
    public:
        int id;
        String name;
        String  weapon;
        String  metalGear;

        Operator(int id, String name, String  weapon, String  metalGear);

        int getId();
        String getName();
        String getWeapon();
        String getMetalGear();
};

#endif
