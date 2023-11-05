//
// Created by tiago on 30-10-2023.
//


#include "Script.h"

Script::Script(const string &database) {
    database_ = database;
    ///O tamanho de leic_class_years e UC_years_ é 3, já que há 3 anos.
    leic_class_years_.resize(3);
    UC_years_.resize(3);
}

void Script::populateUcSet(const string &filename) {
    ///O ficheiro de input é aberto.
    std::ifstream dataFile(filename);

    ///Se não for possível abrir o ficheiro, imprime-se "Error Warning: Unable to open the file " e os detalhes do erro. Sai-se da função.
    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
    }

    ///Caso contrário, a primeira linha do ficheiro é interpretada como header.
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::istringstream ss(line);

        ///A partir de cada uma das restantes linhas do ficheiro, obtém-se, por esta ordem, os valores classCode, ucCode, weekDay, startHour, duration e type .
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


        ///O ano é obtido através do primeiro carater
        int year = classCode.at(0)-'0';

        ///A partir de ucCode, classCode, startHour, duration e type cria-se um novo objeto do tipo dayScheduleEntry, representando uma aula, chamado curr_schedule.
        dayScheduleEntry curr_schedule =  {ucCode,classCode, startHour, duration, type};

        ///Cria-se também uma UC_class uc_temp a partir de ucCode e year e uma LeicClass a partir de classCode
        UC_class uc_temp = UC_class(ucCode,year);

        LeicClass leic_class = LeicClass(classCode);

        ///Procura-se no set all_classes_ a LeicClass criada, faz-se uma cópia classCopy e apaga-se a original do set
        auto classIt = all_classes_.find(leic_class);

        LeicClass classCopy = LeicClass(*classIt);
        all_classes_.erase(classIt);

        ///Adiciona-se curr_schedule ao horário de classCopy no dia weekDay, através da função addDayScheduleEntry de classCopy
        classCopy.addDayScheduleEntry(weekDay, curr_schedule);

        ///Adquire-se no objeto uc_class_temp através da função getUCClass de classCopy o objeto UC_class associado com ucCode e apaga esta UC_class de classCopy.
        UC_class uc_class_temp = classCopy.getUCClass(ucCode);
        classCopy.eraseUcClass(uc_class_temp);

        ///Adiciona-se curr_schedule a uc_class_temp através do mesmo processo usado anteriormente em classCopy.
        uc_class_temp.addDayScheduleEntry(weekDay, curr_schedule);

        ///uc_class_temp é inserido em classCopy através da função insertUcClass .
        classCopy.insertUcClass(uc_class_temp);

        ///Procura-se uc_temp em all_UCs_ . Se for encontrado, cria-se uma cópia uc_temp2 do equivalente de uc_temp em all_UCs_, que é apagado deste. Adiciona-se curr_schedule a uc_temp2 e adiciona-se essa UC_class a all_UCs_ . Essencialmente, o horário é atualizado em all_UCs_ .
        if(all_UCs_.find(uc_temp) != all_UCs_.end()) {
            UC_class uc_temp2 = *all_UCs_.find(uc_temp);
            all_UCs_.erase(uc_temp);
            uc_temp2.addDayScheduleEntry(weekDay, curr_schedule);
            all_UCs_.insert(uc_temp2);
        }

        ///curr_schedule é adicionado a uc_temp e classCopy (uma versão mais atualizada de leic_class) e uc_temp são adicionados aos seus respetivos sets, all_classes_ e all_UCs_ .
        uc_temp.addDayScheduleEntry(weekDay, curr_schedule);
        all_classes_.insert(classCopy);
        all_UCs_.insert(uc_temp);

    }

    ///Por fim, após todas as linhas serem interpretadas, o ficheiro de input é fechado.
    dataFile.close();
}

