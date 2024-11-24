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
    }
}

void show_Pipe(const Pipe& P) {
    cout << "ID: " << P.id << "; Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}

void menu_new_Pipe(Pipe& P) {
    P.id = ++P.maxPipeID;
    cout << "ID: " << P.id << endl;
    cout << "Введите название трубы (на английском язык): ";
    getline(cin, P.Name);
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

void edit_single_pipe(unordered_map<int, Pipe>& Pipes) {
    int id;
    cout << "Все трубы: " << endl;
    view_objects(Pipes, show_Pipe);
    cout << "Введите ID трубы, которую вы хотите отредактировать: ";
    id = check<int>(0, INT_MAX);
    auto it = Pipes.find(id);
    if (it != Pipes.end()) {
        Pipe& P = it->second;
        if (P.diameter > 0) {
            int m;
            while (true) {
                cout << "Выберите параметр, который вы хотите отредактировать: " << endl << "1) Статус 'в ремонте'" << endl<< "0) Выход в меню" << endl<< "Номер команды: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "Старый статус трубы: в ремонте " << boolalpha << P.repair << endl << "Выберите новый статус трубы: " << endl<< "0) Не в ремонте" << endl<< "1) В ремонте" << endl<< "Введите номер команды: ";
                    P.repair = check<int>(0, 1);
                }
            }
        }
    }
    else {
        cout << "Труба с таким ID не найдена!" << endl;
    }
}

void edit_filtered_pipes(unordered_map<int, Pipe>& Pipes, vector<int>& filt_keys_Pipe) {
    int m, repair;
    if (!filt_keys_Pipe.empty()) {
        cout << "Все отфильтрованные трубы: " << endl;
        view_objects_vector(filt_keys_Pipe,Pipes, show_Pipe);
        while (true) {
            cout << "Выберите параметр, который вы хотите отредактировать: " << endl<< "1) Статус 'в ремонте'" << endl<< "0) Выход в меню" << endl<< "Номер команды: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            if (m == 1) {
                cout << "Выберите новый статус трубы: " << endl<< "0) Не в ремонте" << endl<< "1) В ремонте" << endl<< "Введите номер команды: ";
                repair = check<int>(0, 1);
            }
            for (size_t i = 0; i < filt_keys_Pipe.size(); ++i) {
                auto it = Pipes.find(filt_keys_Pipe[i]);
                it->second.repair = repair;
            }
        }
    }
    else {
        cout << "Фильтр ещё не был задан" << endl;
    }
}


void edit_Pipe_filter(unordered_map<int, Pipe>& Pipes, vector<int>& filt_keys_Pipe) {
    int m = 0;
    while (true) {
        cout << "Выберите что вы хотите отредактировать: " << endl << "1) Одну из всех труб" << endl << "2) Группу отфильтрованных труб" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            edit_single_pipe(Pipes);
        }
        if (m == 2) {
            edit_filtered_pipes(Pipes, filt_keys_Pipe);
        }
    }
}

void load(unordered_map<int, Pipe>& Pipes, int& maxPipeID) {
    ifstream in("datapipecs.txt");
    if (!in.is_open()) {
        cout << "Файл не найден" << endl;
        return;
    }
    Pipes.clear();
    string line;
    while (getline(in >> ws, line)) {
        if (line == "data Pipe:") {
            loadPipe(Pipes, in, maxPipeID);
        }
    }
    if (!Pipes.empty()) {
        cout << "Данные о трубах загружены" << endl;
    }
}