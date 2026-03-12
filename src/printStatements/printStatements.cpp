#include "printStatements.h"
#include <Arduino.h>

void printOperators(std::vector<Operator> &operatorsArr) {
  // Push to our C++ Operators Array
  for (Operator op : operatorsArr) {
    Serial.println();
    Serial.print("id: ");
    Serial.println(op.getId());
    Serial.print("Name: ");
    Serial.println(op.getName());
    Serial.print("Weapon: ");
    Serial.println(op.getWeapon());
    Serial.print("MetalGear: ");
    Serial.println(op.getMetalGear());
    Serial.println("-------------------");
  }
}