void Script::populateLeicSet(const string &filename) {
    ///O ficheiro de input é aberto.
    std::ifstream dataFile(filename);

    ///Se não for possível abrir o ficheiro, imprime-se "Error Warning: Unable to open the file " e os detalhes do erro. Sai-se da função.
    if(dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
    }

    ///Caso contrário, a primeira linha do ficheiro é interpretada como header.
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile,line)) {
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            std::istringstream ss(line);

            ///A partir de cada uma das restantes linhas do ficheiro, obtém-se, por esta ordem, uccode e classcode .
            std::string uccode;
            std::string classcode;
            char spacer = ',';
            std::getline(ss, uccode, spacer);
            std::getline(ss, classcode, spacer);

            ///Cria-se um novo objeto LeicClass chamado tempClass a partir de classCode.
            LeicClass tempClass = LeicClass(classcode);

            ///Procura-se tempClass em all_classes_ .
            std::set<LeicClass>::iterator classIt;
            classIt = all_classes_.find(tempClass);

            ///Se for encontrado, cria-se uma cópia e apaga-se o original do set. De seguida, insere-se uma UC_class criada a partir de uccode na cópia, que é inserida em all_classes_ . Essencialmente, atualiza a turma em all_classes_ .
            if (classIt != all_classes_.end()) {
                LeicClass classCopy = LeicClass(*classIt);
                all_classes_.erase(classIt);
                classCopy.insertUcClass(UC_class(uccode));
                all_classes_.insert(classCopy);
            }
            ///Caso contrário, insere-se uma UC_class criada a partir de uccode em tempClass, que é inserida em all_classes_ .
            else {
                tempClass.insertUcClass(UC_class(uccode));
                all_classes_.insert(tempClass);
            }
        }

        ///Por fim, após todas as linhas serem interpretadas, o ficheiro de input é fechado.
        dataFile.close();

}

