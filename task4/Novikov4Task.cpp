#include "my_random_gen.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

class UniformGenerator : public BaseGenerator {
private:
    long double a_, b_;
public:
    UniformGenerator(long double a, long double b) : BaseGenerator(), a_(a), b_(b) {}
    long double generate() override 
    {
        return a_ + uldd_(gen_) * (b_ - a_);
    }
};

struct DailyResult {
    int day;
    double travel_time;
    double lunch_time;
    double total_absence;
};

struct MonthlyResult 
{
    std::vector<DailyResult> days;
    double total_absence;
};

std::string format_with_commas(double value) 
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    std::string s = ss.str();
    
    size_t dot_pos = s.find('.');
    std::string int_part = s.substr(0, dot_pos);
    std::string frac_part = s.substr(dot_pos);
    
    std::string formatted;
    int count = 0;
    for (int i = int_part.length() - 1; i >= 0; --i) 
    {
        formatted = int_part[i] + formatted;
        ++count;
        if (count % 3 == 0 && i > 0) 
        {
            formatted = ',' + formatted;
        }
    }
    
    return formatted + frac_part;
}

MonthlyResult simulate_month() {
    const double a = 3.0;      // min travel time (hours)
    const double b = 5.0;      // max travel time (h)
    const double lunch = 1.0;  // lunch time (h)
    const int days_in_month = 30;
    
    UniformGenerator travel_gen(a, b);
    
    MonthlyResult result;
    result.total_absence = 0.0;
    
    for (int day = 1; day <= days_in_month; ++day) 
    {
        DailyResult dr;
        dr.day = day;
        dr.travel_time = travel_gen.generate();
        dr.lunch_time = lunch;
        dr.total_absence = dr.travel_time + dr.lunch_time;
        
        result.days.push_back(dr);
        result.total_absence += dr.total_absence;
    }
    return result;
}

int main() {
    MonthlyResult month = simulate_month();
    
    std::cout << "day | travel (h) | lunch (h) | total (h)" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    for (const auto& day : month.days) {
        std::cout << "day " << day.day << ": " 
                  << std::fixed << std::setprecision(2)
                  << day.travel_time << " (travel) + " 
                  << day.lunch_time << " (lunch) = " 
                  << day.total_absence << " h" << std::endl;
    }
    
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "total absence: " << format_with_commas(month.total_absence) << " hours" << std::endl;
    
    std::ofstream log("log.log", std::ios::app);
    log << month.total_absence << std::endl;
    log.close();
    
    return 0;
}

//for($i = 1; $i -le 100; $i++ ){.\test.exe >> log.log} 