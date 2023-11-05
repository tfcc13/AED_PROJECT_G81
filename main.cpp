#include <iostream>
#include "Script.h"
#include <cstdlib>
#include <limits>


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

// Done



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
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
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
                cout << endl;
                std::cout << "Theres " << script.consultNumberOfStudentsRegisteredUCs(numberOfUcs) << " students registered at " << numberOfUcs << " UC's" << std::endl;
                cout << endl;
                break;
            case 5:
                clearScreen();
                return;
            case 6:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;

        }
    }

}

// Done
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
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        switch (input) {
            case 1: // Done
                std::cout << "Write the UC name" << std::endl ;
                std::cin >> uc_name;
                cout << endl;
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
                script.consultGreatestNumberOfStudentsUCs(number_of_ucs);
                std::cout <<  std::endl;
                break;
            case 5:
                std::cout << "Write the amount of UC's you want to see" << std::endl;
                std::cin >> number_of_ucs;
                script.consultSmallerNumberOfStudentsUCs(number_of_ucs);
                std::cout << std::endl;
                break;
            case 6:
                clearScreen();
                return;
            case 7:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;
        }
    }
}

//Done
void displayClassMenu(Script& script){
    clearScreen();
    while(!close_program) {
        std::string class_name;
        std::string uc_code;
        int number_of_classes;
        std::cout << "(1) >> Consult class occupancy" << std::endl;
        std::cout << "(2) >> Consult UC class occupancy" << std::endl;
        std::cout << "(3) >> Consult class enrolled students" << std::endl;
        std::cout << "(4) >> Consult UC class enrolled students" << std::endl;
        std::cout << "(5) >> Consult class schedule" << std::endl;
        std::cout << "(6) >> Consult UC class schedule" << std::endl;
        std::cout << "(7) >> Consult classes with the greatest number of students" << std::endl;
        std::cout << "(8) >> Consult classes with the smallest number of students" << std::endl;
        std::cout << "(9) >> Go back" << std::endl;
        std::cout << "(10) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        switch (input) {
            case 1:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                cout << endl;
                script.consultClassOccupancy(class_name);
                cout << std::endl;
                break;
            case 2:
                std::cout << "Write the class name" << std::endl;
                cin >> class_name;
                std::cout << "Write the UC name" << std::endl;
                cin >> uc_code;
                cout << endl;
                script.consultUCCLassOccupancy(class_name,uc_code);
                cout << endl;
                break;
            case 3:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                cout << endl;
                script.consultClassEnrolledStudents(class_name);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Write the class name" << std::endl;
                cin >> class_name;
                std::cout << "Write the UC name" << std::endl;
                cin >> uc_code;
                cout << endl;
                script.consultUCCLassEnrolledStudents(class_name,uc_code);
                cout << endl;
                break;
            case 5:
                std::cout << "Write the class name" << std::endl;
                std::cin >> class_name;
                cout << endl;
                script.PrintWeekScheduleClass(class_name);
                std::cout <<  std::endl;
                break;
            case 6:
                std::cout << "Write the class name" << std::endl;
                cin >> class_name;
                std::cout << "Write the UC name" << std::endl;
                cin >> uc_code;
                cout << endl;
                script.PrintUCClassSchedule(class_name,uc_code);
                cout << endl;
                break;
            case 7:
                std::cout << "Write the amount of classes you want to see" << std::endl;
                std::cin >> number_of_classes;
                script.consultGreatestClasses(number_of_classes);
                std::cout <<  std::endl;
                break;
            case 8:
                std::cout << "Write the amount of classes you want to see" << std::endl;
                std::cin >> number_of_classes;
                cout << endl;
                script.consultSmallestClasses(number_of_classes);
                std::cout << std::endl;
                break;
            case 9:
                clearScreen();
                return;
            case 10:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;
        }
    }

}

