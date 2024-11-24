#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "CS.h"
#include <unordered_map>
#include "functions.h"
using namespace std;

int main() {
    vector<int> filt_keys_Pipe;
    vector<int> filt_keys_CS;
    setlocale(LC_ALL, "RU"); 
    Pipe P;
    compressor_station CS;
    unordered_map<int, Pipe> Pipes = {};
    unordered_map<int, compressor_station> Stations = {};
    while (true) {
        int k = menu();
        if (k == 0) {
            break;
        }
        else if (k == 1) {
            menu_new_Pipe(P);
            Pipes.insert({P.getID(),P});
        }
        else if (k == 2) {
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
            load(Pipes, Pipe::maxPipeID);
            load2(Stations, compressor_station::maxCSID);
        }
    }
    return 0;
}