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
/*template <typename T>
void edit_single_object(unordered_map<int, T>& objects, const string& objectType) {
    int m = 0;
    cout << "Все " << objectType << ": " << endl;

    if (objectType == "Трубы") {
        view_objects(objects, show_Pipe);
    }
    else if (objectType == "Компрессорные станции") {
        view_objects(objects, show_cs);
    }

    cout << "Введите ID " << objectType << ", который вы хотите отредактировать: ";
    int id = check<int>(0, INT_MAX);

    auto it = objects.find(id);
    if (it != objects.end()) {
        T& obj = it->second;
        while (true) {
            cout << "Выберите параметр, который вы хотите отредактировать: " << endl;
            if (objectType == "Трубы") {
                cout << "1) Статус трубы 'в ремонте'" << endl;
            }
            else if (objectType == "Компрессорные станции") {
                cout << "1) Кол-во цехов в работе" << endl;
            }
            cout << "0) Выход в меню" << endl << "Номер команды: ";
            m = check<int>(0, 1);

            if (m == 0) {
                break;
            }
            if (m == 1) {
                if (objectType == "Трубы") {
                    cout << "Старый статус трубы: " << boolalpha << it->second.repair << endl;
                    cout << "Введите новый статус трубы (0 - не в ремонте, 1 - в ремонте): ";
                    it->second.repair = check<int>(0, 1);
                }
                else if (objectType == "Компрессорные станции") {
                    cout << "Старое кол-во цехов в работе: " << it->second.workshopsinwork << endl;
                    cout << "Введите новое кол-во цехов в работе: ";
                    int workshopsinwork = check<int>(0, it->second.workshops);
                    it->second.workshopsinwork = workshopsinwork;
                }
            }
        }
    }
    else {
        cout << objectType << " с таким ID не найдена!" << endl;
    }
}*/


int menu();

void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
void load(unordered_map<int, Pipe>& Pipes, int& maxPipeID);
void load2(unordered_map<int, compressor_station>& Stations, int& maxCSID);
void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType);
void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);