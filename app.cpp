#include <iostream>
#include <cmath>

const double g = 9.81;

double calculateHeight(double u, double angle_rad) {
    return (u * u * sin(2 * angle_rad)) / (2 * g);
}

double calculateTimeOfFlight(double u, double angle_rad) {
    return (2 * u * sin(angle_rad)) / g;
}

double calculateRange(double u, double angle_rad) {
    return (u * u * sin(2 * angle_rad)) / g;
}

int main() {
    double u, angle_degrees;

    std::cout << "Enter the initial velocity of the object (m/s): ";
    std::cin >> u;

    std::cout << "Enter the angle of projection (degrees): ";
    std::cin >> angle_degrees;

    double angle_rad = angle_degrees * M_PI / 180.0;

    double height = calculateHeight(u, angle_rad);
    double time_of_flight = calculateTimeOfFlight(u, angle_rad);
    double range = calculateRange(u, angle_rad);

    std::cout << "Initial velocity: " << u << " m/s\n";
    std::cout << "Launch angle: " << angle_degrees << " degrees\n";
    std::cout << "Height of the projectile: " << height << " meters\n";
    std::cout << "Time of flight: " << time_of_flight << " seconds\n";
    std::cout << "Horizontal range: " << range << " meters\n";

    return 0;
}
