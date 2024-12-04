#pragma once
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
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

bool filterByNameP(const Pipe& P, string name);
bool filterByRepairP(const Pipe& P, int repair);
bool filterByNameCS(const compressor_station& CS, string name);
bool filterByWork(const compressor_station& CS, float work);

template<typename T, typename U>
unordered_set<int> findwithFilter(const unordered_map<int, T>& map, bool (*f)(const T&, U), U param)
{
    unordered_set<int> res;
    for (const auto& [id, val] : map) {
        if (f(val, param)) {
            res.emplace(id);
        }
    }
    return res;
}

template<typename T>
unordered_set<int> selectByChosenID(unordered_map<int, T>& map, unordered_set<int>& set = {})
{
    unordered_set<int> res;
    cout << "Введите нужные вам ID (для остановки введите -1)" << endl;
    while (true)
    {
        int id = check<int>(0,INT_MAX);
        if (id == -1)
            break;
        if (set.size() == 0)
        {
            if (map.contains(id)) res.emplace(id);
        }
        else
            if (map.contains(id) and set.contains(id)) res.emplace(id);
    }
    return res;
}
void coutFoundWithId(unordered_set<int>& set)
{
    cout << "Найденные объекты с ID: ";
    for (int id : set)
        cout << id << " ";
    cout << endl;
}

template<typename T>
void editSelected(unordered_map<int, T>& map, unordered_set<int>& set) {
    int m = 0;
    cout << "Выберите что вы хотите сделать:" << endl << "1) Посмотреть что содержится в фильтре" << endl << "2)Отредактировать отфильтрованные объекты" << endl << "3) Удалить отфильтрованные объекты" << endl "0)Выход" << endl << "Введите команду: ";
    while (true) {
        if (m == 0) {
            break;
        }
        if (m == 1) {
            for (int id : set)
                cout << map[id];
            break;
        }
        if (m == 2) {
            editMap(map);
            break;
        }
        if (m == 3) {
            for (int id : set)
                map.erase(id);
            break;
        }
    }
}

int menu();
string get_line(istream& in);
//string generate_filename();
void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
