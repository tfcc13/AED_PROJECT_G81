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

bool LeicClass::operator<(const LeicClass &other) const {
    return LEIC_class_name_ < other.LEIC_class_name_;
}

const string &LeicClass::getClassName() const {
    return LEIC_class_name_;
}

void LeicClass::PrintClassUc() const {
    for (const UC_class& UC : LEIC_UC_classes_) {
        cout << UC.getUcName() << std::endl;
    }
}

void LeicClass::PrintUcDaySchedule(const string& week_day){
    LEIC_class_schedule_.PrintDaySchedule(week_day);
}

void LeicClass::PrintUcWeekSchedule(){
    LEIC_class_schedule_.PrintWeekSchedule();
}

void LeicClass::addUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.insert(UC_class);
}

void LeicClass::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    LEIC_class_schedule_.addDayScheduleEntry(week_day, entry);
}
