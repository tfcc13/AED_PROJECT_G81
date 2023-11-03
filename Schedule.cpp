//
// Created by tiago on 28-10-2023.
//

#include "Schedule.h"


///Overload do operador de igualdade de dayScheduleEntry
///
/// \param d1 Objeto dayScheduleEntry que se pretende comparar
/// \param d2 Objeto dayScheduleEntry que se pretende comparar
/// \return *True* se forem iguais, *false* caso contrário
bool operator==(const dayScheduleEntry& d1, const dayScheduleEntry& d2) {
    ///Compara individualmente os atributos UC_code, class_code, start_hour, duration e class_type dos dois objetos.
    ///
    ///Se todos forem iguais entre os objetos, então os objetos são iguais.
    return (d1.UC_code == d2.UC_code and
            d1.class_code == d2.class_code and
            d1.start_hour == d2.start_hour and
            d1.duration == d2.duration and
            d1.class_type == d2.class_type);
}

Schedule::Schedule() {
    schedule_ =  {
            {"Monday", {}},
            {"Tuesday",{}},
            {"Wednesday",{}},
            {"Thursday",{}},
            {"Friday",{}}
    };
}

Schedule::Schedule(const Schedule &other) {
    schedule_ = other.schedule_;
}

void Schedule::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    ///No mapa schedule_, é adicionada uma entrada entry dayScheduleEntry ao vetor correspondente ao dia da semana week_day.
    schedule_[week_day].emplace_back(entry);

    ///De seguida, o vetor é ordenado, de modo a que as aulas estejam por ordem.
    sort(schedule_[week_day].begin(), schedule_[week_day].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.start_hour < b.start_hour;
    });
}

void Schedule::removeDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    ///Um iterador it itera pelo vetor correpondente ao dia da semana week_day a que a aula entry que se pretende remover pertence.
    for(auto it = schedule_[week_day].begin(); it != schedule_[week_day].end(); it++){
        ///Quando o iterador corresponde à aula, esta é removida do vetor.
        if(*it == entry){
            schedule_[week_day].erase(it);
        }
    }
    ///De seguida, o vetor é ordenado
    sort(schedule_[week_day].begin(), schedule_[week_day].end(), [](const dayScheduleEntry& a, const dayScheduleEntry& b) {
        return a.start_hour < b.start_hour;
    });
}

bool Schedule::checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry) const{
    double e1_beginning_time = entry.start_hour;
    double e1_finishing_time = entry.start_hour + entry.duration;
    double e2_beginning_time, e2_finishing_time;

    ///Não se verifica a conflitualidade da aula se esta for do tipo T, pois aulas teóricas podem ter sobreposições com qualquer tipo de aula sem se criar conflitos.
    if(entry.class_type != "T"){
        ///Um iterador it itera pelo vetor de aulas correspondente ao dia week_day no mapa schedule_.
        for(auto & it : schedule_.at(week_day)){
            e2_beginning_time = it.start_hour;
            e2_finishing_time = it.start_hour + it.duration;

            ///Se a aula entry começar antes do fim da aula em que se encontra o iterador e esta começar entes do fim da aula entry, tem-se um conflito, logo a função retorna *true*.
            if(e1_beginning_time <= e2_finishing_time and e2_beginning_time <= e1_finishing_time){
                return true;
            }
        }
    }
    ///Caso não se tenha encontrado conflitos, a função retorna *false*.
    return false;
}

void Schedule::addSchedule(const Schedule& s){
    ///Um iterador it_map_elem itera pelos pares de dia e vetor de aulas do horário que se pretende adicionar ao horário base
    /// \note Neste processo, há sempre 5 iterações (uma para cada dia). Assim, como se trata de um número constante, não é tomado em conta no cálculo da complexidade temporal
    for(const auto & it_map_elem : s.schedule_){

        ///Em cada iteração de it_map_elem, um iterador it_schedule_entry itera pelo vetor de aulas desse dia (do horário que se pretende adicionar)
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){

            ///Em cada iteração de it_schedule_entry, a aula é adicionada ao horário base, usando a função addDayScheduleEntry
            this->addDayScheduleEntry(it_map_elem.first, *it_schedule_entry);
        }
    }
}

void Schedule::removeSchedule(const Schedule& s){
    ///Um iterador it_map_elem itera pelos pares de dia e vetor de aulas do horário que se pretende remover do horário base
    /// \note Neste processo, há sempre 5 iterações (uma para cada dia). Assim, como se trata de um número constante, não é tomado em conta no cálculo da complexidade temporal
    for(const auto & it_map_elem : s.schedule_){

        ///Em cada iteração de it_map_elem, um iterador it_schedule_entry itera pelo vetor de aulas desse dia (do horário que se pretende remover)
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){

            ///Em cada iteração de it_schedule_entry, a aula é removida do horário base, usando a função removeDayScheduleEntry
            this->removeDayScheduleEntry(it_map_elem.first, *it_schedule_entry);
        }
    }
}

bool Schedule::checkScheduleConflict(const Schedule& s) const{
    ///Um iterador it_map_elem itera pelos pares de dia e vetor de aulas do horário cuja conflituosidade com o horário base se pretende verificar
    /// \note Neste processo, há sempre 5 iterações (uma para cada dia). Assim, como se trata de um número constante, não é tomado em conta no cálculo da complexidade temporal
    for(const auto & it_map_elem : s.schedule_){

        ///Em cada iteração de it_map_elem, um iterador it_schedule_entry itera pelo vetor de aulas desse dia (do horário que se pretende verificar a conflituosidade)
        for(auto it_schedule_entry = it_map_elem.second.begin(); it_schedule_entry != it_map_elem.second.end(); it_schedule_entry++){

            ///Em cada iteração de it_schedule_entry, verifica-se se a aula tem conflito com o horário base, usando a função checkDayScheduleEntryConflict
            this->checkDayScheduleEntryConflict(it_map_elem.first, *it_schedule_entry);
        }
    }
}

void Schedule::PrintDaySchedule(const string &week_day) const{
    ///A função começa por imprimir a string week_day
    cout << left  << week_day << endl;

    ///Se não houver aulas nesse dia, a função imprime "No classes on this day"
    if (schedule_.at(week_day).empty()){
        cout << left << "No classes on this day" << endl;
    }

    ///Caso haja, imprime uma tabela com os parâmetros "UC code", "Class code", "Start Time", "Duration" e "Type" e com os valores correspondentes a cada aula desse dia (UC_code, class_code, start_hour, duration e class_type, respetivamente)
    else{
        cout << left  << setw(15) << "UC code" << setw(15) << "Class code" << setw(15) << "Start Time" << std::setw(15) << "Duration" << std::setw(15) << "Type" << std::endl;
        for (const auto& classSchedule : schedule_.at(week_day)) {
            cout << left << setw(15) << classSchedule.UC_code
                 << setw(15) << classSchedule.class_code
                 << setw(15) << classSchedule.start_hour
                 << setw(15) << classSchedule.duration
                 << setw(15) << classSchedule.class_type << endl;
        }
    }
}

void Schedule::PrintWeekSchedule() const{
    ///A função executa a função PrintDaySchedule para cada dia da semana, tendo este como week_day de entrada.
    this->PrintDaySchedule("Monday");
    cout << endl;
    this->PrintDaySchedule("Tuesday");
    cout << endl;
    this->PrintDaySchedule("Wednesday");
    cout << endl;
    this->PrintDaySchedule("Thursday");
    cout << endl;
    this->PrintDaySchedule("Friday");
}

