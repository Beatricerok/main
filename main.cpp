#include "failuapdorojimas.h"
#include <iostream>

int main() {
    try {
        std::vector<int> dydziai = {100, 1000, 10000, 100000, 1000000};

        for (int dydis : dydziai) {
            std::string failoVardas = "studentai" + std::to_string(dydis) + ".txt";


            long laikasKuriantFaila = ilgisFunkcijosVykdymui([&]() {
                generuotiFaila(failoVardas, dydis);
            });

            std::cout << "Failo (" << dydis << " irasu) kurimas uztruko: " << laikasKuriantFaila << " ms\n";


            long laikasNuskaitymui = ilgisFunkcijosVykdymui([&]() {
                std::vector<Student> studentai = nuskaitytiIsFailo(failoVardas);
                rikiuotiPagalBalus(studentai);
            });

            std::cout << "Failo (" << dydis << " irasu) apdorojimas užtruko: " << laikasNuskaitymui << " ms\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ivyko klaida: " << e.what() << std::endl;
    }
    return 0;
}
