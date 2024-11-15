#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
#include <unordered_map>

using namespace std;

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
            << "3) Задать фильтр" << endl
            << "4) Просмотр объектов" << endl
            << "5) Редактировать трубу" << endl
            << "6) Редактировать КС" << endl
            << "7) Сохранить данные" << endl
            << "8) Загрузить данные" << endl
            << "0) Выход" << endl
            << "Введите команду которую вы бы хотели выполнить(от 0 до 7): ";
        k = check<int>(0, 8);
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

void filter_P(const unordered_map<int, Pipe>& Pipes, unordered_map<int, Pipe>& Pipes_filter, string Name_def, int rep_def) {
    Pipes_filter.clear();
    for (const auto& pair : Pipes) {
        bool name = Name_def.empty() || pair.second.Name == Name_def;
        bool repair = (rep_def == 3) || (pair.second.repair == rep_def);
        if (name && repair) {
            Pipes_filter.insert({ pair.first,pair.second });
        }
    }
}

void filter_CS(const unordered_map<int, compressor_station>& Stations, unordered_map<int, compressor_station>& Stations_filter, string Name_def, int work) {
    Stations_filter.clear();
    for (const auto& pair : Stations) {
        bool name = Name_def.empty() || pair.second.Name == Name_def;
        bool eff = (work == -1) || ((100 - (float(pair.second.workshopsinwork) / float(pair.second.workshops)) * 100) == work);
        if (name && eff) {
            Stations_filter.insert({ pair.first,pair.second });
        }
    }
}

void setFilterParams(string& Name_Filter, int& Status_Filter, const string& ObjectType) {
    int m = 0;
    while (true) {
        cout << "Какой фильтр для " << ObjectType << " вы хотите задать:" << endl << "1) По имени (" << (!Name_Filter.empty() ? "Заполнен" : "Не заполнен") << ")" << endl << "2) По статусу (" << (Status_Filter != -1 ? "Заполнен" : "Не заполнен") << ")" << endl  << "3) Сбросить фильтр" << endl << "0) Выход" << endl;
        m = check<int>(0, 3);

        if (m == 0) {
            break;
        }

        if (m == 1) {
            cout << "Введите имя по которому вы будете фильтровать " << ObjectType << ": ";
            getline(cin, Name_Filter);
        }
        else if (m == 2) {
            cout << "Введите статус для фильтрации (" << (ObjectType == "трубы" ? "0 = Не в ремонте, 1 = В ремонте" : "Введите процент цехов, не в работе") << "): ";
            Status_Filter = check<int>(0, (ObjectType == "трубы" ? 1 : 100));
        }
        else if (m == 3) {
            Name_Filter = "";
            Status_Filter = -1;
            cout << "Фильтр для " << ObjectType << " сброшен!" << endl;
        }
    }
}

void filter(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations,unordered_map<int, Pipe>& Pipes_filter, unordered_map<int, compressor_station>& Stations_filter) {
    string Name_P = "";
    int Repair_P = -1;
    string Name_CS = "";
    int work_CS = -1;
    int m = 0;
    while (true) {
        cout << "Если вы зайдёте в фильтр и не зададите ни один параметр, то все объекты будут добавлены в фильтр!"<< endl;
        cout << "Выберите, для какого объекта вы хотите задать фильтры:" << endl << "1) Фильтр для трубы" << endl << "2) Фильтр для КС" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);

        if (m == 1) {
            setFilterParams(Name_P, Repair_P, "трубы");
        }
        else if (m == 2) {
            setFilterParams(Name_CS, work_CS, "КС");
        }
        else if (m == 0) {
            filter_P(Pipes, Pipes_filter, Name_P, Repair_P);
            filter_CS(Stations, Stations_filter, Name_CS, work_CS);
            break;
        }
    }
}

