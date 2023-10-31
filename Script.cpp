//
// Created by tiago on 30-10-2023.
//

#include "Script.h"




Script::Script(const string &database) {
    database_ = database;
}




void Script::populateUcSet(const string &filename) {
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
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

        LeicClass leic_class = LeicClass(classCode);

        auto classIt = all_classes.find(leic_class);

        LeicClass classCopy = LeicClass(*classIt);
        all_classes.erase(classIt);
        classCopy.addDayScheduleEntry(weekDay, curr_schedule);
        all_classes.insert(classCopy);



        if(all_UCs.find(uc_temp) != all_UCs.end()) {
            UC_class uc_temp2 = *all_UCs.find(uc_temp);
            all_UCs.erase(uc_temp);
            uc_temp2.addDayScheduleEntry(weekDay, curr_schedule);
            all_UCs.insert(uc_temp2);
        }

        uc_temp.addDayScheduleEntry(weekDay, curr_schedule);

        all_UCs.insert(uc_temp);



    }

    dataFile.close();
}




void Script::populateLeicSet(const string &filename) {
        std::ifstream dataFile(filename);



        if(dataFile.fail()) {
            std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
            std::cerr << "Error details: " << std::strerror(errno) << std::endl;
            return;
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

void Script::populateStudentSet(const string &filename) {
    std::ifstream dataFile(filename);

    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
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
        studentIt = all_students.find(tempStudent);

        if(studentIt == all_students.end()) {
            all_students.insert(tempStudent);
        }

    }

    dataFile.close();
}

void Script::PrintWeekScheduleClass(const string& class_name){
    auto classIt = all_classes.find(LeicClass(class_name));
    LeicClass temp = LeicClass(*classIt);
    temp.PrintUcWeekSchedule();
}

void Script::loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3) {
    populateLeicSet(filename_2);
    populateUcSet(filename_1);
    populateStudentSet(filename_3);

}
