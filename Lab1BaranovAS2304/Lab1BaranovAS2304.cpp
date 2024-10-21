#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Pipe
{
public:
    string Name; //название трубы
    float length; //километры 
    int diameter; //миллиметры
    bool repair; //признак "в ремонте"
    int id;
    static int next_id;
    Pipe() : Name(""), length(), diameter(), repair() {
        id = next_id++;
    }
    Pipe(string P_Name, float P_length, int P_diameter, bool P_repair) {

        Name = P_Name;
        length = P_length;
        diameter = P_diameter;
        repair = P_repair;
        id = ++next_id;
    }
    
};
int Pipe::next_id = 1;

class compressor_station
{
public:
    string Name; //название КС
    int workshops; //Кол-во цехов
    int workshopsinwork; //Кол-во цехов в работе
    int effectiveness; //Коэфф. эффективности
    int id;
    static int next_id;
    compressor_station() : Name(""), workshops(), workshopsinwork(), effectiveness() {
        id = next_id++;
    }
    compressor_station(string CS_Name, int CS_workshops, int CS_workshopsinwork, int CS_effectiveness) {

        Name = CS_Name;
        workshops = CS_workshops;
        workshopsinwork = CS_workshopsinwork;
        effectiveness = CS_effectiveness;
        id = ++next_id;
    }

};
int compressor_station::next_id = 1;

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
    cout << "Труба создана: "<<endl <<"ID-PIPE: "<<P.id << "; Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
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
    cout << "Компрессорная станция создана: " << endl << "ID-CS: " << CS.id << "; Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void show_Pipe(const Pipe& P) {
    cout << "Труба: " << "ID-PIPE: " << P.id << "; Название трубы: " << P.Name << "; Длина трубы: " << P.length << "; Диаметр трубы: " << P.diameter << "; Статус 'в ремонте': " << boolalpha << P.repair << endl;
}
void show_cs(const compressor_station& CS) {
    cout << "Компрессорная станция: " << "ID-CS: " << CS.id << "; Название КС: " << CS.Name << "; Кол-во цехов: " << CS.workshops << "; Кол-во цехов в работе: " << CS.workshopsinwork << "; Коэффициент эффективности КС: " << CS.effectiveness << endl;
}

void searchfilter_Pipe(const vector<Pipe>& P_groupe, string Name, int repair,vector<Pipe>& filterP) {
    if (Name != "" && repair != 3) {
        for (const auto& Pipe : P_groupe) {
            if (Pipe.Name == Name && Pipe.repair == repair) {
                filterP.push_back(Pipe);
            }
        }
    }
    else if (Name != "" && repair == 3) {
        for (const auto& Pipe : P_groupe) {
            if (Pipe.Name == Name) {
                filterP.push_back(Pipe);
            }
        }
    }
    else if (Name == "" && repair != 3) {
        for (const auto& Pipe : P_groupe) {
            if (Pipe.repair == repair) {
                filterP.push_back(Pipe);
            }
        }
    }
    else if (Name == "" && repair == 3){
        for (const auto& Pipe : P_groupe) {     
            filterP.push_back(Pipe);
        }
    }
    if (filterP.size() == 0) {
        cout << endl << "----------------------" << endl;
        cout << "Нет труб подходящих под ваши фильтры" << endl;
        cout << "----------------------" << endl << endl;
    }
    else {
        cout << endl << "----------------------" << endl;
        for (const auto& Pipe : filterP) {
            show_Pipe(Pipe);
        }
        cout << "----------------------" << endl << endl;
    }
    filterP.clear();
}

void menu_Pipe(bool check_NameP, bool check_RepairP) {
    cout << "Задайте фильтр для труб которые вы хотите посмотреть (если не хотите использовать фильтр просто не заполняйте его)" << endl 
    << "1) По имени(" << (check_NameP ? "Заполнен" : "Не заполнен") << ")" << endl
    << "2) По статусу 'в ремонте'(" << (check_RepairP ? "Заполнен" : "Не заполнен") << ")" << endl
    << "3) Просмотр труб " << endl
    << "4) Сбросить фильтр " << endl
    << "0) Выход" << endl
    << "Введите команду: ";
}

void filterPipe(const vector<Pipe>& P_groupe, vector<Pipe>& filterP) {
    bool check_Name = 0;
    bool check_Repair = 0;
    string Name = "";
    int repair = 3;
    int m = 0;
    while (true) {
        menu_Pipe(check_Name, check_Repair);
        m = check(4, 0);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            cout << "Введите имя по которому вы будете фильтровать трубы: ";
            getline(cin, Name);
            check_Name = 1;
        }
        if (m == 2) {
            cout << "Введите статус 'В ремонте' по которому вы будете фильтровать трубы (1 в ремонте, 0 не в ремонте): ";
            repair = check(1, 0);
            check_Repair = 1;
        }
        if (m == 3) {
            searchfilter_Pipe(P_groupe, Name, repair, filterP);
        }
        if (m == 4) {
            check_Name = 0;
            check_Repair = 0;
            Name = "";
            repair = 3;
        }
    }
}

