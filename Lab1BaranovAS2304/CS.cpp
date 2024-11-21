#include "functions.h"
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

int compressor_station::maxCSID = 0;

void SaveCS(int CSID, const compressor_station& CS, ofstream& out)
{
    out << CSID << endl;
    out << CS.Name << endl;
    out << CS.workshops << " " << CS.workshopsinwork << " " << CS.effectiveness << endl;
}

void loadCS(unordered_map<int, compressor_station>& Stations, ifstream& in, int& maxCSID) {
    if (in.is_open()) {
        int id;
        compressor_station CS;
        while (in >> id) {
            getline(in >> ws, CS.Name);
            in >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
            Stations[id] = CS;
            if (id > maxCSID) {
                maxCSID = id;
            }
        }
    }
}

void show_cs(const compressor_station& CS) {
    cout << "�������� ��: " << CS.Name << "; ���-�� �����: " << CS.workshops << "; ���-�� ����� � ������: " << CS.workshopsinwork << "; ����������� ������������� ��: " << CS.effectiveness << endl;
}

void menu_new_ks(compressor_station& CS) {
    CS.id = ++CS.maxCSID;
    cout << "ID: " << CS.id << endl;
    cout << "������� �������� ������������� ������� (�� ���������� ����): ";
    getline(cin, CS.Name);
    cout << "������� ���-�� �����: ";
    CS.workshops = check<int>(1, 0);
    cout << "������� ���-�� ����� � ������: ";
    CS.workshopsinwork = check<int>(0, CS.workshops);
    cout << "������� ����������� ������������� ��(�� 0 �� 100): ";
    CS.effectiveness = check<int>(0, 100);
    show_cs(CS);
}

void filter_CS(const unordered_map<int, compressor_station>& Stations, string Name_def, int work, vector<int>& filt_keys) {
    for (const auto& pair : Stations) {
        bool name = Name_def.empty() || pair.second.Name == Name_def;
        bool eff = (work == -1) || ((100 - (float(pair.second.workshopsinwork) / float(pair.second.workshops)) * 100) == work);
        if (name && eff) {
            filt_keys.push_back(pair.first);
        }
    }
}

void edit_single_CS(unordered_map<int, compressor_station>& Stations) {
    int m = 0;
    cout << "��� ������������� �������: " << endl;
    view_objects(Stations, show_cs);
    cout << "������� ID ������������� �������, ������� �� ������ ���������������: ";
    int id = check<int>(0, INT_MAX);
    auto it = Stations.find(id);
    if (it != Stations.end()) {
        compressor_station& CS = it->second;
        if (CS.workshops > 0) {
            while (true) {
                cout << "�������� ��������, ������� �� ������ ���������������: " << endl<< "1) ���-�� ����� � ������" << endl<< "0) ����� � ����" << endl<< "����� �������: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "������ ���-�� ����� � ������: " << CS.workshopsinwork << endl
                        << "������� ����� ���-�� ����� � ������: ";
                    int workshopsinwork = check<int>(0, CS.workshops);
                    CS.workshopsinwork = workshopsinwork;
                }
            }
        }
    }
    else {
        cout << "������������� ������� � ����� ID �� �������!" << endl;
    }
}

void edit_filtered_CS(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS) {
    int m = 0;
    if (!filt_keys_CS.empty()) {
        cout << "��� ��������������� ������������� �������: " << endl;
        view_objects_vector(filt_keys_CS, Stations, show_cs);
        while (true) {
            cout << "�������� ��������, ������� �� ������ ���������������: " << endl<< "1) ���-�� ����� � ������" << endl<< "0) ����� � ����" << endl<< "����� �������: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            if (m == 1) {
                cout << "������� ����� ���-�� ����� � ������: ";
                int workshopsinwork = check<int>(0, INT_MAX);
                for (size_t i = 0; i < filt_keys_CS.size(); ++i) {
                    auto it = Stations.find(filt_keys_CS[i]);
                    it->second.workshopsinwork = workshopsinwork;
                }
            }
        }
    }
    else {
        cout << "������ ��� �� ��� �����" << endl;
    }
}


void edit_CS_filter(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS) {
    int m = 0;
    while (true) {
        cout << "�������� ��� �� ������ ���������������: " << endl << "1) ���� �� ���� ��" << endl << "2) ������ ��������������� ��" << endl << "0) �����" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            edit_single_CS(Stations);
        }
        if (m == 2) {
            edit_filtered_CS(Stations,filt_keys_CS);
        }
    }
}

void load2(unordered_map<int, compressor_station>& Stations, int& maxCSID) {
    ifstream in("datapipecs.txt");
    if (!in.is_open()) {
        cout << "���� �� ������" << endl;
        return;
    }
    Stations.clear();
    string line2;
    while (getline(in >> ws, line2)) {
        if (line2 == "data CS:") {
            loadCS(Stations, in, maxCSID);
        }
    }
    if (!Stations.empty()) {
        cout << "������ � �� ���������" << endl;
    }
}