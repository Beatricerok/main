#ifndef FAILU_APDOROJIMAS_H
#define FAILU_APDOROJIMAS_H

#include "student.h"
#include <vector>
#include <string>

std::vector<Student> nuskaitytiIsFailo(const std::string& failoVardas);
void irasytiIFaila(const std::vector<Student>& studentai, const std::string& failoVardas);

#endif // FAILU_APDOROJIMAS_H