void searchfilter_CS(const vector<compressor_station>& CS_groupe, string Name, int work, vector<compressor_station>& filter_CS) {
    if (Name != "" && work != -1) {
        filter_CS.clear();
        for (const auto& compressor_station : CS_groupe) {
            if (compressor_station.Name == Name && (100 - (float(compressor_station.workshopsinwork) / float(compressor_station.workshops)) * 100) == work) {
                filter_CS.push_back(compressor_station);
            }
        }
    }
    else if (Name != "" && work == -1) {
        filter_CS.clear();
        for (const auto& compressor_station : CS_groupe) {
            if (compressor_station.Name == Name) {
                filter_CS.push_back(compressor_station);
            }
        }
    }
    else if (Name == "" && work != -1) {
        filter_CS.clear();
        for (const auto& compressor_station : CS_groupe) {
            if ((100 - (float(compressor_station.workshopsinwork) / float(compressor_station.workshops)) * 100) == work){
                filter_CS.push_back(compressor_station);
            }
        }
    }
    else if (Name == "" && work == -1) {
        filter_CS.clear();
        for (const auto& compressor_station : CS_groupe) {
            filter_CS.push_back(compressor_station);
        }
    }
    if (filter_CS.size() == 0) {
        cout << endl << "----------------------" << endl;
        cout << "Нет КС подходящих под ваши фильтры" << endl;
        cout << "----------------------" << endl << endl;
    }
    else {
        cout << endl << "----------------------" << endl;
        for (const auto& compressor_station : filter_CS) {
            show_cs(compressor_station);
        }
        cout << "----------------------" << endl << endl;
    }
}

void menu_CS(bool check_NameCS, bool check_RepairCS) {
    cout << "Задайте фильтр для КС которые вы хотите посмотреть (если не хотите использовать фильтр просто не заполняйте его)" << endl
        << "1) По имени(" << (check_NameCS ? "Заполнен" : "Не заполнен") << ")" << endl
        << "2) По проценту незадействованных цехов(" << (check_RepairCS ? "Заполнен" : "Не заполнен") << ")" << endl
        << "3) Просмотр КС " << endl
        << "4) Сбросить фильтр " << endl
        << "0) Выход" << endl
        << "Введите команду: ";

}

void filterCS(const vector<compressor_station>& CS_groupe, vector<compressor_station>& filter_CS) {
    bool check_Name = 0;
    bool check_work = 0;
    string Name = "";
    int work = -1;
    int m = 0;
    while (true) {
        menu_CS(check_Name, check_work);
        m = check(4, 0);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            cout << "Введите имя по которому вы будете фильтровать КС: ";
            getline(cin, Name);
            check_Name = 1;
        }
        if (m == 2) {
            cout << "Введите процент незапущенных цехов по которому вы будете фильтровать КС: ";
            work = check(100, 0);
            check_work = 1;
        }
        if (m == 3) {
            searchfilter_CS(CS_groupe, Name, work, filter_CS);
        }
        if (m == 4) {
            check_Name = 0;
            check_work = 0;
            Name = "";
            work = -1;
        }
    }
}

void view_all(const vector<Pipe>& P_groupe, const vector<compressor_station>& CS_groupe, vector<Pipe>& filterP, vector<compressor_station>& filter_CS) {
    int m = 0;
    if (P_groupe.size() != 0 && CS_groupe.size() != 0) {
        while (true) {
            cout << "Выберите группу объектов которую вы хотите просмотреть: " << endl << "1) Трубы " << endl << "2) Компрессорные станции" << endl << "0) Выход" << endl << "Введите цифру от 0 до 2: ";
            m = check(2, 0);
            if (m == 1) {
                filterPipe(P_groupe, filterP);
            }
            else if (m == 2) {
                filterCS(CS_groupe, filter_CS);
            }
            else if (m == 0) {
                break;
            }
        }  
    }
    else if (P_groupe.size() != 0 && CS_groupe.size() == 0) {
        cout << "У вас нет объектов типа КС, поэтому вы можете просмотреть только трубы: " << endl;
        filterPipe(P_groupe, filterP);
    }
    else if (P_groupe.size() == 0 && CS_groupe.size() != 0) {
        cout << "У вас нет объектов типа труба, поэтому вы можете просмотреть только КС: " << endl;
        filterCS(CS_groupe, filter_CS);
    }
    else {
        cout << "Вы еще не добавили ни одного объекта." << endl;
    }
}

