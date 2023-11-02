//
// Created by tiago on 30-10-2023.
//

#include "Script.h"

Script::Script(const string &database) {
    database_ = database;
    leic_class_years_.resize(3);
    UC_years_.resize(3);
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

        int year = classCode.at(0)-'0';
        dayScheduleEntry curr_schedule =  {ucCode,classCode, startHour, duration, type};

        UC_class uc_temp = UC_class(ucCode,year);

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

void Script::consultUCEnrolledStudents(const string& uc_name) {
    auto UCClassIt = all_UCs_.find(uc_name);
    UCClassIt->PrintEnrolledStudents();

}

void Script::consultGreatestNumberOfStudentsUCs(int num) {
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);
    auto setIt = sortedByOccupancy.end();
    setIt--;
    if (num <= int(sortedByOccupancy.size())) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt--) {
            std::cout << left << setw(8) << setIt->getUcName() << " | "  << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "Theres only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }

}

void Script::consultSmallerNumberOfStudentsUCs(int num) {
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);
    auto setIt = sortedByOccupancy.begin();
    if (num <= int(sortedByOccupancy.size())) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt++) {
            std::cout << left << setw(8) << setIt->getUcName() << " | " << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "Theres only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }

}

void Script::PrintWeekUCSchedule(const string& uc_name){
    auto itUC = all_UCs_.find(UC_class(uc_name));
    itUC->PrintUcWeekSchedule();
}


int Script::consultClassOccupancy(const string& class_code) {
    auto classIt = all_classes_.find(LeicClass(class_code));
    int num = classIt->getNumberOfEnrolledStudents();
    return num;
}

int Script::consultUCCLassOccupancy(const string& class_code, const string& uc_code) {
    auto classIt = all_classes_.find(LeicClass(class_code));
    UC_class UC_temp = classIt->getUCClass(uc_code);
    return UC_temp.getNumberOfEnrolledStudents();
}

void Script::PrintUCClassSchedule(const string& class_code, const string& uc_code){
    auto classIt = all_classes_.find(LeicClass(class_code));
    UC_class UC_temp = classIt->getUCClass(uc_code);
    UC_temp.PrintUcWeekSchedule();
}

int Script::consultNumberOfStudentsRegisteredUCs(int numberOfUCs) {
    int counter = 0;
    auto studentIt = all_students_.begin();
    for (; studentIt != all_students_.end(); studentIt++) {
        if (studentIt->getNumberOfUCs() == numberOfUCs) counter++;
    }
    return counter;
}

void Script::consultClassEnrolledStudents(const string& class_code) {
    auto classIt = all_classes_.find(LeicClass(class_code));
    set<Student> class_students = classIt->getEnrolledStudents();
    cout << left << setw(14) << "Student number" << " | " << "Student name" << endl;
    for (Student student : class_students) {
        cout << left << setw(14) << student.getIdNumber() << " | " << student.getStudentName() << endl;
    }
}


void Script::consultGreatestClasses(int num_classes){
    auto compareNumberOfStudents = [](const LeicClass& class_a, const LeicClass& class_b) {
        return class_a.getNumberOfEnrolledStudents() < class_b.getNumberOfEnrolledStudents();
    };
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(all_classes_.begin(),all_classes_.end(), compareNumberOfStudents);
    auto classIt = sortedByOccupancy.end();
    classIt--;
    if (num_classes <= int(sortedByOccupancy.size())) {
        std::cout << left << setw(7) << "Class" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num_classes; i++, classIt--) {
            std::cout << left << setw(7) << classIt->getClassName() << " | "  << classIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "Theres only " << sortedByOccupancy.size() << " classes, please choose a smaller number" << std::endl;
    }


}
void Script::consultSmallestClasses(int num_classes){    auto compareNumberOfStudents = [](const LeicClass& class_a, const LeicClass& class_b) {
        return class_a.getNumberOfEnrolledStudents() < class_b.getNumberOfEnrolledStudents();
    };
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(all_classes_.begin(),all_classes_.end(), compareNumberOfStudents);
    auto classIt = sortedByOccupancy.begin();
    if (num_classes <= int(sortedByOccupancy.size())) {
        std::cout << left << setw(7) << "Class" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num_classes; i++, classIt++) {
            std::cout << left << setw(7) << classIt->getClassName() << " | "  << classIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "Theres only " << sortedByOccupancy.size() << " classes, please choose a smaller number" << std::endl;
    }
}

int Script::consultYearOccupancy(int year) {
    set<Student> temp_student;
    set<Student> student_union;
    for (const auto & classIt : leic_class_years_[year]) {
        set<Student> temp = classIt.getEnrolledStudents();
        set_union(temp_student.begin(), temp_student.end(),
                  temp.begin(),temp.end(),
                  inserter(student_union,student_union.begin()));
        temp_student = student_union;
    }
    return  int(student_union.size());
}

// Francisco vê isto

/**
 * @brief prints the students in a year ordered by number
 *
 * This function makes a set of students within a Leic year (1,2 or 3)
 *
 *
 *
 * @param year Recebe o ano que se quer ver
 *
 * @return Description of the return value.
 */

