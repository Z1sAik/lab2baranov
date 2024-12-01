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
    get_line(CS.Name);
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

int edit_single_CS(unordered_map<int, compressor_station>& Stations, int id, int workshopsinwork) {
    auto it = Stations.find(id);
    if (it != Stations.end()) {
        compressor_station& CS = it->second;
        if (workshopsinwork > CS.workshops) {
            cout << "Количество цехов в работе не может превышать доступное количество цехов. Попробуйте снова." << endl;
            return 0;
        }
        else {
            CS.workshopsinwork = workshopsinwork;
            return 1;
        }
    }
    else {
        cout << "Компрессорная станция с таким ID не найдена!" << endl;
        return 0;
    }
}
