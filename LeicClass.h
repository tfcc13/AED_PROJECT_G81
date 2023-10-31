//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_LEICCLASS_H
#define AED_PROJECT_LEICCLASS_H

#include <string>
#include <iostream>
#include <iomanip>
#include "UC_class.h"
#include "Schedule.h"

using namespace std;

class LeicClass {
private:
    string LEIC_class_name_;
    set<UC_class> LEIC_UC_classes_;
    Schedule LEIC_class_schedule_;

public:
    LeicClass(const string& class_name);
    LeicClass(const LeicClass& other);

    bool operator<(const LeicClass& other) const;

    const string& getClassName() const;
    UC_class getUCClass(const string& UC_class_name) const;
    void insertUcClass(const UC_class& UC_class);
    void eraseUcClass(const UC_class& UC_class);

    void PrintClassUc() const;
    void PrintUcDaySchedule(const string& week_day) const;
    void PrintUcWeekSchedule() const;

    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);
    void addSchedule(const Schedule& s);

};

#endif //AED_PROJECT_LEICCLASS_H
