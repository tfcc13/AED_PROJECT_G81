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
    int number_of_vacancies_;
    Schedule UC_class_schedule_;

public:

    UC_class(string& UC_name);
    UC_class(const UC_class& other);
    const string& getUcName() const;
    void getEnrolledStudents() const;
    bool operator<(const UC_class& other) const;
    void getUcDaySchedule(const string& weekDay) const;
    void getUcWeekSchedule() const ;
    void addUcSchedule(const string& weekDay, const dayScheduleEntry& someSchedule);

};

#endif //AED_PROJECT_UC_CLASS_H
