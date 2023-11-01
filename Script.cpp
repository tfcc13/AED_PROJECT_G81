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

        auto classIt = all_classes_.find(leic_class);

        LeicClass classCopy = LeicClass(*classIt);
        all_classes_.erase(classIt);
        classCopy.addDayScheduleEntry(weekDay, curr_schedule);
        UC_class uc_class_temp = classCopy.getUCClass(ucCode);
        classCopy.eraseUcClass(uc_class_temp);
        uc_class_temp.addDayScheduleEntry(weekDay, curr_schedule);
        classCopy.insertUcClass(uc_class_temp);

        if(all_UCs_.find(uc_temp) != all_UCs_.end()) {
            UC_class uc_temp2 = *all_UCs_.find(uc_temp);
            all_UCs_.erase(uc_temp);
            uc_temp2.addDayScheduleEntry(weekDay, curr_schedule);
            all_UCs_.insert(uc_temp2);
        }

        uc_temp.addDayScheduleEntry(weekDay, curr_schedule);
        all_classes_.insert(classCopy);
        all_UCs_.insert(uc_temp);

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
            classIt = all_classes_.find(tempClass);
            if (classIt != all_classes_.end()) {
                LeicClass classCopy = LeicClass(*classIt);
                all_classes_.erase(classIt);
                classCopy.insertUcClass(UC_class(uccode));
                all_classes_.insert(classCopy);
            } else {
                tempClass.insertUcClass(UC_class(uccode));
                all_classes_.insert(tempClass);
            }
        }
        dataFile.close();

}

void Script::populateStudentSet(const string &filename) {
    std::ifstream dataFile(filename);

    if (dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
    }

    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::istringstream ss(line);
        int idNumber;
        std::string studentName;
        std::string UcCode;
        std::string classCode;
        std::string temp;

        std::getline(ss, temp, ',');
        idNumber = std::stoi(temp);
        std::getline(ss, studentName, ',');
        std::getline(ss, UcCode, ',');
        std::getline(ss, classCode, ',');

        auto classIt = all_classes_.find(LeicClass(classCode)); //
        LeicClass tempLeicClass = *classIt; //
        all_classes_.erase(tempLeicClass); //
        UC_class tempUCClass = tempLeicClass.getUCClass(UcCode); //
        tempLeicClass.eraseUcClass(tempUCClass); //
        Schedule schedule = tempUCClass.getUCClassSchedule(); //

        Student tempStudent = Student(idNumber, studentName); //

        auto UCIt = all_UCs_.find(UC_class(UcCode)); //
        auto tempUC = *UCIt; //
        all_UCs_.erase(UCIt); //

        auto studentIt = all_students_.find(tempStudent); //
        if (studentIt != all_students_.end()) {
            tempStudent = *studentIt; //
            all_students_.erase(studentIt); //
            tempUCClass.eraseStudent(tempStudent); //
            tempUC.eraseStudent(tempStudent); //
        }

        tempStudent.addSchedule(classCode, UcCode, schedule); //

        all_students_.insert(tempStudent); //
        tempUCClass.insertStudent(tempStudent); //
        tempLeicClass.insertUcClass(tempUCClass); //
        all_classes_.insert(tempLeicClass); //
        tempUC.insertStudent(tempStudent); //
        all_UCs_.insert(tempUC); //

    }

    dataFile.close();
}

void Script::PrintWeekStudentSchedule(int studentNumber) {
    auto studentIt = all_students_.find(Student(studentNumber,""));
    Student studentTemp = *studentIt;
    studentTemp.PrintUcWeekSchedule();
    std::cout << std::endl;
}

void Script::PrintWeekScheduleClass(const string& class_name){
    auto classIt = all_classes_.find(LeicClass(class_name));
    LeicClass temp = LeicClass(*classIt);
    temp.PrintUcWeekSchedule();
}

void Script::consultStudentEnrolledUCs(int studentNumber) {
    auto studentIt = all_students_.find(Student(studentNumber,""));

    Student studentTemp = *studentIt;
    studentTemp.PrintEnrolledUCs();
}

void Script::consultStudentEnrolledClasses(int studentNumber) {
    auto studentIt = all_students_.find(Student(studentNumber,""));
    studentIt->PrintEnrolledClasses();
}

void Script::consultUCOccupancy(const string& uc_name) {
    auto UCClassIt = all_UCs_.find(UC_class(uc_name));
    std::cout << UCClassIt->getNumberOfEnrolledStudents() << std::endl;
}

void Script::loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3) {
    populateLeicSet(filename_2);
    populateUcSet(filename_1);
    populateStudentSet(filename_3);
}

