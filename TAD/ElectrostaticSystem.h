#ifndef CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H
#define CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H

struct Charge {
    float chargeValue; // +/- number
    float x, y, z; // space coordonates
};

template <typename E>
class ElectrostaticSystem {
private:
    Charge* elems; //?????
    int length;
    int capacity;
    void resize();

public:
    ElectrostaticSystem();
    ElectrostaticSystem(const ElectrostaticSystem& source);
    ElectrostaticSystem& operator=(const ElectrostaticSystem& source);

    void add(E elem);
    bool remove(E elem);
    float totalCharge(E elem);
    float getPotentialAt(float x, float y, float z);
    float getFieldAt(float x, float y, float z);
    float getForceAt(float x, float y, float z);
    float getTotalEnergy();

    bool searchCoord(E elem) const;
    int noOccurrencesSign(E elem) const;
    int size() const;
    ~ElectrostaticSystem();
};

#include "ElectrostaticSystem.tpp"
#endif //CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H