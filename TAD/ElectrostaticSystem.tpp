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

// =============Public functions=============

// Constructor

inline ElectrostaticSystem::ElectrostaticSystem()
        : head(nullptr), length(0) {}

// Copy constructor

inline ElectrostaticSystem::ElectrostaticSystem(const ElectrostaticSystem& source)
        : head(nullptr), length(0) {
    copyFrom(source);
}

inline ElectrostaticSystem& ElectrostaticSystem::operator=(const ElectrostaticSystem& source) {
    if (this != &source) {
        clearList();
        copyFrom(source);
    }
    return *this;
}

// Destructor

inline ElectrostaticSystem::~ElectrostaticSystem() {
    clearList();
}



// =======================
// Inserare / ștergere
// =======================

inline void ElectrostaticSystem::addCharge(const Charge& c) {
    head = new Node(c, head);
    length++;
}

inline bool ElectrostaticSystem::removeChargeAt(float x, float y, float z) {
    if (head == nullptr) return false;

    // ștergere la început
    if (head->elem.x == x && head->elem.y == y && head->elem.z == z) {
        Node* temp = head;
        head = head->next;
        delete temp;
        length--;
        return true;
    }

    // căutare în interior
    Node* crt = head;
    while (crt->next != nullptr) {
        if (crt->next->elem.x == x &&
            crt->next->elem.y == y &&
            crt->next->elem.z == z) {

            Node* temp = crt->next;
            crt->next = temp->next;
            delete temp;
            length--;
            return true;
        }
        crt = crt->next;
    }

    return false;
}

inline void ElectrostaticSystem::clear() {
    clearList();
}

// =======================
// Acces
// =======================

inline int ElectrostaticSystem::getLen() const {
    return length;
}

inline bool ElectrostaticSystem::isEmpty() const {
    return length == 0;
}

inline Charge& ElectrostaticSystem::getAtIndex(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index invalid");

    Node* crt = head;
    for (int i = 0; i < index; i++)
        crt = crt->next;

    return crt->elem;
}

inline Charge* ElectrostaticSystem::findChargeAt(float x, float y, float z) const {
    Node* crt = head;
    while (crt != nullptr) {
        if (crt->elem.x == x && crt->elem.y == y && crt->elem.z == z)
            return &crt->elem;
        crt = crt->next;
    }
    return nullptr;
}

inline Charge& ElectrostaticSystem::getFront() {
    if (head == nullptr)
        throw std::out_of_range("Lista este goala");
    return head->elem;
}

Charge& ElectrostaticSystem::getBack() {
    if (head == nullptr)
        throw std::out_of_range("Lista este goala");

    Node* crt = head;
    while (crt->next != nullptr)
        crt = crt->next;

    return crt->elem;
}

// =======================
// Funcții electrostatice
// =======================

float ElectrostaticSystem::getPotentialAt(float x, float y, float z) const {
    const float k = 8.9875517923e9f;
    float V = 0;

    Node* crt = head;
    while (crt != nullptr) {
        float dx = x - crt->elem.x;
        float dy = y - crt->elem.y;
        float dz = z - crt->elem.z;
        float r = std::sqrt(dx*dx + dy*dy + dz*dz);

        if (r != 0)
            V += k * crt->elem.chargeValue / r;

        crt = crt->next;
    }

    return V;
}

float ElectrostaticSystem::getFieldAt(float x, float y, float z) const {
    const float k = 8.9875517923e9f;
    float E = 0;

    Node* crt = head;
    while (crt != nullptr) {
        float dx = x - crt->elem.x;
        float dy = y - crt->elem.y;
        float dz = z - crt->elem.z;
        float r = std::sqrt(dx*dx + dy*dy + dz*dz);

        if (r != 0)
            E += k * std::abs(crt->elem.chargeValue) / (r*r);

        crt = crt->next;
    }

    return E;
}

float ElectrostaticSystem::getForceAt(float x, float y, float z) const {
    // Forța necesită o sarcină test q_test.
    // Dacă nu ai q_test, poți considera q_test = 1C.
    float q_test = 1.0f;
    return q_test * getFieldAt(x, y, z);
}

float ElectrostaticSystem::getTotalEnergy() const {
    const float k = 8.9875517923e9f;
    float U = 0;

    Node* i = head;
    while (i != nullptr) {
        Node* j = i->next;
        while (j != nullptr) {
            float dx = i->elem.x - j->elem.x;
            float dy = i->elem.y - j->elem.y;
            float dz = i->elem.z - j->elem.z;
            float r = std::sqrt(dx*dx + dy*dy + dz*dz);

            if (r != 0)
                U += k * i->elem.chargeValue * j->elem.chargeValue / r;

            j = j->next;
        }
        i = i->next;
    }

    return U;
}
