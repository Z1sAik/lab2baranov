#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//структуры
struct Pipe
{
    string Name; //название трубы
    float length; //километры 
    int diameter; //миллиметры
    bool repair; //признак "в ремонте" 
};

struct compressor_station
{
    string Name; //название КС
    int workshops; //Кол-во цехов
    int workshopsinwork; //Кол-во цехов в работе
    int effectiveness; //Коэфф. эффективности
};

//Функции
int check(int max, int low) {
    int z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено отрицательное число или ноль! Попробуйте ещё раз: ";
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

float floatcheck(int max, float low) {
    float z;
    cin >> z;
    cin.ignore();
    while (true) {
        if (cin.fail()) {
            cout << "Ошибка. Введено не целое число или символ! Попробуйте ещё раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }
        else if (z < low) {
            cout << "Ошибка. Введено отрицательное число или ноль! Попробуйте ещё раз: ";
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
        k = check(7, 0);
        return k;
    }
}

void menu_new_Pipe(Pipe& P) {
    cout << "Введите название трубы (на английском язык): ";
    getline(cin, P.Name);
    cout << "Введите длину трубы в километрах: ";
    P.length = floatcheck(0, 0.1);
    cout << "Введите диаметр трубы в миллиметрах: ";
    P.diameter = check(0, 1);
    cout << "Выберите в каком состоянии труба: " << endl << "0)Не в ремонте" << endl << "1)В ремонте" << endl;
    P.repair = check(1, 0);
    cout << "Труба создана: " << endl << "Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}

void menu_new_ks(compressor_station& CS) {
    cout << "Введите название компрессорной станции (на английском язык): ";
    getline(cin, CS.Name);
    cout << "Введите кол-во цехов: ";
    CS.workshops = check(0, 1);
    cout << "Введите кол-во цехов в работе: ";
    CS.workshopsinwork = check(CS.workshops, 0);
    cout << "Введите коэффициент эффективности КС(от 0 до 100): ";
    CS.effectiveness = check(100, 0);
    cout << "Компрессорная станция создана: " << endl << "Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void show_Pipe(const Pipe& P) {
    cout << "Труба: " << endl << "Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}
void show_cs(const compressor_station& CS) {
    cout << "Компрессорная станция: " << endl << "Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void view_all(const Pipe& P, const compressor_station& CS) {
    if (CS.workshops > 0 && P.diameter > 0) {
        show_Pipe(P);
        show_cs(CS);
    }
    else if (CS.workshops < 1 && P.diameter > 0) {
        show_Pipe(P);
        cout << "КС еще не была добавлена!" << endl;
    }
    else if (CS.workshops > 0 && P.diameter < 1) {
        show_cs(CS);
        cout << "Труба еще не была добавлена!" << endl;
    }
    else {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
}

void edit_Pipe(Pipe& P) {
    int m = 0;
    if (P.diameter > 0) {
        while (true) {
            cout << "Выберите параметр который вы хотите отредактировать: " << endl << "1) Статус 'в ремонте'" << endl << "0) Выход в меню" << endl << "Номер команды: ";
            m = check(1, 0);
            if (m == 0) {
                break;
            }
            else if (m == 1) {
                cout << "Старый статус трубы: в ремонте " << boolalpha << P.repair << endl;
                cout << "Выберите новый статус трубы: " << endl << "0)Не в ремонте" << endl << "1)В ремонте" << endl << "Введите номер команды: ";
                P.repair = check(1, 0);
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
            m = check(1, 0);
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
void save(const Pipe& P,const compressor_station& CS) {
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
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            menu_new_Pipe(P);
        }
        else if (k == 2) {
            menu_new_ks(CS);
        }
        else if (k == 3) {
            view_all(P, CS);
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