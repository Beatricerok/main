#ifndef FAILUAPDOROJIMAS_H
#define FAILUAPDOROJIMAS_H

#include <string>
#include <vector>
#include <algorithm>

#include "student.h"

// Nuskaitymo funkcija: skaito studentų duomenis iš failo.
// Tyrimams visi duomenys turi būti tie patys.
std::vector<Student> nuskaitytiIsFailo(const std::string& filename);

// Rūšiuoja studentų sąrašą didėjimo tvarka (ascending) pagal galutinį vidurkį.
void rikiuotiPagalBalus(std::vector<Student>& studentai);

// Skirsto studentus į dvi grupes:
// • Kietekai: studentai, kurių galutinis vidurkis ≥ 5.0
// • Vargšiukai: studentai, kurių galutinis vidurkis < 5.0
// Rezultatai surašomi naujuose konteineriuose.
void skirstytiStudentus(const std::vector<Student>& studentai,
                         std::vector<Student>& kietekai,
                         std::vector<Student>& vargsiukai);

// Įrašo studentų rezultatus į failą, gražiai suformatuotus.
void irasytiIFaila(const std::vector<Student>& studentai, const std::string& filename);

// ––––––– Template funkcijos skirstymui pagal strategijas –––––––

// 1 strategija: Kopijimo metodas – studentai kopijuojami į du naujus konteinerius.
template<typename Container>
void splitStudentsCopyStrategy(const Container& students, Container& kietekai, Container& vargsiukai) {
    for (const auto& s : students) {
        if (s.galutinisVid >= 5.0)
            kietekai.push_back(s);
        else
            vargsiukai.push_back(s);
    }
}

// 2 strategija: Perkėlimo metodas – jeigu studentas yra vargšiukas, jis perkeliamas į naują konteinerį
// ir ištrinamas iš pirminio. Po šio žingsnio pirminis konteineris liks tik su kietekais.
template<typename Container>
void splitStudentsMoveStrategy(Container& students, Container& vargsiukai) {
    auto it = students.begin();
    while (it != students.end()) {
        if (it->galutinisVid < 5.0) {
            vargsiukai.push_back(std::move(*it));
            it = students.erase(it);
        } else {
            ++it;
        }
    }
    // Po šio, "students" turi tik kietekus.
}

// 3 strategija: Particionavimo metodas – naudojama std::stable_partition (tinka random access iteratoriams).
// Jei konteineris neturi random access iteratorių (pvz., std::list), galima panaudoti kopijimo strategiją.
template<typename Container>
void splitStudentsPartitionStrategy(Container& students, Container& kietekai, Container& vargsiukai) {
    typedef typename std::iterator_traits<typename Container::iterator>::iterator_category category;
    if (std::is_same<category, std::random_access_iterator_tag>::value) {
        auto partitionPoint = std::stable_partition(students.begin(), students.end(), [](const Student& s) {
            return s.galutinisVid >= 5.0; // kietekai pirmi
        });
        kietekai = Container(students.begin(), partitionPoint);
        vargsiukai = Container(partitionPoint, students.end());
    } else {
        // Jei konteineris neturi random access iteratorių (pvz., std::list), naudokite kopijimo strategiją.
        splitStudentsCopyStrategy(students, kietekai, vargsiukai);
    }
}

#endif // FAILUAPDOROJIMAS_H
