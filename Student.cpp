//
// Created by tiago on 28-10-2023.
//

#include "Student.h"



//Constructor
Student::Student( int id_number, std::string& st_name) {
    this->id_number = id_number;
    this->st_name = st_name;
}

int Student::getIdNumber() const {
    return id_number;
}

const std::string& Student::getStudentName() const {
    return st_name;
}

bool Student::operator<(const Student& other) const {
    return id_number < other.id_number;
}

/*void Student::insertUcCode(const std::string &UcCode) {
   this->uc_code.insert(UcCode);
}
*/
/*const std::set<std::string>& Student::getUcCodes() const {
    return uc_code;
}
*/