#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class IVehicle // Интерфейс для транспортных средств
{
public:
    virtual bool drive(int kilometers) = 0; // Виртуальная функция для передвижения на заданное расстояние
    virtual void refuel() = 0;  // Виртуальная функция для заправки транспортного средства
    virtual void printstatus() = 0; // Виртуальная функция для вывода статуса транспортного средства
    virtual ~IVehicle() = default;  // Виртуальный деструктор для интерфейса
};

class AbstractCar : public IVehicle // Абстрактный класс для автомобилей, реализующий интерфейс IVehicle
{
protected:
    double fuel;        // Текущий уровень топлива
    const double rashod; // Расход топлива
    int run;            // Общее пройденное расстояние
    const double bak;   // Максимальная вместимость бака

public:
    AbstractCar(double fuelbak, const double rashod) : run(0), fuel(fuelbak), bak(fuelbak), rashod(rashod) {}     // Параметризованный конструктор

    AbstractCar() : fuel(0), rashod(0), run(0), bak(0) {} // Добавляем конструктор по умолчанию

    void refuel() // Функция для заправки автомобиля
    {
        double refuel = bak - fuel;
        fuel += refuel;
        cout << "Refueling was successful. In the tank " << fuel << " liters of fuel." << endl;
    }

    bool drive(int kilometers)  // Функция для передвижения на заданное расстояние
    {
        double fuelNeeded = static_cast<double>(kilometers) / rashod;
        if (fuel >= fuelNeeded)
        {
            run += kilometers;
            fuel -= fuelNeeded;
            return true;
        }
        else
        {
            return false;
        }
    }

    void printstatus() // Функция для вывода статуса автомобиля
    {
        cout << "Mileage: " << run << " km. Remaining fuel: " << fuel << " liters." << endl;
    }

};

class Suv : public AbstractCar // Класс для внедорожников, наследующийся от AbstractCar
{
public:
    Suv() : AbstractCar(60, 25) {}


};

class Sedan : public AbstractCar // Класс для седанов, наследующийся от AbstractCar
{
public:
    Sedan() : AbstractCar(43, 7) {} // Легковая машина, бак на 43 литров, расход 7.0 л/100 км


};

class Bus : public AbstractCar // Класс для автобусов, наследующийся от AbstractCar
{
public:
    Bus() : AbstractCar(100, 20) {}


};

class Bicycle : public IVehicle // Класс для велосипедов, реализующий интерфейс IVehicle
{
private:
    int km; // Пройденное расстояние велосипеда

public:
    Bicycle() : km(0) {}

    bool drive(int kilometers) // Функция для передвижения на заданное расстояние
    {
        km += kilometers;
        return true;
    }

    void refuel()  // Функция для заправки велосипеда (пустая, так как у велосипеда нет бака и топлива)
    {
        cout << "The bicycle does not have a fuel tank." << endl;
    }

    void printstatus() // Функция для вывода статуса велосипеда
    {
        cout << "Bike mileage : " << km << " km." << endl;
    }
};

struct RoutePoint // Структура для точек маршрута
{
public:
    int Xkm;      // Координата X точки маршрута
    int Ykm;      // Координата Y точки маршрута
    string name;  // Имя точки маршрута

    RoutePoint() : Xkm(0), Ykm(0), name("Default") {} // Конструктор по умолчанию

    RoutePoint(int kmx, int kmy, string nam) : Xkm(kmx), Ykm(kmy), name(nam) {} // Параметризованный конструктор
};

class Route : public AbstractCar // Класс для маршрута, наследующийся от AbstractCar
{
private:
    vector<RoutePoint> points; // Вектор точек маршрута

public:
    Route(const vector<RoutePoint>& routePoints) : points(routePoints) {} // Параметризованный конструктор

    Route() : AbstractCar(), points() {}  // Добавляем конструктор по умолчанию

    void addPoint(const RoutePoint& point) // Функция для добавления точки к маршруту
    {
        points.push_back(point);
    }

    void run(IVehicle* vehicle) // Функция для прохождения маршрута транспортным средством
    {
        if (points.size() >= 2) {
            for (int i = 0; i < points.size() - 1; i++)
            {
                int xDiff = points[i + 1].Xkm - points[i].Xkm;
                int yDiff = points[i + 1].Ykm - points[i].Ykm;
                int road = sqrt(xDiff * xDiff + yDiff * yDiff);
                cout << "Has drven: " << road << endl;
                if (!vehicle->drive(road))
                {
                    cout << "Not enough fuel. Need refueling." << endl;
                    vehicle->refuel();

                    // Попытаемся проехать еще раз после дозаправки
                    if (!vehicle->drive(road))
                    {
                        cout << "Couldn't drive through even after refueling." << endl;
                        vehicle->printstatus();
                        break; // Прерываем цикл, если не удалось проехать даже после дозаправки
                    }
                }
                vehicle->printstatus();
            }

        }
        else {
            cerr << "ERROR! Enter the correct number of points!" << endl;
        }

    }

    ~Route() = default;
};

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Oh oh! Specify the file route!" << endl;
        return 1;
    }

    ifstream file(argv[1]);//(argv[1]);
    
    if (!file.is_open()){
        cout << "Cannot open file!" << endl;
        return 1;
    }
    Route route;
    int x, y;
    string name;

    while (file >> x >> y >> name) {
        route.addPoint({ x, y, name });
    }

    file.close();

    cout << "Route from file: " << endl;

    IVehicle* vehicles[4] = { new Sedan(), new Suv(), new Bus(), new Bicycle() };
    for (int i = 0; i < 4; ++i) {
        IVehicle* vehicle = vehicles[i];
        route.run(vehicle);
        delete vehicle;
        cout << endl;
    }

    return 0;
}
