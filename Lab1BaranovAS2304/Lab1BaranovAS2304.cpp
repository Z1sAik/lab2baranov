#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
#include <unordered_map>
#include "functions.h"
using namespace std;

int main() {
    string filename = generate_filename();
    logFile.open(filename, std::ios::app);
    if (!logFile) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return 1;
    }
    vector<int> filt_keys_Pipe;
    vector<int> filt_keys_CS;
    setlocale(LC_ALL, "RU"); 
    unordered_map<int, Pipe> Pipes = {};
    unordered_map<int, compressor_station> Stations = {};
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            Pipe P;
            menu_new_Pipe(P);
            Pipes.insert({P.getID(),P});
        }
        else if (k == 2) {
            compressor_station CS;
            menu_new_ks(CS);
            Stations.insert({CS.getID(),CS});
        }
        else if (k == 3) {
            filter(Pipes, Stations,filt_keys_Pipe,filt_keys_CS);
        }
        else if (k == 4) {
            view_all(Pipes, Stations, filt_keys_Pipe, filt_keys_CS);
        }
        else if (k == 5) {
            edit_Pipe_filter(Pipes,filt_keys_Pipe);
        }
        else if (k == 6) {
            edit_CS_filter(Stations,filt_keys_CS);
        }
        else if (k == 7) {
            save(Pipes, Stations);
        }
        else if (k == 8) {
            load(Pipes, Stations, Pipe::maxPipeID, compressor_station::maxCSID);
        }
    }
    logFile.close();
    return 0;
}