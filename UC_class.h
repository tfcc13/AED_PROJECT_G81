//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_UC_CLASS_H
#define AED_PROJECT_UC_CLASS_H

#include <iostream>
#include <string>
#include "Student.h"
#include "Schedule.h"

using namespace std;

class UC_class {
private:

    string UC_name_;
    set<Student> enrolled_students_;
    int number_of_enrolled_students_;
    Schedule UC_class_schedule_;

public:

    UC_class(const string& UC_name);
    UC_class(const UC_class& other);

    bool operator<(const UC_class& other) const;

    const string& getUcName() const;
    void insertStudent(Student& s);
    void eraseStudent(Student& s);
    const int getNumberOfEnrolledStudents() const;
    const int getNumberOfVacancies() const;
    Schedule getUCClassSchedule() const;

    void PrintEnrolledStudents() const;
    void PrintUcDaySchedule(const string& week_day) const;
    void PrintUcWeekSchedule() const;

    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);

};

#endif //AED_PROJECT_UC_CLASS_H
