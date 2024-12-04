#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
#include <unordered_map>
#include "functions.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "RU"); 
    unordered_map<int, Pipe> Pipes = {};
    unordered_map<int, compressor_station> Stations = {};
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            Pipe P = Pipe::newPipe();
            Pipes.emplace(P.getID(), P);
        }
        else if (k == 2) {
            compressor_station CS = compressor_station::newCS();
            Stations.emplace(CS.getID(), CS);
        }
        else if (k == 3) {
            //filter(Pipes, Stations,filt_keys_Pipe,filt_keys_CS);
        }
        else if (k == 4) {
            if (Pipes.empty() && Stations.empty()) {
                cout << "Вы ещё не добавили ни одного объекта" << endl;
            }

            else
            {
                cout << "Все трубы:" << endl; 
                view(Pipes);
                cout << "Все компрессорные станции:" << endl; 
                view(Stations);
            }
        }
        else if (k == 5) {
            //edit_filtered_objects(Pipes, filt_keys_Pipe,show_Pipe,edit_single_Pipe);
        }
        else if (k == 6) {
            //edit_filtered_objects(Stations, filt_keys_CS,show_cs,edit_single_CS);
        }
        else if (k == 7) {
            save(Pipes, Stations);
        }
        else if (k == 8) {
            load(Pipes, Stations);
        }
        else if (k == 9) {
            //remove_objects(Pipes, Stations, filt_keys_Pipe, filt_keys_CS);
        }
    }
    return 0;
}