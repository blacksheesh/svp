#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class IVehicle // Интерфейс для транспортных средств
{
public:
    virtual bool drive(int kilometers) = 0; // Виртуальная функция для передвижения на заданное расстояние
    virtual void refuel() = 0;  // Виртуальная функция для заправки транспортного средства
    virtual void printstatus() = 0; // Виртуальная функция для вывода статуса транспортного средства

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

    AbstractCar() : fuel(0), rashod(0), run(0), bak(0){} // Добавляем конструктор по умолчанию

    void refuel() // Функция для заправки автомобиля
    {
        fuel = bak;
            cout << "Заправка прошла успешно. В баке " << fuel << " литров топлива." << endl;
    }

    bool drive(int kilometers)  // Функция для передвижения на заданное расстояние
    {
        double fuelNeeded = static_cast<double>(kilometers) / rashod;
        if ( fuel >= fuelNeeded)
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
        cout << "Пробег: " << run << " км. Осталось топлива: " << fuel << " литров." << endl;
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
        cout << "Велосипед не имеет бака для заправки." << endl;
    }

    void printstatus() // Функция для вывода статуса велосипеда
    {
        cout << "Пробег велосипеда: " << km << " км." << endl;
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
                cout << "Проехали: " << road << endl;
                if (!vehicle->drive(road))
                {
                    cout << "Не хватает топлива. Нужна дозаправка." << endl;
                    vehicle->refuel();

                    // Попытаемся проехать еще раз после дозаправки
                    if (!vehicle->drive(road))
                    {
                        cout << "Не удалось проехать даже после дозаправки." << endl;
                        vehicle->printstatus();
                        break; // Прерываем цикл, если не удалось проехать даже после дозаправки
                    }
                }
                vehicle->printstatus();
            }

        }
        else {
            cout << "ОШИБКА! Введите верное количество точек!" << endl;
        }

    }


};

int main()
{
    setlocale(LC_ALL, "Russian");
    Route routes[2];
    routes[0].addPoint(RoutePoint(0, 0, "Point1"));
    routes[0].addPoint(RoutePoint(100, 0, "Point2"));
    routes[0].addPoint(RoutePoint(200, 100, "Point3"));
    routes[0].addPoint(RoutePoint(300, 300, "Point4"));
    routes[0].addPoint(RoutePoint(100, 400, "Point5"));
    routes[1].addPoint(RoutePoint(0, 0, "Урюпинск"));
    routes[1].addPoint(RoutePoint(0, 540, "Воронеж"));
    routes[1].addPoint(RoutePoint(420, 540, "Борисоглебск"));

    IVehicle* vehicles[4] = { new Sedan, new Suv, new Bus, new Bicycle };
    for (int i = 0; i < 4; i++)
    {
        IVehicle* vehicle = vehicles[i];
        routes[0].run(vehicle);
        routes[1].run(vehicle);
        delete vehicle;
        cout << endl;
    }
    return 0;
}
