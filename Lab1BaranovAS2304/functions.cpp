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
        cout << "///////  ����  ///////" << endl
            << "1) �������� �����" << endl
            << "2) �������� ��" << endl
            << "3) ������ ������" << endl
            << "4) �������� ��������" << endl
            << "5) ������������� �����" << endl
            << "6) ������������� ��" << endl
            << "7) ��������� ������" << endl
            << "8) ��������� ������" << endl
            << "0) �����" << endl
            << "������� ������� ������� �� �� ������ ���������(�� 0 �� 8): ";
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
        out << "data CS:" << endl;
        for (auto& pair : Stations) {
            SaveCS(pair.first, pair.second, out);
        }
        cout << "������ ���������!" << endl;
    }
    out.close();
}

void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType) {
    int m = 0;
    while (true) {
        cout << "����� ������ ��� " << ObjectType << " �� ������ ������:" << endl << "1) �� ����� (" << (!Name_Filter.empty() ? "��������" : "�� ��������") << ")" << endl << "2) �� ������� (" << (Status_Filter != -1 && Status_Filter != -2 ? "��������" : "�� ��������") << ")" << endl << "3) �������� ������" << endl << "0) �����" << endl;
        m = check<int>(0, 3);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            cout << "������� ��� �� �������� �� ������ ����������� " << ObjectType << ": ";
            getline(cin, Name_Filter);
        }
        else if (m == 2) {
            cout << "������� ������ ��� ���������� (" << (ObjectType == "�����" ? "0 = �� � �������, 1 = � �������" : "������� ������� �����, �� � ������") << "): ";
            Status_Filter = check<int>(0, (ObjectType == "�����" ? 1 : 100));
        }
        else if (m == 3) {
            if (ObjectType == "�����") {
                Name_Filter = "";
                Status_Filter = -1;
                cout << "������ ��� " << ObjectType << " �������!" << endl;
            }
            else {
                Name_Filter = "";
                Status_Filter = -2;
                cout << "������ ��� " << ObjectType << " �������!" << endl;
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
        cout << "��������, ��� ������ ������� �� ������ ������ �������:" << endl << "1) ������ ��� �����" << endl << "2) ������ ��� ��"<< endl << "0) �����" << endl;
        m = check<int>(0, 2);

        if (m == 1) {
            setFilterParams(Name_P, Repair_P, "�����");
        }
        else if (m == 2) {
            setFilterParams(Name_CS, work_CS, "��");
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
        cout << "��� �� ������ �����������?:" << endl << "1) ��� �������" << endl << "2) ������� �������� �� �������" << endl << "0) �����" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            if (!Pipes.empty()) {
                cout << "��� �����: " << endl;
                view_objects(Pipes, show_Pipe);
            }
            if (!Stations.empty()) {
                cout << "��� ������������� �������: " << endl;
                view_objects(Stations, show_cs);
            }
            objects_empty(Pipes, Stations);
        }
        if (m == 2) {
            if (!filt_keys_Pipe.empty()) {
                cout << "��� ��������������� �����: " << endl;
                view_objects_vector(filt_keys_Pipe, Pipes, show_Pipe);
            }
            if (!filt_keys_CS.empty()) {
                cout << "��� ��������������� ������������� �������: " << endl;
                view_objects_vector(filt_keys_CS, Stations, show_cs);
            }
            objects_empty_vector(filt_keys_Pipe, filt_keys_CS);
        }
    }
}