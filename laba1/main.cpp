#include <iostream>

using namespace std;

int main() {
    char choice;
    cout << "What do you want to calculate? (v - speed, t - time, s - distance): ";
    cin >> choice;

    if (choice == 'v') {
        // Calculate velocity
        double distance, time;
        cout << "Enter distance (in kilometers): ";
        cin >> distance;
        cout << "Enter time (in hours): ";
        cin >> time;

        double speed = distance / time;
        cout << "Speed: " << speed << " km/h" << endl;
    } else if (choice == 't') {
        // Calculate time
        double distance, speed;
        cout << "Enter distance (in kilometers): ";
        cin >> distance;
        cout << "Enter speed (in km/h): ";
        cin >> speed;

        double time = distance / speed;
        cout << "Time: " << time << " hours" << endl;
    } else if (choice == 's') {
        // Calculate distance
        double speed, time;
        cout << "Enter speed (in km/h): ";
        cin >> speed;
        cout << "Enter time (in hours): ";
        cin >> time;

        double distance = speed * time;
        cout << "Distance: " << distance << " km" << endl;
    } else {
        cout << "Invalid choice. Please select 'v', 't', or 's'." << endl;
    }

    return 0;
}
