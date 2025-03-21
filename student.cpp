#include "student.h"
#include <numeric>
#include <algorithm>

double skaiciuotiVidurki(const std::vector<int>& paz) {
    if (paz.empty()) return 0.0;
    return std::accumulate(paz.begin(), paz.end(), 0.0) / paz.size();
}

double skaiciuotiMediana(std::vector<int> paz) {
    if (paz.empty()) return 0.0;
    std::sort(paz.begin(), paz.end());
    size_t n = paz.size();
    if (n % 2 == 0)
        return (paz[n/2 - 1] + paz[n/2]) / 2.0;
    else
        return paz[n/2];
}