//Done
void displayYearMenu(Script& script){
    clearScreen();

    while(!close_program) {
        string uc_code;
        int year;
        string class_code;
        int n_students;

        std::cout << "(1) >> Consult the number of enrolled students in a year" << std::endl;
        std::cout << "(2) >> Consult a list of enrolled students in a year" << std::endl;
        std::cout << "(3) >> Consult UC's in a year" << std::endl;
        std::cout << "(4) >> Consult UC's in a year by in ascending order by occupancy" << std::endl;
        std::cout << "(5) >> Consult UC's in a year by in descending order by occupancy" << std::endl;
        std::cout << "(6) >> Consult UC's in a year with a minimum of n students" << std::endl;
        std::cout << "(7) >> Consult UC's in a year with a maximum of n students" << std::endl;
        std::cout << "(8) >> Consult classes in a year" << std::endl;
        std::cout << "(9) >> Consult classes in a year in ascending order by occupancy" << std::endl;
        std::cout << "(10) >> Consult classes in a year in descending order by occupancy" << std::endl;
        std::cout << "(11) >> Consult classes in a year with a minimum of n students" << std::endl;
        std::cout << "(12) >> Consult classes in a year with a maximum of n students" << std::endl;
        std::cout << "(13) >> Go back" << std::endl;
        std::cout << "(14) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;

        int input;
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        switch (input) {
            case 1:
                std::cout << "Insert the year you want to consult the occupancy" << std::endl;
                cin >> year;
                cout << endl;
                script.consultYearOccupancy(year);
                cout << endl;
                break;
            case 2:
                std::cout << "Insert the year you want to consult the enrolled students" << std::endl;
                cin >> year;
                cout << endl;
                script.consultEnrolledStudentsYear(year);
                cout << endl;
                break;
            case 3:
                std::cout << "Insert the year you want to consult the UC's names" << std::endl;
                cin >> year;
                cout << endl;
                script.consultUCsByYear(year);
                cout << endl;
                break;
            case 4:
                std::cout << "Insert the year you want to consult the UC's ascending occupancy " << std::endl;
                cin >> year;
                cout << endl;
                script.consultUCsByYearByAscendingOccupancy(year);
                std::cout << endl;
                break;
            case 5:
                std::cout << "Insert the year you want to consult the UC's descending occupancy " << std::endl;
                cin >> year;
                cout << endl;
                script.consultUCsByYearByDescendingOccupancy(year);
                std::cout << endl;
                break;
            case 6:
                std::cout << "Insert the year you want to consult the UC's" << std::endl;
                cin >> year;
                cout << "Write the minimum of N students " << std::endl;
                cin >> n_students;
                cout << endl;
                script.consultUCsWithMinNStudents(year,n_students);
                std::cout << endl;
                break;
            case 7:
                std::cout << "Insert the year you want to consult the UC's" << std::endl;
                cin >> year;
                cout << "Write the maximum of N students " << std::endl;
                cin >> n_students;
                cout << endl;
                script.consultUCsWithMaxNStudents(year,n_students);
                std::cout << endl;
                break;
            case 8:
                std::cout << "Insert the year you want to consult classes names" << std::endl;
                cin >> year;
                cout << endl;
                script.consultClassesInaYear(year);
                std::cout << endl;
                break;
            case 9:
                std::cout << "Insert the year you want to consult classes occupancy by ascending order" << std::endl;
                cin >> year;
                cout << endl;
                script.consultClassesInaYearByAscendingOccupancy(year);
                std::cout << endl;
                break;
            case 10:
                std::cout << "Insert the year you want to consult classes occupancy by descending order" << std::endl;
                cin >> year;
                cout << endl;
                script.consultClassesInaYearByDescendingOccupancy(year);
                std::cout << endl;
                break;
            case 11:
                std::cout << "Insert the year you want to consult classes with a minimum of N students" << std::endl;
                cin >> year;
                cout << "Insert the minimum of N students " << std::endl;
                cin >> n_students;
                cout << endl;
                script.consultClassesWithMinNStudents(year, n_students);
                cout << endl;
                break;
            case 12:
                std::cout << "Insert the year you want to consult classes with a maximum of N students" << std::endl;
                cin >> year;
                cout << "Insert the maximum of N students " << std::endl;
                cin >> n_students;
                cout << endl;
                script.consultClassesWithMaxNStudents(year, n_students);
                cout << endl;
                break;
            case 13:
                clearScreen();
                return;
            case 14:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;
        }
    }
}


