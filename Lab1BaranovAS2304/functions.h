#pragma once
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

extern ofstream logFile;

template <typename T, typename Param>
using Filter = bool(*)(const T&, Param);

bool filterByNameP(const Pipe& pipe,string name);
bool filterByRepairP(const Pipe& pipe, int repair);
bool filterByNameCS(const compressor_station& cs,string name);
bool filterByWork(const compressor_station& cs, int work);

template <typename T, typename Param>
void Filter_map(const unordered_map<int, T>& objects, Filter<const T&, Param> filter, Param param, vector<int>& filteredKeys) {
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

    if (!logFile) {
        cerr << "Ошибка: файл не открыт для записи!" << endl;
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

template<typename T>
int get_valid_id(const vector<int>& filt_keys, const vector<int>& selected_ids) {
    while (true) {
        cout << "Введите ID: ";
        int id = check<int>(-1, INT_MAX);
        if (id == -1) return -1;

        if (find(filt_keys.begin(), filt_keys.end(), id) == filt_keys.end()) {
            cout << "ID " << id << " не найден. Попробуйте снова." << endl;
        }
        else if (find(selected_ids.begin(), selected_ids.end(), id) != selected_ids.end()) {
            cout << "ID " << id << " уже добавлен в список. Попробуйте снова." << endl;
        }
        else {
            return id;
        }
    }
}

template<typename T>
void edit_single_object(unordered_map<int, T>& objects,const vector<int>& filt_keys,void (*show_fn)(const T&),int (*edit_fn)(unordered_map<int, T>&, int, int)) {
    view_objects_vector(filt_keys, objects, show_fn);
    vector<int> selected_ids;
    int id = get_valid_id<T>(filt_keys, selected_ids);

    while (true) {
        cout << "Введите новое значение: ";
        int workshopsinwork = check(0, INT_MAX);
        if (edit_fn(objects, id, workshopsinwork)) {
            cout << "Изменения успешно применены!" << endl;
            break;
        }
    }
}

template<typename T>
void edit_group_objects(unordered_map<int, T>& objects,const vector<int>& filt_keys,void (*show_fn)(const T&),int (*edit_fn)(unordered_map<int, T>&, int, int)) {
    view_objects_vector(filt_keys, objects, show_fn);
    vector<int> selected_ids;
    cout << "Для остановки ввода введите -1 для завершения" << endl;
    while (true) {
        int id = get_valid_id<T>(filt_keys, selected_ids);
        if (id == -1) break;
        selected_ids.push_back(id);
    }

    if (selected_ids.empty()) {
        cout << "Не было введено ни одного корректного ID." << endl;
        return;
    }
    cout << "Введите новое значение: ";
    int workshopsinwork = check(0, INT_MAX);
    for (int id : selected_ids) {
        if (edit_fn(objects, id, workshopsinwork)) {
            cout << "Изменения успешно применены для объекта с ID: " << id << endl;
        }
        else {
            cout << "Ошибка при редактировании объекта с ID: " << id << endl;
        }
    }
}

template<typename T>
void edit_filtered_objects(unordered_map<int, T>& objects,vector<int> filt_keys,void (*show_fn)(const T&),int (*edit_fn)(unordered_map<int, T>&, int, int)) {
    if (filt_keys.empty()) {
        cout << "Фильтр ещё не был задан" << endl;
        return;
    }

    while (true) {
        cout << "1) Один объект" << endl << "2) Группа объектов" << endl << "0) Выход" << endl << "Номер команды: ";
        int m = check<int>(0, 2);
        if (m == 0) break;

        if (m == 1) {
            edit_single_object(objects, filt_keys, show_fn, edit_fn);
        }
        else if (m == 2) {
            edit_group_objects(objects, filt_keys, show_fn, edit_fn);
        }
    }
}

template<typename T>
void remove_objects_by_ids(unordered_map<int, T>& objects, const vector<int>& filt_keys) {
    vector<int> selected_ids;
    while (true) {
        int id = get_valid_id<T>(filt_keys, selected_ids);
        if (id == -1) break;
        selected_ids.push_back(id);
    }

    for (int id : selected_ids) {
        auto it = objects.find(id);
        if (it != objects.end()) {
            objects.erase(it);
            cout << "Объект с ID " << id << " успешно удален." << endl;
        }
        else {
            cout << "Объект с ID " << id << " не найден." << endl;
        }
    }
}

int menu();
void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations);
void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);
void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations, int& maxPipeID, int& maxCSID);
void get_line(string& input);
string generate_filename();
void remove_objects(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS);