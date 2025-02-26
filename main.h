#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class big_decimal{
    private:
    public:
        vector <char> dig;
        long long before;
        long long after;
        char sgn = 1;
        long long actual_after = 0;
        big_decimal(vector<char> v, long long b, long long a, char ssgn);

        big_decimal(int b, long long aft = 10);

        big_decimal(long double a);


        big_decimal(string a, long long aft = 10);

        friend ostream& operator<<(ostream& out, const big_decimal &a);
        friend big_decimal operator+(const big_decimal &a, const big_decimal &b);
        friend big_decimal operator*(const big_decimal& a, const big_decimal& b);
        friend big_decimal operator-(const big_decimal& a, const big_decimal& b);
        friend big_decimal operator/(const big_decimal& a, const big_decimal& b);
        friend void print(const big_decimal& a);
        friend bool operator>(const big_decimal &a, const big_decimal &b);
        friend bool operator<(const big_decimal &a, const big_decimal &b);
        friend bool operator==(const big_decimal &a, const big_decimal &b);
        friend bool operator!=(const big_decimal &a, const big_decimal &b);
        friend void pi(int precision);
        big_decimal &operator=(const big_decimal &a) = default;
        big_decimal (const big_decimal &other) = default;
        big_decimal ( big_decimal &&other) = default;

        virtual ~big_decimal() = default;
};
