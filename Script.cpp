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
            } else{
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
    ///A função procura em all_students_ o estudante a partir de studentNumber.
    auto studentIt = all_students_.find(Student(studentNumber,""));

    ///Caso não seja encontrado, "Student not found" é impresso e sai-se da função.
    if (studentIt == all_students_.end()) {
        cout << "Student not found" << std::endl;
        return;
    }


    ///Caso contrário, as UC's em que está inscrito são impressas a partir da sua função PrintEnrolledUCs.
    studentIt->PrintEnrolledUCs();

}

void Script::consultStudentEnrolledClasses(int studentNumber) {
    ///A função procura em all_students_ o estudante a partir de studentNumber.
    auto studentIt = all_students_.find(Student(studentNumber,""));

    ///Caso não seja encontrado, "Student not found" é impresso e sai-se da função.
    if (studentIt == all_students_.end()) {
        cout << "Student not found" << std::endl;
        return;
    }

    ///Caso contrário, imprime-se as turmas em que o estudante está inscrito através da sua função PrintEnrolledClasses.
    studentIt->PrintEnrolledClasses();
}

void Script::consultUCOccupancy(const string& uc_name) {
    ///A função procura em all_UCs_ a UC a partir de uc_name.
    auto UCClassIt = all_UCs_.find(UC_class(uc_name));

    ///Caso não seja encontrado, "UC not found" é impresso e sai-se da função.
    if(UCClassIt == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }

    ///Caso contrário, imprime-se #<uc_name> has <número de estudantes inscritos> students ". O número de estudantes inscritos na UC é obtido através da sua função getNumberOfEnrolledStudents.
    std::cout << uc_name << " has " << UCClassIt->getNumberOfEnrolledStudents()  << " students " << std::endl;
}

void Script::consultUCEnrolledStudents(const string& uc_name) {
    ///A função procura em all_UCs_ a UC a partir de uc_name.
    auto UCClassIt = all_UCs_.find(UC_class(uc_name));

    ///Caso não seja encontrado, "UC not found" é impresso e sai-se da função.
    if(UCClassIt == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }

    ///Caso contrário, imprime-se os estudantes inscritos na UC, através da sua função PrintEnrolledStudents.
    UCClassIt->PrintEnrolledStudents();
}

void Script::consultGreatestNumberOfStudentsUCs(int num) {

    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos UC_class, uc1 e uc2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em uc1 for menor que em uc2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos de all_UCs_ ordenados a partir de compareNumberOfStudents.
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);

    ///Cria-se também um iterador setIt que irá iterar por sortedByOccupancy, começando no fim.
    auto setIt = sortedByOccupancy.end();
    setIt--;

    ///Se o número *num* for válido, imprime-se "UC | Enrolled students" (header da tabela) e, por *num* iterações, imprime-se o nome da UC (obtido por getUcName) e o número de estudantes incritos (obtido por getNumberOfEnrolledStudents) da UC na posição de setIt. A cada iteração, o valor de setIt diminui, iterando por sortedByOccupancy no sentido negativo.
    if (num <= int(sortedByOccupancy.size()) && num > 0) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt--) {
            std::cout << left << setw(8) << setIt->getUcName() << " | "  << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    } else{
        ///Se *num* não for válido, imprime-se "There's only <número de estudantes na UC (tamanho de sortedByOccupancy)> UC's, please choose a smaller number" .
        std::cout << "There's only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }
}

void Script::consultSmallerNumberOfStudentsUCs(int num) {

    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos UC_class, uc1 e uc2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em uc1 for menor que em uc2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos de all_UCs_ ordenados a partir de compareNumberOfStudents.
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(all_UCs_.begin(),all_UCs_.end(), compareNumberOfStudents);

    ///Cria-se um iterador setIt que irá iterar por sortedByOccupancy, começando no início.
    auto setIt = sortedByOccupancy.begin();

    ///Se o número *num* for válido, imprime-se "UC | Enrolled students" (header da tabela) e, por *num* iterações, imprime-se o nome da UC (obtido por getUcName) e o número de estudantes incritos (obtido por getNumberOfEnrolledStudents) da UC na posição de setIt. A cada iteração, o valor de setIt aumenta, iterando por sortedByOccupancy no sentido positivo.
    if (num <= int(sortedByOccupancy.size()) && num > 0) {
        std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num; i++, setIt++) {
            std::cout << left << setw(8) << setIt->getUcName() << " | " << setIt->getNumberOfEnrolledStudents() << std::endl;
        }
    } else{
        ///Se *num* não for válido, imprime-se "There's only <número de estudantes na UC (tamanho de sortedByOccupancy)> UC's, please choose a smaller number" .
        std::cout << "There's only " << sortedByOccupancy.size() << " UC's, please choose a smaller number" << std::endl;
    }
}

void Script::PrintWeekUCSchedule(const string& uc_name){
    ///Procura-se em all_UCs_ a UC cujo horário se pretende imprimir.
    auto itUC = all_UCs_.find(UC_class(uc_name));

    ///Caso não seja encontrada, imprime-se "UC not found" e sai-se da função.
    if(itUC == all_UCs_.end()) {
        cout << "UC not found" << std::endl;
        return;
    }

    ///Caso contrário, o horário semanal é impresso a partir da função PrintUcWeekSchedule da UC.
    itUC->PrintUcWeekSchedule();
}

void Script::consultClassOccupancy(const string& class_code) {
    ///Procura-se em all_classes_ a turma cujo número de estudantes se pretende consultar.
    auto classIt = all_classes_.find(LeicClass(class_code));

    ///Se a turma não for encontrada, imprime-se "Class not found" e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, imprime-se "This class has <número de estudantes inscritos na turma> students". O número de estudantes é obtido a partir da função getNumberOfEnrolledStudents da turma.
    std::cout << "This class has " << classIt->getNumberOfEnrolledStudents() << " students" << std::endl;
}

