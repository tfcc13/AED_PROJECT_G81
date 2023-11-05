#include "LeicClass.h"

LeicClass::LeicClass() :
    LEIC_class_name_(),
    LEIC_UC_classes_(),
    LEIC_class_schedule_() {}

LeicClass::LeicClass(const string& class_name) :
        LEIC_class_name_(class_name),
        LEIC_UC_classes_(),
        LEIC_class_schedule_() {}

LeicClass::LeicClass(const LeicClass& other) {
    LEIC_class_name_ = other.LEIC_class_name_;
    LEIC_UC_classes_ = other.LEIC_UC_classes_;
    LEIC_class_schedule_ = other.LEIC_class_schedule_;
}

bool LeicClass::operator<(const LeicClass &other) const {
    return LEIC_class_name_ < other.LEIC_class_name_;
}

const string &LeicClass::getClassName() const {
    return LEIC_class_name_;
}

UC_class LeicClass::getUCClass(const string &UC_class_name) const {
    ///A turma é encontrada através da função find de LEIC_UC_classes_.
    auto it = LEIC_UC_classes_.find(UC_class(UC_class_name));
    ///Caso não seja encontrada, a função retorna um objeto UC_class com UC_name_ "Nao existe".
    if(it == LEIC_UC_classes_.end()){
        UC_class ret = UC_class("Nao existe");
        return ret;
    }
    return *it;
}

void LeicClass::insertUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.insert(UC_class);
}

void LeicClass::eraseUcClass(const UC_class& UC_class) {
    LEIC_UC_classes_.erase(UC_class);
}

void LeicClass::PrintClassUc() const {
    ///Por cada elemento de LEIC_UC_classes_, a função imprime o nome da UC, UC_name_, através da função getUcName .
    for (const UC_class& UC : LEIC_UC_classes_) {
        cout << UC.getUcName() << std::endl;
    }
}

int LeicClass::getNumberOfEnrolledStudents() const{
    ///A função executa getEnrolledStudents, sendo o seu valor de retorno guardado na variável total_enrolled_students_in_class.
    set<Student> total_enrolled_students_in_class = this->getEnrolledStudents();
    ///O número de estudantes é obtido através da função size desse set.
    return int(total_enrolled_students_in_class.size());
}

set<Student> LeicClass::getEnrolledStudents() const{
    set<Student> total_enrolled_students_in_class;
    for(const auto & LEIC_UC_class : LEIC_UC_classes_){
        set<Student> temp_UC_class_enrolled_students = LEIC_UC_class.getEnrolledStudents();
        total_enrolled_students_in_class.insert(temp_UC_class_enrolled_students.begin(), temp_UC_class_enrolled_students.end());
    }
    return  total_enrolled_students_in_class;
}

Schedule LeicClass::getLeicClassSchedule() const{
    return LEIC_class_schedule_;
}

void LeicClass::PrintUcDaySchedule(const string& week_day) const{
    ///O horário é impresso através da função PrintDaySchedule de LEIC_class_schedule_
    LEIC_class_schedule_.PrintDaySchedule(week_day);
}

void LeicClass::PrintUcWeekSchedule() const{
    ///O horário é impresso através da função PrintWeekSchedule de LEIC_class_schedule_
    LEIC_class_schedule_.PrintWeekSchedule();
}

void LeicClass::addDayScheduleEntry(const string &week_day, const dayScheduleEntry& entry){
    ///A aula é adicionada a LEIC_class_schedule_ através da função addDayScheduleEntry
    LEIC_class_schedule_.addDayScheduleEntry(week_day, entry);
}

void LeicClass::addSchedule(const Schedule& s){
    ///O horário s é adicionado a LEIC_class_schedule_ através da função addSchedule deste.
    LEIC_class_schedule_.addSchedule(s);
}


