//
// Created by tiago on 28-10-2023.
//

#include "LeicClass.h"

LeicClass::LeicClass(const string& class_name) :
        LEIC_class_name_(class_name),
        LEIC_UC_classes_(),
        LEIC_class_schedule_() {}

LeicClass::LeicClass(const LeicClass& other) {
    LEIC_class_name_ = other.LEIC_class_name_;
    LEIC_UC_classes_ = other.LEIC_UC_classes_;
    LEIC_class_schedule_ = other.LEIC_class_schedule_;
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

void LeicClass::addUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.insert(UC_class);
}

void LeicClass::AddDayScheduleEntryLEICClass(const string &week_day, const dayScheduleEntry& entry){
    LEIC_class_schedule_.addDayScheduleEntry(week_day, entry);
}

bool LeicClass::operator<(const LeicClass &other) const {
    return LEIC_class_name_ < other.LEIC_class_name_;
}