void Script::consultUCCLassOccupancy(const string& class_code, const string& uc_code) {
    ///Procura-se em all_classes_ a turma cujo número de estudantes se pretende consultar.
    auto classIt = all_classes_.find(LeicClass(class_code));

    ///Se a turma não for encontrada, imprime-se "Class not found" e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, obtém-se a através da função getUCClass da turma a turma da UC pretendida, através de uc_code. Esta é guardada no objeto UC_temp do tipo UC_class.
    UC_class UC_temp = classIt->getUCClass(uc_code);

    ///Caso não exista turma desta UC (o seu nome é "Nao existe"), imprime-se "Class found but UC not found" e sai-se da função.
    if(UC_temp.getUcName() == "Nao existe") {
        cout << "Class found but UC not found" << endl;
        return;
    }

    ///Caso contrário, imprime-se "The UC <uc_code> in class <class_code> has <número de estudantes inscritos> students". O número de estudantes inscritos obtém-se através da função getNumberOfEnrolledStudents de UC_temp.
    std::cout << "The UC " << uc_code << " in class " << class_code << " has " << UC_temp.getNumberOfEnrolledStudents() << " students" << std::endl;
}

void Script::PrintUCClassSchedule(const string& class_code, const string& uc_code){
    ///Procura-se em all_classes_ a turma pretendida, a partir de class_code.
    auto classIt = all_classes_.find(LeicClass(class_code));

    ///Se esta não for encontrada, "Class not found" é impresso e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, obtém-se a através da função getUCClass da turma a turma da UC pretendida, através de uc_code. Esta é guardada no objeto UC_temp do tipo UC_class.
    UC_class UC_temp = classIt->getUCClass(uc_code);

    ///Caso não exista turma desta UC (o seu nome é "Nao existe"), imprime-se "Class found but UC not found" e sai-se da função.
    if(UC_temp.getUcName() == "Nao existe") {
        cout << "Class found but UC not found" << endl;
        return;
    }

    ///Caso contrário, o horário da turma da UC é impresso a partir da sua função PrintUcWeekSchedule.
    UC_temp.PrintUcWeekSchedule();
}

int Script::consultNumberOfStudentsRegisteredUCs(int numberOfUCs) {
    ///A função cria um contador, inicializado em 0.
    int counter = 0;

    ///Um iterador itera por all_students_. Em cada iteração, se o estudante na posição do iterador estiver inscrito em *numberOfUCs*, o contador é incrmentado em 1. O número de UC's do aluno é obtido através da sua função getNumberOfUCs.
    auto studentIt = all_students_.begin();
    for (; studentIt != all_students_.end(); studentIt++) {
        if (studentIt->getNumberOfUCs() == numberOfUCs) counter++;
    }
    ///Por fim, a função retorna o valor final do contador, isto é, o número de estudantes inscritos em *numberOfUCs* UC's.
    return counter;
}

void Script::consultClassEnrolledStudents(const string& class_code) {
    ///A função procura em all_classes_ a turma pretendida a partir de class_code.
    auto classIt = all_classes_.find(LeicClass(class_code));

    ///Se esta não for encontrada, "Class not found" é impresso e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, guarda-se no set class_students os alunos inscritos na turma, obtidos através da sua função getEnrolledStudents.
    set<Student> class_students = classIt->getEnrolledStudents();

    ///A função imprime "Student number | Student name", o header da tabela que se irá formar.
    cout << left << setw(14) << "Student number" << " | " << "Student name" << endl;

    ///Por fim, por cada estudante em class_students, imprime-se "<número de estudante> | <nome>", obtidos a partir de getIdNumber e getStudentName, respetivamente.
    for (Student student : class_students) {
        cout << left << setw(14) << student.getIdNumber() << " | " << student.getStudentName() << endl;
    }
}

void Script::consultUCCLassEnrolledStudents(const string& class_code, const string& uc_code) {
    ///A função procura em all_classes_ a turma pretendida a partir de class_code.
    auto classIt = all_classes_.find(LeicClass(class_code));

    ///Se esta não for encontrada, "Class not found" é impresso e sai-se da função.
    if(classIt == all_classes_.end()) {
        cout << "Class not found" << endl;
        return;
    }

    ///Caso contrário, obtém-se a através da função getUCClass da turma a turma da UC pretendida, através de uc_code. Esta é guardada no objeto UC_temp do tipo UC_class.
    UC_class UC_temp = classIt->getUCClass(uc_code);

    ///Caso não exista turma desta UC (o seu nome é "Nao existe"), imprime-se "Class found but UC not found" e sai-se da função.
    if(UC_temp.getUcName() == "Nao existe") {
        cout << "Class found but UC not found" << endl;
        return;
    }

    ///Caso contrário, os estudantes são impressos através da função PrintEnrolledStudents de UC_temp.
    /// \note Os estudantes serão impressos no formato definido por PrintEnrolledStudents: "Student number: <id_number_> Student name: <st_name_>"
    UC_temp.PrintEnrolledStudents();
}

void Script::consultGreatestClasses(int num_classes){
    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos LeicClass, class_a e class_b, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em class_a for menor que em class_b e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const LeicClass& class_a, const LeicClass& class_b) {
        return class_a.getNumberOfEnrolledStudents() < class_b.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos de all_classes_ ordenados a partir de compareNumberOfStudents.
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(all_classes_.begin(),all_classes_.end(), compareNumberOfStudents);

    ///Cria-se também um iterador classIt que irá iterar por sortedByOccupancy, começando no fim.
    auto classIt = sortedByOccupancy.end();
    classIt--;

    ///Se o número *num_classes* for válido, imprime-se "Class | Enrolled students" (header da tabela) e, por *num_classes* iterações, imprime-se o nome da turma (obtido por getClassName) e o número de estudantes incritos (obtido por getNumberOfEnrolledStudents) da turma na posição de classIt. A cada iteração, o valor de classIt diminui, iterando por sortedByOccupancy no sentido negativo.
    if (num_classes <= int(sortedByOccupancy.size()) && num_classes > 0) {
        std::cout << left << setw(7) << "Class" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num_classes; i++, classIt--) {
            std::cout << left << setw(7) << classIt->getClassName() << " | "  << classIt->getNumberOfEnrolledStudents() << std::endl;
        }
    } else{
        ///Se *num_classes* não for válido, imprime-se "There's only <número de estudantes na turma (tamanho de sortedByOccupancy)> classes, please choose a smaller number" .
        std::cout << "Theres only " << sortedByOccupancy.size() << " classes, please choose a smaller number" << std::endl;
    }
}

