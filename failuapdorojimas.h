#ifndef FAILU_APDOROJIMAS_H
#define FAILU_APDOROJIMAS_H

#include "student.h"
#include <vector>
#include <string>
#include <functional>

void generuotiFaila(const std::string& failoVardas, int skaicius);
std::vector<Student> nuskaitytiIsFailo(const std::string& failoVardas);
void irasytiIFaila(const std::vector<Student>& studentai, const std::string& failoVardas);
void rikiuotiPagalBalus(std::vector<Student>& studentai);
long ilgisFunkcijosVykdymui(std::function<void()> funkcija);

#endif

