#pragma once
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template <typename T, typename Param>
using Filter = bool(*)(const T&, Param);

bool filterByNameP(const Pipe& pipe,string& name);
bool filterByRepairP(const Pipe& pipe, int& repair);
bool filterByNameCS(const compressor_station& cs,string& name);
bool filterByWork(const compressor_station& cs, int& work);

template <typename T, typename Param>
void Filter_map(const unordered_map<int, T>& objects, Filter<const T&, Param&> filter, Param param, vector<int>& filteredKeys) {
    filteredKeys.clear();
    for (const auto& pair : objects) {
        if (filter(pair.second, param)) {
            filteredKeys.push_back(pair.first);
        }
    }
}

template <typename T>
T check(T low, T max) {
    T z;
    cin >> z;
    cin.ignore();
    ofstream logFile("input_log.txt", ios::app);
    if (!logFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return z;
    }

    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено число меньше минимального! Попробуйте ещё раз: ";
        }
        else if (max != 0 && z > max) {
            cout << "Ошибка. Введено число больше максимального! Попробуйте ещё раз: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
        
    }
    logFile << z << endl;
    logFile.close(); 
    return z;
}

template <typename T1, typename T2>
void objects_empty_vector(const T1& pipes, const T2& stations) {
    if (pipes.empty() && stations.empty()) {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
    else if (!pipes.empty() && stations.empty()) {
        cout << "КС еще не были добавлены!" << endl;
    }
    else if (pipes.empty() && !stations.empty()) {
        cout << "Трубы еще не были добавлены!" << endl;
    }
    else {
        return;
    }
}


template <typename T1, typename T2>
void objects_empty(const T1& pipes, const T2& stations) {
    if (pipes.empty() && stations.empty()) {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
    else if (!pipes.empty() && stations.empty()) {
        cout << "КС еще не были добавлены!" << endl;
    }
    else if (pipes.empty() && !stations.empty()) {
        cout << "Трубы еще не были добавлены!" << endl;
    }
    else {
        return;
    }
}

template <typename T, typename ShowFunc>
void view_objects(const unordered_map<int, T>& objects, ShowFunc show) {
    for (const auto& pair : objects) {
        show(pair.second);
    }
}

template <typename T, typename ShowFunc>
void view_objects_vector(const vector<int>& objects, const unordered_map<int, T>& myMap, ShowFunc show) {
    for (size_t i = 0; i < objects.size(); ++i) {
        auto it = myMap.find(objects[i]);
        if (it != myMap.end()) {
            show(it->second);
        }
        else {
            cout << "Ключ " << objects[i] << " не найден в map." << endl;
        }
    }
}

int menu();
void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations, int& maxPipeID, int& maxCSID);
void get_line(string& input);