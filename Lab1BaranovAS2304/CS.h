#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
class compressor_station
{
public:
    int id;
    static int maxCSID;
    string Name; //название КС
    int workshops; //Кол-во цехов
    int workshopsinwork; //Кол-во цехов в работе
    int effectiveness; //Коэфф. эффективности
    compressor_station() :id(0), Name(""), workshops(), workshopsinwork(), effectiveness() {
    }
    compressor_station(int CS_id, string CS_Name, int CS_workshops, int CS_workshopsinwork, int CS_effectiveness) {

        id = CS_id;
        Name = CS_Name;
        workshops = CS_workshops;
        workshopsinwork = CS_workshopsinwork;
        effectiveness = CS_effectiveness;
    }

    int getID()
    {
        return id;
    }

};
void SaveCS(int CSID, const compressor_station& CS, ofstream& out);
void loadCS(unordered_map<int, compressor_station>& Stations, ifstream& in, int& maxCSID);
void edit_single_CS(unordered_map<int, compressor_station>& Stations);
void edit_filtered_CS(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS);
void edit_CS_filter(unordered_map<int, compressor_station>& Stations, vector<int> filt_keys_CS);
void filter_CS(const unordered_map<int, compressor_station>& Stations, string Name_def, int work, vector<int>& filt_keys);
void menu_new_ks(compressor_station& CS);
void show_cs(const compressor_station& CS);
void load2(unordered_map<int, compressor_station>& Stations, int& maxCSID);