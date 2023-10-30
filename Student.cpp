//
// Created by tiago on 28-10-2023.
//

#include "Student.h"

// Constructor
Student::Student(int id_number, std::string& st_name) :
        id_number_(id_number),
        st_name_(st_name),
        st_enrolled_UC_and_classes_(),
        st_number_of_UCs_(0),
        st_schedule_() {}

int Student::getIdNumber() const {
    return id_number_;
}

const std::string& Student::getStudentName() const {
    return st_name_;
}

int Student::getNumberOfUCs() const {
    return st_number_of_UCs_;
}

bool Student::operator<(const Student& other) const {
    return id_number_ < other.id_number_;
}

/*void Student::insertUcCode(const std::string &UcCode) {
   this->uc_code.insert(UcCode);
}
*/
/*const std::set<std::string>& Student::getUcCodes() const {
    return uc_code;
}
*/