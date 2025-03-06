
#include "failu_apdorojimas.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

std::vector<Student> nuskaitytiIsFailo(const std::string& failoVardas) {
    std::ifstream failas(failoVardas);
    std::vector<Student> studentai;
    if (!failas) {
        throw std::runtime_error("Klaida! Nepavyko atidaryti failo: " + failoVardas);
    }

    std::string eilute;
    std::getline(failas, eilute);

    while (std::getline(failas, eilute)) {
        std::istringstream iss(eilute);
        Student s;
        iss >> s.vardas >> s.pavarde;

        int pazymys;
        while (iss >> pazymys) {
            s.paz.push_back(pazymys);
        }
        s.egz = s.paz.back();
        s.paz.pop_back();

        s.galutinisVid = 0.4 * skaiciuotiVidurki(s.paz) + 0.6 * s.egz;
        s.galutinisMed = 0.4 * skaiciuotiMediana(s.paz) + 0.6 * s.egz;

        studentai.push_back(s);
    }
    return studentai;
}

void irasytiIFaila(const std::vector<Student>& studentai, const std::string& failoVardas) {
    std::ofstream failas(failoVardas);
    if (!failas) {
        throw std::runtime_error("Klaida! Nepavyko sukurti failo: " + failoVardas);
    }

    failas << std::left << std::setw(15) << "Vardas"
           << std::setw(15) << "Pavarde"
           << std::setw(20) << "Galutinis (Vid.)"
           << std::setw(20) << "Galutinis (Med.)" << std::endl;
    failas << std::string(70, '-') << std::endl;

    for (const auto& s : studentai) {
        failas << std::left << std::setw(15) << s.vardas
               << std::setw(15) << s.pavarde
               << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisVid
               << std::setw(20) << std::fixed << std::setprecision(2) << s.galutinisMed
               << std::endl;
    }
}
