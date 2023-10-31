//
// Created by tiago on 31-10-2023.
//

#ifndef AED_PROJECT_REQUEST_H
#define AED_PROJECT_REQUEST_H

#include <iostream>
#include <string>

using namespace std;

class Request {

private:
    std::string request_type_;
public:
    void changeStudentUC();
    void changeStudentClass();
    void switchStudentUC();
    void switchStudentClass();


};


#endif //AED_PROJECT_REQUEST_H
