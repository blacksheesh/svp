#ifndef OBJECTS_H
#define OBJECTS_H
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
class Objects
{

public:
    Objects();
};

struct RoutePoint
{
    int xKm, yKm;
    string name;
    RoutePoint(int xKm, int yKm, string name) : xKm(xKm), yKm(yKm), name(name) {}

};


class IVehicle
{
public:
    virtual bool drive(int kilometres) = 0;
    virtual void refuel() = 0;
    virtual void printStatus() = 0;
    virtual int getMilage() = 0;
    virtual int getFuelLevel() = 0;
};

class Route
{
public:
    vector <string> v;
    vector <int> v1;
    vector <int> v2;
    int xKm1, yKm1;
    int  dist;

    void addPoint(const RoutePoint& point)
    {
        v.push_back(point.name);
        v1.push_back(point.xKm);
        v2.push_back(point.yKm);
    }
    void  run(IVehicle* vehicle)
    {
        if (v.size() < 2)
        {
            cout << "Ошибка!" << endl;

        }
        else
        {
            for (size_t i = 0; i < v1.size() - 1; ++i)
            {
                xKm1 = v1[i + 1] - v1[i];
                yKm1 = v2[i + 1] - v2[i];
                dist = static_cast<int>(sqrt((pow(xKm1, 2) + pow(yKm1, 2))));
                if (!vehicle->drive(dist))
                {
                    vehicle->refuel();
                    if (!vehicle->drive(dist))
                    {
                        cout << "Нельзя проехать данный маршрут" << endl;
                        return;
                    }
                }
            }
           // vehicle->printStatus();
        }

    }
};


class AbstractCar : public IVehicle
{
protected:
    int distance;
    int fuel;
    int tankcapacity;
    double fuelConsumption;
    //AbstractCar() {};

public:
    AbstractCar(double _fuelConsumption, int _fuel) : distance(0), fuel(_fuel),
fuelConsumption(_fuelConsumption) {}

    bool drive(int kilometres)
    {
        int requiredFuel = static_cast<int>(kilometres * fuelConsumption);
        if (fuel < requiredFuel)
        {
            cout << "Недостаточно топлива для прохождения данной дистанции!" << endl;
            return false;
        }

        distance += kilometres;
        fuel -= requiredFuel;
        return true;
    }

    void refuel()
    {
        fuel = tankcapacity;

    }

    void printStatus()
    {
        cout << "Пробег: " << distance << " км" << endl;
        cout << "Остаток топлива: " << fuel << "%" << endl;
    }

    int getMilage()
    {
        return distance;
    }
    int getFuelLevel()
    {
        return fuel;
    }
};

class Sedan : public AbstractCar
{
public:
    Sedan() :AbstractCar(fuelConsumption, 60)
    {
        tankcapacity = 60;
        fuelConsumption = 0.1;
    }
};

class Suv : public AbstractCar
{
public:
    Suv() :AbstractCar(fuelConsumption, 80)
    {
        tankcapacity = 80;
        fuelConsumption = 0.25;
    }
};

class Bus : public AbstractCar
{
public:
    Bus() : AbstractCar(fuelConsumption, 100)
    {
        tankcapacity = 100;
        fuelConsumption = 0.35;
    }
};


class Bicycle : public IVehicle
{
private:
    int distance = 0;

public:

    bool drive(int kilometres)
    {
        distance += kilometres;
        return true;
    }

    void refuel()
    {
        //не тратится :)
    }

    void printStatus()
    {
        cout << "Пробег: " << distance << " км" << endl;
    }
    int getMilage()
    {
       return distance;
    }
    int getFuelLevel()
    {

    }

};
