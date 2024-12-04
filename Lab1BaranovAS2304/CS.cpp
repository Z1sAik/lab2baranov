#include "functions.h"
#include "CS.h"
#include "Pipe.h"
#include <iostream>
#include <fstream>

using namespace std;

int compressor_station::maxID = 0;

std::ostream& operator<<(std::ostream& out, const compressor_station& CS) {
    out << "ID: " << CS.id
        << "; Имя: " << CS.Name 
        << "; Кол-во цехов: " << CS.workshops
        << "; Кол-во цехов в работе: " << CS.workshopsinwork 
        << "; Эффективности: " << CS.effectiveness << "%" << endl;
    return out;
}

std::ofstream& operator<<(std::ofstream& fout, const compressor_station& CS) {
    if (fout.is_open()) {
        fout << CS.id << endl
            << CS.Name << endl
            << CS.workshops << endl
            << CS.workshopsinwork << endl
            << CS.effectiveness << endl;
    }
    return fout;
}

std::istream& operator>>(std::istream& in, compressor_station& CS) {
    CS.id = ++CS.maxID;
    cout << "Создание новой КС" << endl;
    cout << "ID: " << CS.id << endl;
    cout << "Введите название компрессорной станции (на английском язык): ";
    CS.Name = get_line(in);
    cout << "Введите кол-во цехов: ";
    CS.workshops = check<int>(0, INT_MAX);
    cout << "Введите кол-во цехов в работе: ";
    CS.workshopsinwork = check<int>(0, CS.workshops);
    cout << "Введите коэффициент эффективности КС(от 0 до 100): ";
    CS.effectiveness = check<int>(0, 100);
    return in;
}

std::ifstream& operator>>(std::ifstream& fin, compressor_station& CS) {
    if (fin.is_open()) {
        fin >> CS.id;
        fin.ignore();
        getline(fin >> ws, CS.Name);
        fin >> CS.workshops;
        fin >> CS.workshopsinwork;
        fin >> CS.effectiveness;
    }
    return fin;
}

compressor_station compressor_station::newCS()
{
    compressor_station CS;
    cin >> CS;
    return CS;
}

void compressor_station::resetMaxID()
{
    maxID = 0;
}

bool compressor_station::runworkshop()
{
    if (workshopsinwork < workshops)
    {
        workshopsinwork +=1;
        return 1;
    }
    else
        return 0;
}

bool compressor_station::stopworkshop()
{
    if (workshopsinwork > 0)
    {
        workshopsinwork -=1;
        return 1;
    }
    else
        return 0;
}

unordered_set<int> selectByChosenFilter(unordered_map<int, compressor_station>& Stations) {
    unordered_set<int> res;
    cout << "Выберите фильтр:" << endl << "1)По имени" << endl << "2)По проценту нерабочих цехов (0–100): " << "0) Выход" << endl;
    int m = 0;
    while (true) {
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        else if (m == 1) {
            cout << "Введите часть имени: ";
            string name = get_line(cin);
            res = findwithFilter(Stations, filterByNameCS, name);
            break;
        }
        else if (m == 2) {
            cout << "Введите процент нерабочих цехов (0–100): "; float status = check<float>(0, 100);
            res = findwithFilter(Stations, filterByWork, status);
            break;
        }
    }
    return res;
}

void edit(unordered_map<int, compressor_station>& Stations) {
    if (!Stations.empty()) {
        cout << "Что вы хотите сделать с КС" << endl << "1) Запустить 1 цех" << endl << "2) Остановить 1 цех" << "0) Выход" << endl;
    }
    else {
        cout << "Нет объектов для редактирования!" << endl;
    }
    int m = 0;
    while (true) {
        if (m == 0) {
            break;
        }
        if (m == 1) {
            for (auto& [id, cs] : Stations)
                if (!cs.runworkshop())
                    cout << "Невозможно изменить CS " << id << endl;
            break;
        }
        if (m == 2) {
            for (auto& [id, cs] : Stations)
                if (!cs.stopworkshop())
                    cout << "Невозможно изменить CS " << id << endl;

            break;
        }
    }
    if (!Stations.empty()) cout << "Редактирование выполненно!" << endl;
}