void Script::populateStudentSet(const string &filename) {
    ///O ficheiro de input é aberto.
    std::ifstream dataFile(filename);

    ///Se não for possível abrir o ficheiro, imprime-se "Error Warning: Unable to open the file " e os detalhes do erro. Sai-se da função.
    if (dataFile.fail()) {
        std::cerr << "Error Warning: Unable to open the file " << filename << std::endl;
        std::cerr << "Error details: " << std::strerror(errno) << std::endl;
        return;
    }

    ///Caso contrário, a primeira linha do ficheiro é interpretada como header.
    std::string header;
    getline(dataFile, header);
    std::string line;

    while (std::getline(dataFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::istringstream ss(line);

        ///A partir de cada uma das restantes linhas do ficheiro, obtém-se, por esta ordem, idNumber, studentName, UcCode e classCode.
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

        ///Procura-se em all_classes_ a LeicLass criada a partir de classCode
        auto classIt = all_classes_.find(LeicClass(classCode)); //

        ///Cria-se uma cópia dessa LeicClass, apaga-se o original de all_classes_, guarda-se a UC_class da cópia num objeto tempUCClass a partir da sua função getUCClass e apaga-se essa UC_class da cópia através da função eraseUcClass. Obtém-se também o horário schedule dessa UC a partir da sua função getUCClassSchedule .
        LeicClass tempLeicClass = *classIt; //
        all_classes_.erase(tempLeicClass); //
        UC_class tempUCClass = tempLeicClass.getUCClass(UcCode); //
        tempLeicClass.eraseUcClass(tempUCClass); //
        Schedule schedule = tempUCClass.getUCClassSchedule(); //

        ///É criado um estudante tempStudent a partir de idNumber e studentName.
        Student tempStudent = Student(idNumber, studentName); //

        ///Procura-se em all_UCs_ um objeto UC_class criado a partir de UcCode. Copia-se esse objeto para um objeto tempUC e apaga-se o original de all_UCs_.
        auto UCIt = all_UCs_.find(UC_class(UcCode)); //
        auto tempUC = *UCIt; //
        all_UCs_.erase(UCIt); //

        ///Procura-se tempStudent em all_students_. Se for encontrado, é apagado em all_students_, tempUCClass e tempUC.
        auto studentIt = all_students_.find(tempStudent); //
        if (studentIt != all_students_.end()) {
            tempStudent = *studentIt; //
            all_students_.erase(studentIt); //
            tempUCClass.eraseStudent(tempStudent); //
            tempUC.eraseStudent(tempStudent); //
        }

        ///Adiciona-se um horário a tempStudent a partir de classCode, UcCode e schedule, através da sua função addSchedule.
        tempStudent.addSchedule(classCode, UcCode, schedule); //


        ///Insere-se tempStudent em all_students_ e tempUCCLass, que é inserida em tempLeicClass, que por sua vez é inserida em all_classes_. tempStudent é também inserido em tempUC, que por sua vez é inserido em all_UCs_.
        all_students_.insert(tempStudent); //
        tempUCClass.insertStudent(tempStudent); //
        tempLeicClass.insertUcClass(tempUCClass); //
        all_classes_.insert(tempLeicClass); //
        tempUC.insertStudent(tempStudent); //
        all_UCs_.insert(tempUC); //

    }

    ///Por fim, após todas as linhas serem interpretadas, o ficheiro de input é fechado.
    dataFile.close();
}

void Script::PrintWeekStudentSchedule(int studentNumber) {
    ///A função procura em all_students_ o estudante a partir de studentNumber.
    auto studentIt = all_students_.find(Student(studentNumber,""));

    ///Caso não seja encontrado, "Student not found" é impresso e sai-se da função.
    if (studentIt == all_students_.end()) {
        cout << "Student not found" << std::endl;
        return;
    }

    ///Caso contrário, cria-se uma cópia do estudante encontrado e o seu horário semanal é impresso a partir da sua função PrintUcWeekSchedule.
    Student studentTemp = *studentIt;
    studentTemp.PrintUcWeekSchedule();
    std::cout << std::endl;
}

void Script::PrintWeekScheduleClass(const string& class_name){
    ///A função procura em all_classes_ a turma a partir de class_name.
    auto classIt = all_classes_.find(LeicClass(class_name));

    ///Caso não seja encontrada, "Class not found" é impresso e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, cria-se uma cópia da turma encontrada e o seu horário semanal é impresso a partir da sua função PrintUcWeekSchedule.
    LeicClass temp = LeicClass(*classIt);
    temp.PrintUcWeekSchedule();
}

void Script::consultStudentEnrolledUCs(int studentNumber) {

    auto studentIt = all_students_.find(Student(studentNumber,""));

    if (studentIt == all_students_.end()) {
        cout << "Student not found" << std::endl;
        return;
    }


    Student studentTemp = *studentIt;
    studentTemp.PrintEnrolledUCs();
}

void Script::consultStudentEnrolledClasses(int studentNumber) {
    auto studentIt = all_students_.find(Student(studentNumber,""));

    if (studentIt == all_students_.end()) {
        cout << "Student not found" << std::endl;
        return;
    }


    studentIt->PrintEnrolledClasses();
}

void Script::consultUCOccupancy(const string& uc_name) {
    auto UCClassIt = all_UCs_.find(UC_class(uc_name));

    if(UCClassIt == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }

    std::cout << UCClassIt->getNumberOfEnrolledStudents() << std::endl;
}

void Script::consultUCEnrolledStudents(const string& uc_name) {
    auto UCClassIt = all_UCs_.find(uc_name);

    if(UCClassIt == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }


    UCClassIt->PrintEnrolledStudents();

}

void Script::consultGreatestNumberOfStudentsUCs(int num) {


    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);
    auto setIt = sortedByOccupancy.end();
    setIt--;
    if (num <= int(sortedByOccupancy.size()) && num > 0) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt--) {
            std::cout << left << setw(8) << setIt->getUcName() << " | "  << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "There's only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }

}

void Script::consultSmallerNumberOfStudentsUCs(int num) {
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);
    auto setIt = sortedByOccupancy.begin();
    if (num <= int(sortedByOccupancy.size()) && num > 0) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt++) {
            std::cout << left << setw(8) << setIt->getUcName() << " | " << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "There's only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }

}

void Script::PrintWeekUCSchedule(const string& uc_name){
    auto itUC = all_UCs_.find(UC_class(uc_name));

    if(itUC == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }


    itUC->PrintUcWeekSchedule();
}


void Script::consultClassOccupancy(const string& class_code) {
    auto classIt = all_classes_.find(LeicClass(class_code));

    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }
    std::cout << "This class has " << classIt->getNumberOfEnrolledStudents() << " students" << std::endl;
}

void Script::consultUCCLassOccupancy(const string& class_code, const string& uc_code) {
    auto classIt = all_classes_.find(LeicClass(class_code));

    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    UC_class UC_temp = classIt->getUCClass(uc_code);

    if(UC_temp.getUcName() == "Nao existe") {
        cout << "Class found but UC not found" << endl;
        return;
    }



    std::cout << "The UC " << uc_code << " in class " << class_code << " has " << UC_temp.getNumberOfEnrolledStudents() << " students" << std::endl;

}

