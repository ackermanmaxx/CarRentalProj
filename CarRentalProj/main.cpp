#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <list>
#include <unordered_set>

using namespace std;

struct Car {
    int car_id;
    string mark_c;
    string model;
    double price_per_day;
    vector<string> features;
    pair<double, double> location;
    bool is_rented;

    Car() {
        car_id = 0;
        mark_c = "";
        model = "";
        price_per_day = 0.0;
        features = {};
        location = {0.0, 0.0};
        is_rented = false;
    }

    Car(int id, string mk, string mdl, double price, vector<string> f_s, pair<double, double> loc) {
        car_id = id;
        mark_c = mk;
        model = mdl;
        price_per_day = price;
        features = f_s;
        location = loc;
        is_rented = false;
    }
};

struct Customer {
    int customer_id;
    string name;
    string contact;

    Customer() {
        customer_id = 0;
        name = "";
        contact = "";
    }

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

    RentalOrder(int id, Customer cust, Car carr, int days) {
        order_id = id;
        customer = cust;
        car = carr;
        rental_days = days;
        total_price = days * carr.price_per_day;
    }
};

class RentalService {
private:
    list<Car> available_cars;
    queue<RentalOrder> orders_queue;
    unordered_set<int> rented_car_ids;

    double distance(pair<double, double> loc1, pair<double, double> loc2) {
        return sqrt(pow(loc1.first - loc2.first, 2) + pow(loc1.second - loc2.second, 2));
    }

public:
    void addCar(const Car& car) {
        available_cars.push_back(car);
    }

    void sortCars(const string& method, pair<double, double> user_location = {0.0, 0.0}) {
        if (method == "price") {
            available_cars.sort([](const Car& a, const Car& b) {
                return a.price_per_day < b.price_per_day;
            });
        } else if (method == "features") {
            available_cars.sort([](const Car& a, const Car& b) {
                return a.features.size() > b.features.size();
            });
        } else if (method == "distance") {
            available_cars.sort([&](const Car& a, const Car& b) {
                return distance(a.location, user_location) < distance(b.location, user_location);
            });
        }
    }

    void requestRentalInteractive() {
        cout << "Enter customer ID: ";
        int customer_id;
        cin >> customer_id;

        cout << "Enter customer name: ";
        string name;
        cin.ignore();
        getline(cin, name);

        cout << "Enter customer contact: ";
        string contact;
        getline(cin, contact);

        Customer customer(customer_id, name, contact);

        cout << "Enter customer location (x y): ";
        double x, y;
        cin >> x >> y;

        cout << "Choose sorting method (price, features, distance): ";
        string sort_method;
        cin >> sort_method;

        if (sort_method == "distance") {
            sortCars(sort_method, {x, y});
        } else {
            sortCars(sort_method);
        }

        cout << "\nAvailable cars (sorted):\n";
        int index = 1;
        for (const auto& car : available_cars) {
            if (rented_car_ids.count(car.car_id) == 0) {
                cout << index++ << ". Car ID: " << car.car_id << ", Make: " << car.mark_c << ", Model: " << car.model
                     << ", Price per day: " << car.price_per_day << ", Features: ";
                for (const auto& feature : car.features) {
                    cout << feature << " ";
                }
                cout << ", Distance: " << distance(car.location, {x, y}) << endl;
            }
        }

        if (!available_cars.empty()) {
            cout << "\nEnter the number of the car you want to rent: ";
            int car_choice;
            cin >> car_choice;

            auto it = available_cars.begin();
            advance(it, car_choice - 1);

            Car selected_car = *it;

            if (rented_car_ids.count(selected_car.car_id) > 0) {
                cout << "Sorry, this car has already been rented." << endl;
                return;
            }

            cout << "Enter rental days: ";
            int rental_days;
            cin >> rental_days;

            double total_price = rental_days * selected_car.price_per_day;
            cout << "Total price for rental: " << total_price << endl;

            cout << "Do you want to proceed with the order? (yes/no): ";
            string confirmation;
            cin >> confirmation;

            if (confirmation == "yes" || confirmation == "YES") {
                int order_id = orders_queue.size() + 1;
                RentalOrder order(order_id, customer, selected_car, rental_days);
                orders_queue.push(order);
                rented_car_ids.insert(selected_car.car_id);

                cout << "Rental order created successfully!" << endl;
                cout << "Order ID: " << order_id << ", Car: " << selected_car.mark_c << " " << selected_car.model
                     << ", Total price: " << order.total_price << endl;
            } else {
                cout << "Order not confirmed. Returning to the menu." << endl;
            }
        } else {
            cout << "No cars available for rental." << endl;
        }
    }

    void displaySavedOrders() {
        if (orders_queue.empty()) {
            cout << "No rental orders saved." << endl;
            return;
        }

        cout << "\nSaved rental orders:\n";

        queue<RentalOrder> temp_queue = orders_queue;

        while (!temp_queue.empty()) {
            RentalOrder order = temp_queue.front();
            temp_queue.pop();

            cout << "Order ID: " << order.order_id << ", Customer: " << order.customer.name
                 << ", Car: " << order.car.mark_c << " " << order.car.model << ", Total price: " << order.total_price
                 << endl;
        }
    }
};

int main() {
    RentalService rentalService;
    rentalService.addCar(Car(1, "Lada", "Priora", 250.0, {"Stens", "Red colour"}, {90.0, 134.0}));
    rentalService.addCar(Car(2, "Lada", "Calina", 155.0, {"Dorogo", "Ploho"}, {500.0, 3.0}));
    rentalService.addCar(Car(3, "Daewoo", "Matiz", 1000.0, {"Backup Camera"}, {402.0, 113.0}));
    rentalService.addCar(Car(4, "BMW", "M8", 2000.0, {"650HP", "Switching Drives", "Alcantara"}, {200.0, 150.0}));

    int choice;
    do {
        cout << "\nCar Rental System Menu:" << endl;
        cout << "1. Request a rental" << endl;
        cout << "2. View saved rental orders" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                rentalService.requestRentalInteractive();
                break;
            }
            case 2: {
                rentalService.displaySavedOrders();
                break;
            }
            case 3: {
                cout << "Exiting system. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 3);

    return 0;
}
//comment
//comment
//comment
