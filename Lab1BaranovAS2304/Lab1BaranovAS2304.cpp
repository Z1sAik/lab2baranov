#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
#include <unordered_map>

using namespace std;

//ID
int id_P = 0;
int id_CS = 0;

//Функции
template <typename T>
T check(T low, T max) {
    T z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено число меньше минимального! Попробуйте ещё раз: ";
        }
        else if (max != 0 && z > max) {
            cout << "Ошибка. Введено число больше максимального! Попробуйте ещё раз: ";
        }
        else {
            break;
        }
        cin >> z;
        cin.ignore();
    }
    return z;
}

int menu() {
    int k = -1;
    while (true) {
        cout << "///////  Меню  ///////" << endl
            << "1) Добавить трубу" << endl
            << "2) Добавить КС" << endl
            << "3) Просмотр объектов" << endl
            << "4) Редактировать трубу" << endl
            << "5) Редактировать КС" << endl
            << "6) Сохранить данные" << endl
            << "7) Загрузить данные" << endl
            << "0) Выход" << endl
            << "Введите команду которую вы бы хотели выполнить(от 0 до 7): ";
        k = check<int>(0, 7);
        return k;
    }
}

void show_Pipe(const Pipe& P) {
    cout << "Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}
void show_cs(const compressor_station& CS) {
    cout << "Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void menu_new_Pipe(Pipe& P) {
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

void menu_new_ks(compressor_station& CS) {
    cout << "Введите название компрессорной станции (на английском язык): ";
    getline(cin, CS.Name);
    cout << "Введите кол-во цехов: ";
    CS.workshops = check<int>(1, 0);
    cout << "Введите кол-во цехов в работе: ";
    CS.workshopsinwork = check<int>(0,CS.workshops);
    cout << "Введите коэффициент эффективности КС(от 0 до 100): ";
    CS.effectiveness = check<int>(0, 100);
    show_cs(CS);
}

//"2) По статусу 'в ремонте'(" << (check_RepairP ? "Заполнен" : "Не заполнен") << ")" << endl
void view_and_filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations) {
    int fil_P = 0;
    int fil_CS = 0;
    int m = 0;
    while (true) {
        cout << "Выберите параметр который вы хотите отредактировать: " << endl << "1) Просмотреть все" << endl << "2) Фильтр для трубы(" << (fil_P ? "Заполнен" : "Не заполнен") << ")" << endl << "3) Фильтр для КС(" << (fil_CS ? "Заполнен" : "Не заполнен") << ")" << endl << "0) Выйти";
        m = check<int>(0, 3);
        if (m == 1) {
            view_all()
        }
    }

}
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, unordered_map<int, Pipe>& Pipes_filter, unordered_map<int, compressor_station>& Stations_filter) {
    for (const auto& pair : Pipes) {
        cout << "ID: " << pair.first << ";";
        show_Pipe(pair.second);
    }
    for (const auto& pair : Stations) {
        cout << "ID: " << pair.first << ";";
        show_cs(pair.second);
    }
    if (Pipes.empty() && Stations.empty()) {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
    else if (!Pipes.empty() && Stations.empty()) {
        cout << "КС еще не была добавлена!" << endl;
    }
    else if (Pipes.empty() && !Stations.empty()) {
        cout << "Труба еще не была добавлена!" << endl;
    }
    else {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
}

void filter_P(const unordered_map<int, Pipe>& Pipes,unordered_map<int, Pipe>& Pipes_filter, string Name_def,int rep_def) {
    if (Name_def == "" && rep_def == 3) {
        cout << "Не выбран фильтр";
    }
    else if (Name_def == "") {
        for (const auto& pair : Pipes) {
            if (pair.second.repair == rep_def) {
                Pipes_filter.insert({ pair.first,pair.second });
            }
        }
    }
    else if (rep_def == 3) {
        for (const auto& pair : Pipes) {
            if (pair.second.Name == Name_def) {
                Pipes_filter.insert({ pair.first,pair.second });
            }
        }
    }
    else {
        for (const auto& pair : Pipes) {
            if (pair.second.repair == rep_def && pair.second.Name == Name_def) {
                Pipes_filter.insert({ pair.first,pair.second });
            }
        }
    }
}

void filter_CS(const unordered_map<int, compressor_station>& Stations, unordered_map<int, compressor_station>& Stations_filter, string Name_def, int eff_def) {
    if (Name_def == "" && eff_def == -1) {
        cout << "Не выбран фильтр";
    }
    else if (Name_def == "") {
        for (const auto& pair : Stations) {
            if (pair.second.effectiveness == eff_def) {
                Stations_filter.insert({ pair.first,pair.second });
            }
        }
    }
    else if (eff_def == -1) {
        for (const auto& pair : Stations) {
            if (pair.second.Name == Name_def) {
                Stations_filter.insert({ pair.first,pair.second });
            }
        }
    }
    else {
        for (const auto& pair : Stations) {
            if (pair.second.effectiveness == eff_def && pair.second.Name == Name_def) {
                Stations_filter.insert({ pair.first,pair.second });
            }
        }
    }
}

void edit_Pipe(Pipe& P) {
    int m = 0;
    if (P.diameter > 0) {
        while (true) {
            cout << "Выберите параметр который вы хотите отредактировать: " << endl << "1) Статус 'в ремонте'" << endl << "0) Выход в меню" << endl << "Номер команды: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            else if (m == 1) {
                cout << "Старый статус трубы: в ремонте " << boolalpha << P.repair << endl;
                cout << "Выберите новый статус трубы: " << endl << "0)Не в ремонте" << endl << "1)В ремонте" << endl << "Введите номер команды: ";
                P.repair = check<int>(0, 1);
            }
        }
    }
    else {
        cout << "Вы еще не добавили трубу и не можете посмотреть ее параметры. Пожалуйста настройтe трубу в меню(пункт 1)" << endl;
    }
}

void edit_CS(compressor_station& CS) {
    int m = 0;
    if (CS.workshops > 0) {
        while (true) {
            cout << "Выберите параметр который вы хотите отредактировать: " << endl << "1) Кол-во цехов в работе" << endl << "0) Выход в меню" << endl << "Номер команды: ";
            m = check<int>(0, 1);
            if (m == 0) {
                break;
            }
            else if (m == 1) {
                cout << "Общее кол-во цехов: " << CS.workshops << "; Старое кол-во цехов в работе: " << CS.workshopsinwork << endl;
                cout << "Введите новое кол-во цехов в работе: ";
                CS.workshopsinwork = check(CS.workshops, 0);
            }
        }
    }
    else {
        cout << "Вы еще не добавили КС и не можете посмотреть ее параметры. Пожалуйста настройтe КС в меню(пункт 2)" << endl;
    }
}
void SavePipe(const Pipe& P, ofstream& out)
{
    out << "data Pipe:" << endl;
    out << P.Name << endl;
    out << P.length << " " << P.diameter << " " << P.repair << endl;
}

void SaveCS(const compressor_station& CS, ofstream& out)
{
    out << "data CS:" << endl;
    out << CS.Name << endl;
    out << CS.workshops << " " << CS.workshopsinwork << " " << CS.effectiveness << endl;;
}

void loadPipe(Pipe& P, ifstream& in)
{
    if (in.is_open()) {
        getline(in >> ws, P.Name);
        in >> P.length >> P.diameter >> P.repair;
    }
}
void loadCS(compressor_station& CS, ifstream& in) {
    if (in.is_open()) {
        getline(in >> ws, CS.Name);
        in >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
    }
}
void save(const Pipe& P, const compressor_station& CS) {
    ofstream out;
    out.open("datapipecs.txt");
    if (out.is_open())
    {
        if (P.Name.empty() && CS.Name.empty()) {
            cout << "У вас нет данных для записи!" << endl;
            return;
        }
        if (!P.Name.empty() && CS.Name.empty()) {
            SavePipe(P, out);
            cout << "Данные о трубе записаны!" << endl;
        }
        if (!CS.Name.empty() && P.Name.empty()) {
            SaveCS(CS, out);
            cout << "Данные о КС записаны!" << endl;
        }

    }
    out.close();
}

void load(Pipe& P, compressor_station& CS) {
    ifstream in("datapipecs.txt");
    if (!in.is_open())
    {
        cout << "not found" << endl;
        return;
    }
    P = {};
    CS = {};
    string finde;
    while (getline(in >> ws, finde)) {
        if (finde == "data Pipe:") {
            loadPipe(P, in);
            cout << "Данные из файла о трубе записаны" << endl;
        }
        if (finde == "data CS:") {
            loadCS(CS, in);
            cout << "Данные из файла о КС записаны" << endl;
        }
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    Pipe P;
    compressor_station CS;
    unordered_map<int, Pipe> Pipes = {};
    unordered_map<int, Pipe> Pipes_filter = {};
    unordered_map<int, compressor_station> Stations = {};
    unordered_map<int, compressor_station> Stations_filter = {};
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            menu_new_Pipe(P);
            Pipes.insert({++id_P,P});
        }
        else if (k == 2) {
            menu_new_ks(CS);
            Stations.insert({++id_CS,CS});
        }
        else if (k == 3) {
            view_and_filter(Pipes, Stations);
        }
        else if (k == 4) {
            edit_Pipe(P);
        }
        else if (k == 5) {
            edit_CS(CS);
        }
        else if (k == 6) {
            save(P, CS);
        }
        else if (k == 7) {
            load(P, CS);
        }
    }
    return 0;
}