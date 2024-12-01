#include "functions.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

int Pipe::maxPipeID = 0;

void SavePipe(int pipeID, const Pipe& P, ofstream& out)
{
    out << pipeID << endl;
    out << P.Name << endl;
    out << P.length << " " << P.diameter << " " << P.repair << endl;
}

void loadPipe(unordered_map<int, Pipe>& Pipes, ifstream& in, int& maxPipeID) {
    if (in.is_open()) {
        int id;
        Pipe P; 
        while (in >> id) {
            P.id = id;
            getline(in >> ws, P.Name);
            in >> P.length >> P.diameter >> P.repair;
            Pipes[id] = P;
            if (id > maxPipeID) {
                maxPipeID = id;
            }
        }
        in.clear();
    }
}

void show_Pipe(const Pipe& P) {
    cout << "ID: " << P.id << "; Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}

void menu_new_Pipe(Pipe& P) {
    P.id = ++P.maxPipeID;
    cout << "ID: " << P.id << endl;
    cout << "Введите название трубы (на английском язык): ";
    get_line(P.Name);
    cout << "Введите длину трубы в километрах: ";
    P.length = check<float>(0.1, 0);
    cout << "Введите диаметр трубы в миллиметрах: ";
    P.diameter = check<int>(1, 0);
    cout << "Выберите в каком состоянии труба: " << endl << "0)Не в ремонте" << endl << "1)В ремонте" << endl;
    P.repair = check<int>(0, 1);
    show_Pipe(P);
}

void filter_P(const unordered_map<int, Pipe>& Pipes, string Name_def, int rep_def, vector<int>& filt_keys) {
    for (const auto& pair : Pipes) {
        bool name = Name_def.empty() || pair.second.Name == Name_def;
        bool repair = (rep_def == 3) || (pair.second.repair == rep_def);
        if (name && repair) {
            filt_keys.push_back(pair.first);
        }
    }
}

int edit_single_Pipe(unordered_map<int, Pipe>& Pipes, int id, int repair) {
    auto it = Pipes.find(id);
    if (it != Pipes.end()) {
        Pipe& P = it->second;
        if (repair > 1) {
            cout << "Неверно введено значение 'в работе!'" << endl;
            return 0;
        }
        else {
            P.repair = repair;
            return 1;
        }
    }
    else {
        cout << "Труба с таким ID не найдена!" << endl;
        return 0;
    }
}
