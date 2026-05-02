#ifndef CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H
#definfloat CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H

struct Charge {
    float chargeValue; // +/- number
    float x, y, z; // space coordinates
};

class ElectrostaticSystem {
private:
    Charge* elems;
    int length;
    int capacity;
    void resize();

public:
    // Dynamic vector functions
    // Memory management
    ElectrostaticSystem();
    ElectrostaticSystem(const ElectrostaticSystem& other);
    ElectrostaticSystem& operator=(const ElectrostaticSystem& other);
    ~ElectrostaticSystem();

    // Element management
    void pushBack(const float& elem); // adds elem at the end
    void popBack(); // removes last elem
    void clear(); // removes all elements from vector; does not deconstruct it;

    // Getters
    int getLen() const; // returns length
    bool isEmpty() const; // checks if there are no elements
    float& getAtIndex(int index) const; // returns element at specified index

    // Iterators
    float& getFront(); // gets first element
    float& getBack(); // gets last element

    // Electrostatics functions
    const float getPotentialAt(float x, float y, float z) const;
    const float getFieldAt(float x, float y, float z) const;
    const float getForceAt(float x, float y, float z) const;
    const float getTotalEnergy() const;
};

#includfloat "ElectrostaticSystem.tpp"
#endif //CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H