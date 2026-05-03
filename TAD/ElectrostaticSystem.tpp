#pragma once
#include "ElectrostaticSystem.h"
#include <cmath>

// =======================
// Constructori / destructor
// =======================

ElectrostaticSystem::ElectrostaticSystem()
        : head(nullptr), length(0) {}

ElectrostaticSystem::ElectrostaticSystem(const ElectrostaticSystem& source)
        : head(nullptr), length(0) {
    copyFrom(source);
}

ElectrostaticSystem& ElectrostaticSystem::operator=(const ElectrostaticSystem& source) {
    if (this != &source) {
        clearList();
        copyFrom(source);
    }
    return *this;
}

ElectrostaticSystem::~ElectrostaticSystem() {
    clearList();
}

// =======================
// Funcții interne
// =======================

void ElectrostaticSystem::copyFrom(const ElectrostaticSystem& other) {
    if (other.head == nullptr) {
        head = nullptr;
        length = 0;
        return;
    }

    Node* crtOther = other.head;
    head = new Node(crtOther->elem);
    Node* crt = head;
    crtOther = crtOther->next;

    while (crtOther != nullptr) {
        crt->next = new Node(crtOther->elem);
        crt = crt->next;
        crtOther = crtOther->next;
    }

    length = other.length;
}

void ElectrostaticSystem::clearList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    length = 0;
}

// =======================
// Inserare / ștergere
// =======================

void ElectrostaticSystem::addCharge(const Charge& c) {
    head = new Node(c, head);
    length++;
}

bool ElectrostaticSystem::removeChargeAt(float x, float y, float z) {
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

void ElectrostaticSystem::clear() {
    clearList();
}

// =======================
// Acces
// =======================

int ElectrostaticSystem::getLen() const {
    return length;
}

bool ElectrostaticSystem::isEmpty() const {
    return length == 0;
}

Charge& ElectrostaticSystem::getAtIndex(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index invalid");

    Node* crt = head;
    for (int i = 0; i < index; i++)
        crt = crt->next;

    return crt->elem;
}

Charge* ElectrostaticSystem::findChargeAt(float x, float y, float z) const {
    Node* crt = head;
    while (crt != nullptr) {
        if (crt->elem.x == x && crt->elem.y == y && crt->elem.z == z)
            return &crt->elem;
        crt = crt->next;
    }
    return nullptr;
}

Charge& ElectrostaticSystem::getFront() {
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
