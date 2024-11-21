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
    cout << "ID: " << P.id << "; �������� �����: " << P.Name << "; ����� �����: " << P.length << "; ������� �����: " << P.diameter << "; ������ '� �������': " << boolalpha << P.repair << endl;
}

void menu_new_Pipe(Pipe& P) {
    P.id = ++P.maxPipeID;
    cout << "ID: " << P.id << endl;
    cout << "������� �������� ����� (�� ���������� ����): ";
    getline(cin, P.Name);
    cout << "������� ����� ����� � ����������: ";
    P.length = check<float>(0.1, 0);
    cout << "������� ������� ����� � �����������: ";
    P.diameter = check<int>(1, 0);
    cout << "�������� � ����� ��������� �����: " << endl << "0)�� � �������" << endl << "1)� �������" << endl;
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
    cout << "��� �����: " << endl;
    view_objects(Pipes, show_Pipe);
    cout << "������� ID �����, ������� �� ������ ���������������: ";
    id = check<int>(0, INT_MAX);
    auto it = Pipes.find(id);
    if (it != Pipes.end()) {
        Pipe& P = it->second;
        if (P.diameter > 0) {
            int m;
            while (true) {
                cout << "�������� ��������, ������� �� ������ ���������������: " << endl << "1) ������ '� �������'" << endl<< "0) ����� � ����" << endl<< "����� �������: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "������ ������ �����: � ������� " << boolalpha << P.repair << endl << "�������� ����� ������ �����: " << endl<< "0) �� � �������" << endl<< "1) � �������" << endl<< "������� ����� �������: ";
                    P.repair = check<int>(0, 1);
                }
            }
        }
    }
    else {
        cout << "����� � ����� ID �� �������!" << endl;
    }
}

void edit_filtered_pipes(unordered_map<int, Pipe>& Pipes, vector<int>& filt_keys_Pipe) {
    int m, repair;
    if (!filt_keys_Pipe.empty()) {
        cout << "��� ��������������� �����: " << endl;
        view_objects_vector(filt_keys_Pipe,Pipes, show_Pipe);
        while (true) {
            cout << "�������� ��������, ������� �� ������ ���������������: " << endl<< "1) ������ '� �������'" << endl<< "0) ����� � ����" << endl<< "����� �������: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            if (m == 1) {
                cout << "�������� ����� ������ �����: " << endl<< "0) �� � �������" << endl<< "1) � �������" << endl<< "������� ����� �������: ";
                repair = check<int>(0, 1);
            }
            for (size_t i = 0; i < filt_keys_Pipe.size(); ++i) {
                auto it = Pipes.find(filt_keys_Pipe[i]);
                it->second.repair = repair;
            }
        }
    }
    else {
        cout << "������ ��� �� ��� �����" << endl;
    }
}


void edit_Pipe_filter(unordered_map<int, Pipe>& Pipes, vector<int>& filt_keys_Pipe) {
    int m = 0;
    while (true) {
        cout << "�������� ��� �� ������ ���������������: " << endl << "1) ���� �� ���� ����" << endl << "2) ������ ��������������� ����" << endl << "0) �����" << endl;
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
        cout << "���� �� ������" << endl;
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
        cout << "������ � ������ ���������" << endl;
    }
}