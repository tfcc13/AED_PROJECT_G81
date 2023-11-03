//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_UC_CLASS_H
#define AED_PROJECT_UC_CLASS_H

#include <iostream>
#include <string>
#include "Student.h"
#include "Schedule.h"

using namespace std;


///Classe que representa turmas de determinada UC
class UC_class {
private:

    string UC_name_;
    int UC_year_;
    set<Student> enrolled_students_;
    int number_of_enrolled_students_;
    Schedule UC_class_schedule_;

public:

    ///Construtor de UC_class
    //
    ///**Time Complexity:** O(1)
    ///
    /// \param UC_name Nome da UC
    /// \param uc_year Ano da UC (valor padrão = 1)
    ///
    /// number_of_enrolled_students_ = 0 e enrolled_students_ e UC_class_schedule estão ambos vazios.
    UC_class(const string& UC_name, int uc_year=1);


    ///Copy Constructor de Student
    ///
    ///Cria uma nova UC_class a partir de uma já existente, copiando todos os seus atributos.
    ///
    ///**Time Coplexity:** O(1)
    /// \param other UC_class que se pretende copiar
    UC_class(const UC_class& other);


    ///Operador de comparação <
    ///
    ///Compara UC_name_
    ///
    ///**Time Complexity:** O(n)
    /// \param other UC que se pretende comparar com a UC atual
    /// \return *true* se UC_name da UC atual for menor que UC_name de other, *false* caso contrário
    bool operator<(const UC_class& other) const;


    ///Operador de comparação !=
    ///
    ///Compara UC_name_
    ///
    ///**Time Complexity:** O(n)
    /// \param other UC que se pretende comparar com a UC atual
    /// \return *true* se UC_name da UC atual for diferente de UC_name de other, *false* caso contrário
    bool operator!=(const UC_class& other) const;


    ///Função getter de UC_name_
    ///
    ///**Time Complexity:** O(1)
    /// \return  UC_name_
    const string& getUcName() const;



    ///Adiciona um estudante s aos alunos inscritos na turma da UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param s Estudante que se pretende adicionar
    void insertStudent(Student& s);


    ///Remove um estudante s dos alunos inscritos na turma da UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param s Estudante que se pretende remover
    void eraseStudent(Student& s);


    ///Função getter de enrolled_students_
    ///
    ///**Time Complexity:** O(n)
    /// \return enrolled_students_
    set<Student> getEnrolledStudents() const;

    ///Obtém o número de estudantes inscritos na turma da UC
    ///
    ///**Time Complexity:** O(1)
    /// \return Número de estudantes inscritos na turma da UC
    int getNumberOfEnrolledStudents() const;


    ///Função getter de UC_year_
    ///
    ///**Time Complexity:** O(1)
    /// \return UC_year_
    int getUCYear() const;


    ///Obtém o número de vagas disponíveis na turma para a UC
    ///
    /// \note O número máximo de alunos é 27
    ///
    ///**Time Complexity:** O(1)
    /// \return Número de vagas disponíveis na turma para a UC
    int getNumberOfVacancies() const;


    ///Função getter de UC_class_schedule_
    ///
    ///**Time Complexity:** O(1)
    /// \return UC_class_schedule_
    Schedule getUCClassSchedule() const;


    ///Imprime os estudantes inscritos na turma da UC
    ///
    ///**Time Complexity:** O(n)
    void PrintEnrolledStudents() const;

    ///Imprime o horário da turma da UC num determinado dia
    ///
    ///**Time Complexity:** O(n)
    /// \param week_day Dia cujo horário se pretende imprimir
    void PrintUcDaySchedule(const string& week_day) const;


    ///Imprime o horário semanal da turma da UC
    ///
    ///**Time Complexity:** O(n)
    void PrintUcWeekSchedule() const;


    ///Adiciona uma aula ao horário da turma
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param week_day Dia ao qual se pretende adicionar a aula
    /// \param entry Aula que se pretende adicionar
    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);

};

#endif //AED_PROJECT_UC_CLASS_H
