#ifndef CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H
#define CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H

struct Charge {
    float chargeValue;
    float x, y, z;
};

class ElectrostaticSystem {
private:
    struct Node {
        Charge elem;
        Node* next;

        Node(const Charge& c, Node* next = nullptr)
            : elem(c), next(next) {}
    };

    Node* head;
    int length;

    void copyFrom(const ElectrostaticSystem& other);
    void clearList();

public:
    ElectrostaticSystem();
    ElectrostaticSystem(const ElectrostaticSystem& source);
    ElectrostaticSystem& operator=(const ElectrostaticSystem& source);
    ~ElectrostaticSystem();

    // Inserare / ștergere
    void addCharge(const Charge& c);
    bool removeChargeAt(float x, float y, float z);
    void clear();

    // Acces
    int getLen() const;
    bool isEmpty() const;
    Charge& getAtIndex(int index) const;

    // Căutare
    Charge* findChargeAt(float x, float y, float z) const;

    // Electrostatică
    float getPotentialAt(float x, float y, float z) const;
    float getFieldAt(float x, float y, float z) const;
    float getForceAt(float x, float y, float z) const;
    float getTotalEnergy() const;
};

#endif