void Script::consultEnrolledStudentsYear(int year) {
    set<Student> temp_student;
    // Francisco ve isto
    /// This set is a union of unique students in a year
    set<Student> student_union;
    for (const auto & classIt : leic_class_years_[year]) {
        set<Student> temp = classIt.getEnrolledStudents();
        set_union(temp_student.begin(), temp_student.end(),
                  temp.begin(),temp.end(),
                  inserter(student_union,student_union.begin()));
    temp_student = student_union;
    }
    cout << left << setw(9) << "Number" << " | " << "Student Name" << std::endl;
    for (const auto & student : student_union) {
        cout << left << setw(9) << student.getIdNumber() << " | " << student.getStudentName() << endl;
    }
}

void Script::requestAddClass(int student_id, const string& class_code) {
    auto studentIt = all_students_.find(Student(student_id,""));
    auto classIt = all_classes_.find(LeicClass(class_code));

}

void Script::requestRemoveClass(int student_id, const std::string &class_code) {

    auto studentIt = all_students_.find(Student(student_id,""));
    Student original_student = *studentIt;
    Student modified_student = *studentIt;
    all_students_.erase(studentIt);

    auto classIt = all_classes_.find(LeicClass(class_code));
    LeicClass temp_LeicClass = *classIt;
    all_classes_.erase(classIt);

    auto student_enrolled_UC_and_classes = studentIt->get_student_enrolled_UC_and_classes();

    // Atualizar horário do estudante e registar UCs removidas
    set<string> removed_UCs;
    for(const auto& class_code_UC_code_pair : student_enrolled_UC_and_classes){
        string current_class_code =  class_code_UC_code_pair.first;
        string current_UC_code = class_code_UC_code_pair.second;
        if(current_class_code == class_code){
            Schedule schedule_to_remove = temp_LeicClass.getUCClass(current_UC_code).getUCClassSchedule();
            modified_student.removeSchedule(current_class_code, current_UC_code, schedule_to_remove);
            removed_UCs.insert(current_UC_code);
        }
    }

    // Atualizar LeicClass e all_UCs_
    for(const string& UC_code : removed_UCs){
        // LeicClass
        UC_class temp_UCClass = temp_LeicClass.getUCClass(UC_code);
        temp_LeicClass.eraseUcClass(UC_code);
        temp_UCClass.eraseStudent(original_student);
        temp_LeicClass.insertUcClass(temp_UCClass);
        // all_UCs_
        auto UCIt = all_UCs_.find(UC_class(UC_code));
        UC_class temp_UC = *UCIt;
        temp_UC.eraseStudent(original_student);
        all_UCs_.erase(UCIt);
        all_UCs_.insert(temp_UC);
    }

    all_classes_.insert(temp_LeicClass);
    all_students_.insert(modified_student);

}

// Para na UC, inscrever nas turmas com menos alunos
vector<pair<string, int>> Script::getNumberOfEnrolledStudentsPerClassInUC(const string& UC_code) const{
    vector<pair<string, int>> NumberOfEnrolledStudentsPerClass;
    for(const LeicClass& current_class : all_classes_){
        auto itUCClass = current_class.getUCClass(UC_code);
        if(itUCClass != UC_class("Não existe")){
            NumberOfEnrolledStudentsPerClass.emplace_back(current_class.getClassName(), itUCClass.getNumberOfEnrolledStudents());
        }
    }
    std::sort(NumberOfEnrolledStudentsPerClass.begin(), NumberOfEnrolledStudentsPerClass.end(),
              [](const pair<string, int>& a, const pair<string, int>& b) {
                  return a.second < b.second;
              });
}

// Para verificar o balanço de alunos entre turmas na mesma UC
bool Script::checkBalanceBetweenTwoClassesInUC(const string& UC_code, const string& class_code_1, const string& class_code_2){
    auto NumberOfEnrolledStudentsPerClass = this->getNumberOfEnrolledStudentsPerClassInUC(UC_code);
    auto it1 = find_if(NumberOfEnrolledStudentsPerClass.begin(), NumberOfEnrolledStudentsPerClass.end(), [class_code_1](const pair<std::string, int>& p) {
        return p.first == class_code_1;
    });
    auto it2 = find_if(NumberOfEnrolledStudentsPerClass.begin(), NumberOfEnrolledStudentsPerClass.end(), [class_code_2](const pair<std::string, int>& p) {
        return p.first == class_code_2;
    });
    return abs(it1->second - it2->second) <= 4;
}



void Script::loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3) {
    populateLeicSet(filename_2);
    populateUcSet(filename_1);
    populateStudentSet(filename_3);
}

void Script::loadYear() {
    for (const auto & classIt : all_classes_) {
        if(classIt.getClassName().at(0) == '1') {
            leic_class_years_.at(0).insert(classIt);
        }
        else if((classIt.getClassName().at(0) == '2')) {
            leic_class_years_.at(1).insert(classIt);
        }
        else if((classIt.getClassName().at(0) == '3')) {
            leic_class_years_.at(2).insert(classIt);
        }
    }
    for(const auto & UCIt : all_UCs_) {
        if(UCIt.getUCYear() == 1) {
            UC_years_.at(0).insert(UCIt);
        }
        else if((UCIt.getUCYear() == 2)) {
            UC_years_.at(1).insert(UCIt);
        }
        else if((UCIt.getUCYear() == 3)) {
            UC_years_.at(0).insert(UCIt);
        }
    }
}

