//
// Created by tiago on 28-10-2023.
//

#ifndef AED_PROJECT_SCHEDULE_H
#define AED_PROJECT_SCHEDULE_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

struct dayScheduleEntry {
    string UC_code;
    string class_code;
    double start_hour;
    double duration;
    string class_type;
};

class Schedule {
private:
    map<string, vector<dayScheduleEntry>> schedule_;

public:
    Schedule();
    Schedule(const Schedule& other);

    void addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);
    void removeDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry);
    bool checkDayScheduleEntryConflict(const string &week_day, const dayScheduleEntry& entry); // Se houver conflito, return true

    void addSchedule(const Schedule& s); // Dar merge do objeto horário atual com outro objeto horário de entrada
    void removeSchedule(const Schedule& s); // Dar split de um objeto horário de entrada com o objeto horário atual
    bool checkScheduleConflict(const Schedule& s); // Verificar se existem conflitos entre o objeto horário atual com outro objeto horário de entrada. Se houver conflito, return true

    void PrintDaySchedule(const std::string& week_day);
    void PrintWeekSchedule();

};



#endif //AED_PROJECT_SCHEDULE_H
