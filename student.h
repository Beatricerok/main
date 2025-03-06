
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;
    int egz;
    double galutinisVid;
    double galutinisMed;
};

double skaiciuotiVidurki(const std::vector<int>& paz);
double skaiciuotiMediana(std::vector<int> paz);

#endif // STUDENT_H
