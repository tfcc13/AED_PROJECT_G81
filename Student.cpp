//
// Created by tiago on 28-10-2023.
//

#include "Student.h"

// Constructor
Student::Student(int id_number, const std::string& st_name) :
        id_number_(id_number),
        st_name_(st_name),
        st_enrolled_UC_and_classes_(),
        st_number_of_UCs_(0),
        st_schedule_() {}

Student::Student(const Student& other){
    id_number_ = other.id_number_;
    st_name_ = other.st_name_;
    st_enrolled_UC_and_classes_ = other.st_enrolled_UC_and_classes_;
    st_number_of_UCs_ = other.st_number_of_UCs_;
    st_schedule_ = other.st_schedule_;
}

bool Student::operator<(const Student& other) const {
    return id_number_ < other.id_number_;
}

int Student::getIdNumber() const {
    return id_number_;
}

const std::string& Student::getStudentName() const {
    return st_name_;
}

int Student::getNumberOfUCs() const {
    return st_number_of_UCs_;
}

void Student::PrintUcDaySchedule(const string& week_day){
    st_schedule_.PrintDaySchedule(week_day);
}

void Student::PrintUcWeekSchedule(){
    st_schedule_.PrintWeekSchedule();
}


void Student::PrintEnrolledUCs() const {
    for (const auto& pair : st_enrolled_UC_and_classes_) {
        std::cout  << pair.first << " - " << pair.second << std::endl;
    }
}

void Student::addSchedule(const string& class_code, const string& UC_code, const Schedule& s){
    st_enrolled_UC_and_classes_.insert(make_pair(class_code, UC_code));
    st_schedule_.addSchedule(s);
    st_number_of_UCs_ = st_enrolled_UC_and_classes_.size();
}

void Student::removeSchedule(const string& class_code, const string& UC_code, const Schedule& s){
    st_enrolled_UC_and_classes_.erase(make_pair(class_code, UC_code));
    st_schedule_.removeSchedule(s);
    st_number_of_UCs_ = st_enrolled_UC_and_classes_.size();
}

bool Student::checkScheduleConflict(const Schedule& s){
    st_schedule_.checkScheduleConflict(s);
}

/*void Student::insertUcCode(const std::string &UcCode) {
   this->uc_code.insert(UcCode);
}
*/
/*const std::set<std::string>& Student::getUcCodes() const {
    return uc_code;
}
*/