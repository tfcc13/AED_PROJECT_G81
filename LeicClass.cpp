//
// Created by tiago on 28-10-2023.
//


#include "LeicClass.h"

LeicClass::LeicClass(const std::string& class_name) {

    leic_class_name = class_name;

}

LeicClass::LeicClass(const LeicClass& other) {
    leic_class_name = other.leic_class_name;

    for (const UC_class& uc : other.leic_uc_classes) {
        leic_uc_classes.insert(uc);
    }
}

const std::string &LeicClass::getClassName() const {
    return leic_class_name;
}

void LeicClass::getClassUc() const {
    std::cout << "This class has the following UC's:" << std::endl;
    for (const UC_class& uc : leic_uc_classes) {
        std::cout << uc.getUcName() << std::endl;
    }
}

void LeicClass::addUcClass(const UC_class& ucClass) {
    leic_uc_classes.insert(ucClass);
}

bool LeicClass::operator<(const LeicClass &other) const {
    return leic_class_name < other.leic_class_name;
}


