#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

// Struktūra, apibūdinanti studento duomenis
struct Student {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;   // 15 ND pažymių
    int egz;                // Egzamino pažymys
    double galutinisVid;    // Galutinis vidurkis (apskaičiuotas iš ND pažymių)
    double galutinisMed;    // Galutinė mediana (apskaičiuota iš ND pažymių)
};

double skaiciuotiVidurki(const std::vector<int>& paz);
double skaiciuotiMediana(std::vector<int> paz);

#endif // STUDENT_H
