//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_LEICCLASS_H
#define AED_PROJECT_LEICCLASS_H

#include <string>
#include "UC_class.h"
#include <iostream>
#include <iomanip>
#include "Schedule.h"

class LeicClass {
private:
    std::string leic_class_name;
    std::set<UC_class> leic_uc_classes;
    Schedule leicClassSchedule;

public:
    LeicClass(const std::string& class_name);

    LeicClass(const LeicClass& other);

    const std::string& getClassName() const;

    void getClassUc() const;

    void addUcClass(const UC_class& ucClass);

    bool operator<(const LeicClass& other) const;
};

#endif //AED_PROJECT_LEICCLASS_H
