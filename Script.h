//
// Created by tiago on 30-10-2023.
//

#ifndef AED_PROJECT_SCRIPT_H
#define AED_PROJECT_SCRIPT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Student.h"
#include "Schedule.h"
#include "LeicClass.h"
#include "UC_class.h"


using namespace std;



class Script {

public:

    std::set<UC_class> populateUcSet(const std::string& filename);
    std::set<LeicClass> populateLeicSet(const std::string& filename);
    std::set<Student> populateStudentSet(const std::string& filename);

private:
    std::set<UC_class> all_ucs;// = populateUcSet("input/classes.csv");
    std::set<LeicClass> all_classes;// = populateLeicSet("input/classes_per_uc.csv");
    std::set<Student> student_set; //= populateStudentSet("input/students_classes.csv");


};


#endif //AED_PROJECT_SCRIPT_H
