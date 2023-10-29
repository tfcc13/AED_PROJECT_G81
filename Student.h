//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <set>
#include "Schedule.h"

using namespace std;

struct pair_compare
{
    bool operator()(const pair<string, string>& left_pair, const pair<string, string>& right_pair) const
    {
        return left_pair.first < right_pair.first;
    }
};

class Student {

private:
    int id_number_;
    string st_name_;
    set<pair<string, string>, pair_compare> st_enrolled_UC_and_classes_; // <UC_code, classe_code> ordenados pelo UC_code
    int st_number_of_UCs_; // Para depois contar alunos inscritos em x cadeiras
    Schedule st_schedule_;

public:
    //Constructor
    Student(int id_number, std::string& st_name);

    int getIdNumber() const;
    const string& getStudentName() const;
    int getNumberOfUCs() const;
    //void addUCAndClass(const pair<string, string> UC_and_Class);
    //void removeUCAndClass(const pair<string, string> UC_and_Class);
    //void switchUCAndClass(const pair<string, string> old_UC_and_Class, const pair<string, string> new_UC_and_Class);
    //void insertUcCode(const std::string& UcCode);
    // const set<string>& getUcCodes() const;
    bool operator<(const Student& other) const;
};

#endif //AED_PROJECT_STUDENT_H
