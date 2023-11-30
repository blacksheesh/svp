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
    double ostfuelroad; // Оставшееся топливо для текущего пути
    int run;            // Общее пройденное расстояние
    const double bak;   // Максимальная вместимость бака
    double fuelroad;    // Максимальное расстояние, которое можно проехать с полным баком

public:
    AbstractCar(double fuelbak, const double maxfuelroad, const double rashod) : run(0), fuel(fuelbak), bak(fuelbak), fuelroad(maxfuelroad), rashod(rashod) {}     // Параметризованный конструктор

    AbstractCar() : fuel(0), rashod(0), ostfuelroad(0), run(0), bak(0), fuelroad(0) {} // Добавляем конструктор по умолчанию

    void refuel() // Функция для заправки автомобиля
    {
        double refuel = bak - fuel;
        fuel += refuel;
        ostfuelroad = fuelroad;
        cout << "Заправка прошла успешно. В баке " << fuel << " литров топлива." << endl;
    }

    bool drive(int kilometers)  // Функция для передвижения на заданное расстояние
    {
        double fuelNeeded = static_cast<double>(kilometers) / rashod;
        if (ostfuelroad >= kilometers && fuel >= fuelNeeded)
        {
            run += kilometers;
            fuel -= fuelNeeded;
            ostfuelroad -= kilometers;
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
    Suv() : AbstractCar(70, 420, 25) {}


};

class Sedan : public AbstractCar // Класс для седанов, наследующийся от AbstractCar
{
public:
    Sedan() : AbstractCar(43, 614, 7) {} // Легковая машина, бак на 43 литров, расход 7.0 л/100 км


};

class Bus : public AbstractCar // Класс для автобусов, наследующийся от AbstractCar
{
public:
    Bus() : AbstractCar(120, 700, 20) {}


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
            for (auto& point : points)
            {
                cout << "Конец маршрута в точке: (" << point.Xkm << "," << point.Ykm << ") " << point.name << endl;
                int road = sqrt(pow(point.Xkm, 2) + pow(point.Ykm, 2));
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
            cerr << "ОШИБКА! Введите верное количество точек!" << endl;
        }

    }

    ~Route() = default;
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 2) {
        cout << "Ошибка: Необходимо указать имя файла с маршрутом." << endl;
        return 1;
    }

    ifstream file("route.txt");//(argv[1]);
    if (!file.is_open()) {
        cout << "Ошибка: Невозможно открыть файл с маршрутом." << endl;
        return 1;
    }

    Route route;
    int x, y;
    string name;

    while (file >> x >> y >> name) {
        route.addPoint({ x, y, name });
    }

    file.close();

    cout << "Маршрут из файла:" << endl;

    IVehicle* vehicles[4] = { new Sedan(), new Suv(), new Bus(), new Bicycle() };
    for (int i = 0; i < 4; ++i) {
        IVehicle* vehicle = vehicles[i];
        route.run(new Sedan());
        delete vehicle;
        cout << endl;
    }

       return 0;
}