template <typename T1, typename T2>
void objects_empty(const T1& pipes, const T2& stations) {
    if (pipes.empty() && stations.empty()) {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
    else if (!pipes.empty() && stations.empty()) {
        cout << "КС еще не были добавлены!" << endl;
    }
    else if (pipes.empty() && !stations.empty()) {
        cout << "Трубы еще не были добавлены!" << endl;
    }
    else {
        return;
    }
}

template <typename T, typename ShowFunc>
void view_objects(const unordered_map<int, T>& objects, ShowFunc show) {
    for (const auto& pair : objects) {
        cout << "ID: " << pair.first << "; ";
        show(pair.second);
    }
}
void view_all(const unordered_map<int, Pipe>& Pipes, const unordered_map<int, compressor_station>& Stations, unordered_map<int, Pipe>& Pipes_filter, unordered_map<int, compressor_station>& Stations_filter) {
    int m = 0;
    while (true) {
        cout << "Что вы хотите просмотреть?:" << endl << "1) Все объекты" << endl << "2) Объекты заданные по фильтру" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            if (!Pipes.empty()) {
                cout << "Все трубы: " << endl;
                view_objects(Pipes, show_Pipe);
            }
            if (!Stations.empty()) {
                cout << "Все компрессорные станции: " << endl;
                view_objects(Stations, show_cs);
            }
            objects_empty(Pipes, Stations);
        }
        if (m == 2) {
            if (!Pipes_filter.empty()) {
                cout << "Все отфильтрованные трубы: " << endl;
                view_objects(Pipes_filter, show_Pipe);
            }
            if (!Stations_filter.empty()) {
                cout << "Все отфильтрованные компрессорные станции: " << endl;
                view_objects(Stations_filter, show_cs);
            }
            objects_empty(Pipes_filter, Stations_filter);
        }
    }
}

void edit_Pipes(unordered_map<int, Pipe>& Pipes, unordered_map<int, Pipe>& Pipes_filter, int a) {
    int m = 0;
    int repair = -1;
    if (a == 0) {
        if (Pipes.empty()) {
            cout << "У вас еще нет ни одной трубы" << endl;
        }
        else {
            cout << "Все трубы: " << endl;
            view_objects(Pipes, show_Pipe);
            cout << "Введите ID трубы, которую вы хотите отредактировать: ";
            int id = check<int>(0, INT_MAX);
            auto it = Pipes.find(id);
            if (it != Pipes.end()) {
                Pipe& P = it->second;
                if (P.diameter > 0) {
                    while (true) {
                        cout << "Выберите параметр, который вы хотите отредактировать: " << endl << "1) Статус 'в ремонте'" << endl << "0) Выход в меню" << endl << "Номер команды: ";
                        m = check<int>(0, 1);
                        if (m == 0) {
                            break;
                        }
                        if (m == 1) {
                            cout << "Старый статус трубы: в ремонте " << boolalpha << P.repair << endl << "Выберите новый статус трубы: " << endl << "0) Не в ремонте" << endl << "1) В ремонте" << endl << "Введите номер команды: ";
                            P.repair = check<int>(0, 1);
                        }
                    }
                }
            }
            else {
                cout << "Труба с таким ID не найдена!" << endl;
            }
        }
    }
    else {
        if (!Pipes_filter.empty()) {
            cout << "Все отфильтрованные трубы: " << endl;
            view_objects(Pipes_filter, show_Pipe);
            while (true) {
                cout << "Выберите параметр, который вы хотите отредактировать: " << endl << "1) Статус 'в ремонте'" << endl << "0) Выход в меню" << endl << "Номер команды: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "Выберите новый статус трубы: " << endl << "0) Не в ремонте" << endl << "1) В ремонте" << endl << "Введите номер команды: ";
                    repair = check<int>(0, 1);
                }
                for (auto& pair : Pipes_filter) {
                    pair.second.repair = repair;
                    auto it = Pipes.find(pair.first);
                    if (it != Pipes.end()) {
                        it->second.repair = repair;
                    }
                }
            }
        }
        else {
            cout << "Фильтр ещё не был задан" << endl;
        }
    }
}

void edit_Pipe_filter(unordered_map<int, Pipe>& Pipes, unordered_map<int, Pipe>& Pipes_filter) {
    int m = 0;
    while (true) {
        cout << "Выберите что вы хотите отредактировать: " << endl << "1) Одну из всех труб" << endl << "2) Группу отфильтрованных труб" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            edit_Pipes(Pipes, Pipes_filter, 0);
        }
        if (m == 2) {
            edit_Pipes(Pipes, Pipes_filter, 1);
        }
    }
}

