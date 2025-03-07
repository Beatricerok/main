#include <algorithm>

void rikiuotiPagalBalus(std::vector<Student>& studentai) {
    std::vector<Student> vargsiukai;
    std::vector<Student> kietiakiai;

    for (const auto& studentas : studentai) {
        if (studentas.galutinisVid < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakiai.push_back(studentas);
        }
    }


    std::sort(vargsiukai.begin(), vargsiukai.end(), [](const Student& a, const Student& b) {
        return a.galutinisVid > b.galutinisVid;
    });

    std::sort(kietiakiai.begin(), kietiakiai.end(), [](const Student& a, const Student& b) {
        return a.galutinisVid > b.galutinisVid;
    });

    irasytiIFaila(vargsiukai, "vargsiukai.txt");
    irasytiIFaila(kietiakiai, "kietiakiai.txt");
}

