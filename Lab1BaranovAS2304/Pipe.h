#pragma once
#include <string>
using namespace std;
class Pipe
{
public:
    string Name; //�������� �����
    float length; //��������� 
    int diameter; //����������
    bool repair; //������� "� �������"
    Pipe() : Name(""), length(), diameter(), repair() {
    }
    Pipe(string P_Name, float P_length, int P_diameter, bool P_repair) {

        Name = P_Name;
        length = P_length;
        diameter = P_diameter;
        repair = P_repair;
    }
    
};