#include <random>

std::random_device rd;

class BaseGenerator {
    protected:
        std::mt19937 gen_{rd()};
        std::uniform_real_distribution<long double> uldd_{0, 1};
    public:
        virtual long double generate() {return uldd_(gen_);}
        virtual ~BaseGenerator() {}
};

class BinominalGenerator {
    private:
        mutable BaseGenerator base_gen_;
        double prob_;
        size_t n_;
    public:
        BinominalGenerator (double prob, size_t n) : prob_(prob), n_(n) {}

        size_t generate() const {
            size_t result = 0;
            for(size_t i = 0; i < n_; ++i)
            result += (base_gen_.generate() < prob_ ? 1 : 0);
            return result;
        }
};


using PoissonGenerator = BinominalGenerator;
//for($i = 1; $i -le  100; $i++ ){.\t.exe >> log.log;}