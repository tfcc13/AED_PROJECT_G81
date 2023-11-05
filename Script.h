#ifndef AED_PROJECT_SCRIPT_H
#define AED_PROJECT_SCRIPT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <filesystem>
#include "Student.h"
#include "Schedule.h"
#include "LeicClass.h"
#include "UC_class.h"

using namespace std;

///@struct DataBaseState
///
///@brief Estrutura que guarda o estado da base de dados numa da altura

struct DataBaseState {

    set<LeicClass>  all_classes;
    set<UC_class> all_UCs;
    set<Student> all_students;
};

///Inclui as funções principais para o funcionamento do programa
class Script {

public:

    ///Constructor de Script
    ///
    ///**Time Complexity:** O(1)
    /// \param database Nome de database_
    Script(const string& database);

    ///Carrega os dados dos ficheiros, usando-os para popular os sets de UC's, turmas e estudantes
    ///
    ///Isto acontece através das funções populateUcSet , populateLeicSet e populateStudentSet, respetivamente.
    ///
    /// **Time Complexity:** O(n)
    /// \param filename_1 Ficheiro que se irá usar para popular all_UCs_
    /// \param filename_2 Ficheiro que se irá usar para popular all_classes_
    /// \param filename_3 Ficheiro que se irá usar para popular all_students_
    void loadData(const std::string& filename_1, const std::string& filename_2, const std::string& filename_3);

    ///Divide as turmas e UC's por ano
    ///
    ///**Time Complexity:** O(n * log n)
    void loadYear();

    /// Popula all_UCs_
    ///
    /// \note Cada objeto em UC_class_, no final do processo, é uma junção de todas as turmas dessa UC.
    ///**Time Complexity:** O(n)
    /// \param filename Ficheiro que se irá usar para popular os sets
    void populateUcSet(const std::string& filename);

    ///Popula all_classes_
    ///
    ///**Time Complexity:** O(n)
    /// \param filename Ficheiro que se irá usar para popular o set
    void populateLeicSet(const std::string& filename);

    ///Popula all_students_
    ///
    ///**Time Complexity:** O(n)
    /// \param filename Ficheiro que se irá usar para popular o set
    void populateStudentSet(const std::string& filename);


    ///Imprime o horário semanal de um estudante
    ///
    ///**Time Complexity:** O(log n)
    /// \param studentNumber Número do estudante cujo horário se pretende imprimir
    void PrintWeekStudentSchedule(int studentNumber);

    ///Imprime o horário semanal de uma turma
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_name Nome da turma cujo horário se pretende imprimir
    void PrintWeekScheduleClass(const string& class_name);

    ///Imprime as UC's em que um estudante está inscrito
    ///
    ///**Time Complexity:** O(log n)
    /// \param studentNumber Número do estudante cujas UC's se pretende imprimir
    void consultStudentEnrolledUCs(int studentNumber);

    ///Imprime as turmas em que um estudante está inscrito
    ///
    ///**Time Complexity:** O(log n)
    /// \param studentNumber Número do estudante cujas UC's se pretende imprimir
    void consultStudentEnrolledClasses(int studentNumber);

    ///Imprime o número de estudantes inscritos numa UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param uc_name Nome da UC cujo número de estudantes inscritos se pretende imprimir
    void consultUCOccupancy(const string& uc_name);

    ///Imprime os estudantes inscritos numa UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param uc_name Nome da UC cujos estudantes inscritos se pretende imprimir
    void consultUCEnrolledStudents(const string& uc_name);

    ///Imprime o nome e o número de alunos das *num* UC's com mais estudantes.
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param num Número de UC's que se pretende imprimir
    void consultGreatestNumberOfStudentsUCs(int num);

    ///Imprime o nome e número de alunos das *num* UC's com menos estudantes.
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param num Número de UC's que se pretende imprimir.
    void consultSmallerNumberOfStudentsUCs(int num);

    ///Imprime o horário semanal de uma UC.
    ///
    ///**Time Complexity:** O(log n)
    /// \param uc_name Nome da UC cujo hprário se pretende imprimir
    void PrintWeekUCSchedule(const string& uc_name);

    ///Imprime o horário semanal de uma UC numa turma específica
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_code Código da turma pretendida
    /// \param uc_code Código da UC pretendida
    void PrintUCClassSchedule(const string& class_code, const string& uc_code);

    ///Imprime o número de estudantes inscritos numa turma
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_code Código da turma cujo número de estudantes se pretende saber.
    void consultClassOccupancy(const string& class_code);

    ///Imprime o número de estudantes inscritos numa turma de uma UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_code
    /// \param uc_code
    void consultUCCLassOccupancy(const string& class_code, const string& uc_code);

    ///Obtém o número de estudantes inscritos num determinado número de UC's
    ///
    ///**Time Complexity:** O(n)
    /// \param numberOfUCs Número de UC's
    /// \return número de estudantes inscritos nesse número de UC's
    int consultNumberOfStudentsRegisteredUCs(int numberOfUCs);

    ///Imprime os estudantes inscritos numa turma
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_code Código da turma cujos alunos se pretende consultar
    void consultClassEnrolledStudents(const string& class_code);

    ///Imprime os estudantes inscrito numa turma duma UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param class_code Código da turma
    /// \param uc_code Código da UC
    void consultUCCLassEnrolledStudents(const string& class_code, const string& uc_code);

