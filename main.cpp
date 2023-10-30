#include <iostream>

#include <cstdio>
#include"Student.h"
#include "UC_class.h"
#include "LeicClass.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


std::set<UC_class> populateUcSet(const std::string& filename) {
    std::set<UC_class> uc_classes;
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return uc_classes;
    }
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        std::istringstream ss(line);

        std::string classCode;
        std::string ucCode;
        std::string weekDay;
        double startHour;
        double duration;
        std::string type;
        std::string temp;
        std::string temp2;

        char spacer = ',';


        std::getline(ss, classCode, spacer);
        std::getline(ss, ucCode, spacer);
        std::getline(ss, weekDay, spacer);
        std::getline(ss, temp, spacer);
        startHour = std::stod(temp);
        std::getline(ss, temp2, spacer);
        duration = std::stod(temp2);
        std::getline(ss, type, spacer);

        dayScheduleEntry curr_schedule =  {ucCode,classCode, startHour, duration, type};

        UC_class uc_temp = UC_class(ucCode);
        if(uc_classes.find(uc_temp) != uc_classes.end()) {
            UC_class uc_temp2 = *uc_classes.find(uc_temp);
            uc_classes.erase(uc_temp);
            uc_temp2.addUcSchedule(weekDay, curr_schedule);
            uc_classes.insert(uc_temp2);
        }

        uc_temp.addUcSchedule(weekDay, curr_schedule);

        uc_classes.insert(uc_temp);



    }

    dataFile.close();
    return uc_classes;



}

/*
std::set<UC> populateUcSet(const std::string& filename) {
    std::set<UC> uc_classes;
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return uc_classes;
    }
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        std::istringstream ss(line);

        std::string classCode;
        std::string ucCode;
        std::string weekDay;
        double startHour;
        double duration;
        std::string type;
        std::string temp;
        std::string temp2;

        char spacer = ',';


        std::getline(ss, classCode, spacer);
        std::getline(ss, ucCode, spacer);
        std::getline(ss, weekDay, spacer);
        std::getline(ss, temp, spacer);
        startHour = std::stod(temp);
        std::getline(ss, temp2, spacer);
        duration = std::stod(temp2);
        std::getline(ss, type, spacer);

        uc_classes.insert(ucCode);



    }

    dataFile.close();
    return uc_classes;



}
*/

std::set<LeicClass> populateLeicSet(const std::string& filename) {
    std::set<LeicClass> leicClasses;
    std::ifstream dataFile(filename);



    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return leicClasses;
    }
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        std::istringstream ss(line);
        std::string uccode;
        std::string classcode;
        char spacer = ',';
        std::getline(ss, uccode, spacer);
        std::getline(ss, classcode, spacer);

        LeicClass tempClass = LeicClass(classcode);
        std::set<LeicClass>::iterator classIt;
        classIt = leicClasses.find(tempClass);
        if (classIt != leicClasses.end()) {
            LeicClass classCopy = *classIt;
            leicClasses.erase(classIt);
            classCopy.addUcClass(UC_class(uccode));
            leicClasses.insert(classCopy);
        } else {
            tempClass.addUcClass(uccode);
            leicClasses.insert(tempClass);

        }
    }
    dataFile.close();
    return leicClasses;



}

std::set<Student> populateStudentSet(const std::string& filename) {
    std::set<Student> students;
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return students;
    }

    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        std::istringstream ss(line);
        int idNumber;
        std::string studentName;
        std::string UcCode;
        std::string classCode;
        std::string temp;

        std::getline(ss, temp, ',');
        idNumber =  std::stoi(temp);
        std::getline(ss, studentName, ',');
        std::getline(ss, UcCode, ',');
        std::getline(ss, classCode, ',');

        std::set<Student>::iterator studentIt;

        Student tempStudent = Student(idNumber, studentName);

        studentIt = students.find(tempStudent);

        if(studentIt == students.end()) {
            students.insert(tempStudent);
        }

    }

    dataFile.close();
    return students;

}

int main() {


    std::set<Student> result = populateStudentSet("input/students_classes.csv");
    std::set<UC_class> totalUc = populateUcSet("input/classes.csv");
    std::set<LeicClass> allClasses = populateLeicSet("input/classes_per_uc.csv");

    int counter = 1;
    for (const Student& student : result) {
        std::cout << counter << " - " <<  "ID: " << student.getIdNumber() << ", Name: " << student.getStudentName() << std::endl;
        counter++;
    }


    counter = 1;
    for (const UC_class& uc : totalUc) {
        std::cout << counter << " - " << "UC name: " << uc.getUcName() << std::endl;
        uc.getUcWeekSchedule();
        counter++;
    }

    counter = 1;

    for (const LeicClass& classes : allClasses) {
        std::cout << counter << " - " << "Class name: "<< std::endl;
        std::cout << "Class UC's " << std::endl;
        classes.getClassUc() ;
        counter++;
    }


    return 0;
}