void Script::consultSmallestClasses(int num_classes){
    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos LeicClass, class_a e class_b, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em class_a for menor que em class_b e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const LeicClass& class_a, const LeicClass& class_b) {
        return class_a.getNumberOfEnrolledStudents() < class_b.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos de all_classes_ ordenados a partir de compareNumberOfStudents.
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(all_classes_.begin(),all_classes_.end(), compareNumberOfStudents);

    ///Cria-se também um iterador classIt que irá iterar por sortedByOccupancy, começando no início.
    auto classIt = sortedByOccupancy.begin();

    ///Se o número *num_classes* for válido, imprime-se "Class | Enrolled students" (header da tabela) e, por *num_classes* iterações, imprime-se o nome da turma (obtido por getClassName) e o número de estudantes incritos (obtido por getNumberOfEnrolledStudents) da turma na posição de classIt. A cada iteração, o valor de classIt aumenta, iterando por sortedByOccupancy no sentido positivo.
    if (num_classes <= int(sortedByOccupancy.size()) && num_classes > 0) {
        std::cout << left << setw(7) << "Class" << " | " << "Enrolled students" << std::endl;
        for (int i = 0; i < num_classes; i++, classIt++) {
            std::cout << left << setw(7) << classIt->getClassName() << " | "  << classIt->getNumberOfEnrolledStudents() << std::endl;
        }
    } else{
        ///Se *num_classes* não for válido, imprime-se "There's only <número de estudantes na turma (tamanho de sortedByOccupancy)> classes, please choose a smaller number" .
        std::cout << "Theres only " << sortedByOccupancy.size() << " classes, please choose a smaller number" << std::endl;
    }
}

void Script::consultYearOccupancy(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    set<Student> temp_student;
    set<Student> student_union;
    ///Caso contrário, para cada turma do conjunto de turmas do ano year (set na posição year-1 de leic_class_years_), obtém-se os alunos inscritos pela função getEnrolledStudents. Outro set acumula os estudantes ao longo das iterações.
    for (const auto & classIt : leic_class_years_[year-1]) {
        set<Student> temp = classIt.getEnrolledStudents();
        set_union(temp_student.begin(), temp_student.end(),
                  temp.begin(),temp.end(),
                  inserter(student_union,student_union.begin()));
        temp_student = student_union;
    }

    ///Por fim, imprime-se "The  first/second/third year has <número de estudantes> students", sendo que o número de estudantes é obtido a partir do tamanho do set referido anteriormente.
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

void Script::consultEnrolledStudentsYear(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    set<Student> temp_student;
    set<Student> student_union;
    ///Caso contrário, para cada turma do conjunto de turmas do ano year (set na posição year-1 de leic_class_years_), obtém-se os alunos inscritos pela função getEnrolledStudents. Outro set acumula os estudantes ao longo das iterações.
    for (const auto & classIt : leic_class_years_[year-1]) {
        set<Student> temp = classIt.getEnrolledStudents();
        set_union(temp_student.begin(), temp_student.end(),
                  temp.begin(),temp.end(),
                  inserter(student_union,student_union.begin()));
        temp_student = student_union;
    }

    ///De seguida, a função imprime o header da tabela que se irá criar, "Number | Student Name"
    cout << left << setw(9) << "Number" << " | " << "Student Name" << std::endl;

    ///Por fim, para cada estudante no set, imprime-se o número de estudante (obtido por getIdNumber) e o nome (obtido por getStudentName).
    for (const auto & student : student_union) {
        cout << left << setw(9) << student.getIdNumber() << " | " << student.getStudentName() << endl;
    }
}

void Script::consultUCsByYear(int year){
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, a função imprime o header da tabela que se irá criar, "UC code | Occupancy".
    cout << left << setw(8) << "UC code" << " | " << "Occupancy" << endl;
    ///Por fim, para cada UC do conjunto de UC's do ano pretendido (set na posição year-1 de UC_years_), imprime-se o nome da UC (obtido por getUcName) e o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents).
    for (const auto& uc_class : UC_years_[year-1]) {
        cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() << std::endl;
    }
}

void Script::consultUCsByYearByAscendingOccupancy(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos UC_class, uc1 e uc2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em uc1 for menor que em uc2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() < uc2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos do set correspondente às UC's desse ano em UC_years_, ordenados a partir de compareNumberOfStudents.
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(UC_years_[year-1].begin(),UC_years_[year-1].end(), compareNumberOfStudents);
    ///A função imprime o header da tabela que se irá criar, "UC | Enrolled Students".
    std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;

    ///Por fim, para cada UC em sortedByOccupancy, imprime-se o nome da UC (obtido por getUCName) e o número de estudantes inscritos nesta (obtido por getNumberOfEnrolledStudents). Como o set está ordenado por ordem crescente de número de estudantes, é essa a orden de impressão.
    for (const auto& uc:sortedByOccupancy) {
        std::cout << left << setw(8) << uc.getUcName() << " | "  << uc.getNumberOfEnrolledStudents() << std::endl;
    }
}

void Script::consultUCsByYearByDescendingOccupancy(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos UC_class, uc1 e uc2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em uc1 for maior que em uc2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const UC_class& uc1, const UC_class& uc2) {
        return uc1.getNumberOfEnrolledStudents() > uc2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos do set correspondente às UC's desse ano em UC_years_, ordenados a partir de compareNumberOfStudents.
    set<UC_class, decltype(compareNumberOfStudents)> sortedByOccupancy(UC_years_[year-1].begin(),UC_years_[year-1].end(), compareNumberOfStudents);
    ///A função imprime o header da tabela que se irá criar, "UC | Enrolled Students".
    std::cout << left << setw(8) << "UC" << " | " << "Enrolled students" << std::endl;

    ///Por fim, para cada UC em sortedByOccupancy, imprime-se o nome da UC (obtido por getUCName) e o número de estudantes inscritos nesta (obtido por getNumberOfEnrolledStudents). Como o set está ordenado por ordem decrescente de número de estudantes, é essa a orden de impressão.
    for (const auto& uc:sortedByOccupancy) {
        std::cout << left << setw(8) << uc.getUcName() << " | "  << uc.getNumberOfEnrolledStudents() << std::endl;
    }
}

void Script::consultUCsWithMinNStudents(int year, int number) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, cria-se um objeto flag do tipo bool, com valor *false*.
    bool flag = false;

    ///A função imprime o header da tabela que se irá criar, "UC code | Occupancy".
    cout << left << setw(8) <<  "UC code" << " | " << "Occupancy" << endl;

    ///Para cada UC do conjunto de UC's do ano pretendido (set na posição year-1 de UC_years_), se o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents) for maior ou igual ao mínimo desejado, imprime-se o nome (obtido por getUcName) e o número de estudantes (obtido por getNumberOfEnrolledStudents).
    for (const auto& uc_class : UC_years_[year-1]) {
        if (uc_class.getNumberOfEnrolledStudents() >= number) {
            cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() <<  std::endl;
            ///Além disso, nessa condição, o valor de flag é definido como *true*.
            flag = true;
        }
    }

    ///Se, após se iterar pelo ano inteiro, flag tiver valor *false*, conclui-se que este não foi alterado para *true*, ou seja, não foram encontradas UC's com um número de estudantes superior ou igual ao mínimo desejado.
    ///Assim, a função imprime "There is no UC with a minimum of <mínimo> students".
    if (!flag) {
        cout << "There is no UC with a minimum of " << number << " students" <<  std::endl;
    }
}