void edit_Pipe(vector<Pipe>& P_groupe,vector<Pipe>& filterP) {
    int m = 0;
    int check_fil = 0;
    string Name = "";
    int repair = -1;
    while (true) {
        cout << "Что вы хотите сделать(если фильтр не задан трубы невозможно редактировать)?" << endl << "1) Задать фильтр для редактирования(" << (check_fil ? "Заполнен" : "Не заполнен") << ")" << endl << "2) Редактировать выбранные трубы" << endl << "0) Выход" << endl << "Введите команду: ";
        m = check(2, 0);
        if (m == 0) {
            break;
        }
        if (m == 1) {
            filterPipe(P_groupe, filterP);
            check_fil = 1;
        }
        if (m == 2) {
            while (true) {
                cout << "Что вы хотите отредактировать у выбраной группы?" << endl << "1) Название" << endl << "2) Статус 'в ремонте'" << endl << "0) Выход" << endl << "Введите команду: ";
                m = check(2, 0);
                if (m == 0) {
                    break;
                }
                if (m == 1) {
                    cout << "Введите новое название: ";
                    getline(cin, Name);
                    for (auto& Pipe1 : P_groupe) {
                        for (auto& Pipe2 : filterP) {
                            Pipe2.Name = Name;
                            if (Pipe1.id == Pipe2.id) {
                                Pipe1 = Pipe2;
                            }
                        }
                    }
                }
                if (m == 2) {
                    cout << "Введите новый статус 'в ремонте'( 1 - в ремонте; 0 - не в ремонте ): ";
                    m = check(1, 0);
                    repair = m;
                    for (auto& Pipe1 : P_groupe) {
                        for (auto& Pipe2 : filterP) {
                            Pipe2.repair = repair;
                            if (Pipe1.id == Pipe2.id) {
                                Pipe1 = Pipe2;
                            }
                        }
                    }
                }
            }
        }
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
    out << "data Pipe id("<<P.id<<"):" << endl;
    out << P.Name << endl;
    out << P.id << " " << P.length << " " << P.diameter << " " << P.repair << endl;
}

void SaveCS(const compressor_station& CS, ofstream& out)
{
    out << "data CS id("<<CS.id<<"):" << endl;
    out << CS.Name << endl;
    out << CS.id << " " << CS.workshops << " " << CS.workshopsinwork << " " << CS.effectiveness << endl;;
}

void loadPipe(Pipe& P, ifstream& in)
{
    if (in.is_open()) {
        getline(in >> ws, P.Name);
        in >> P.id >> P.length >> P.diameter >> P.repair;
    }
}
void loadCS(compressor_station& CS, ifstream& in) {
    if (in.is_open()) {
        getline(in >> ws, CS.Name);
        in >> CS.id >> CS.workshops >> CS.workshopsinwork >> CS.effectiveness;
    }
}
void save(const vector<Pipe> P_groupe,const vector<compressor_station> CS_groupe) {
    ofstream out;
    out.open("datapipecs.txt");
    if (out.is_open())
    {
        if (P_groupe.size() == 0 && CS_groupe.size() == 0) {
            cout << "У вас нет данных для записи!" << endl;
            return;
        }
        else if (P_groupe.size() != 0 && CS_groupe.size() == 0) {
            for (const auto& Pipe : P_groupe) {
                SavePipe(Pipe,out);
            }
        cout << "Данные о трубах записаны!" << endl;
        }
        else if (P_groupe.size() == 0 && CS_groupe.size() != 0) {
            for (const auto& compressor_station : CS_groupe) {
                SaveCS(compressor_station, out);
            }
        cout << "Данные о КС записаны!" << endl;
        }
        else if (P_groupe.size() != 0 && CS_groupe.size() != 0) {
            for (const auto& compressor_station : CS_groupe) {
                SaveCS(compressor_station, out);
            }
            for (const auto& Pipe : P_groupe) {
                SavePipe(Pipe, out);
            }
        cout << "Данные о трубах и КС записаны!" << endl;
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
    vector<Pipe> P_groupe;
    vector<compressor_station> CS_groupe;
    vector <Pipe> filterP;
    vector<compressor_station> filter_CS;
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            Pipe P;
            menu_new_Pipe(P);
            P_groupe.push_back(P);
        }
        else if (k == 2) {
            compressor_station CS;
            menu_new_ks(CS);
            CS_groupe.push_back(CS);
        }
        else if (k == 3) {
            view_all(P_groupe, CS_groupe,filterP, filter_CS);
        }
        else if (k == 4) {
            edit_Pipe(P_groupe, filterP);
        }
        else if (k == 5) {
            //edit_CS(CS);
        }
        else if (k == 6) {
            save(P_groupe, CS_groupe);
        }
        else if (k == 7) {
            //load(P, CS);
        }
    }
    return 0;
}