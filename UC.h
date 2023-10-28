//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

#include <iostream>
#include <string>
#include "Student.h"
#include "Schedule.h"



class UC {
private:

    std::string uc_name;
    std::set<Student> enrolled_students;
    Schedule uc_schedule;

public:

    UC(std::string& name);
    UC(const UC& other);
    const std::string& getUcName() const;
    void getEnrolledStudents() const;
    bool operator<(const UC& other) const;
    void getUcDaySchedule(const std::string& weekDay) const;
    void getUcWeekSchedule() const ;
    void addUcSchedule(const std::string& weekDay, const classSchedule& someSchedule);

};

#endif //AED_PROJECT_UC_H
