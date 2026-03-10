#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <optional>

class Operator {
private:
    /* data */
public:
    int id;
    String name;
    String weapon;
    String metalGear;

    Operator(int id, String name, String weapon, String metalGear){
        this->id = id;
        this->name = name;
        this->weapon = weapon;
        this->metalGear = metalGear;
    }
    // Default values
    Operator() : id(0), name("Jack"), weapon("Famas"), metalGear("None") {}
};

Operator* getOperatorbyId(std::vector<Operator> &operators, int targetId) {
    auto it = std::find_if(operators.begin(), operators.end(), [targetId](const Operator &obj) {
        return obj.id == targetId;
    });
    // Check if a matching object was found
    if (it != operators.end()) {
        // Return the pointer (Operator*) to the found object
        return &(*it);
    } else {
        // Return nullptr if not found
        return nullptr;
    }
}

void removeOperatorById(std::vector<Operator> &operators, int targetId) {
    // std::remove_if shifts elements to be kept to the front and returns an iterator 
    // to the new logical end of the remaining elements.
    auto it = std::remove_if(operators.begin(), operators.end(), [targetId](const Operator &obj) { 
        return obj.id == targetId; 
    });

    // vector::erase then removes the elements from the new logical end to the actual end.
    operators.erase(it, operators.end());
}

Operator* updateOperatorById(std::vector<Operator> &operators, 
    int targetId, 
    String updatedName,
    String updatedWeapon,
    String updatedMetalgear) {
    // Use reference (&)in &obj to modify the actual object in the vector
    auto operatorObj = std::find_if(operators.begin(), operators.end(), [targetId](const Operator &obj){
        return obj.id == targetId;
    });

    if (operatorObj != operators.end()) {
        operatorObj->name = updatedName;
        operatorObj->weapon = updatedWeapon;
        operatorObj->metalGear = updatedMetalgear;
        // Return the pointer (Operator*) to the updated object
        return &(*operatorObj);
    } else {
        return nullptr;
    }
}


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

