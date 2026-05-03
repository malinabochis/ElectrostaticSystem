#include <iostream>
#include "UI.h"
#include "../TAD/ElectrostaticSystem.h"

UI::UI() : system() {}

void UI::menu() {
    std::cout << R"(
____________________________________________________________________
    1: Print all charges in the system
    2: Add charge
    3: Remove charge at (x, y, z)
    4: Clear system of all charges
    5: Find charge at (x, y, z)
    6: Value of the electric potential V at (x, y, z)
    7: Value of the electric field E at (x, y, z)
    8: Value of the electric force on a test charge at (x, y, z)
    9: Value of the electric force on the charge at (x, y, z)
    10: Value of the total energy
> Input: )";
}

void UI::printCharges() const {
    std::cout << R"(
____________________________________________________________________
)";
    if (system.isEmpty()) {
        std::cout << "There are no charges in the system\n";
        return;
    }

    for (int i = 0; i < system.getLen(); i++) {
        Charge& c = system.getAtIndex(i);
        std::cout << "[" << i << "] "
                  << "Charge: " << c.chargeValue << " Coulomb | "
                  << "Position: (" << c.x << ", " << c.y << ", " << c.z << ")\n";
    }
}

void UI::printCharge(const Charge& c) {
    std::cout << "Charge: " << c.chargeValue << " Coulomb | "
              << "Position: (" << c.x << ", " << c.y << ", " << c.z << ")\n";
}

void UI::addChargeUI() {
    std::cout << R"(
____________________________________________________________________
Add new charge into the system - value q and coordinates (x, y, z)
Input structure: value x y z
> Input: )";

    float value, x, y, z;
    std::cin >> value >> x >> y >> z;

    Charge c;
    c.chargeValue = value;
    c.x = x;
    c.y = y;
    c.z = z;

    system.addCharge(c);
    std::cout << "Charge added successfully!";
}

void UI::removeChargeAtUI() {
    std::cout << R"(
____________________________________________________________________
Remove a charge based on its coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    if (!system.removeChargeAt(x, y, z))
        std::cout << "No charge at the specified coordinates.";
    else
        std::cout << "Charge removed successfully!";
}

void UI::clearSystemUI() {
    system.clear();
    std::cout << R"(
____________________________________________________________________
System has been cleared!
)";
}

void UI::findChargeAtUI() const {
    std::cout << R"(
____________________________________________________________________
Find a charge based on its coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    Charge* c = system.findChargeAt(x, y, z);
    if (c == nullptr)
        std::cout << "No charge at the specified coordinates.";
    else
        printCharge(*c);
}

void UI::getPotentialAtUI() const {
    std::cout << R"(
____________________________________________________________________
Value of the electric potential at coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    std::cout << "V = " << system.getPotentialAt(x, y, z) << "\n";
}

void UI::getFieldAtUI() const {
    std::cout << R"(
____________________________________________________________________
Value of the electric field at coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    std::cout << "E = " << system.getFieldAt(x, y, z) << "\n";
}

void UI::getForceAtUI() const {
    std::cout << R"(
____________________________________________________________________
Value of the electric force on a test charge at coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    std::cout << "F = " << system.getForceAt(x, y, z) << "\n";
}

void UI::getForceOnUI() const {
    std::cout << R"(
____________________________________________________________________
Value of the force on a charge based on its coordinates - (x, y, z)
Input structure: x y z
> Input: )";

    float x, y, z;
    std::cin >> x >> y >> z;

    Charge* c = system.findChargeAt(x, y, z);
    if (c == nullptr)
        std::cout << "No charge at the specified coordinates.";
    else
        std::cout << "F = " << system.getForceOn(*c) << "\n";
}

void UI::getTotalEnergyUI() const {
    std::cout << R"(
____________________________________________________________________
Total electric energy stored in the system:
)";
    std::cout << "W = " << system.getTotalEnergy() << "\n";
}

void UI::run() {
    std::cout << "Electrostatic system\n";

    while (true) {
        menu();
        int userInput;
        std::cin >> userInput;

        switch (userInput) {
            case 1: printCharges(); break;
            case 2: addChargeUI(); break;
            case 3: removeChargeAtUI(); break;
            case 4: clearSystemUI(); break;
            case 5: findChargeAtUI(); break;
            case 6: getPotentialAtUI(); break;
            case 7: getFieldAtUI(); break;
            case 8: getForceAtUI(); break;
            case 9: getForceOnUI(); break;
            case 10: getTotalEnergyUI(); break;
            default: std::cout << "Input error"; break;
        }
    }
}

void UI::preloadSystem() {
    Charge c1{}; c1.chargeValue = +5; c1.x = 1; c1.y = 2; c1.z = 3;
    Charge c2{}; c2.chargeValue = -5; c2.x = 1; c2.y = 2; c2.z = -3;

    system.addCharge(c1);
    system.addCharge(c2);
}