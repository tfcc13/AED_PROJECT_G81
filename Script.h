//
// Created by tiago on 30-10-2023.
//

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


    ///
    void consultUCOccupancy(const string& uc_name);
    void consultUCEnrolledStudents(const string& uc_name);
    void consultGreatestNumberOfStudentsUCs(int num);
    void consultSmallerNumberOfStudentsUCs(int num);
    void PrintWeekUCSchedule(const string& uc_name);
    void PrintUCClassSchedule(const string& class_code, const string& uc_code);
    void consultClassOccupancy(const string& class_code);
    void consultUCCLassOccupancy(const string& class_code, const string& uc_code);
    int consultNumberOfStudentsRegisteredUCs(int numberOfUCs);
    void consultClassEnrolledStudents(const string& class_code);
    void consultGreatestClasses(int num_classes);
    void consultSmallestClasses(int num_classes);
    void consultYearOccupancy(int year);
    void consultEnrolledStudentsYear(int year);
    void consultUCsByYear(int year);
    void consultUCsByYearByAscendingOccupancy(int year);
    void consultUCsByYearByDescendingOccupancy(int year);
    void consultUCsWithMinNStudents(int year, int number);
    void consultUCsWithMaxNStudents(int year, int number);
    void consultClassesInaYear(int year);
    void consultClassesInaYearByAscendingOccupancy(int year);
    void consultClassesInaYearByDescendingOccupancy(int year);
    void consultClassesWithMinNStudents(int year, int number);
    void consultClassesWithMaxNStudents(int year, int number);


    void captureState();
    void restoreState(DataBaseState& previous_state);
    void undoLastAction();

    void requestRemoveClassForAllUCs(int student_code, const string& class_code);
    void requestSwitchAllUCstoClass(int student_code, const string& class_code);
    void requestSwitchSingleUCtoClass(int student_code, const string& UC_code);
    bool requestAddUCInClass(int student_id, const string& class_code, const string& UC_code);
    void requestRemoveSingleUC(int student_code, const string& UC_code);

    void saveChangesToCsvFile(const string& filename);

    vector<pair<string, int>> getNumberOfEnrolledStudentsPerClassInUC(const string& UC_code) const; // <class, Nº de alunos>. Por ordem de menos alunos para mais alunos. Tentar inscrever na que tem menos alunos (se compatível)
    bool checkBalanceBetweenTwoClassesInUC(const string& UC_code, const string& class_code_1, const string& class_code_2);

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