#include <iostream>
#include <string>
using namespace std;
// Класс-интерфейс IVehicle (транспортное средство)
class IVehicle {
public:
    virtual void drive(int kilometers) = 0;
    virtual void refuel() = 0;
    virtual void printStatus() = 0;
};
// Класс AbstractCar (базовый класс для автомобилей)
class AbstractCar : public IVehicle {
protected:
    int run;         // пробег
    double fuel;         // количество топлива в баке (в литрах)
    const double volumeTank; // вместимость бака (в литрах)
    const double consumptionFuel; // расход топлива (литры на 100 км)
public:
    AbstractCar(double volume, double consumption)
        : run(0), fuel(0), volumeTank(volume), consumptionFuel(consumption) {}
    void drive(int kilometers) override {
        double fuelNeeded = (static_cast<double>(kilometers) / 100.0) * consumptionFuel;
        if (fuel >= fuelNeeded) {
            run += kilometers;
            fuel -= fuelNeeded;
            cout << "Пройдено расстояние: " << kilometers << " км. Осталось топлива: " << fuel << " литров." << endl;
        }
        else {
            cout << "Недостаточно топлива для поездки на расстояние " << kilometers << " км." << endl;
        }
    }
    void refuel() override {
        fuel = volumeTank;
        cout << "Заправка прошла успешно. В баке " << fuel << " литров топлива." << endl;
    }
    void printStatus() override {
        cout << "Пробег: " << run << " км. Осталось топлива: " << fuel << " литров." << endl;
    }
};
// Класс Sedan (легковая машина)
class Sedan : public AbstractCar {
public:
    Sedan() : AbstractCar(43.0, 7.0) {} // Легковая машина, бак на 43 литров, расход 7.0 л/100 км
};
// Класс Suv (внедорожник)
class Suv : public AbstractCar {
public:
    Suv() : AbstractCar(80.0, 10.0) {} // Внедорожник, бак на 80 литров, расход 10.0 л/100 км
};
// Класс Bus (автобус)
class Bus : public AbstractCar {
public:
    Bus() : AbstractCar(200.0, 15.0) {} // Автобус, бак на 200 литров, расход 15.0 л/100 км
};
// Класс Bicycle (велосипед)
class Bicycle : public IVehicle {
private:
    int mileage; // пробег велосипеда
public:
    Bicycle() : mileage(0) {}
    void drive(int kilometers) override {
        mileage += kilometers;
        cout << "Пройдено расстояние: " << kilometers << " км. Пробег велосипеда: " << mileage << " км." << endl;
    }
    void refuel() override {
        // У велосипеда нет бака и топлива, поэтому этот метод не делает ничего.
        cout << "Велосипед не имеет бака для заправки." << endl;
    }
    void printStatus() override {
        cout << "Пробег велосипеда: " << mileage << " км." << endl;
    }
};
int main() {
    setlocale(LC_ALL, "ru");
    IVehicle* vehicles[4] = { new Sedan(), new Suv(), new Bus(), new Bicycle() };
    for (int i = 0; i < 4; ++i) {
        IVehicle* vehicle = vehicles[i];
        vehicle->refuel();
        vehicle->printStatus();
        vehicle->drive(120);
        vehicle->printStatus();
        vehicle->drive(420);
        vehicle->printStatus();
        vehicle->drive(300);
        vehicle->printStatus();
        vehicle->refuel();
        vehicle->drive(300);
        vehicle->printStatus();
        delete vehicle;
        cout << endl;
    }
    return 0;
}
