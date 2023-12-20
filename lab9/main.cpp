#include <iostream>
#include "windows.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <..\objects\objects.h>
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream file;
    string str;

    if (argc < 2)
    {
        cout << "Ошибка! Подайте на вход файл с маршрутом." << endl;
        return 1;
    }
    string filePath = argv[1];

    cout << argv[0] << argv[1] << endl;
    file.open(argv[1]);
    if (!file)
    {
        cout << "Ошибка! Невозможно открыть файл с маршрутом." << endl;
        return 1;
    }
    int x, y;
    Route routes;
    while (file >> x >> y >> str)
    {
        routes.addPoint(RoutePoint(x, y, str));
    }

    file.close();

    IVehicle* vehicles[4] = { new Sedan, new Suv, new Bus,new Bicycle };
    for (int i = 0; i < 4; ++i)
    {
        IVehicle* vehicle = vehicles[i];
        cout << "Транспорт " << i << endl;

        routes.run(vehicle);
        vehicle->printStatus();
        delete vehicle;
        cout << endl;

    }
    return 0;
};