void Script::consultUCsWithMaxNStudents(int year, int number) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(UC_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, cria-se um objeto flag do tipo bool, com valor *false*.
    bool flag = false;

    ///A função imprime o header da tabela que se irá criar, "UC code | Occupancy".
    cout << left << setw(8) <<  "UC code" << " | " << "Occupancy" << endl;

    ///Para cada UC do conjunto de UC's do ano pretendido (set na posição year-1 de UC_years_), se o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents) for menor ou igual ao o máximo desejado, imprime-se o nome (obtido por getUcName) e o número de estudantes (obtido por getNumberOfEnrolledStudents).
    for (const auto& uc_class : UC_years_[year-1]) {
        if (uc_class.getNumberOfEnrolledStudents() <= number) {
            cout << left << setw(8) << uc_class.getUcName() << " | " << uc_class.getNumberOfEnrolledStudents() <<  std::endl;
            ///Além disso, nessa condição, o valor de flag é definido como *true*.
            flag = true;
        }
    }

    ///Se, após se iterar pelo ano inteiro, flag tiver valor *false*, conclui-se que este não foi alterado para *true*, ou seja, não foram encontradas UC's com um número de estudantes inferior ou igual ao máximo desejado.
    ///Assim, a função imprime "There is no UC with a maximum of <máximo> students"
    if (!flag) {
        cout << "There is no UC with a maximum of " << number << " students" <<  std::endl;
    }
}

void Script::consultClassesInaYear(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, a função imprime o header da tabela que se irá criar, "Class code | Occupancy".
    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;

    ///Por fim, para cada turma do conjunto de turmas do ano pretendido (set na posição year-1 de leic_class_years_), imprime-se o nome (obtido por getClassName) e o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents).
    for (const auto & classIt : leic_class_years_[year-1]) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }
}

void Script::consultClassesInaYearByAscendingOccupancy(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }
    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos LeicClass, class1 e class2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em class1 for menor que em class2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const LeicClass class1, const LeicClass class2) {
        return class1.getNumberOfEnrolledStudents() < class2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos do conjunto de turmas do ano pretendido (set na posição year-1 de leic_class_years_) ordenados a partir de compareNumberOfStudents.
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(leic_class_years_[year-1].begin(),leic_class_years_[year-1].end(), compareNumberOfStudents);

    ///A função imprime o header da tabela que se irá criar, "Class code | Occupancy".
    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;

    ///Por fim, para cada turma em sortedByOccupancy, imprime-se o nome da turma (obtido por getClassName) e o número de estudantes inscritos nesta (obtido por getNumberOfEnrolledStudents). Como o set está ordenado por ordem crescente de número de estudantes, é essa a orden de impressão.
    for (const auto & classIt : sortedByOccupancy) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }
}

void Script::consultClassesInaYearByDescendingOccupancy(int year) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///A função cria uma função lambda compareNumberOfStudents, cujos parâmetros são dois objetos LeicClass, class1 e class2, respetivamente.
    ///Esta retorna *true* se o número de estudantes incritos, obtidos a partir da função getNumberOfEnrolledStudents, em class1 for maior que em class2 e retorna *false* caso contrário.
    auto compareNumberOfStudents = [](const LeicClass class1, const LeicClass class2) {
        return class1.getNumberOfEnrolledStudents() > class2.getNumberOfEnrolledStudents();
    };

    ///De seguida, cria-se um novo set sortedByOccupancy, com os elementos do conjunto de turmas do ano pretendido (set na posição year-1 de leic_class_years_) ordenados a partir de compareNumberOfStudents.
    set<LeicClass, decltype(compareNumberOfStudents)> sortedByOccupancy(leic_class_years_[year-1].begin(),leic_class_years_[year-1].end(), compareNumberOfStudents);

    ///A função imprime o header da tabela que se irá criar, "Class code | Occupancy".
    cout << left << setw(10) <<  "Class Code" << " | " << "Occupancy" << endl;

    ///Por fim, para cada turma em sortedByOccupancy, imprime-se o nome da turma (obtido por getClassName) e o número de estudantes inscritos nesta (obtido por getNumberOfEnrolledStudents). Como o set está ordenado por ordem decrescente de número de estudantes, é essa a orden de impressão.
    for (const auto & classIt : sortedByOccupancy) {
        cout << left << setw(10) << classIt.getClassName() << " | " << classIt.getNumberOfEnrolledStudents() <<  std::endl;
    }
}

