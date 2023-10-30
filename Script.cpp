//
// Created by tiago on 30-10-2023.
//

#include "Script.h"


std::set<UC_class> Script::populateUcSet(const string &filename) {
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return all_ucs;
    }
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
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
        if(all_ucs.find(uc_temp) != all_ucs.end()) {
            UC_class uc_temp2 = *all_ucs.find(uc_temp);
            all_ucs.erase(uc_temp);
            uc_temp2.addUcSchedule(weekDay, curr_schedule);
            all_ucs.insert(uc_temp2);
        }

        uc_temp.addUcSchedule(weekDay, curr_schedule);

        all_ucs.insert(uc_temp);



    }

    dataFile.close();
    return all_ucs;



}




std::set<LeicClass> Script::populateLeicSet(const string &filename) {
        std::ifstream dataFile(filename);



        if(dataFile.fail()) {
            std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
            std::cerr << "Error details: " << std::strerror(errno) << std::endl;
            return all_classes;
        }
        std::string header;
        getline(dataFile, header);
        std::string line;

        while (std::getline(dataFile,line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::istringstream ss(line);
            std::string uccode;
            std::string classcode;
            char spacer = ',';
            std::getline(ss, uccode, spacer);
            std::getline(ss, classcode, spacer);


            LeicClass tempClass = LeicClass(classcode);
            std::set<LeicClass>::iterator classIt;
            classIt = all_classes.find(tempClass);
            if (classIt != all_classes.end()) {
                LeicClass classCopy = LeicClass(*classIt);
                all_classes.erase(classIt);
                classCopy.addUcClass(UC_class(uccode));
                all_classes.insert(classCopy);
            } else {
                tempClass.addUcClass(uccode);
                all_classes.insert(tempClass);


            }
        }
        dataFile.close();




    }

std::set<Student> Script::populateStudentSet(const string &filename) {
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return student_set;
    }

    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
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
        studentIt = student_set.find(tempStudent);

        if(studentIt == student_set.end()) {
            student_set.insert(tempStudent);
        }

    }

    dataFile.close();
    return student_set;

}