void edit_CS(unordered_map<int, compressor_station>& Stations, unordered_map<int, compressor_station>& Stations_filter, int a) {
    int m = 0;
    int workshopsinwork = -1;
    if (a == 0) {
        if (Stations.empty()) {
            cout << "У вас еще нет ни одной компрессорной станции" << endl;
        }
        else {
            cout << "Все компрессорные станции: " << endl;
            view_objects(Stations, show_cs);
            cout << "Введите ID компрессорной станции, которую вы хотите отредактировать: ";
            int id = check<int>(0, INT_MAX);
            auto it = Stations.find(id);
            if (it != Stations.end()) {
                compressor_station& CS = it->second;
                if (CS.workshops > 0) {
                    while (true) {
                        cout << "Выберите параметр, который вы хотите отредактировать: " << endl << "1) Кол-во цехов в работе" << endl << "0) Выход в меню" << endl << "Номер команды: ";
                        m = check<int>(0, 1);
                        if (m == 0) {
                            break;
                        }
                        if (m == 1) {
                            cout << "Старое кол-во цехов в работе: " << CS.workshopsinwork << endl << "Введите новое кол-во цехов в работе: ";
                            workshopsinwork = check<int>(0, CS.workshops);
                            CS.workshopsinwork = workshopsinwork;
                        }
                    }
                }
            }
            else {
                cout << "Компрессорная станция с таким ID не найдена!" << endl;
            }
        }
    }
    else {
        if (!Stations_filter.empty()) {
            cout << "Все отфильтрованные компрессорные станции: " << endl;
            view_objects(Stations_filter, show_cs);
            while (true) {
                cout << "Выберите параметр, который вы хотите отредактировать: " << endl << "1) Кол-во цехов в работе" << endl << "0) Выход в меню" << endl << "Номер команды: ";
                m = check<int>(0, 1);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "Введите новое кол-во цехов в работе: ";
                    workshopsinwork = check<int>(0, INT_MAX);
                }
                for (auto& pair : Stations_filter) {
                    pair.second.workshopsinwork = workshopsinwork;
                    auto it = Stations.find(pair.first);
                    if (it != Stations.end()) {
                        it->second.workshopsinwork = workshopsinwork;
                    }
                }
            }
        }
        else {
            cout << "Фильтр ещё не был задан" << endl;
        }
    }
}

void edit_CS_filter(unordered_map<int, compressor_station>& Stations, unordered_map<int, compressor_station>& Stations_filter) {
    int m = 0;
    while (true) {
        cout << "Выберите что вы хотите отредактировать: " << endl << "1) Одну из всех КС" << endl << "2) Группу отфильтрованных КС" << endl << "0) Выход" << endl;
        m = check<int>(0, 2);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            edit_CS(Stations, Stations_filter, 0);
        }
        if (m == 2) {
            edit_CS(Stations, Stations_filter, 1);
        }
    }
}

void SavePipe(int pipeID,const Pipe& P, ofstream& out)
{
    out << pipeID << endl;
    out << P.Name << endl;
    out << P.length << " " << P.diameter << " " << P.repair << endl;
}

void SaveCS(int CSID, const compressor_station& CS, ofstream& out)
{
    out << CSID << endl;
    out << CS.Name << endl;
    out << CS.workshops << " " << CS.workshopsinwork << " " << CS.effectiveness << endl;
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

void save(unordered_map<int, Pipe>& Pipes,unordered_map<int, compressor_station>& Stations) {
    ofstream out;
    out.open("datapipecs.txt");
    if (out.is_open())
    {
        objects_empty(Pipes, Stations);
        out << "data Pipe:" << endl;
        for (auto& pair : Pipes) {
            SavePipe(pair.first,pair.second, out);
        }
        out << "data CS:" << endl;
        for (auto& pair : Stations) {
            SaveCS(pair.first,pair.second, out);
        }
    }
    out.close();
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
void load2(unordered_map<int, compressor_station>& Stations, int& maxCSID) {
    ifstream in("datapipecs.txt");
    if (!in.is_open()) {
        cout << "Файл не найден" << endl;
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
        cout << "Данные о КС загружены" << endl;
    }
}

int main() {
    int maxCSID = 0;
    int maxPipeID = 0;
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
            Pipes.insert({++maxPipeID,P});
        }
        else if (k == 2) {
            menu_new_ks(CS);
            Stations.insert({++maxCSID,CS});
        }
        else if (k == 3) {
            filter(Pipes, Stations, Pipes_filter, Stations_filter);
        }
        else if (k == 4) {
            view_all(Pipes, Stations, Pipes_filter, Stations_filter);
        }
        else if (k == 5) {
            edit_Pipe_filter(Pipes,Pipes_filter);
        }
        else if (k == 6) {
            edit_CS_filter(Stations,Stations_filter);
        }
        else if (k == 7) {
            save(Pipes, Stations);
        }
        else if (k == 8) {
            load(Pipes, maxPipeID);
            load2(Stations, maxCSID);
        }
    }
    return 0;
}