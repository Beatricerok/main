#include "failuapdorojimas.h"
#include "student.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>

// Įrašo studentų rezultatus į nurodytą failą, naudojant gražų stulpelių išlygiavimą.
void irasytiIFaila(const std::vector<Student>& studentai, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo įrašymui: " + filename);
    }

    // Antraštė
    outFile << std::left << std::setw(15) << "Vardas"
            << std::left << std::setw(15) << "Pavarde"
            << std::right << std::setw(15) << "GalutinisVid"
            << std::right << std::setw(15) << "GalutinisMed" << "\n";
    outFile << std::string(60, '-') << "\n";

    for (const auto& stud : studentai) {
        outFile << std::left << std::setw(15) << stud.vardas
                << std::left << std::setw(15) << stud.pavarde
                << std::right << std::setw(15) << std::fixed << std::setprecision(2) << stud.galutinisVid
                << std::right << std::setw(15) << std::fixed << std::setprecision(2) << stud.galutinisMed
                << "\n";
    }
}

// Nuskaitymo funkcija – atidaro nurodytą failą, praleidžia antraštės eilutę,
// skaito kiekvieną eilutę su studento duomenimis (vardas, pavardė, 15 ND pažymių, egzamino pažymys),
// apskaičiuoja pažymių vidurkį ir medianą, ir grąžina studentų vektorių.
std::vector<Student> nuskaitytiIsFailo(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::vector<Student> studentai;
    std::string line;
    // Praleidžiame antraštės eilutę
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        if (line.empty()) continue; // Praleidžiame tuščias eilutes

        std::istringstream iss(line);
        Student stud;

        // Nuskaitome vardą ir pavardę
        if (!(iss >> stud.vardas >> stud.pavarde)) {
            std::cerr << "Klaida skaitant vardą ir pavardę eilutėje: " << line << "\n";
            continue;
        }

        // Nuskaitome 15 ND pažymių
        stud.paz.resize(15);
        for (int i = 0; i < 15; ++i) {
            if (!(iss >> stud.paz[i])) {
                std::cerr << "Klaida skaitant ND pažymius eilutėje: " << line << "\n";
                break;
            }
        }

        // Nuskaitome egzamino pažymį
        if (!(iss >> stud.egz)) {
            std::cerr << "Klaida skaitant egzamino pažymį eilutėje: " << line << "\n";
            continue;
        }

        // Apskaičiuojame pažymių vidurkį ir medianą
        stud.galutinisVid = skaiciuotiVidurki(stud.paz);
        stud.galutinisMed = skaiciuotiMediana(stud.paz);

        studentai.push_back(stud);
    }

    return studentai;
}

// Rūšiuoja studentų sąrašą didėjimo tvarka pagal galutinį vidurkį.
void rikiuotiPagalBalus(std::vector<Student>& studentai) {
    std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
        return a.galutinisVid < b.galutinisVid;
    });
}

// Skirsto studentus į dvi grupes:
// • Kietekai: studentai, kurių galutinis vidurkis ≥ 5.0
// • Vargšiukai: studentai, kurių galutinis vidurkis < 5.0
// Abu rezultatai surašomi didėjimo tvarka.
void skirstytiStudentus(const std::vector<Student>& studentai,
                         std::vector<Student>& kietekai,
                         std::vector<Student>& vargsiukai) {
    for (const auto& stud : studentai) {
        if (stud.galutinisVid >= 5.0)
            kietekai.push_back(stud);
        else
            vargsiukai.push_back(stud);
    }
    std::sort(kietekai.begin(), kietekai.end(), [](const Student& a, const Student& b) {
        return a.galutinisVid < b.galutinisVid;
    });
    std::sort(vargsiukai.begin(), vargsiukai.end(), [](const Student& a, const Student& b) {
        return a.galutinisVid < b.galutinisVid;
    });
}
