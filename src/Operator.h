#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include<WString.h>

class Operator {
    private:
        /* data */
    public:
        int id;
        String name;
        String  weapon;
        String  metalGear;

        Operator(int id, String name, String  weapon, String  metalGear);

};

Operator* getOperatorbyId(std::vector<Operator> &operators, int targetId);

void removeOperatorById(std::vector<Operator> &operators, int targetId);

Operator* updateOperatorById(std::vector<Operator> &operators, 
    int targetId, 
    String updatedName,
    String updatedWeapon,
    String updatedMetalgear);


// Struct Method

// struct Operator {
//     int id;
//     String name;
//     String weapon;
//     String metalGear;

//     Operator(int i, String n, String w, String m) : id(i), name(n), weapon(w), metalGear(m) {}

//     // Constructor
//     // Default constructor is also a good practice if you need to create an empty object
//     Operator() : id(0), name(""), weapon(""), metalGear("") {}
// };