void Script::consultClassesWithMinNStudents(int year, int number) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, cria-se um objeto flag do tipo bool, com valor *false*.
    bool flag = false;

    ///A função imprime o header da tabela que se irá criar, "Class code | Occupancy".
    cout << left << setw(10) <<  "Class code" << " | " << "Occupancy" << endl;

    ///Para cada turma do conjunto de turmas do ano pretendido (set na posição year-1 de leic_class_years_), se o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents) for maior ou igual ao mínimo desejado, imprime-se o nome (obtido por getClassName) e o número de estudantes (obtido por getNumberOfEnrolledStudents).
    for (const auto& classeIt : leic_class_years_[year-1]) {
        if (classeIt.getNumberOfEnrolledStudents() >= number) {
            cout << left << setw(10) << classeIt.getClassName() << " | " << classeIt.getNumberOfEnrolledStudents() <<  std::endl;
            ///Além disso, nessa condição, o valor de flag é definido como *true*.
            flag = true;
        }
    }
    ///Se, após se iterar pelo ano inteiro, flag tiver valor *false*, conclui-se que este não foi alterado para *true*, ou seja, não foram encontradas turmas com um número de estudantes superior ou igual ao mínimo desejado.
    ///Assim, a função imprime "There is no class with a minimum of <mínimo> students"
    if (!flag) {
        cout << "There is no class with a minimum of " << number << " students" <<  std::endl;
    }
}
void Script::consultClassesWithMaxNStudents(int year, int number) {
    ///Se year for um ano inválido, a função imprime "That's not a valid year " e termina.
    if(year > int(leic_class_years_.size()) || year < 1) {
        cout << "That's not a valid year " << endl;
        return;
    }

    ///Caso contrário, cria-se um objeto flag do tipo bool, com valor *false*.
    bool flag = false;

    ///A função imprime o header da tabela que se irá criar, "Class code | Occupancy".
    cout << left << setw(10) <<  "Class code" << " | " << "Occupancy" << endl;

    ///Para cada turma do conjunto de turmas do ano pretendido (set na posição year-1 de leic_class_years_), se o número de estudantes inscritos (obtido por getNumberOfEnrolledStudents) for inferior ou igual ao máximo desejado, imprime-se o nome (obtido por getClassName) e o número de estudantes (obtido por getNumberOfEnrolledStudents).
    for (const auto& classeIt : leic_class_years_[year-1]) {
        if (classeIt.getNumberOfEnrolledStudents() <= number) {
            cout << left << setw(10) << classeIt.getClassName() << " | " << classeIt.getNumberOfEnrolledStudents() <<  std::endl;
            ///Além disso, nessa condição, o valor de flag é definido como *true*.
            flag = true;
        }
    }
    ///Se, após se iterar pelo ano inteiro, flag tiver valor *false*, conclui-se que este não foi alterado para *true*, ou seja, não foram encontradas turmas com um número de estudantes inferior ou igual ao máximo desejado.
    ///Assim, a função imprime "There is no class with a maximum of <máximo> students"
    if (!flag) {
        cout << "There is no class with a maximum of " << number << " students" <<  std::endl;
    }
}

