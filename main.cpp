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
    clearScreen();
    while(!close_program) {
        int studentNumber;
        int numberOfUcs;
        std::cout << "(1) >> Consult student schedule" << std::endl;
        std::cout << "(2) >> Consult student enrolled ucs" << std::endl;
        std::cout << "(3) >> Consult student class" << std::endl;
        std::cout << "(4) >> Consult the number of students registered in n UC's" << std::endl;
        std::cout << "(5) >> Go back" << std::endl;
        std::cout << "(6) >> Close menu" << std::endl;
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
                std::cout << "Insert student number;" << std::endl;
                std::cin >> studentNumber;
                std::cout <<  std::endl;
                script.consultStudentEnrolledUCs(studentNumber);
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "Insert student number;" << std::endl;
                std::cin >> studentNumber;
                std::cout <<  std::endl;
                script.consultStudentEnrolledClasses(studentNumber);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Insert the number of UC's a student has" << std::endl;
                std::cin >> numberOfUcs;
                std::cout << "Theres " << script.consultNumberOfStudentsRegisteredUCs(numberOfUcs) << " students registered at " << numberOfUcs << " UC's" << std::endl;
            case 5:
                std::cout << "Goes to the previous menu" << std::endl;
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

void displayUcMenu(Script& script){
    clearScreen();
    while(!close_program) {
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
            case 1: // Done
                std::cout << "Write the UC name" << std::endl ;
                std::cin >> uc_name;
                script.consultUCOccupancy(uc_name);
                std::cout << std::endl;
                break;
            case 2: // Done

                std::cout << "Write the UC name" << std::endl;
                std::cin >> uc_name;
                script.consultUCEnrolledStudents(uc_name);
                std::cout << std::endl;
                break;
            case 3: // Done
                std::cout << "Write the UC name" << std::endl;
                std::cin >> uc_name;
                script.PrintWeekUCSchedule(uc_name);
                std::cout << std::endl;
                break;
            case 4:

                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_ucs;
                std::cout << "Shows uc names and theirs occupancy" << std::endl;
                script.consultGreatestNumberOfStudentsUCs(number_of_ucs);

                break;
            case 5:
                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_ucs;
                script.consultSmallerNumberOfStudentsUCs(number_of_ucs);
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
    clearScreen();
    while(!close_program) {
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
                std::cout << "Write the amount of classes you want to see" << std::endl;
                std::cin >> number_of_classes;
                std::cout << "Shows classes  names and theirs occupancy" << std::endl;
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
    clearScreen();
    while(!close_program) {
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
        std::cout << "(3) >> Undo last action" << std::endl;
        std::cout << "(4) >> Close menu" << std::endl;
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
                std::cout << "Last action undone" << std::endl;
            case 4:
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                std::cout << "Choose a valid option" << std::endl;
                break;

        }

    }
}




int main() {
    Script new_script = Script("database");
    new_script.loadData("input/classes.csv","input/classes_per_uc.csv","input/students_classes.csv");
    displayInterfaceMenu(new_script);
    return 0;
}
