#include "functions.h"
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>

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
            << "9) Удаление объектов" << endl
            << "0) Выход" << endl
            << "Введите команду которую вы бы хотели выполнить(от 0 до 9): ";
        k = check<int>(0, 9);
        return k;
    }
}

string get_line(istream& in) {
    string input;
    getline(in >> ws, input);
    cerr << input << endl;
    return input;
}

/*string generate_filename() {
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
}*/

void save(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations) {
    string filename;
    cout << "Введите имя файла для сохранения: ";
    filename = get_line(cin);
    filename += ".txt";
    ofstream out;
    out.open(filename);
    if (out.is_open()) {
        out << "data Pipe:" << endl;
        saveMap(out, Pipes);
        out << "end data" << endl;
        out << "data CS:" << endl;
        saveMap(out, Stations);
        out << "end data" << endl;
        cout << "Данные сохранены в файл: " << filename << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи!" << endl;
    }
    out.close();
}

void load(unordered_map<int, Pipe>& Pipes, unordered_map<int, compressor_station>& Stations) {
    string filename;
    cout << "Введите имя файла для загрузки: ";
    filename = get_line(cin);

    if (filename.find(".txt") == string::npos) {
        filename += ".txt";
    }

    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Файл " << filename << " не найден!" << endl;
        return;
    }
    Pipe::resetMaxID();
    compressor_station::resetMaxID();
    Stations.clear();
    Pipes.clear();
    string line;
    while (getline(in >> ws, line)) {
        if (line == "data Pipe:") {
            loadMap(in, Pipes);
        }
        if (line == "data CS:") {
            loadMap(in, Stations);
        }
    }
    if (!Pipes.empty() || !Stations.empty()) {
        cout << "Данные загружены из файла: " << filename << endl;
    }

    in.close();
}

bool filterByNameP(const Pipe& P, string name) {
    size_t pos = P.getName().find(name);
    return pos != string::npos;
}

bool filterByRepairP(const Pipe& P, int repair) {
    return P.getRepair() == repair;
}

bool filterByNameCS(const compressor_station& CS, string name) {
    size_t pos = CS.getName().find(name);
    return pos != string::npos;
}

bool filterByWork(const compressor_station& CS, float work) {
    return CS.notinwork() == work;
}