void Script::PrintUCClassSchedule(const string& class_code, const string& uc_code){
    auto classIt = all_classes_.find(LeicClass(class_code));

    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    UC_class UC_temp = classIt->getUCClass(uc_code);

    if(UC_temp.getUcName() == "Nao existe") {
        cout << "Class found but UC not found" << endl;
        return;
    }

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
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }
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
    if (num_classes <= int(sortedByOccupancy.size()) && num_classes > 0) {
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
    if (num_classes <= int(sortedByOccupancy.size()) && num_classes > 0) {
        std::cout << left << setw(7) << "Class" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num_classes; i++, classIt++) {
            std::cout << left << setw(7) << classIt->getClassName() << " | "  << classIt->getNumberOfEnrolledStudents() << std::endl;
        }
    }
    else {
        std::cout << "Theres only " << sortedByOccupancy.size() << " classes, please choose a smaller number" << std::endl;
    }
}

void Script::consultYearOccupancy(int year) {
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    set<Student> temp_student;
    set<Student> student_union;
    for (const auto & classIt : leic_class_years_[year-1]) {
        set<Student> temp = classIt.getEnrolledStudents();
        set_union(temp_student.begin(), temp_student.end(),
                  temp.begin(),temp.end(),
                  inserter(student_union,student_union.begin()));
        temp_student = student_union;
    }
    if (year == 1) {
        cout << "The  first year has " << student_union.size() << " students" << endl;
    }
    else if (year == 2) {
        cout << "The second year has " << student_union.size() << " students" << endl;
    }
    else if (year == 3) {
        cout << "The third year has " << student_union.size() << " students" << endl;
    }
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
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    set<Student> temp_student;
    // Francisco ve isto
    /// This set is a union of unique students in a year
    set<Student> student_union;
    for (const auto & classIt : leic_class_years_[year-1]) {
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

void Script::consultUCsByYear(int year){
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    cout << left << setw(8) << "UC code" << " | " << "Occupancy" << endl;
    for (const auto& uc_class : UC_years_[year-1]) {
        cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() << std::endl;
    }
}


void Script::consultUCsByYearByAscendingOccupancy(int year) {
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };

    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(UC_years_[year-1].begin(),UC_years_[year-1].end(), compareNumberOfStudents);
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (const auto& uc:sortedByOccupancy) {
            std::cout << left << setw(8) << uc.getUcName() << " | "  << uc.getNumberOfEnrolledStudents() << std::endl;
        }


}

void Script::consultUCsByYearByDescendingOccupancy(int year) {
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() > uc2.getNumberOfEnrolledStudents();
    };

    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(UC_years_[year-1].begin(),UC_years_[year-1].end(), compareNumberOfStudents);
    std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
    for (const auto& uc:sortedByOccupancy) {
        std::cout << left << setw(8) << uc.getUcName() << " | "  << uc.getNumberOfEnrolledStudents() << std::endl;
    }

}

void Script::consultUCsWithMinNStudents(int year, int number) {
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    bool flag = false;
    cout << left << setw(8) <<  "UC code" << " | " << "Occupancy" << endl;
    for (const auto& uc_class : UC_years_[year-1]) {
        if (uc_class.getNumberOfEnrolledStudents() >= number) {
            cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() <<  std::endl;
            flag = true;
        }
    }
    if (!flag) {
        cout << "There is no UC with a minimum of " << number << " students" <<  std::endl;
    }
}



void Script::consultUCsWithMaxNStudents(int year, int number) {
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    bool flag = false;

    cout << left << setw(8) <<  "UC code" << " | " << "Occupancy" << endl;
    for (const auto& uc_class : UC_years_[year-1]) {
        if (uc_class.getNumberOfEnrolledStudents() <= number) {
            cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() <<  std::endl;
            flag = true;
        }
    }
    if (!flag) {
        cout << "There is no UC with a maximum of " << number << " students" <<  std::endl;
    }
}

void Script::consultClassesInaYear(int year) {
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;
    for (const auto & classIt : leic_class_years_[year-1]) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }

}

