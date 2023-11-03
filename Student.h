//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <set>
#include "Schedule.h"

using namespace std;

struct pair_compare
{
    bool operator()(const pair<string, string>& left_pair, const pair<string, string>& right_pair) const
    {   if (left_pair.first == right_pair.first) {
        return left_pair.second < right_pair.second;
    }
        return left_pair.first < right_pair.first;
    }
};

///Classe que representa Estudantes
class Student {

private:
    ///Número de identificação do estudante
    int id_number_;
    ///Nome do estudante
    string st_name_;
    ///Conjunto dos pares ordenados \<class_code, UC_code\>, ordenados por ordem crescente de class_code
    set<pair<string, string>, pair_compare> st_enrolled_UC_and_classes_;
    ///Número de UC's frequentadas pelo estudante
    int st_number_of_UCs_; // Para depois contar alunos inscritos em x cadeiras
    ///Horário do estudante
    Schedule st_schedule_;

public:

    ///Construtor de Student
    ///
    ///**Time Complexity:** O(1)
    /// \param id_number Número de identificação do estudante
    /// \param st_name Nome do estudante
    ///
    ///O estudante não está inscrito em quaisquer UC's ou turmas, logo o set st_enrolled_UC_and_classes_ é criado vazio, st_number_of_UCs_ = 0 e o horário, representado por st_schedule_, está vazio.
    Student(int id_number, const std::string& st_name);


    ///Copy Constructor de Student
    ///
    ///Cria um novo Student a partir de um já existente, copiando todos os seus atributos.
    ///
    ///**Time Coplexity:** O(1)
    /// \param other Student que se pretende copiar
    Student(const Student& other);


    ///Operador de comparação <
    ///
    ///Verifica se o número de identificação do aluno atual é menor que o número de identificação de um outro aluno
    ///
    ///**Time Complexity:** O(1)
    /// \param other Estudante cujo número de identificação se pretende comparar com o estudante atual
    /// \return *true* se o número de identificação do estudante atual for menor que o do estudante other, *false* caso contrário
    bool operator<(const Student& other) const;



    ///Função getter de id_number_
    ///
    ///**Time Complexity:** O(1)
    /// \return  id_number_
    int getIdNumber() const;

    ///Função getter de st_name_
    ///
    ///**Time Complexity:** O(1)
    /// \return  st_name_
    const string& getStudentName() const;


    ///Função getter de st_enrolled_UC_and_classes_
    ///
    ///**Time Complexity:** O(1)
    /// \return  st_enrolled_UC_and_classes_
    set<pair<string, string>, pair_compare> get_student_enrolled_UC_and_classes() const;


    ///Função getter de st_number_of_UCs_
    ///
    ///**Time Complexity:** O(1)
    /// \return  st_number_of_UCs_
    int getNumberOfUCs() const;




    ///Imprime o horário de um determinado dia
    ///
    ///O horário do dia week_day é impresso através da função PrintDaySchedule de st_schedule_
    ///
    ///**Time Complexity:** O(n)
    /// \param week_day Dia cujo horário se pretende imprimir
    void PrintUcDaySchedule(const string& week_day) const;

    ///Imprime o horário semanal do estudante
    ///
    ///O horário é impresso através da função PrintWeekSchedule de st_schedule_
    ///
    ///**Time Complexity:** O(n)
    void PrintUcWeekSchedule() const;


    ///Imprime as UC's em que o estudante está inscrito, bem como as respetivas turmas
    ///
    ///**Time Complexity:** O(n)
    void PrintEnrolledUCs() const;


    ///Imprime as turmas em que o estudante está inscrito
    ///
    ///**Time Complexity:** O(n)
    void PrintEnrolledClasses() const;



    ///Adiciona o horário de uma turma para uma unidade curricular ao horário do estudante
    ///
    ///**Time Complexity:** O(n^2 * log n)
    ///
    /// \param class_code Turma cujo horário se pretende adicionar
    /// \param UC_code UC cujo horário se pretende adicionar
    /// \param s Horário que se pretende adicionar
    void addSchedule(const string& class_code, const string& UC_code, const Schedule& s);



    ///Remove o horário de uma turma para uma unidade curricular do horário do estudante
    ///
    ///**Time Complexity:** O(n^2 * log n)
    ///
    /// \param class_code Turma cujo horário se pretende remover
    /// \param UC_code UC cujo horário se pretende remover
    /// \param s Horário que se pretende remover
    void removeSchedule(const string& class_code, const string& UC_code, const Schedule& s);



    ///Verifica se há algum conflito de aulas entre o horário do estudante e outro horário
    ///
    ///**Time Complexity:** O(n^2)
    /// \param s Horário cuja conflituosidade com o horário do estudante se pretende verificar
    /// \return *True* se houver conflito, *False* caso contrário
    bool checkScheduleConflict(const Schedule& s) const;

    //void addUCAndClass(const pair<string, string> UC_and_Class);
    //void removeUCAndClass(const pair<string, string> UC_and_Class);
    //void switchUCAndClass(const pair<string, string> old_UC_and_Class, const pair<string, string> new_UC_and_Class);
    //void insertUcCode(const std::string& UcCode);
    // const set<string>& getUcCodes() const;

};

#endif //AED_PROJECT_STUDENT_H
