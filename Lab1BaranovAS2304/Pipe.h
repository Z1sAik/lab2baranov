#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class Pipe
{
public:
    int id;
    static int maxPipeID;
    string Name; //название трубы
    float length; //километры 
    int diameter; //миллиметры
    bool repair; //признак "в ремонте"

    Pipe() : id(0), Name(""), length(0.0f), diameter(0), repair(false) {
    } 

    Pipe(int P_id, string P_Name, float P_length, int P_diameter, bool P_repair){
        id = P_id;
        Name = P_Name;
        length = P_length;
        diameter = P_diameter;
        repair = P_repair;
    }

    int getID()
    {
        return id;
    }
    
};

void SavePipe(int id, const Pipe& pipe, ofstream& out);
void loadPipe(unordered_map<int, Pipe>& pipes, ifstream& in, int& maxPipeID);
void filter_P(const unordered_map<int, Pipe>& Pipes, string Name_def, int rep_def, vector<int>& filt_keys);
void menu_new_Pipe(Pipe& P);
void show_Pipe(const Pipe& P);
int edit_single_Pipe(unordered_map<int, Pipe>& Pipes, int id, int repair);