void Script::requestAddUCInClass(int student_code, const string& class_code, const string& UC_code) {
    ///A função procura em all_students_ o estudante pretendido a partir de student_code.
    auto studentIt = all_students_.find(Student(student_code, ""));

    ///Se este não for encontrado, o pedido é rejeitado e a função termina.
    if (studentIt == all_students_.end()) {
        cout << "Request denied." << endl;
        cout << "Invalid student code. Please enter a valid student code." << endl;
        return;
    }

    Student temp_student = *studentIt;
    ///Obtém-se set dos pares <UC, turma> do estudante a partir da sua função get_student_enrolled_UC_and_classes.
    auto student_enrolled_UC_and_classes = temp_student.get_student_enrolled_UC_and_classes();
    ///Se em algum par do set o segundo elemento for igual a UC_code, isto é, se o estudante já estiver inscrito na UC, o pedido é rejeitado e a função termina.
    for(const auto& class_code_UC_code_pair : student_enrolled_UC_and_classes){
        if(class_code_UC_code_pair.second == UC_code){
            cout << "Request denied." << endl;
            cout << "The student is already enrolled in this UC." << endl;
            return;
        }
    }

    ///Caso contrário, se o número de UC's do estudante, obtido por getNumberOfUCs, for maior ou igual a 7 (número máximo de UC's), o pedido é rejeitado e a função termina.
    if (studentIt->getNumberOfUCs() >= 7) {
        cout << "Request denied." << endl;
        cout << "The student is already enrolled in the maximum of 7 UC's." << endl;
        return;
    }

    ///Por outro lado, se a função continuar, procura-se em all_classes_ a turma pretendida a partir de class_code.
    auto classIt = all_classes_.find(LeicClass(class_code));
    LeicClass temp_LeicClass = *classIt;
    ///Se esta não for encontrada, o pedido é rejeitado e a função termina.
    if (classIt == all_classes_.end()) {
        cout << "Request denied." << endl;
        cout << "Invalid class code. Please enter a valid class code." << endl;
        return;
    }

    // Verificação de UC_class
    ///Caso contrário, guarda-se no objeto do tipo UC_class temp_UC_Class a turma da UC, obtida por UC_code, da turma pretendida.
    UC_class temp_UC_Class = temp_LeicClass.getUCClass(UC_code);
    ///Se esta turma da UC não existir, o pedido é rejeitado e a função termina.
    if (temp_UC_Class.getUcName() == "Nao existe") {
        cout << "Request denied." << endl;
        cout << "UC not found in the class code under consideration. Please enter a valid UC code." << endl;
        return;
    }

    ///Se o número de estudantes for o máximo da turma, o pedido é rejeitado e a função termina.
    if(temp_UC_Class.getNumberOfEnrolledStudents() >= 27){
        cout << "Request denied." << endl;
        cout << "The current UC class has already reached it's maximum capacity of 27 students." << endl;
        return;
    }

    ///Se a função continuar, verifica-se se o horário de temp_UC_class, obtido por getUCClassSchedule, é compatíve
    Schedule schedule_to_add = temp_UC_Class.getUCClassSchedule();
    // Verifica se o horário da UC_class é compatível com o horário do estudante
    ///Se for incompatível, o pedido é rejeitado e a função termina.
    if (temp_student.checkScheduleConflict(schedule_to_add)) {
        cout << "Request denied." << endl;
        cout << "The student's schedule " << student_code << " is not compatible with class schedule " << class_code
             << " of UC " << UC_code << "." << endl;
        return;
    }

    /// Guarda-se o vetor de pares com nome das turmas e o número de estudantes da UC definida por UC_code nessa turma, a partir da função getNumberOfEnrolledStudentsPerClassInUC.
    auto number_of_enrolled_students_per_class_in_UC = this->getNumberOfEnrolledStudentsPerClassInUC(UC_code);

    ///Guarda-se também os números de estudantes da turma com menos estudantes e da turma com mais estudantes (primeiro e último membro do vetor).
    int min_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.at(0).second;
    int max_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.back().second;

    auto it = std::find_if(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
                           [class_code](const pair<string, int>& p) {
                               return p.first == class_code;
                           });

    ///Se a diferença entre os números de estudantes for superior a 4, considera-se que não existe equilíbrio.
    if(abs(max_number_of_enrolled_students_per_class_in_UC - min_number_of_enrolled_students_per_class_in_UC) > 4){
        // Balance does not exist
        ///Neste caso, se a inscrição do estudante não ajudar a atingir equilíbrio, o pedido é rejeitado, o programa indica as turmas com um número de estudantes menor que o máximo e a função termina.
        if(it->second == max_number_of_enrolled_students_per_class_in_UC){
            cout << "Request denied." << endl;
            cout << "The balance of class occupation in this UC has not been reached yet. To achieve balance, you must enroll in the classes with fewer students than the current maximum number(" << max_number_of_enrolled_students_per_class_in_UC << "), which are:" << endl;
            for(const auto& elem : number_of_enrolled_students_per_class_in_UC){
                if(elem.second < max_number_of_enrolled_students_per_class_in_UC){
                    cout << elem.first << " (" << elem.second << ") students enrolled" << endl;
                }
            }
            return;
        } else{
            ///Se ajudar, o pedido é aprovado.
            cout << "Request approved." << endl;
            cout << "The balance of class occupation in this UC has not been reached yet. Your request will help achieve this balance." << endl;
        }
    } else{
        ///Por outro lado, se o equilíbrio existir, verifica-se se o equilíbrio será perturbado pela inscrição.
        // Balance exists
        *it++;
        std::sort(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
                  [](const pair<string, int>& a, const pair<string, int>& b) {
                      return a.second < b.second;
                  });

        int min_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.at(0).second;
        int max_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.back().second;

        ///Se perturbar, o pedido é rejeitado e a função termina.
        if(abs(max_number_of_enrolled_students_per_class_in_UC - min_number_of_enrolled_students_per_class_in_UC) > 4){
            cout << "Request denied. This request disrupts class occupancy. The difference in the number of students enrolled in any class within the same UC must be less than or equal to 4." << endl;
            return;
        }
        ///Se não perturbar, o pedido é aceite.
        cout << "Request approved." << endl;
        cout << "The balance between class occupation was not disturbed." << endl;
    }

    ///Se o pedido foi aprovado, os sets all_students_, all_classes_ e allUCs_ apagam as informações do estudante, da turma e da UC, respetivamente.
    // Request aprovado
    auto UCIt = all_UCs_.find(UC_class(UC_code));
    auto temp_UC = *UCIt;
    // erases
    all_students_.erase(temp_student);
    all_classes_.erase(temp_LeicClass);
    all_UCs_.erase(temp_UC);
    // Alterações
    ///Adiciona-se ao aluno o horário a partir de class_code, UC_code e schedule_to_add, através da função addSchedule
    temp_student.addSchedule(class_code, UC_code, schedule_to_add);
    ///Insere-se o estudante na turma da UC através da função insertStudent.
    temp_UC_Class.insertStudent(temp_student);
    ///Insere-se a turma da UC na turma LeicClass através da função insertUcClass.
    temp_LeicClass.insertUcClass(temp_UC_Class);
    ///Insere-se na UC o estudante, através de insertStudent.
    temp_UC.insertStudent(temp_student);
    // inserts
    ///O estudante, a turma e a UC, agora atualizados, são colocados de novo nos sets all_students, all_classes e all_UCs_, respetivamente.
    all_students_.insert(temp_student);
    all_classes_.insert(temp_LeicClass);
    all_UCs_.insert(temp_UC);
    // Retorno
    ///Por fim, a função imprime "(<UC>, <turma>) added."
    cout << "(" << UC_code << ", "  << class_code << ") added." << std::endl;
}

void Script::requestRemoveSingleUC(int student_code, const string& UC_code){
    // Student (erase + temp)
    ///O estudante é procurado em all_students_.
    auto studentIt = all_students_.find(Student(student_code,""));
    if(studentIt == all_students_.end()){
        ///Se não for encontrado, é impressa a mensagem "Invalid student code. Please enter a valid student code." e a função termina.
        cout << "Invalid student code. Please enter a valid student code." << endl;
        return;
    }
    ///Se for, cria-se uma cópia do estudante e elimina-se o original do set.
    Student temp_student = *studentIt;
    all_students_.erase(studentIt);

    // UC (erase + temp)
    ///A UC é procurada em all_UCs_.
    auto UCIt = all_UCs_.find(UC_class(UC_code));
    if(UCIt == all_UCs_.end()){
        ///Se não for encontrada, é impressa a mensagem "Invalid UC code. Please enter a valid UC code." e a função termina.
        cout << "Invalid UC code. Please enter a valid UC code." << endl;
        return;
    }
    ///Se for, cria-se uma cópia da UC e elimina-se a original do set.
    UC_class temp_UC = *UCIt;
    all_UCs_.erase(UCIt);

    // LeicClass e UC_class (erase + temp)
    auto student_enrolled_UC_and_classes = temp_student.get_student_enrolled_UC_and_classes();
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

    // Alterações dos objetos temporários
    temp_UC.eraseStudent(temp_student);
    temp_UC_Class.eraseStudent(temp_student);
    temp_LEIC_class.eraseUcClass(temp_UC_Class);

    temp_student.removeSchedule(class_name, UC_code, temp_UC_Class.getUCClassSchedule());

    temp_UC_Class.insertStudent(temp_student);
    temp_LEIC_class.insertUcClass(temp_UC_Class);

    // Inserts
    all_UCs_.insert(temp_UC);
    all_students_.insert(temp_student);
    all_classes_.insert(temp_LEIC_class);

    cout << "UC removed." << std::endl;
}

