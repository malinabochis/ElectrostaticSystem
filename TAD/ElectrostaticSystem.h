#ifndef CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H
#define CHARGEENERGYCALCULATOR_ELECTROSTATICSYSTEM_H

// head → [Node1] → [Node2] → [Node3] → nullptr


struct Charge {
    float chargeValue;
    float x, y, z;
};

class ElectrostaticSystem {
private:
    // everything in the private part is the definition of a list of nodes

    struct Node { // node is a container for the element Charge
        Charge elem; // each node contains only one charge particle
        Node* next;  // and a pointer to the next one in line

        Node(const Charge& c, Node* next = nullptr) // used when creating a new node: Node* n = new Node(c, head) meaning creating a new node with charge c having as next neighbor the head (or nullptr if it's the only one in the list)
            : elem(c), next(next) {} // the implementation being here, there is no need for a constructor without parameters, bcs we do not want to be able to create a node without having already a charge to put in it
    };

    // creation of new node:
    Node* head; // pointer to the first node: head
    int length;

    // functions for copy and annihilation of nodes:
    void copyFrom(const ElectrostaticSystem& source); // deep copy of entire list of nodes (creates new nodes identical to source nodes)
    void clearList(); // deletes every node so that we need not delete them manually (to avoid memory leak)

public:
    ElectrostaticSystem();
    ElectrostaticSystem(const ElectrostaticSystem& source);
    ElectrostaticSystem& operator=(const ElectrostaticSystem& source);
    ~ElectrostaticSystem();

    // Basic operations
    void addCharge(const Charge& c);
    bool removeChargeAt(float x, float y, float z);
    void clear();

    // Access
    int getLen() const;
    bool isEmpty() const;
    Charge& getAtIndex(int index) const; // ?? public
    Charge &getFront() const; // ?? do we rlly need it
    Charge &getBack() const; // ?? do we rlly need it

    // Search
    Charge* findChargeAt(float x, float y, float z) const;

    // Electrostatics
    float getPotentialAt(float x, float y, float z) const;
    float getFieldAt(float x, float y, float z) const;
    float getForceAt(float x, float y, float z) const;
    float getTotalEnergy() const;
};

#endif
