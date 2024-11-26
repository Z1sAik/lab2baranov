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
            CS.id = id; 
            getline(in >> ws, CS.Name);
            in >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
            Stations[id] = CS;
            if (id > maxCSID) {
                maxCSID = id;
            }
        }
        in.clear();
    }
}

void show_cs(const compressor_station& CS) {
    cout << "ID: " << CS.id << "; Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void menu_new_ks(compressor_station& CS) {
    CS.id = ++CS.maxCSID;
    cout << "ID: " << CS.id << endl;
    cout << "Введите название компрессорной станции (на английском язык): ";
    getline(cin, CS.Name);
    cout << "Введите кол-во цехов: ";
    CS.workshops = check<int>(1, 0);
    cout << "Введите кол-во цехов в работе: ";
    CS.workshopsinwork = check<int>(0, CS.workshops);
    cout << "Введите коэффициент эффективности КС(от 0 до 100): ";
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
    cout << "Все компрессорные станции: " << endl;
    view_objects(Stations, show_cs);
    cout << "Введите ID компрессорной станции, которую вы хотите отредактировать: ";
    int id = check<int>(0, INT_MAX);
    auto it = Stations.find(id);
    if (it != Stations.end()) {
        compressor_station& CS = it->second;
        if (CS.workshops > 0) {
            while (true) {
                cout << "Выберите параметр, который вы хотите отредактировать: " << endl<< "1) Кол-во цехов в работе" << endl<< "0) Выход в меню" << endl<< "Номер команды: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "Старое кол-во цехов в работе: " << CS.workshopsinwork << endl
                        << "Введите новое кол-во цехов в работе: ";
                    int workshopsinwork = check<int>(0, CS.workshops);
                    CS.workshopsinwork = workshopsinwork;
                }
            }
        }
    }
    else {
        cout << "Компрессорная станция с таким ID не найдена!" << endl;
    }
}

void edit_filtered_CS(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS) {
    int m = 0;
    if (!filt_keys_CS.empty()) {
        cout << "Все отфильтрованные компрессорные станции: " << endl;
        view_objects_vector(filt_keys_CS, Stations, show_cs);
        while (true) {
            cout << "Выберите параметр, который вы хотите отредактировать: " << endl<< "1) Кол-во цехов в работе" << endl<< "0) Выход в меню" << endl<< "Номер команды: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            if (m == 1) {
                cout << "Введите новое кол-во цехов в работе: ";
                int workshopsinwork = check<int>(0, INT_MAX);
                for (size_t i = 0; i < filt_keys_CS.size(); ++i) {
                    auto it = Stations.find(filt_keys_CS[i]);
                    it->second.workshopsinwork = workshopsinwork;
                }
            }
        }
    }
    else {
        cout << "Фильтр ещё не был задан" << endl;
    }
}


void edit_CS_filter(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS) {
    int m = 0;
    while (true) {
        cout << "Выберите что вы хотите отредактировать: " << endl << "1) Одну из всех КС" << endl << "2) Группу отфильтрованных КС" << endl << "0) Выход" << endl;
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