void Script::requestRemoveClassForAllUCs(int student_code, const std::string& class_code) {
    // Student (erase + temp)
    auto studentIt = all_students_.find(Student(student_code,""));
    if(studentIt == all_students_.end()){
        cout << "Invalid student code. Please enter a valid student code." << endl;
        return;
    }
    Student original_student = *studentIt;
    Student temp_student = original_student;
    all_students_.erase(studentIt);
    // LeicClass (erase + temp)
    auto classIt = all_classes_.find(LeicClass(class_code));
    if(classIt == all_classes_.end()){
        cout << "Invalid class code. Please enter a valid class code." << endl;
        return;
    }
    auto student_enrolled_UC_and_classes = original_student.get_student_enrolled_UC_and_classes();
    LeicClass temp_LeicClass = *classIt;
    all_classes_.erase(classIt);

    // Atualizar horário do estudante e registar UCs removidas
    set<string> removed_UCs;
    for(const auto& class_code_UC_code_pair : student_enrolled_UC_and_classes){
        string current_class_code = class_code_UC_code_pair.first;
        string current_UC_code = class_code_UC_code_pair.second;
        cout << current_UC_code << current_class_code << endl;
        if(current_class_code == class_code){
            Schedule schedule_to_remove = temp_LeicClass.getUCClass(current_UC_code).getUCClassSchedule();
            temp_student.removeSchedule(current_class_code, current_UC_code, schedule_to_remove);
            removed_UCs.insert(current_UC_code);
        }
    }

    if(removed_UCs.empty()){
        cout << "The student with code " << student_code << " is not enrolled in any UC in class " << class_code << endl;
        return;
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
        all_UCs_.erase(UCIt);
        temp_UC.eraseStudent(original_student);
        all_UCs_.insert(temp_UC);
        cout << UC_code << " was removed from " << class_code << "."<< endl;
    }

    all_classes_.insert(temp_LeicClass);
    all_students_.insert(temp_student);
    loadYear();
}

void Script::requestSwitchSingleUCtoClass(int student_code, const string& new_class_code, const string& UC_code){
    // Verificação de Student
    auto studentIt = all_students_.find(Student(student_code, ""));
    if (studentIt == all_students_.end()) {
        cout << "Request denied." << endl;
        cout << "Invalid student code. Please enter a valid student code." << endl;
        return;
    }
    Student original_student = *studentIt;
    Student temp_student = original_student;

    // Verificação de UC_class
    auto student_enrolled_UC_and_classes = temp_student.get_student_enrolled_UC_and_classes();
    bool UC_exists = false;
    string old_class_code;
    for(const auto& class_code_UC_code_pair : student_enrolled_UC_and_classes){
        if(class_code_UC_code_pair.second == UC_code){
            UC_exists = true;
            old_class_code = class_code_UC_code_pair.first;
        }
    }
    if(!UC_exists){
        cout << "Request denied." << endl;
        cout << "The student is still not enrolled in this UC." << endl;
        return;
    }
    if(old_class_code == new_class_code){
        cout << "Request denied." << endl;
        cout << "The classes involved in the switch are the same." << endl;
        return;
    }

    // Verificação de LeicClass_new
    auto classIt_new = all_classes_.find(LeicClass(new_class_code));
    if (classIt_new == all_classes_.end()) {
        cout << "Request denied." << endl;
        cout << "Invalid new class code. Please enter a valid class code." << endl;
        return;
    }
    LeicClass temp_LeicClass_new = *classIt_new;

    // Verificação de UC_class_new
    UC_class temp_UC_Class_new = temp_LeicClass_new.getUCClass(UC_code);
    if (temp_UC_Class_new.getUcName() == "Nao existe") {
        cout << "Request denied." << endl;
        cout << "UC not found in the new class code under consideration. Please enter a valid UC code." << endl;
        return;
    }
    if(temp_UC_Class_new.getNumberOfEnrolledStudents() >= 27){
        cout << "Request denied." << endl;
        cout << "The new UC class has already reached it's maximum capacity of 27 students." << endl;
        return;
    }
    Schedule new_schedule = temp_UC_Class_new.getUCClassSchedule();

    // LeicClass_old
    auto classIt_old = all_classes_.find(LeicClass(old_class_code));
    LeicClass temp_LeicClass_old = *classIt_old;

    // Verificação de UC_class_old
    UC_class temp_UC_Class_old = temp_LeicClass_old.getUCClass(UC_code);
    Schedule old_schedule = temp_UC_Class_old.getUCClassSchedule();

    temp_student.removeSchedule(old_class_code, UC_code, old_schedule);

    // Verifica se o horário da UC_class_new é compatível com o horário do estudante sem o old_schedule
    if (temp_student.checkScheduleConflict(new_schedule)) {
        cout << "Request denied." << endl;
        cout << "The student's schedule " << student_code << " is not compatible with the new class schedule " << new_class_code
             << " of UC " << UC_code << "." << endl;
        return;
    }

    auto number_of_enrolled_students_per_class_in_UC = this->getNumberOfEnrolledStudentsPerClassInUC(UC_code);
    int min_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.at(0).second;
    int max_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.back().second;

    auto it_old = std::find_if(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
                           [old_class_code](const pair<string, int>& p) {
                               return p.first == old_class_code;
                           });

    auto it_new = std::find_if(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
                               [new_class_code](const pair<string, int>& p) {
                                   return p.first == new_class_code;
                               });

    if(abs(max_number_of_enrolled_students_per_class_in_UC - min_number_of_enrolled_students_per_class_in_UC) > 4){
        // Balance does not exist
        if(it_old->second <= it_new->second){
            cout << "Request denied." << endl;
            cout << "The balance of class occupation in this UC has not been reached yet. To achieve balance, you should enroll in classes with fewer number of students compared to the current (" << it_old->second << "), which are:" << endl;
            for(const auto& elem : number_of_enrolled_students_per_class_in_UC){
                if(it_old->second > elem.second){
                    cout << elem.first << ": " << elem.second << " students enrolled" << endl;
                }
                return;
            }
        } else{
            cout << "Request approved." << endl;
            cout << "The balance of class occupation in this UC has not been reached yet. Your request will help achieve this balance." << endl;
        }
    } else{
        // Balance exists
        *it_old--;
        *it_new++;
        std::sort(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
                  [](const pair<string, int>& a, const pair<string, int>& b) {
                      return a.second < b.second;
                  });

        int min_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.at(0).second;
        int max_number_of_enrolled_students_per_class_in_UC = number_of_enrolled_students_per_class_in_UC.back().second;

        if(abs(max_number_of_enrolled_students_per_class_in_UC - min_number_of_enrolled_students_per_class_in_UC) > 4){
            cout << "Request denied. This request disrupts class occupancy. The difference in the number of students enrolled in any class within the same UC must be less than or equal to 4." << endl;
            return;
        }
        cout << "Request approved." << endl;
        cout << "The balance between class occupation was not disturbed." << endl;
    }

    // Request aprovado
    auto UCIt = all_UCs_.find(UC_class(UC_code));
    auto temp_UC = *UCIt;
    // erases
    all_students_.erase(original_student);
    all_classes_.erase(temp_LeicClass_old);
    all_classes_.erase(temp_LeicClass_new);
    all_UCs_.erase(temp_UC);
    temp_UC_Class_old.eraseStudent(original_student);
    temp_UC.eraseStudent(original_student);
    // Alterações
    temp_student.addSchedule(new_class_code, UC_code, new_schedule);
    // inserts
    temp_UC_Class_new.insertStudent(temp_student);
    temp_LeicClass_old.insertUcClass(temp_UC_Class_old);
    temp_LeicClass_new.insertUcClass(temp_UC_Class_new);
    temp_UC.insertStudent(temp_student);
    all_students_.insert(temp_student);
    all_classes_.insert(temp_LeicClass_new);
    all_classes_.insert(temp_LeicClass_old);
    all_UCs_.insert(temp_UC);

    cout << "(" << UC_code << ", "  << old_class_code << ") was switched to " << "(" << UC_code << ", "  << new_class_code << ") added." << std::endl;

}

