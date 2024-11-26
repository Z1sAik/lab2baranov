#include "functions.h"
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;


int menu() {
    int k = -1;
    while (true) {
        cout << "///////  Меню  ///////" << endl
            << "1) Добавить трубу" << endl
            << "2) Добавить КС" << endl
            << "3) Задать фильтр" << endl
            << "4) Просмотр объектов" << endl
            << "5) Редактировать трубу" << endl
            << "6) Редактировать КС" << endl
            << "7) Сохранить данные" << endl
            << "8) Загрузить данные" << endl
            << "0) Выход" << endl
            << "Введите команду которую вы бы хотели выполнить(от 0 до 8): ";
        k = check<int>(0, 8);
        return k;
    }
}


void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations) {
    ofstream out;
    out.open("datapipecs.txt");
    if (out.is_open())
    {
        objects_empty(Pipes, Stations);
        out << "data Pipe:" << endl;
        for (auto& pair : Pipes) {
            SavePipe(pair.first, pair.second, out);
        }
        out << "end data" << endl;
        out << "data CS:" << endl;
        for (auto& pair : Stations) {
            SaveCS(pair.first, pair.second, out);
        }
        out << "end data" << endl;
        cout << "Данные сохранены!" << endl;
    }
    out.close();
}

void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType) {
    int m = 0;
    while (true) {
        cout << "Какой фильтр для " << ObjectType << " вы хотите задать:" << endl << "1) По имени (" << (!Name_Filter.empty() ? "Заполнен" : "Не заполнен") << ")" << endl << "2) По статусу (" << (Status_Filter != -1 && Status_Filter != -2 ? "Заполнен" : "Не заполнен") << ")" << endl << "3) Сбросить фильтр" << endl << "0) Выход" << endl;
        m = check<int>(0, 3);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            cout << "Введите имя по которому вы будете фильтровать " << ObjectType << ": ";
            getline(cin, Name_Filter);
        }
        else if (m == 2) {
            cout << "Введите статус для фильтрации (" << (ObjectType == "трубы" ? "0 = Не в ремонте, 1 = В ремонте" : "Введите процент цехов, не в работе") << "): ";
            Status_Filter = check<int>(0, (ObjectType == "трубы" ? 1 : 100));
        }
        else if (m == 3) {
            if (ObjectType == "труба") {
                Name_Filter = "";
                Status_Filter = -1;
                cout << "Фильтр для " << ObjectType << " сброшен!" << endl;
            }
            else {
                Name_Filter = "";
                Status_Filter = -2;
                cout << "Фильтр для " << ObjectType << " сброшен!" << endl;
            }
        }
    }
}

void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe,vector<int>& filt_keys_CS) {
    string Name_P = "";
    int Repair_P = -1;
    string Name_CS = "";
    int work_CS = -2;
    int m = 0;
    while (true) {
        cout << "Выберите, для какого объекта вы хотите задать фильтры:" << endl << "1) Фильтр для трубы" << endl << "2) Фильтр для КС"<< endl << "0) Выход" << endl;
        m = check<int>(0, 2);

        if (m == 1) {
            setFilterParams(Name_P, Repair_P, "трубы");
        }
        else if (m == 2) {
            setFilterParams(Name_CS, work_CS, "КС");
        }
        else if (m == 0) {
            filter_P(Pipes, Name_P, Repair_P, filt_keys_Pipe);
            filter_CS(Stations, Name_CS, work_CS, filt_keys_CS);
            break;
        }
    }
}

void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int> &filt_keys_Pipe, vector<int>& filt_keys_CS) {
    int m = 0;
    while (true) {
        cout << "Что вы хотите просмотреть?:" << endl << "1) Все объекты" << endl << "2) Объекты заданные по фильтру" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            if (!Pipes.empty()) {
                cout << "Все трубы: " << endl;
                view_objects(Pipes, show_Pipe);
            }
            if (!Stations.empty()) {
                cout << "Все компрессорные станции: " << endl;
                view_objects(Stations, show_cs);
            }
            objects_empty(Pipes, Stations);
        }
        if (m == 2) {
            if (!filt_keys_Pipe.empty()) {
                cout << "Все отфильтрованные трубы: " << endl;
                view_objects_vector(filt_keys_Pipe, Pipes, show_Pipe);
            }
            if (!filt_keys_CS.empty()) {
                cout << "Все отфильтрованные компрессорные станции: " << endl;
                view_objects_vector(filt_keys_CS, Stations, show_cs);
            }
            objects_empty_vector(filt_keys_Pipe, filt_keys_CS);
        }
    } 
}

void load(unordered_map<int, Pipe>& Pipes, unordered_map<int,compressor_station>& Stations, int& maxPipeID, int& maxCSID) {
    ifstream in("datapipecs.txt");
    if (!in.is_open()) {
        cout << "Файл не найден" << endl;
        return;
    }
    Stations.clear();
    Pipes.clear();
    string line;
    while (getline(in >> ws, line)) {
        if (line == "data Pipe:") {
            loadPipe(Pipes, in, maxPipeID);
        }
        if (line == "data CS:") {
            loadCS(Stations, in, maxCSID);
        }
    }
    if (!Pipes.empty() || !Stations.empty()) {
        cout << "Данные загружены" << endl;
    }
}