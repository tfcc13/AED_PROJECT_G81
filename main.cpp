#include <iostream>
#include "Script.h"
#include <cstdlib>


bool close_program = false;


void clearScreen() {
#ifdef _WIN32 // for Windows
    std::system("cls");
#elif defined(__APPLE__) // for macOS
    std::system("clear");
#else // assuming Unix-based system (Linux)
    std::system("clear");
#endif
}


void displayStudentMenu(Script& script){
    while(!close_program) {
        clearScreen();
        int studentNumber;
        std::cout << "(1) >> Consult student schedule" << std::endl;
        std::cout << "(2) >> Consult student enrolled ucs" << std::endl;
        std::cout << "(3) >> Consult student class" << std::endl;
        std::cout << "(4) >> Go back" << std::endl;
        std::cout << "(5) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;
        switch (input) {
            case 1:
                std::cout << "Insert student number;" << std::endl;
                std::cin >> studentNumber;
                std::cout <<  std::endl;
                script.PrintWeekStudentSchedule(studentNumber);
                break;
            case 2:
                std::cout << "Prints the number of uc's and ucs names" << std::endl;
                break;
            case 3:
                std::cout << "Prints student class name" << std::endl;
                break;
            case 4:
                std::cout << "Goes to the previous menu" << std::endl;
                return;
            case 5:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;

        }
    }

}

void displayUcMenu(Script& script){
    while(!close_program) {
        clearScreen();
        std::string uc_name;
        int number_of_ucs;
        std::cout << "(1) >> Consult UC occupancy" << std::endl;
        std::cout << "(2) >> Consult UC enrolled students" << std::endl;
        std::cout << "(3) >> Consult UC schedule" << std::endl;
        std::cout << "(4) >> Consult UC's with the greatest number of students" << std::endl;
        std::cout << "(5) >> Consult UC's with the smallest number of students" << std::endl;
        std::cout << "(6) >> Go back" << std::endl;
        std::cout << "(7) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;
        switch (input) {
            case 1:
                std::cout << "Write the UC name" << std::endl ;
                std::cin >> uc_name;
                std::cout << "Shows uc occupancy" << std::endl;
                break;
            case 2:

                std::cout << "Write the UC name" << std::endl;
                std::cin >> uc_name;
                std::cout << "Shows uc enrolled students" << std::endl;
                break;
            case 3:
                std::cout << "Write the UC name" << std::endl;
                std::cin >> uc_name;
                std::cout << "Shows uc schedule" << std::endl;
                break;
            case 4:

                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_ucs;
                std::cout << "Shows uc names and theirs occupancy" << std::endl;
                break;
            case 5:
                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_ucs;
                std::cout << "Shows uc names and theirs occupancy" << std::endl;
                break;
            case 6:
                std::cout << "Goes to the previous menu" << std::endl;
                return;
            case 7:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;
        }
    }
}
void displayClassMenu(Script& script){
    while(!close_program) {
        clearScreen();
        std::string class_name;
        int number_of_classes;
        std::cout << "(1) >> Consult class occupancy" << std::endl;
        std::cout << "(2) >> Consult class enrolled students" << std::endl;
        std::cout << "(3) >> Consult class schedule" << std::endl;
        std::cout << "(4) >> Consult classes with the greatest number of students" << std::endl;
        std::cout << "(5) >> Consult classes with the smallest number of students" << std::endl;
        std::cout << "(6) >> Go back" << std::endl;
        std::cout << "(7) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;

        switch (input) {
            case 1:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                std::cout << "Shows class occupancy" << std::endl;
                break;
            case 2:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                std::cout << "Shows class enrolled students" << std::endl;
                break;
            case 3:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                script.PrintWeekScheduleClass(class_name);
                std::cout <<  std::endl;
                break;
            case 4:
                std::cout << "Write the amount of classes you want to see" << std::endl;
                std::cin >> number_of_classes;
                std::cout << "Shows classes names and theirs occupancy" << std::endl;
                break;
            case 5:
                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_classes;
                std::cout << "Shows uc names and theirs occupancy" << std::endl;
                break;
            case 6:
                std::cout << "Goes to the previous menu" << std::endl;
                return;
            case 7:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;
        }
    }

}
void displayYearMenu(Script& script){}


void displayDataConsultationMenu(Script& script){
    while(!close_program) {
        clearScreen();
        std::cout << "(1) >> Consult data by student" << std::endl;
        std::cout << "(2) >> Consult data by uc" << std::endl;
        std::cout << "(3) >> Consult data by class" << std::endl;
        std::cout << "(4) >> Consult data by year" << std::endl;
        std::cout << "(5) >> Go back" << std::endl;
        std::cout << "(6) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        std::cin >> input;
        std::cout << std::endl;

        switch (input) {
            case 1:
                displayStudentMenu(script);
                break;
            case 2:
                displayUcMenu(script);
                break;
            case 3:
                displayClassMenu(script);
                break;
            case 4:
                displayYearMenu(script);
                break;
            case 5:
                return;
            case 6:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;
        }
    }
}
void displayRequestMenu(Script& script){}




void displayInterfaceMenu(Script& script) {

    while(!close_program) {
        clearScreen();
        std::cout << "(1) >> Data Consultation" << std::endl;
        std::cout << "(2) >> Requests" << std::endl;
        std::cout << "(3) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;
        int input;
        std::cin >> input;
        std::cout << std::endl;

        switch (input) {
            case 1:
                displayDataConsultationMenu(script);
                break;
            case 2:
                displayRequestMenu(script);
                break;
            case 3:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;

        }

    }
}


/*
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
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
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
            LeicClass classCopy = LeicClass(*classIt);
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
        studentIt = students.find(tempStudent);

        if(studentIt == students.end()) {
            students.insert(tempStudent);
        }

    }

    dataFile.close();
    return students;

}
*/



int main() {
    Script new_script = Script("database");
    new_script.loadData("input/classes.csv","input/classes_per_uc.csv","input/students_classes.csv");

/*

    std::set<UC_class> totalUc = populateUcSet("input/classes.csv");
    std::set<LeicClass> allClasses = populateLeicSet("input/classes_per_uc.csv");
    std::set<Student> result = populateStudentSet("input/students_classes.csv");

    int counter = 1;
    for (const Student& student : result) {
        std::cout << counter << " - " <<  "ID: " << student.getIdNumber() << ", Name: " << student.getStudentName() << std::endl;
        counter++;
    }

    std::vector<string>  weekdays = {"Monday","Tuesday","Wednesday","Thursday","Friday",};


    counter = 1;
    for (const UC_class& uc : totalUc) {
        std::cout << counter << " - " << "UC name: " << uc.getUcName() << std::endl;
        uc.getUcWeekSchedule();
    }

    counter = 1;

    for (const LeicClass& classes : allClasses) {
        std::cout << counter << " - " << "Class name: "<<  classes.getClassName() << std::endl;
        classes.getClassUc() ;
        counter++;
    }
*/

    displayInterfaceMenu(new_script);
    return 0;
}