    ///Imprime o nome e o número de alunos das *num_classes* turmas com mais estudantes.
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param num_classes Número de turmas que se pretende imprimir
    void consultGreatestClasses(int num_classes);

    ///Imprime o nome e o número de alunos das *num_classes* turmas com menos estudantes.
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param num_classes Número de turmas que se pretende imprimir
    void consultSmallestClasses(int num_classes);

    ///Imprime o número de estudantes de um ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano cujo número de estudantes se pretende consultar
    void consultYearOccupancy(int year);

    ///Imprime os estudantes de um ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano cujos estudantes se pretende consultar
    void consultEnrolledStudentsYear(int year);

    ///Imprime as UC's de um ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano cujas UC's se pretende consultar
    void consultUCsByYear(int year);

    ///Imprime as UC's de um ano por ordem crescente de número de alunos inscritos
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param year Ano cujas UC's se pretende consultar
    void consultUCsByYearByAscendingOccupancy(int year);

    ///Imprime as UC's de um ano por ordem decrescente de número de alunos inscritos
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param year Ano cujas UC's se pretende consultar
    void consultUCsByYearByDescendingOccupancy(int year);

    ///Imprime as UC's com um número de estudantes igual ou superior a um determinado número, num determinado ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano que se pretende analisar
    /// \param number Número mínimo de estudantes
    void consultUCsWithMinNStudents(int year, int number);

    ///Imprime as UC's com um número de estudantes igual ou inferior a um determinado número, num determinado ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano que se pretende analisar
    /// \param number Número máximo de estudantes
    void consultUCsWithMaxNStudents(int year, int number);

    ///Imprime as turmas de um ano
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano cujas turmas se pretende analisar
    void consultClassesInaYear(int year);

    ///Imprime as turmas de um ano por ordem crescente de número de alunos inscritos
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param year Ano cujas turmas se pretende consultar
    void consultClassesInaYearByAscendingOccupancy(int year);

    ///Imprime as turmas de um ano por ordem crescente de número de alunos inscritos
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param year Ano cujas turmas se pretende consultar
    void consultClassesInaYearByDescendingOccupancy(int year);

    ///Imprime as turmas com um número de estudantes igual ou superior a um determinado número, num determinado ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano que se pretende analisar
    /// \param number Número mínimo de estudantes
    void consultClassesWithMinNStudents(int year, int number);

    ///Imprime as UC's com um número de estudantes igual ou inferior a um determinado número, num determinado ano.
    ///
    ///**Time Complexity:** O(n)
    /// \param year Ano que se pretende analisar
    /// \param number Número máximo de estudantes
    void consultClassesWithMaxNStudents(int year, int number);

    ///Guarda o estado atual dos estudantes, turmas e anos
    ///
    ///**Time Complexity:** O(n)
    void captureState();

    ///Restaura o estado da base de dados para o estado pretendido
    ///
    ///**Time Complexity:** O(n)
    /// \param previous_state Estado ao qual se pretende retornar a base de dados
    void restoreState(DataBaseState& previous_state);

    ///Desfaz a última ação
    ///
    ///**Time Complexity:** O(n * log n)
    void undoLastAction();

    ///Adiciona uma turma de uma UC a um aluno
    ///
    ///**Time Complexity:** O(n)
    /// \param student_code Código do estudante
    /// \param class_code Código da turma
    /// \param UC_code Código da UC
    void requestAddUCInClass(int student_code, const string& class_code, const string& UC_code);

    ///Remove a inscrição de um aluno numa UC
    ///
    ///**Time Complexity:** O(n)
    /// \param student_code Código do estudante
    /// \param UC_code Código da UC
    void requestRemoveSingleUC(int student_code, const string& UC_code);


    ///Remove a inscrição de um aluno numa turma, para todas as UC's
    ///
    ///**Time Complexity:** O(n)
    /// \param student_code Código do estudante
    /// \param class_code Código da turma
    void requestRemoveClassForAllUCs(int student_code, const string& class_code);


    /// Troca a turma de uma UC de um estudante
    ///
    ///**Time Complexity:** O(n)
    /// \param student_code Código do estudante
    /// \param new_class_code Código da nova turma
    /// \param UC_code Código da UC
    void requestSwitchSingleUCtoClass(int student_code, const string& new_class_code, const string& UC_code);

    ///Obtém o número de estudantes por turma de uma determinada UC
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param UC_code UC cujo número de estudantes por turma se pretende saber
    /// \return Vetor de pares em que estão associados o nome da turma e o número de estudantes da UC nessa turma
    vector<pair<string, int>> getNumberOfEnrolledStudentsPerClassInUC(const string& UC_code) const;



    ///Guarda alterações num ficheiro csv
    ///
    ///**Time Complexity:**
    /// \param filename Ficheiro no qual se pretende guardar alterações
    void saveChangesToCsvFile(const string& filename);

private:
    std::set<UC_class> all_UCs_;// = populateUcSet("input/classes.csv");
    std::set<LeicClass> all_classes_;// = populateLeicSet("input/classes_per_uc.csv");
    std::set<Student> all_students_; //= populateStudentSet("input/students_classes.csv");
    std::vector<set<LeicClass>> leic_class_years_;
    std::vector<set<UC_class>> UC_years_;
    std::string  database_;
    queue<string> requests_queue_;
    stack<DataBaseState> system_changes_record_;

};

#endif //AED_PROJECT_SCRIPT_H