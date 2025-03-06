
#include "student.h"
#include <algorithm>
#include <numeric>

// Funkcija vidurkiui skaiciuoti
double skaiciuotiVidurki(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

// Funkcija medianai skaiciuoti
double skaiciuotiMediana(std::vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    size_t dydis = paz.size();
    if (dydis % 2 == 0) {
        return (paz[dydis / 2 - 1] + paz[dydis / 2]) / 2.0;
    } else {
        return paz[dydis / 2];
    }
}
