#include "my_random_gen.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

class TruncatedNormalGenerator : public BaseGenerator {
private:
    long double M_, sigma_, Tmin_, Tmax_;
public:
    TruncatedNormalGenerator(long double M, long double sigma, long double Tmin, long double Tmax) 
        : BaseGenerator(), M_(M), sigma_(sigma), Tmin_(Tmin), Tmax_(Tmax) {}
    
    long double generate() override {
        long double U1, U2, V1, V2, S, X;
        do {
            U1 = uldd_(gen_);
            U2 = uldd_(gen_);
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while (S >= 1 || S == 0);
        
        X = V1 * std::sqrt(-2 * std::log(S) / S);
        X = X * sigma_ + M_;
        
        // Truncation
        if (X < Tmin_) X = Tmin_;
        if (X > Tmax_) X = Tmax_;
        
        return X;
    }
};

struct OrderResult {
    int order_number;
    double start_time;
    double end_time;
};

struct DailyResult {
    std::vector<OrderResult> orders;
    int orders_count;
    double total_time;
};

DailyResult simulate_day() {
    const double M = 5.0;          // mean repair time (hours)
    const double sigma = 0.2;      // standard deviation (hours)
    const double Tmin = 1.0;       // min repair time (hours)
    const double Tmax = 6.0;       // max repair time (hours)
    const double work_time = 14.0; // total working time (hours)
    
    TruncatedNormalGenerator repair_gen(M, sigma, Tmin, Tmax);
    
    DailyResult result;
    result.orders_count = 0;
    result.total_time = 0.0;
    
    double current_time = 0.0;
    int order_num = 1;
    
    while (current_time < work_time) {
        double repair_time = repair_gen.generate();
        
        if (current_time + repair_time > work_time) {
            break;
        }
        
        OrderResult order;
        order.order_number = order_num;
        order.start_time = current_time;
        order.end_time = current_time + repair_time;
        
        result.orders.push_back(order);
        result.orders_count++;
        
        current_time = order.end_time;
        order_num++;
    }
    
    result.total_time = current_time;
    
    return result;
}

int main() {
    DailyResult day = simulate_day();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "order | start time | end time | duration" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& order : day.orders) {
        double duration = order.end_time - order.start_time;
        std::cout << "order " << order.order_number << ": " 
                  << order.start_time << " h - " 
                  << order.end_time << " h (" 
                  << duration << " h)" << std::endl;
    }
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "total orders: " << day.orders_count << std::endl;
    std::cout << "total time: " << day.total_time << " hours" << std::endl;
    
    std::ofstream log("log.log", std::ios::app);
    log << day.orders_count << std::endl;
    log.close();
    
    return 0;
}

//for($i = 1; $i -le 100; $i++ ){.\test.exe >> log.log}