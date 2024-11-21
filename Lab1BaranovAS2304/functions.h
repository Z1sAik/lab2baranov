#pragma once
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
T check(T low, T max) {
    T z;
    cin >> z;
    cin.ignore();
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
void load(unordered_map<int, Pipe>& Pipes, int& maxPipeID);
void load2(unordered_map<int, compressor_station>& Stations, int& maxCSID);
void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType);
void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);