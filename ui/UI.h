#ifndef ELECTROSTATICSYSTEM_UI_H
#define ELECTROSTATICSYSTEM_UI_H
#include "../TAD/ElectrostaticSystem.h"

class UI {
private:
    ElectrostaticSystem system;
    static void menu() ;
    void addChargeUI();
    void removeChargeAtUI();
    void clearSystemUI();

    void printCharges() const;
    static void printCharge(const Charge& c) ;

    void findChargeAtUI() const;
    void getPotentialAtUI() const;
    void getFieldAtUI() const;
    void getForceAtUI() const;
    void getForceOnUI() const;
    void getTotalEnergyUI() const;

public:
    UI();
    void run();
    void preloadSystem();
};

#endif //ELECTROSTATICSYSTEM_UI_H