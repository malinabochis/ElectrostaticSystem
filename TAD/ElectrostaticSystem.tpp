#include "ElectrostaticSystem.h"

    /**
     * @brief [Short sentence describing what the function does]
     *
     * [Optional: Longer explanation of logic, edge cases, or complexity]
     *
     * @param [parameter_name] [Description of the input]
     * @return [Description of what the function returns]
     * @throws [Exception type] [Conditions under which this is thrown]
     */

ElectrostaticSystem::resize() {
    /**
     * @brief Resizes the vectors max capacity
     */
    capacity *= 2;
    Charge* newElems = new Charge[capacity];
    for (int i=0; i<length; i++) {
        newElems[i] = elems[i];
    }
    delete[] elems;
    elems = newElems;
}

ElectrostaticSystem::ElectrostaticSystem() {
}

ElectrostaticSystem::ElectrostaticSystem(const ElectrostaticSystem &other) {
}

ElectrostaticSystem & ElectrostaticSystem::operator=(const ElectrostaticSystem &other) {
}

ElectrostaticSystem::~ElectrostaticSystem() {
}

void ElectrostaticSystem::pushBack(const float &elem) {
}

void ElectrostaticSystem::popBack() {
}

void ElectrostaticSystem::clear() {
}

int ElectrostaticSystem::getLen() const {
}

bool ElectrostaticSystem::isEmpty() const {
}

float & ElectrostaticSystem::getAtIndex(int index) const {
}

float & ElectrostaticSystem::getFront() {
}

float & ElectrostaticSystem::getBack() {
}

const float ElectrostaticSystem::getPotentialAt(float x, float y, float z) const {
}

const float ElectrostaticSystem::getFieldAt(float x, float y, float z) const {
}

const float ElectrostaticSystem::getForceAt(float x, float y, float z) const {
}

const float ElectrostaticSystem::getTotalEnergy() const {
}