//
// Created by tiago on 30-10-2023.
//

#ifndef AED_PROJECT_SCRIPT_H
#define AED_PROJECT_SCRIPT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stack>
#include <queue>
#include "Student.h"
#include "Schedule.h"
#include "LeicClass.h"
#include "UC_class.h"


using namespace std;



class Script {

public:

    Script(const string& database);
    void loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3);
    void populateUcSet(const std::string& filename);
    void populateLeicSet(const std::string& filename);
    void populateStudentSet(const std::string& filename);
    void PrintWeekStudentSchedule(int studentNumber);
    void PrintWeekScheduleClass(const string& class_name);
    void consultStudentEnrolledUCs(int studentNumber);
    void consultStudentEnrolledClasses(int studentNumber);
    void consultUCOccupancy(const string& uc_name);
    void consultUCEnrolledStudents(const string& uc_name);
    void consultGreatestNumberOfStudentsUCs(int num);
    void consultSmallerNumberOfStudentsUCs(int num);
    void PrintWeekUCSchedule(const string& uc_name);
    void consultClassOccupancy(const string& class_code);
    int consultNumberOfStudentsRegisteredUCs(int numberOfUCs);

    void requestAddUC(string& student_id, string& uc_code);
    void requestAddClass(int student_id, const string& class_code);
    void requestRemoveUC();
    void requestRemoveClass(int student_id, const string& class_code);
    void requestSwitchUC();
    void requestSwitchClass();


private:
    std::set<UC_class> all_UCs_;// = populateUcSet("input/classes.csv");
    std::set<LeicClass> all_classes_;// = populateLeicSet("input/classes_per_uc.csv");
    std::set<Student> all_students_; //= populateStudentSet("input/students_classes.csv");
    std::string  database_;
    queue<string> requests_queue_;
    stack<string> system_changes_record_;

};


#endif //AED_PROJECT_SCRIPT_H
