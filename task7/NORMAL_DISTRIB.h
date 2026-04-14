#include "my_random_gen.h"

class NormalGenerator : public BaseGenerator{
    private:
        long double m_, se_;
    public:
    NormalGenerator(long double m, long double se) : BaseGenerator(), m_(m), se_(se) {}
    long double generate() {
        long double U1, U2, V1, V2, S;
        do 
        {
            U1 = uldd_(gen_);
            U2 = uldd_(gen_);
            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        }
        while(S >= 1);
        long double X1 = V1 * sqrt(-2 * std::log(S) / S);
        long double X2 = V2 * sqrt(-2 * std::log(S) / S);
        X1 = X1 * se_ + m_;
        X2 = X2 * se_ + m_;
        return uldd_(gen_) < 0.5 ? X1 : X2;
    }
};