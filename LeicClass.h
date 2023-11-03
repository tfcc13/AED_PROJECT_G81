//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_LEICCLASS_H
#define AED_PROJECT_LEICCLASS_H

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "UC_class.h"
#include "Schedule.h"

using namespace std;


///Classe que representa uma turma, com todas as suas UC's
class LeicClass {
private:
    string LEIC_class_name_;
    set<UC_class> LEIC_UC_classes_;
    Schedule LEIC_class_schedule_;

public:


    ///Default Constructor de LeicClass
    ///
    ///Todos os atributos de LeicClass são inicializados vazios
    ///
    ///**Time Complexity:** O(1)
    LeicClass();

    ///Constructor de LeicClass
    ///
    ///**Time Complexity:** O(1)
    ///
    /// \param class_name Nome da turma
    ///
    /// Os restantes atributos são inicializados vazios.
    LeicClass(const string& class_name);



    ///Copy Constructor de LeicClass
    ///
    ///Cria uma nova LeicClass a partir de uma já existente, copiando todos os seus atributos.
    ///
    ///**Time Coplexity:** O(n)
    /// \param other LeicClass que se pretende copiar
    LeicClass(const LeicClass& other);



    ///Overload do operador de comparação <
    ///
    ///Compara Leic_class_name_
    ///
    ///**Time Complexity:** O(n)
    /// \param other LeicClass que se pretende comparar com a LeicClass atual
    /// \return *true* se Leic_class_name_ da turma atual for menor que Leic_class_name_ de other, *false* caso contrário
    bool operator<(const LeicClass& other) const;



    ///Função getter de LEIC_class_name_
    ///
    ///**Time Complexity:** O(1)
    /// \return LEIC_class_name_
    const string& getClassName() const;


    ///Obtém a turma de uma determinada UC
    ///
    ///**Time Complexity:** O(log n)
    /// \param UC_class_name Nome da turma da UC
    /// \return Turma da UC pretendida
    UC_class getUCClass(const string& UC_class_name) const;


    ///Adiciona um objeto UC_class à turma
    ///
    ///O objeto é adicionado ao set LEIC_UC_classes_
    ///**Time Complexity:** O(log n)
    /// \param UC_class Objeto que se pretende adicionar
    void insertUcClass(const UC_class& UC_class);

    ///Remove um objeto UC_class da turma
    ///
    ///O objeto é removido do set LEIC_UC_classes_
    ///**Time Complexity:** O(log n)
    /// \param UC_class Objeto que se pretende remover
    void eraseUcClass(const UC_class& UC_class);


    ///Obtém o número de estudantes inscritos na turma
    ///
    ///**Time Complexity:** O(n)
    /// \return
    int getNumberOfEnrolledStudents() const;



    ///Obtém os estudantes inscritos na turma
    ///
    ///**Time Complexity:** O(n)
    /// \return Estudantes inscritos na turma
    set<Student> getEnrolledStudents() const;



    ///Função getter de LEIC_class_schedule_
    ///
    ///**Time Complexity:** O(1)
    /// \return LEIC_class_schedule_
    Schedule getLeicClassSchedule() const;



    ///Imprime todas as UC's da turma
    ///
    ///**Time Complexity:** O(n)
    void PrintClassUc() const;

    ///Imprime o horário da turma num determinado dia
    ///
    ///**Time Complexity:** O(n)
    /// \param week_day Dia cujo horário se pretende imprimir
    void PrintUcDaySchedule(const string& week_day) const;


    ///Imprime o horário semanal da turma
    ///
    ///**Time Complexity:** O(n)
    void PrintUcWeekSchedule() const;



    ///Adiciona uma aula ao horário da turma
    ///
    ///**Time Complexity:** O(n * log n)
    /// \param week_day Dia a que se pretende adicionar a aula
    /// \param entry Aula que se pretende adicionar
    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);



    ///Funde o horário atual da turma com outro horário
    ///
    ///**Time Complexity:** O(n^2 * log n)
    /// \param s Horário que se pretende fundir com o horário da turma
    void addSchedule(const Schedule& s);

};

#endif //AED_PROJECT_LEICCLASS_H