vector<pair<string, int>> Script::getNumberOfEnrolledStudentsPerClassInUC(const string& UC_code) const{
    ///A função cria um vetor de pares de string e int chamado number_of_enrolled_students_per_class_in_UC.
    vector<pair<string, int>> number_of_enrolled_students_per_class_in_UC;
    ///Para cada turma em all_classes_, se a UC obtida a partir de UC_code existir, o par constituído pelo nome da turma (obtido por getClassName) e pelo número de estudantes inscritos na UC (obtido por getNumberOfEnrolledStudents) é colocado em number_of_enrolled_students_per_class_in_UC.
    for(const LeicClass& current_class : all_classes_){
        auto UCClass = current_class.getUCClass(UC_code);
        if(UCClass.getUcName() != "Nao existe"){
            number_of_enrolled_students_per_class_in_UC.emplace_back(make_pair(current_class.getClassName(), UCClass.getNumberOfEnrolledStudents()));
        }
    }
    ///No fim desse processo, number_of_enrolled_students_per_class_in_UC é ordenado por ordem crescente de estudantes inscritos.
    std::sort(number_of_enrolled_students_per_class_in_UC.begin(), number_of_enrolled_students_per_class_in_UC.end(),
              [](const pair<string, int>& a, const pair<string, int>& b) {
                  return a.second < b.second;
              });
    ///Por fim, number_of_enrolled_students_per_class_in_UC é retornado.
    return number_of_enrolled_students_per_class_in_UC;
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
    ///É criado um estado da base de dados, current_state, no qual se guarda os sets all_students, all_classes_ e all_UCs_ atuais.
    DataBaseState current_state;
    current_state.all_students = all_students_;
    current_state.all_classes = all_classes_;
    current_state.all_UCs = all_UCs_;

    ///De seguida, este estado é colocado no topo da stack system_changes_record, que contém todos os estados da base de dados guardados.
    system_changes_record_.push(current_state);
}

void Script::restoreState(DataBaseState& previous_state) {
    ///Os sets all_classes_, all_UCs_ e all_students de previous_state são atribuídos aos respetivos sets atuais.
    all_classes_ = previous_state.all_classes;
    all_UCs_ = previous_state.all_UCs;
    all_students_ = previous_state.all_students;
}

void Script::undoLastAction() {
    ///Se o registo de estados anteriores não estiver vazio, guarda-se o objeto no topo da stack system_changes_record no objeto previous_state.
    if(!system_changes_record_.empty()) {
        DataBaseState previous_state = system_changes_record_.top();
        ///Este é removido da stack.
        system_changes_record_.pop();
        ///O estado previous_state é restaurado pela função restoreState e os estudantes, UC's e turmas são divididos por ano.
        restoreState(previous_state);
        loadYear();
        ///Por fim, a mensagem "Last database state was restored" é impressa.
        cout << "Last database state was restored" << endl;
        cout << endl;
    } else{
        ///Por outro lado, se o registo estiver vazio, nada disto ocorre e a mensagem "There's nothing to undo" é impressa.
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

