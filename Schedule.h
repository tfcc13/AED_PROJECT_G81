#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

///@struct dayScheduleEntry
///
///@brief Estrutura que representa uma aula
struct dayScheduleEntry {
    ///Código da unidade curricular
    string UC_code;

    ///Código da turma
    string class_code;

    ///Hora de início da aula
    double start_hour;

    ///Duração da aula em horas
    double duration;

    ///Tipo de aula (T, TP ou PL)
    string class_type;
};

///Classe que representa horários
class Schedule {
private:
    ///Mapa que representa o horário
    ///
    ///O mapa faz corresponder aos dias da semana, em forma de string, as aulas desse dia, na forma de vetor de dayScheduleEntry.
    map<string, vector<dayScheduleEntry>> schedule_;

public:

    ///Default Constructor de Schedule
    ///
    ///schedule_ tem strings para os dias da semana (exceto sábado e domingo) e a cada uma delas corresponde um vetor vazio, isto é, não há aulas em nenhum dia.
    ///
    ///**Time Complexity:** O(1)
    Schedule();

    ///Copy Constructor de Schedule
    ///
    ///Cria um novo Schedule copiando um já existente
    ///
    ///**Time Complexity:** O(n)
    /// \param other Schedule que se pretende copiar
    Schedule(const Schedule& other);

    ///Adiciona uma aula
    ///
    ///**Time Complexity:** O(n * log n) (devido ao sort)
    /// \param week_day Dia ao qual se pretende adicionar uma aula
    /// \param entry Aula que se pretende adicionar
    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);

    ///Remove uma aula
    ///
    ///
    ///**Time Complexity:** O(n * log n) (devido ao sort)
    /// \param week_day Dia a que pertence a aula que se pretende remover
    /// \param entry Aula que se pretende remover
    void removeDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);

    ///Verifica se uma determinada aula tem uma sobreposição conflituosa com outra aula
    ///
    ///**Time Complexity:** O(n)
    /// \param week_day Dia da aula
    /// \param entry Aula cuja conflitualidade se pretende verificar
    /// \return *True* se houver conflito, *False* caso contrário
    bool checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry) const; // Se houver conflito, return true

    ///Funde o horário atual com outro horário
    ///
    ///**Time Complexity:** O(n^2 * log n)
    /// \param s Horário que se pretende fundir com o horário atual
    void addSchedule(const Schedule& s);

    ///Remove do horário atual as aulas de outro horário
    ///
    ///**Time Complexity:** O(n^2 * log n)
    /// \param s Horário que se pretende remover do horário atual
    void removeSchedule(const Schedule& s); // Dar split de um objeto horário de entrada com o objeto horário atual

    ///Verifica se há algum conflito de aulas entre o horário atual e outro horário
    ///
    ///**Time Complexity:** O(n^2)
    /// \param s Horário cuja conflituosidade com o horário atual se pretende verificar
    /// \return *True* se houver conflito, *False* caso contrário
    bool checkScheduleConflict(const Schedule& s) const;

    ///Imprime o horário de um dia
    ///
    ///**Time Complexity:** O(n)
    /// \param week_day Dia cujo horário se pretende imprimir
    void PrintDaySchedule(const std::string& week_day) const;

    ///Imprime o horário semanal
    ///
    ///**Time Complexity:** O(n)
    void PrintWeekSchedule() const;
};

#endif //AED_PROJECT_SCHEDULE_H