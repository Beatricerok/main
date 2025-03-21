#include "failuapdorojimas.h"
#include "student.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <string>

// Matavimo funkcija – grąžina vykdymo trukmę milisekundėmis.
template <typename Func>
long measureExecutionTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Pagalbinių funkcijų: konvertuoja std::list arba std::deque į std::vector, kad būtų galima panaudoti išvedimo funkciją.
template <typename Container>
std::vector<Student> toVector(const Container& cont) {
    return std::vector<Student>(cont.begin(), cont.end());
}

int main() {
    try {
        // Testavimo failų pavadinimai – visi tyrimams naudojami tie patys duomenys.
        std::vector<std::string> failai = {
            "studentai100.txt",
            "studentai1000.txt",
            "studentai10000.txt",
            "studentai100000.txt"
        };

        for (const auto& filename : failai) {
            // Pradiniai duomenys visada skaitomi į std::vector<Student>
            std::vector<Student> original = nuskaitytiIsFailo(filename);

            // ----- TESTAI SU std::vector -----
            {
                // 1 strategija: Copy
                std::vector<Student> vCopy = original;
                std::vector<Student> kietekai, vargsiukai;
                long t = measureExecutionTime([&]() {
                    splitStudentsCopyStrategy(vCopy, kietekai, vargsiukai);
                });
                irasytiIFaila(kietekai, "vector_copy_kietekai_" + filename);
                irasytiIFaila(vargsiukai, "vector_copy_vargsiukai_" + filename);
                std::cout << "std::vector, Copy strategija (" << filename << "): " << t << " ms\n";
            }
            {
                // 2 strategija: Move
                std::vector<Student> vMove = original;
                std::vector<Student> vargsiukai;
                long t = measureExecutionTime([&]() {
                    splitStudentsMoveStrategy(vMove, vargsiukai);
                });
                // Po move, vMove turėtų likti tik su kietekais.
                irasytiIFaila(vMove, "vector_move_kietekai_" + filename);
                irasytiIFaila(vargsiukai, "vector_move_vargsiukai_" + filename);
                std::cout << "std::vector, Move strategija (" << filename << "): " << t << " ms\n";
            }
            {
                // 3 strategija: Partition
                std::vector<Student> vPart = original;
                std::vector<Student> kietekai, vargsiukai;
                long t = measureExecutionTime([&]() {
                    splitStudentsPartitionStrategy(vPart, kietekai, vargsiukai);
                });
                irasytiIFaila(kietekai, "vector_partition_kietekai_" + filename);
                irasytiIFaila(vargsiukai, "vector_partition_vargsiukai_" + filename);
                std::cout << "std::vector, Partition strategija (" << filename << "): " << t << " ms\n";
            }

            // ----- TESTAI SU std::list -----
            {
                std::list<Student> lCopy(original.begin(), original.end());
                std::list<Student> kietekai, vargsiukai;
                long t = measureExecutionTime([&]() {
                    splitStudentsCopyStrategy(lCopy, kietekai, vargsiukai);
                });
                // Konvertuojame į vector išvedimui
                irasytiIFaila(toVector(kietekai), "list_copy_kietekai_" + filename);
                irasytiIFaila(toVector(vargsiukai), "list_copy_vargsiukai_" + filename);
                std::cout << "std::list, Copy strategija (" << filename << "): " << t << " ms\n";
            }

            // ----- TESTAI SU std::deque -----
            {
                std::deque<Student> dCopy(original.begin(), original.end());
                std::deque<Student> kietekai, vargsiukai;
                long t = measureExecutionTime([&]() {
                    splitStudentsCopyStrategy(dCopy, kietekai, vargsiukai);
                });
                irasytiIFaila(toVector(kietekai), "deque_copy_kietekai_" + filename);
                irasytiIFaila(toVector(vargsiukai), "deque_copy_vargsiukai_" + filename);
                std::cout << "std::deque, Copy strategija (" << filename << "): " << t << " ms\n";
            }

            // Galite panašiai implementuoti Move ir Partition strategijas ir su std::list bei std::deque,
            // tačiau tai gali būti papildomai – atsižvelgiant į konteinerio savybes (pvz., list savybes leidžia O(1) trynimą).
        }
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
    }
    return 0;
}
