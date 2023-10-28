//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H


#include <string>
#include <set>
#include "Schedule.h"


class Student {

private:
    int id_number;
    std::string st_name;
    //std::set<std::string> uc_code;
    //set dos alunos
    //schedule
public:
    //Constructor
    Student(int id_number, std::string& st_name);

    int getIdNumber() const;
    const std::string& getStudentName() const;
    //void insertUcCode(const std::string& UcCode);
    // const std::set<std::string>& getUcCodes() const;
    bool operator<(const Student& other) const;
};



#endif //AED_PROJECT_STUDENT_H
