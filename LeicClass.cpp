//
// Created by tiago on 28-10-2023.
//

#include "LeicClass.h"

UC_class::UC_class(string& UC_name) :
        UC_name_(UC_name),
        enrolled_students_(),
        number_of_enrolled_students_(0),
        number_of_vacancies_(27),
        UC_class_schedule_(){}

LeicClass::LeicClass(const string& class_name) :
        LEIC_class_name_(class_name),
        LEIC_UC_classes_()
    {}

LeicClass::LeicClass(const LeicClass& other) {
    LEIC_class_name_ = other.LEIC_class_name_;

    for (const UC_class& uc : other.LEIC_UC_classes_) {
        LEIC_UC_classes_.insert(uc);
    }
}

const string &LeicClass::getClassName() const {
    return LEIC_class_name_;
}

void LeicClass::getClassUc() const {
    cout << "This class has the following UC's:" << std::endl;
    for (const UC_class& uc : LEIC_UC_classes_) {
        cout << uc.getUcName() << std::endl;
    }
}

void LeicClass::addUcClass(const UC_class& ucClass) {
    LEIC_UC_classes_.insert(ucClass);
}

bool LeicClass::operator<(const LeicClass &other) const {
    return LEIC_class_name_ < other.LEIC_class_name_;
}


