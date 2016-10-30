#include <iostream>

class fraction
{
	
private:
	int cntr; 
	int denom;

	int gcd(int a, int b);
	void shorten_fraction();
	void process_sign();
public:
	fraction(int c, int d) ;
	fraction();

	~fraction();
	operator double();
	void set_counter(int cntr);
	int get_counter() const;

	void set_denom(int denom);
	int get_denom()const;
	
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
		
	inline void check_char(std::istream&is, char ch);
	friend std::istream& operator >> (std::istream& is, fraction& f);
	friend std::ostream& operator << (std::ostream& os, fraction f);
};

