#pragma once
#include <string>
using namespace std;
class compressor_station
{
public:
    string Name; //название КС
    int workshops; //Кол-во цехов
    int workshopsinwork; //Кол-во цехов в работе
    int effectiveness; //Коэфф. эффективности
    compressor_station() : Name(""), workshops(), workshopsinwork(), effectiveness() {
    }
    compressor_station(string CS_Name, int CS_workshops, int CS_workshopsinwork, int CS_effectiveness) {

        Name = CS_Name;
        workshops = CS_workshops;
        workshopsinwork = CS_workshopsinwork;
        effectiveness = CS_effectiveness;
    }

};
