#ifndef CPP16_EX3_FRACTION_H
#define CPP16_EX3_FRACTION_H
#include <iostream>

class fraction {

private:
    int _cntr;
    int _denom;

    int gcd(int a, int b);

    void shorten_fraction();

    void process_sign();

public:
    fraction(int c, int d = 1);

    fraction() : _cntr(0), _denom(1) {};

    ~fraction();

    operator double();

    void set_counter(int cntr);

    int get_counter() const;

    void set_denom(int denom);

    int get_denom() const;

    fraction operator-() const;

    fraction operator+(const fraction rhs) const;

    fraction operator-(const fraction rhs) const;

    fraction operator*(const fraction rhs) const;

    fraction operator/(const fraction rhs) const;

    fraction operator+(const int rhs) const;

    fraction operator-(const int rhs) const;

    fraction operator*(const int rhs) const;

    fraction operator/(const int rhs) const;

    friend fraction operator+(const int lhs, const fraction rhs);

    friend fraction operator-(const int lhs, const fraction rhs);

    friend fraction operator*(const int lhs, const fraction rhs);

    friend fraction operator/(const int lhs, const fraction rhs);

    bool operator==(const fraction rhs) const;

    bool operator!=(const fraction rhs) const;

    bool operator<(const fraction rhs) const;

    bool operator>(const fraction rhs) const;

    bool operator<=(const fraction rhs) const;

    bool operator>=(const fraction rhs) const;

    inline void check_char(std::istream &is, char ch);

    friend std::istream &operator>>(std::istream &is, fraction &f);

    friend std::ostream &operator<<(std::ostream &os, fraction f);
};

#endif