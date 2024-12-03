#include "functions.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

int Pipe::maxID = 0;

std::ostream& operator<<(std::ostream& out, const Pipe& P) {
    out << "Pipe ID = " << P.id << endl
        << "Имя: " << P.Name << endl
        << "Длина: " << P.length << endl
        << "Диаметр: " << P.diameter << endl
        << "Efficiency: " << P.repair << endl;
    return out;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipe& P) {
    if (fout.is_open()) {
        fout << P.id << endl
            << P.Name << endl
            << P.length << endl
            << P.diameter << endl
            << P.repair << endl;
    }
    return fout;
}

std::istream& operator>>(std::istream& in, Pipe& P) {
    cout << "Создание новой трубы" << endl;
    cout << "ID: " << P.id << endl;
    cout << "Введите название трубы (на английском язык): ";
    get_line(P.Name);
    cout << "Введите длину трубы в километрах: ";
    P.length = check<float>(0.1, 0);
    cout << "Введите диаметр трубы в миллиметрах: ";
    P.diameter = check<int>(1, 0);
    cout << "Выберите в каком состоянии труба: " << endl << "0)Не в ремонте" << endl << "1)В ремонте" << endl;
    P.repair = check<int>(0, 1);
    return in;
}

std::ifstream& operator>>(std::ifstream& fin, Pipe& P) {
    if (fin.is_open()) {
        fin >> P.id;
        fin.ignore();
        getline(fin, P.Name);
        fin >> P.length;
        fin >> P.diameter;
        fin >> P.repair;
    }
    return fin;
}

Pipe Pipe::newPipe()
{
    Pipe P;
    cin >> P;
    return P;
}

void Pipe::resetMaxID()
{
    maxID = 0;
}

void Pipe::editPipe()
{
    repair = !repair;
}
