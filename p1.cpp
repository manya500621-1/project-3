#include <iostream>
#include <string>

using namespace std;

class Vehicle {
private:
    int id;
    string mfg;
    string mdl;
    int yr;

public:
    static int total;

    Vehicle(int i = 0, string m = "", string md = "", int y = 0) {
        id = i;
        mfg = m;
        mdl = md;
        yr = y;
        total++;
    }

    virtual ~Vehicle() {}

    void setId(int i) { id = i; }
    int getId() { return id; }

    void setMfg(string m) { mfg = m; }
    string getMfg() { return mfg; }

    void setMdl(string md) { mdl = md; }
    string getMdl() { return mdl; }

    void setYr(int y) { yr = y; }
    int getYr() { return yr; }

    virtual void show() {
        cout << "ID: " << id << " | Mfg: " << mfg << " | Model: " << mdl << " | Year: " << yr;
    }
};

int Vehicle::total = 0;

class Car : public Vehicle {
protected:
    string fuel;

public:
    Car(int i = 0, string m = "", string md = "", int y = 0, string f = "") 
        : Vehicle(i, m, md, y) {
        fuel = f;
    }

    void setFuel(string f) { fuel = f; }
    string getFuel() { return fuel; }

    void show() override {
        Vehicle::show();
        cout << "  Fuel: " << fuel;
    }
};

class ElectricCar : public Car {
protected:
    int bat;

public:
    ElectricCar(int i = 0, string m = "", string md = "", int y = 0, string f = "", int b = 0)
        : Car(i, m, md, y, f) {
        bat = b;
    }

    void setBat(int b) { bat = b; }
    int getBat() { return bat; }

    void show() override {
        Car::show();
        cout << " Bat: " << bat << "kWh";
    }
};

class Aircraft {
protected:
    int rng;

public:
    Aircraft(int r = 0) {
        rng = r;
    }

    virtual ~Aircraft() {}

    void setRng(int r) { rng = r; }
    int getRng() { return rng; }

    virtual void showAir() {
        cout << " Range: " << rng << "km";
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int i = 0, string m = "", string md = "", int y = 0, string f = "", int r = 0)
        : Car(i, m, md, y, f), Aircraft(r) {}

    void show() override {
        Car::show();
        Aircraft::showAir();
    }
};

class SportsCar : public ElectricCar {
private:
    int spd;

public:
    SportsCar(int i = 0, string m = "", string md = "", int y = 0, string f = "", int b = 0, int s = 0)
        : ElectricCar(i, m, md, y, f, b) {
        spd = s;
    }

    void setSpd(int s) { spd = s; }
    int getSpd() { return spd; }

    void show() override {
        ElectricCar::show();
        cout << "  Top Speed: " << spd << "km/h";
    }
};

class Sedan : public Car {
private:
    int boot;

public:
    Sedan(int i = 0, string m = "", string md = "", int y = 0, string f = "", int b = 0)
        : Car(i, m, md, y, f) {
        boot = b;
    }

    void show() override {
        Car::show();
        cout << " Boot Space: " << boot << "L";
    }
};

class SUV : public Car {
private:
    bool awd;

public:
    SUV(int i = 0, string m = "", string md = "", int y = 0, string f = "", bool a = false)
        : Car(i, m, md, y, f) {
        awd = a;
    }

    void show() override {
        Car::show();
        cout << " AWD: " << (awd ? "Yes" : "No");
    }
};

class VehicleRegistry {
private:
    Vehicle* list[100];
    int count;

public:
    VehicleRegistry() {
        count = 0;
    }

    ~VehicleRegistry() {
        for (int i = 0; i < count; i++) {
            delete list[i];
        }
    }

    void add(Vehicle* v) {
        if (count < 100) {
            list[count++] = v;
            cout << "Vehicle added successfully.\n";
        } else {
            cout << "Registry full!\n";
        }
    }

    void viewAll() {
        if (count == 0) {
            cout << "No vehicles in registry.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            list[i]->show();
            cout << endl;
        }
        cout << "Total registered: " << Vehicle::total << endl;
    }

    void search(int id) {
        for (int i = 0; i < count; i++) {
            if (list[i]->getId() == id) {
                cout << "Found: ";
                list[i]->show();
                cout << endl;
                return;
            }
        }
        cout << "Vehicle not found.\n";
    }
};

int main() {
    VehicleRegistry reg;
    int ch;

    do {
        cout << "1. Add Vehicle 2. View All 3. Search by ID 4. Exit Enter choice: ";
        cin >> ch;

        if (ch == 1) {
            int type, i, y;
            string m, md, f;
            cout << "Types 1. Car 2. Electric Car 3. Flying Car 4. Sports Car 5. Sedan 6. SUV Choose type: ";
            cin >> type;

            cout << "Enter ID: "; cin >> i;
            cout << "Enter Mfg: "; cin.ignore(); getline(cin, m);
            cout << "Enter Model: "; getline(cin, md);
            cout << "Enter Year: "; cin >> y;

            if (type == 1) {
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                reg.add(new Car(i, m, md, y, f));
            } else if (type == 2) {
                int b;
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                cout << "Enter Bat (kWh): "; cin >> b;
                reg.add(new ElectricCar(i, m, md, y, f, b));
            } else if (type == 3) {
                int r;
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                cout << "Enter Range (km): "; cin >> r;
                reg.add(new FlyingCar(i, m, md, y, f, r));
            } else if (type == 4) {
                int b, s;
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                cout << "Enter Bat (kWh): "; cin >> b;
                cout << "Enter Top Speed: "; cin >> s;
                reg.add(new SportsCar(i, m, md, y, f, b, s));
            } else if (type == 5) {
                int boot;
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                cout << "Enter Boot Space (L): "; cin >> boot;
                reg.add(new Sedan(i, m, md, y, f, boot));
            } else if (type == 6) {
                bool a;
                cout << "Enter Fuel: "; cin.ignore(); getline(cin, f);
                cout << "Enter AWD (1 for Yes, 0 for No): "; cin >> a;
                reg.add(new SUV(i, m, md, y, f, a));
            }
        } else if (ch == 2) {
            reg.viewAll();
        } else if (ch == 3) {
            int searchId;
            cout << "Enter ID to search: ";
            cin >> searchId;
            reg.search(searchId);
        }
    } while (ch != 4);

    return 0;
}