#pragma once
#include <string>
using namespace std;
class compressor_station
{
public:
    string Name; //�������� ��
    int workshops; //���-�� �����
    int workshopsinwork; //���-�� ����� � ������
    int effectiveness; //�����. �������������
    compressor_station() : Name(""), workshops(), workshopsinwork(), effectiveness() {
    }
    compressor_station(string CS_Name, int CS_workshops, int CS_workshopsinwork, int CS_effectiveness) {

        Name = CS_Name;
        workshops = CS_workshops;
        workshopsinwork = CS_workshopsinwork;
        effectiveness = CS_effectiveness;
    }

};