//done
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
        //std::cin >> input;
        //std::cout << std::endl;

        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

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
                clearScreen();
                return;
            case 6:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;
        }
    }
}


void displayRequestMenu(Script& script){
    clearScreen();
    while(!close_program) {

        std::string class_code;
        std::string UC_code;
        int student_code;
        std::cout << "(1) >> Add class" << std::endl;
        std::cout << "(2) >> Remove a student class from all enrolled UC's" << std::endl;
        std::cout << "(3) >> Switch class" << std::endl;
        std::cout << "(4) >> Add UC" << std::endl;
        std::cout << "(5) >> Remove UC" << std::endl;
        std::cout << "(6) >> Switch UC" << std::endl;
        std::cout << "(7) >> Go back" << std::endl;
        std::cout << "(8) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;
        int input;
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        switch (input) {
            case 1:
                std::cout << "Adds a  class" << std::endl;
                script.captureState();
                break;
            case 2:
                std::cout << "Insert student code" << std::endl;
                cin >> student_code;
                std::cout << "Insert the class code to remove" << std::endl;
                cin >> class_code;
                cout << endl;
                script.captureState();
                script.requestRemoveClassForAllUCs(student_code, class_code);
                cout << endl;
                break;
            case 3:
                std::cout << "Switches a  class" << std::endl;
            case 4:
                script.captureState();
                std::cout << "Adds UC's" << std::endl;
                std::cout << std::endl;
                break;
            case 5:
                std::cout << "Insert student code" << std::endl;
                cin >> student_code;
                std::cout << "Insert the UC code to remove" << std::endl;
                cin >> UC_code;
                script.captureState();
                script.requestRemoveUC(student_code, UC_code);
                std::cout << std::endl;
                break;
            case 6:
                std::cout << "Switches UC's" << std::endl;
                script.captureState();
                std::cout << std::endl;
                break;
            case 7:
                clearScreen();
                return;
            case 8:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                std::cout << std::endl;
                break;

        }

    }

}




//done

void displayInterfaceMenu(Script& script) {
    clearScreen();
    while(!close_program) {
        string filename;
        std::cout << "(1) >> Data Consultation" << std::endl;
        std::cout << "(2) >> Requests" << std::endl;
        std::cout << "(3) >> Undo last action" << std::endl;
        std::cout << "(4) >> Save the changes into a csv file" << std::endl;
        std::cout << "(5) >> Close menu" << std::endl;
        std::cout << "Please choose an option" << std::endl;
        int input;
        //std::cin >> input;
        //std::cout << std::endl;
        while (true) {

            if (std::cin >> input) {
                std::cout << std::endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        switch (input) {
            case 1:
                displayDataConsultationMenu(script);
                break;
            case 2:
                displayRequestMenu(script);
                break;
            case 3:
                script.undoLastAction();
                std::cout << "Last action undone" << std::endl;
                break;
            case 4:
                std::cout << "Write the name of output  csv file" << std::endl;
                cin >> filename;
                script.saveChangesToCsvFile(filename);
                cout << std::endl;
                break;
            case 5:
                clearScreen();
                std::cout << "Menu closed" << std::endl;
                close_program = true;
                break;
            default:
                clearScreen();
                std::cout << "Choose a valid option" << std::endl;
                cout << endl;
                break;

        }

    }
}




int main() {
    Script new_script = Script("database");
    new_script.loadData("input/classes.csv","input/classes_per_uc.csv","input/students_classes.csv");
    new_script.loadYear();
    displayInterfaceMenu(new_script);
    return 0;
}
