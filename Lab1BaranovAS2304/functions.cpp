#include "functions.h"
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

ofstream logFile;

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
    string filename;
    cout << "Введите имя файла для сохранения: ";
    get_line(filename);

    ofstream out;
    out.open(filename);
    if (out.is_open()) {
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
        cout << "Данные сохранены в файл: " << filename << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи!" << endl;
    }
    out.close();
}

void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType) {
    while (true) {
        cout << "Выберите фильтр для " << ObjectType << ":" << endl;
        cout << "1) По имени (" << (!Name_Filter.empty() ? "Заполнен" : "Не заполнен") << ")" << endl;
        cout << "2) По статусу (" << (Status_Filter >= 0 ? "Заполнен" : "Не заполнен") << ")" << endl;
        cout << "3) Сбросить фильтры" << endl;
        cout << "0) Выход" << endl;
        int m = check<int>(0, 3);
        if (m == 1) {
            cout << "Введите имя для фильтрации: ";
            get_line(Name_Filter);
        }
        if (m == 2) {
            if (ObjectType == "трубы") {
                cout << "Введите статус для фильтрации (0 = Не в ремонте, 1 = В ремонте): ";
                Status_Filter = check<int>(0, 1);
            }
            else {
                cout << "Введите процент нерабочих цехов для фильтрации (0–100): ";
                Status_Filter = check<int>(0, 100);
            }
        }
        if (m == 3) {
            Name_Filter = "";
            Status_Filter = (ObjectType == "трубы" ? -1 : -2);
            cout << "Фильтры для " << ObjectType << " сброшены." << endl;
        }
        if (m == 0) {
            break;
        }
    }    
}

bool filterByNameP(const Pipe& pipe, string& name) {
    return pipe.Name == name;
}

bool filterByRepairP(const Pipe& pipe, int& repair) {
    return pipe.repair == repair;
}

bool filterByNameCS(const compressor_station& cs, string& name) {
    return cs.Name == name;
}

bool filterByWork(const compressor_station& cs, int& work) {
    return cs.workshopsinwork == work;
}


void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, vector<int>& filt_keys_Pipe, vector<int>& filt_keys_CS) {
    string Name_P = "";
    int Repair_P = -1;
    string Name_CS = "";
    int work_CS = -2;
    int m = 0;
    while (true) {
        cout << "Выберите, для какого объекта вы хотите задать фильтры:" << endl<< "1) Фильтр для трубы" << endl<< "2) Фильтр для КС" << endl<< "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 1) {
            setFilterParams(Name_P, Repair_P, "трубы");
            if (!Name_P.empty()) {
                Filter_map(Pipes,filterByNameP, Name_P, filt_keys_Pipe);
            }
            if (Repair_P != -1) {
                Filter_map(Pipes, filterByRepairP, Repair_P, filt_keys_Pipe);
            }
        }
        else if (m == 2) {
            setFilterParams(Name_CS, work_CS, "КС");
            if (!Name_CS.empty()) {
                Filter_map(Stations,filterByNameCS, Name_CS, filt_keys_CS);
            }
            if (work_CS != -2) {
                Filter_map(Stations, filterByWork, work_CS, filt_keys_CS);
            }
        }
        else if (m == 0) {
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

void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations, int& maxPipeID, int& maxCSID) {
    string filename;
    cout << "Введите имя файла для загрузки: ";
    get_line(filename);

    if (filename.find(".txt") == string::npos) {
        filename += ".txt";
    }

    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл " << filename << " не найден!" << endl;
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
        cout << "Данные загружены из файла: " << filename << endl;
    }

    in.close();
}

void get_line(string& input) {
    if (!logFile) {
        cerr << "Ошибка: файл не открыт для записи!" << endl;
        return;
    }
    getline(cin >> ws, input);
    logFile << input << endl;
}

string generate_filename() {
    time_t now = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);

    stringstream ss;
    ss << "log_"
        << localTime.tm_year + 1900 << "-"
        << localTime.tm_mon + 1 << "-"
        << localTime.tm_mday << "_"
        << localTime.tm_hour << "-"
        << localTime.tm_min << "-"
        << localTime.tm_sec << ".txt";

    return ss.str();
}