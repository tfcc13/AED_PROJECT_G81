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
    set<pair<string, string>, pair_compare> st_enrolled_UC_and_classes_; // <class_code, UC_code> ordenados pelo UC_code
    int st_number_of_UCs_; // Para depois contar alunos inscritos em x cadeiras
    Schedule st_schedule_;

public:
    Student(int id_number, const std::string& st_name);
    Student(const Student& other);

    bool operator<(const Student& other) const;

    int getIdNumber() const;
    const string& getStudentName() const;
    int getNumberOfUCs() const;
    void PrintUcDaySchedule(const string& week_day);
    void PrintUcWeekSchedule();
    void PrintEnrolledUCs();

    void addSchedule(const string& class_code, const string& UC_code, const Schedule& s);
    void removeSchedule(const string& class_code, const string& UC_code, const Schedule& s);
    bool checkScheduleConflict(const Schedule& s);

    //void addUCAndClass(const pair<string, string> UC_and_Class);
    //void removeUCAndClass(const pair<string, string> UC_and_Class);
    //void switchUCAndClass(const pair<string, string> old_UC_and_Class, const pair<string, string> new_UC_and_Class);
    //void insertUcCode(const std::string& UcCode);
    // const set<string>& getUcCodes() const;

};

#endif //AED_PROJECT_STUDENT_H
