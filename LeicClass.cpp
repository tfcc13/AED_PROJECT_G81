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

UC_class LeicClass::getUCClass(const string &UC_class_name) const {
    auto it = LEIC_UC_classes_.find(UC_class(UC_class_name));
    return *it;
}

void LeicClass::insertUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.insert(UC_class);
}

void LeicClass::eraseUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.erase(UC_class);
}

void LeicClass::PrintClassUc() const {
    for (const UC_class& UC : LEIC_UC_classes_) {
        cout << UC.getUcName() << std::endl;
    }
}

int LeicClass::getNumberOfEnrolledStudents() const{
    set<Student> total_enrolled_students_in_class = this->getEnrolledStudents();
    return int(total_enrolled_students_in_class.size());
}

set<Student> LeicClass::getEnrolledStudents() const{
    set<Student> total_enrolled_students_in_class;
    for(const auto & LEIC_UC_class : LEIC_UC_classes_){
        set<Student> temp_UC_class_enrolled_students = LEIC_UC_class.getEnrolledStudents();
        total_enrolled_students_in_class.insert(temp_UC_class_enrolled_students.begin(), temp_UC_class_enrolled_students.end());
    }
    return  total_enrolled_students_in_class;
}

void LeicClass::PrintUcDaySchedule(const string& week_day) const{
    LEIC_class_schedule_.PrintDaySchedule(week_day);
}

void LeicClass::PrintUcWeekSchedule() const{
    LEIC_class_schedule_.PrintWeekSchedule();
}

void LeicClass::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    LEIC_class_schedule_.addDayScheduleEntry(week_day, entry);
}

void LeicClass::addSchedule(const Schedule& s){
    LEIC_class_schedule_.addSchedule(s);
}