void Script::consultClassesInaYearByAscendingOccupancy(int year) {
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    auto compareNumberOfStudents = [](const LeicClass class1, const LeicClass class2) {
        return class1.getNumberOfEnrolledStudents() < class2.getNumberOfEnrolledStudents();
    };

    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(leic_class_years_[year-1].begin(),leic_class_years_[year-1].end(), compareNumberOfStudents);

    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;

    for (const auto & classIt : sortedByOccupancy) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }

}


void Script::consultClassesInaYearByDescendingOccupancy(int year) {
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    auto compareNumberOfStudents = [](const LeicClass class1, const LeicClass class2) {
        return class1.getNumberOfEnrolledStudents() > class2.getNumberOfEnrolledStudents();
    };

    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(leic_class_years_[year-1].begin(),leic_class_years_[year-1].end(), compareNumberOfStudents);

    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;

    for (const auto & classIt : sortedByOccupancy) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }


}

void Script::consultClassesWithMinNStudents(int year, int number) {
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    bool flag = false;

    cout << left << setw(10) <<  "Class code" << " | " << "Occupancy" << endl;
    for (const auto& classeIt : leic_class_years_[year-1]) {
        if (classeIt.getNumberOfEnrolledStudents() >= number) {
            cout << left << setw(10) << classeIt.getClassName() << " | " << classeIt.getNumberOfEnrolledStudents() <<  std::endl;
            flag = true;
        }
    }
    if (!flag) {
        cout << "There is no class with a minimum of " << number << " students" <<  std::endl;
    }
}
void Script::consultClassesWithMaxNStudents(int year, int number) {    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    bool flag = false;

    cout << left << setw(10) <<  "Class code" << " | " << "Occupancy" << endl;
    for (const auto& classeIt : leic_class_years_[year-1]) {
        if (classeIt.getNumberOfEnrolledStudents() <= number) {
            cout << left << setw(10) << classeIt.getClassName() << " | " << classeIt.getNumberOfEnrolledStudents() <<  std::endl;
            flag = true;
        }
    }
    if (!flag) {
        cout << "There is no class with a maximum of " << number << " students" <<  std::endl;
    }
}

// AQUI

void Script::requestRemoveUC(int student_code, const string& UC_code){

    // studentIt
    auto studentIt = all_students_.find(Student(student_code,""));
    if(studentIt == all_students_.end()){
        cout << "Invalid student code. Please enter a valid student code." << endl;
        return;
    }
    Student temp_student = *studentIt;
    all_students_.erase(studentIt);

    // UCIt
    auto UCIt = all_UCs_.find(UC_class(UC_code));
    if(UCIt == all_UCs_.end()){
        cout << "Invalid UC code. Please enter a valid UC code." << endl;
        return;
    }
    UC_class temp_UC = *UCIt;
    all_UCs_.erase(UCIt);

    // LeicClassIt
    auto student_enrolled_UC_and_classes = studentIt->get_student_enrolled_UC_and_classes();
    auto classNameIt = std::find_if(student_enrolled_UC_and_classes.begin(), student_enrolled_UC_and_classes.end(),
                                    [UC_code](const std::pair<std::string, std::string>& classPair) {
                                        return classPair.second == UC_code;
                                    }
    );
    string class_name = classNameIt->first;
    if(classNameIt == student_enrolled_UC_and_classes.end()){
        cout << "UC not found in the student under consideration. Please enter a valid UC code." << endl;
        return;
    }
    auto LeicClassIt = all_classes_.find(LeicClass(class_name));
    UC_class temp_UC_Class = LeicClassIt->getUCClass(UC_code);

    LeicClass temp_LEIC_class = *LeicClassIt;
    all_classes_.erase(*LeicClassIt);

    temp_LEIC_class.eraseUcClass(temp_UC_Class);
    temp_UC_Class.eraseStudent(temp_student);

    auto s = temp_UC_Class.getUCClassSchedule();
    temp_student.removeSchedule(class_name, UC_code, s);
    temp_UC.eraseStudent(temp_student);
    temp_UC_Class.insertStudent(temp_student);
    temp_LEIC_class.insertUcClass(temp_UC_Class);

    // inserts
    all_UCs_.insert(temp_UC);
    all_students_.insert(temp_student);
    all_classes_.insert(temp_LEIC_class);

    cout << "UC removed" << std::endl;
}

