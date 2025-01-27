#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

struct Car {
    int car_id;
    string mark_c;
    string model;
    double price_per_day;
    vector<string> features;
    pair<double, double> location;

    Car(int id, string mk, string mdl, double price, vector<string> f_s, pair<double, double> loc) {
        car_id = id;
        mark_c = mk;
        model = mdl;
        price_per_day = price;
        features = f_s;
        location = loc;
    }
};

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
