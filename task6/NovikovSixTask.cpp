#include "my_random_gen.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

class ExponentialGenerator : public BaseGenerator {
private:
    long double lambda_;
public:
    ExponentialGenerator(long double lambda) : BaseGenerator(), lambda_(lambda) {}
    long double generate() override {
        return -std::log(1.0L - uldd_(gen_)) / lambda_;
    }
};

struct SimulationResult {
    double bus10_time;
    double passenger10_time;
};

SimulationResult simulate() {
    const double bus_mean = 2.0;           // mean time between buses (minutes)
    const double bus_lambda = 1.0 / bus_mean;  // bus arrival rate (buses per minute)
    const double passenger_lambda = 0.3;   // passenger arrival rate (persons per minute)
    
    ExponentialGenerator bus_gen(bus_lambda);
    ExponentialGenerator passenger_gen(passenger_lambda);
    
    SimulationResult result;
    result.bus10_time = 0.0;
    result.passenger10_time = 0.0;
    
    // Time of 10th bus
    for (int i = 0; i < 10; ++i) {
        result.bus10_time += bus_gen.generate();
    }
    
    // Time of 10th passenger
    for (int i = 0; i < 10; ++i) {
        result.passenger10_time += passenger_gen.generate();
    }
    
    return result;
}

int main() {
    SimulationResult result = simulate();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "10th bus arrival time: " << result.bus10_time << " minutes" << std::endl;
    std::cout << "10th passenger arrival time: " << result.passenger10_time << " minutes" << std::endl;
    
    std::ofstream log("log.log", std::ios::app);
    log << result.bus10_time << " " << result.passenger10_time << std::endl;
    log.close();
    
    return 0;
}

//for($i = 1; $i -le 100; $i++ ){.\test.exe >> log.log}