//AQUI

void Script::requestAddClass(int student_id, const string& class_code) {
    auto studentIt = all_students_.find(Student(student_id,""));
    auto classIt = all_classes_.find(LeicClass(class_code));

}

void Script::requestRemoveClass(int student_id, const std::string& class_code) {

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
            //modified_student.removeSchedule(current_class_code, current_UC_code, schedule_to_remove);
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

    cout << "teste";

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


void Script::saveChangesToCsvFile(const string& filename) {


    std::string sourceDirectory = __FILE__;
    sourceDirectory = sourceDirectory.substr(0, sourceDirectory.find_last_of("/\\"));


    std::string output_directory = sourceDirectory + "/output/";
    std::string csv_filename = output_directory + filename +".csv";

    std::filesystem::create_directories(output_directory);

    // Open the CSV file in write mode and clear its contents if it already exists
    std::ofstream outputFile(csv_filename, std::ios::out | std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the CSV file for writing." << std::endl;
        return;
    }

    char  delim = ',';
    outputFile << "StudentCode" << delim << "StudentName" << delim << "UcCode" << delim << "ClassCode" << '\r' << '\n';
    for (const auto& studentIt : all_students_) {
        auto uc_classes = studentIt.get_student_enrolled_UC_and_classes();
        for(const auto& uc_classes_pairs : uc_classes) {
            outputFile << studentIt.getIdNumber() << delim << studentIt.getStudentName() << delim << uc_classes_pairs.second << delim << uc_classes_pairs.first << '\r' << '\n';
        }
    }

    // Close the CSV file
    outputFile.close();

    std::cout << "CSV file created or cleared successfully in the output directory." << std::endl;

}

void Script::captureState() {
    DataBaseState current_state;
    current_state.all_students = all_students_;
    current_state.all_classes = all_classes_;
    current_state.all_UCs = all_UCs_;
    system_changes_record_.push(current_state);
}

void Script::restoreState(DataBaseState& previous_state) {
    all_classes_ = previous_state.all_classes;
    all_UCs_ = previous_state.all_UCs;
    all_students_ = previous_state.all_students;
}


void Script::undoLastAction() {
    if(!system_changes_record_.empty()) {
        DataBaseState previous_state = system_changes_record_.top();
        system_changes_record_.pop();
        restoreState(previous_state);
        loadYear();
        cout << "Last database state was restored" << endl;
        cout << endl;
    }
    else {
        cout << "There's nothing to undo" << endl;
        cout << endl;
    }
}




void Script::loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3) {
    populateLeicSet(filename_2);
    populateUcSet(filename_1);
    populateStudentSet(filename_3);
}

void Script::loadYear() {
    ///Cada LeicClass em all_classes_ é inserida num set do vetor leic_class_years_ .
    ///O set em que é inserido é determinado pelo primeiro caracter do nome (obtido pela função getClassName ).
    ///Se o primeiro caracter for 1, vai para o set na posição 0 do vetor, que representa o primeiro ano.
    ///Se o primeiro caracter for 2, vai para o set na posição 1 do vetor, que representa o segundoo ano.
    ///Se o primeiro caracter for 3, vai para o set na posição 2 do vetor, que representa o terceiro ano.
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


    ///Cada UC_Class em all_UCs_ é inserida num set do vetor UC_years_ .
    ///O set em que é inserido é determinado pelo ano da UC, obtido pela função getUCYear .
    ///Se o ano for 1, vai para o set na posição 0 do vetor, que representa o primeiro ano.
    ///Se o ano for 2, vai para o set na posição 1 do vetor, que representa o segundoo ano.
    ///Se o ano for 3, vai para o set na posição 2 do vetor, que representa o terceiro ano.
    for(const auto & UCIt : all_UCs_) {
        if(UCIt.getUCYear() == 1) {
            UC_years_.at(0).insert(UCIt);
        }
        else if((UCIt.getUCYear() == 2)) {
            UC_years_.at(1).insert(UCIt);
        }
        else if((UCIt.getUCYear() == 3)) {
            UC_years_.at(2).insert(UCIt);
        }
    }
}

