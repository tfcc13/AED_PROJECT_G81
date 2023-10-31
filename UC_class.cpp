//
// Created by tiago on 28-10-2023.
//

#include "UC_class.h"

UC_class::UC_class(const string& UC_name) :
        UC_name_(UC_name),
        enrolled_students_(),
        number_of_enrolled_students_(0),
        number_of_vacancies_(27),
        UC_class_schedule_() {}

UC_class::UC_class(const UC_class &other) {
    UC_name_ = other.UC_name_;
    enrolled_students_ = other.enrolled_students_;
    number_of_enrolled_students_ = other.number_of_enrolled_students_;
    number_of_vacancies_ = other.number_of_vacancies_;
    UC_class_schedule_ = other.UC_class_schedule_;
}

bool UC_class::operator<(const UC_class &other) const {
    return UC_name_ < other.UC_name_;
}

const Schedule& UC_class::getUCClassSchedule() const{
    return UC_class_schedule_;
}

const string& UC_class::getUcName() const {
    return UC_name_;
}

void UC_class::PrintEnrolledStudents() const {
    for (const Student& student : enrolled_students_) {
        std::cout << "Student number: " << student.getIdNumber() << " Student name: " << student.getStudentName() << std::endl;
    }
}

void UC_class::PrintUcDaySchedule(const string& week_day){
    UC_class_schedule_.PrintDaySchedule(week_day);
}

void UC_class::PrintUcWeekSchedule() {
    UC_class_schedule_.PrintWeekSchedule();
}

void UC_class::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    UC_class_schedule_.addDayScheduleEntry(week_day, entry);
}




