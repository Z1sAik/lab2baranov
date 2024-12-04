#pragma once
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T, typename Param>
using Filter = bool(*)(const T&, Param);

template <typename T>
T check(T low, T max) {
    T z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cerr << z << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено число меньше минимального! Попробуйте ещё раз: ";
            cerr << z  << endl;
        }
        else if (z > max) {
            cout << "Ошибка. Введено число больше максимального! Попробуйте ещё раз: ";
            cerr << z << endl;
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

template <typename T>
void view(const unordered_map<int, T>& map) {
    if (!map.empty()) {
        for (auto& [id, val] : map)
        {
            cout << val;
        }
    }
    else {
        cout << "Вы ещё не добавили ни одного объекта!" << endl;
    }
}

template<typename T>
void saveMap(ofstream& fout, const unordered_map<int, T>& map)
{
	for (auto& [id, val] : map)
	{
		fout << val;
	}
}

template<typename T>
void loadMap(ifstream& fin, unordered_map<int, T>& map) {
    T val;
    while (fin >> val) {
        int id = val.getID();
        map.emplace(id, val);
        if (id > T::getmaxID()) {
            T::setmaxID(id);
        }
    }
    fin.clear();
}

int menu();
string get_line(istream& in);
//string generate_filename();
void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
