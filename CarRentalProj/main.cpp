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
    Car() : car_id(0), mark_c(""), model(""), price_per_day(0.0), features({}), location({0.0, 0.0}) {}
    Car(int id, string mk, string mdl, double price, vector<string> f_s, pair<double, double> loc) {
        car_id = id;
        mark_c = mk;
        model = mdl;
        price_per_day = price;
        features = f_s;
        location = loc;
    }
};
struct Customer {
    int customer_id;
    string name;
    string contact;
    Customer() : customer_id(0), name(""), contact("") {}
    Customer(int id, string nm, string c_t) {
        customer_id = id;
        name = nm;
        contact = c_t;
    }
};
struct RentalOrder {
    int order_id;
    Customer customer;
    Car car;
    int rental_days;
    double total_price;

    RentalOrder(int id, Customer cust, Car carr, int days)
    {
        order_id = id;
        customer = cust;
        car = carr;
        rental_days = days;
        total_price = days * carr.price_per_day;
    }
};
class RentalService
{
private:
    list<Car> available_cars;
    queue<pair<Customer, pair<double, double>>> rental_requests;
    double distance(pair<double, double> loc1, pair<double, double> loc2) {
        return sqrt(pow(loc1.first - loc2.first, 2) + pow(loc1.second - loc2.second, 2));
    }

public:
    
};

int main() {
    cout << "Hello, World!\n";
    return 0;
}
