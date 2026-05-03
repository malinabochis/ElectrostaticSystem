#pragma once
#include "ElectrostaticSystem.h"
#include <cmath>
#include <stdexcept>

// =============Internal functions=============

inline void ElectrostaticSystem::copyFrom(const ElectrostaticSystem& source) {
    if (source.head == nullptr) {
        head = nullptr;
        length = 0;
        return;
    }

    const Node* crtSource = source.head; // current node from source list
    head = new Node(crtSource->elem); // creating first node of the new list
    Node* crt = head; // current node from the new list
    crtSource = crtSource->next; // going to the next node from the source list

    while (crtSource != nullptr) {
        crt->next = new Node(crtSource->elem);
        crt = crt->next;
        crtSource = crtSource->next;
    }

    length = source.length;
}

inline void ElectrostaticSystem::clearList() {
    while (head != nullptr) {
        const Node* temp = head;
        head = head->next;
        delete temp;
    }
    length = 0; // at the end, head will be nullptr
}

// =============Public standard functions=============

// Constructor

inline ElectrostaticSystem::ElectrostaticSystem()
        : head(nullptr), length(0) {}

// Copy constructor

inline ElectrostaticSystem::ElectrostaticSystem(const ElectrostaticSystem& source)
        : head(nullptr), length(0) {
    copyFrom(source);
}

// Operator =

inline ElectrostaticSystem& ElectrostaticSystem::operator=(const ElectrostaticSystem& source) {
    if (this != &source) { // if this and source are not the exact same object at the same memory address
        clearList();
        copyFrom(source);
    }
    return *this;
}

// Destructor

inline ElectrostaticSystem::~ElectrostaticSystem() {
    clearList();
}


//~~~~~~~~~Basic operations~~~~~~~~~

// add

inline void ElectrostaticSystem::addCharge(const Charge& c) {
    head = new Node(c, head); // next = head (pointer to the first existing node) --> the next node at which the new node points is the first node of the old list (meaning the new node is now the first in list)
    length++;
}

// remove

inline bool ElectrostaticSystem::removeChargeAt(const float x, const float y, const float z) {
    if (head == nullptr) return false;

    if (head->elem.x == x && head->elem.y == y && head->elem.z == z) {
        const Node* temp = head;
        head = head->next;
        delete temp;
        length--;
        return true;
    }

    Node* crt = head;
    while (crt->next != nullptr) {
        if (crt->next->elem.x == x && // if the next node is the one to be removed
            crt->next->elem.y == y &&
            crt->next->elem.z == z) {

            const Node* temp = crt->next;
            crt->next = temp->next; // the "next" pointer points to the node after the one to be removed so that the one to be removed is now not linked to the stack and can be easily deleted
            delete temp;
            length--;
            return true;
        }
        crt = crt->next; // onto the next one in list
    }

    return false;
}

// clear

inline void ElectrostaticSystem::clear() {
    clearList();
}


// ~~~~~~~~~Access~~~~~~~~~

// getLen

inline int ElectrostaticSystem::getLen() const {
    return length;
}

// isEmpty

inline bool ElectrostaticSystem::isEmpty() const {
    return length == 0;
}

// getAtIndex

inline Charge& ElectrostaticSystem::getAtIndex(const int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index invalid");

    Node* crt = head;
    for (int i = 0; i < index; i++)
        crt = crt->next;

    return crt->elem;
}

// getFront

inline Charge& ElectrostaticSystem::getFront() const {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    return head->elem;
}

// getBack

inline Charge& ElectrostaticSystem::getBack() const {
    if (head == nullptr)
        throw std::out_of_range("List is empty");

    Node* crt = head;
    while (crt->next != nullptr)
        crt = crt->next;

    return crt->elem;
}

// ~~~~~~~~~Search~~~~~~~~~

// findChargeAt

inline Charge* ElectrostaticSystem::findChargeAt(const float x, const float y, const float z) const {
    Node* crt = head;
    while (crt != nullptr) {
        if (crt->elem.x == x && crt->elem.y == y && crt->elem.z == z)
            return &crt->elem;
        crt = crt->next;
    }
    return nullptr;
}


// =============Electrostatics functions=============

// getPotentialAt

inline float ElectrostaticSystem::getPotentialAt(const float x, const float y, const float z) const {
    float V = 0;

    const Node* crt = head;
    while (crt != nullptr) {
        constexpr float k = 8.9875517923e9f; // = 1 / (4 * pi * eps_0)
        const float dx = x - crt->elem.x;
        const float dy = y - crt->elem.y;
        const float dz = z - crt->elem.z;
        const float r = std::sqrt(dx*dx + dy*dy + dz*dz);

        if (r != 0)
            V += k * crt->elem.chargeValue / r;

        crt = crt->next;
    }

    return V;
}

// getFieldAt

inline float ElectrostaticSystem::getFieldAt(const float x, const float y, const float z) const {
    float E = 0;

    const Node* crt = head;
    while (crt != nullptr) {
        constexpr float k = 8.9875517923e9f;
        const float dx = x - crt->elem.x;
        const float dy = y - crt->elem.y;
        const float dz = z - crt->elem.z;
        const float r = std::sqrt(dx*dx + dy*dy + dz*dz);

        if (r != 0)
            E += k * std::abs(crt->elem.chargeValue) / (r*r);

        crt = crt->next;
    }

    return E;
}

// getForceAt

inline float ElectrostaticSystem::getForceAt(const float x, const float y, const float z) const {
    // Force needs a test charge
    constexpr float q_test = 1.0f; // without the test charge specified, consider test charge to be 1C [SI UNITS]
    return q_test * getFieldAt(x, y, z);
}

// getForceOn

inline float ElectrostaticSystem::getForceOn(const Charge c) const{
    return c.chargeValue * getFieldAt(c.x, c.y, c.z);
}

// getTotalEnergy

inline float ElectrostaticSystem::getTotalEnergy() const {
    float U = 0;

    const Node* i = head;
    while (i != nullptr) {
        Node* j = i->next;
        while (j != nullptr) {
            constexpr float k = 8.9875517923e9f;
            const float dx = i->elem.x - j->elem.x;
            const float dy = i->elem.y - j->elem.y;
            const float dz = i->elem.z - j->elem.z;
            const float r = std::sqrt(dx*dx + dy*dy + dz*dz);

            if (r != 0)
                U += k * i->elem.chargeValue * j->elem.chargeValue / r;

            j = j->next;
        }
        i = i->next;
    }

    return U;
}
