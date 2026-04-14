#include "my_random_gen.h"
#include <iostream>
#include <vector>
#include <fstream>
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

struct ExcursionResult {
    int excursions_count;
    double total_time;
};

ExcursionResult simulate_period() {
    const double lambda = 40.0;        // clients per hour
    const int group_size = 20;         // clients per excursion
    const double T = 3.5;              // total time (hours)
    
    ExponentialGenerator exp_gen(lambda);
    
    ExcursionResult result;
    result.excursions_count = 0;
    result.total_time = 0.0;
    int clients = 0;
    
    while (result.total_time < T) 
    {
        double interarrival_time = exp_gen.generate();
        result.total_time += interarrival_time;
        
        if (result.total_time >= T) 
        {
            break;
        }
        
        clients++;
        
        if (clients == group_size) 
        {
            result.excursions_count++;
            clients = 0;
        }
    }
    return result;
}

int main() {
    ExcursionResult result = simulate_period();
    
    std::cout << "Excursions count: " << result.excursions_count << std::endl;
    std::cout << "Total time: " << result.total_time << " hours" << std::endl;
    
    std::ofstream log("log.log", std::ios::app);
    log << result.excursions_count << std::endl;
    log.close();
    
    return 0;
}

//for($i = 1; $i -le 100; $i++ ){.\test.exe >> log.log}