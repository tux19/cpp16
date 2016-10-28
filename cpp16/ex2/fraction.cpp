#include "stdafx.h"
#include "fraction.h"
#include <iostream>
#include <exception>

class myexception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "ERROR: Devision by 0!";
	}
} division_by_zero;

fraction::fraction(int c = 0, int d = 1) 
	: cntr(c), denom(d)
{
	if(d == 0)
	{
		throw division_by_zero;
	}
	process_sign();
	shorten_fraction();
}
fraction::fraction()
{
	cntr = 0;
	denom = 1;
	if (denom == 0)
	{
		throw division_by_zero;
	}
	process_sign();
	shorten_fraction();
}
;

fraction::~fraction()
{
}

void fraction::process_sign()
{
	if( denom < 0 && cntr < 0)
	{
		denom = abs(denom);
		cntr = abs(cntr);
	}else if((denom < 0 && cntr > 0) || (denom > 0 && cntr < 0))
	{
		denom = abs(denom);
		cntr = 0 - abs(cntr);
	}
}

void fraction::shorten_fraction()
{
	auto tmp_gcd = gcd(abs(denom), abs(cntr));
	denom /= tmp_gcd;
	cntr /= tmp_gcd;
}

int fraction::gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

void fraction::set_counter(int cntr)
{
	fraction::cntr = cntr;
	shorten_fraction();
}

int fraction::get_counter() const
{
	return fraction::cntr;
}

void fraction::set_denom(int denom)
{
	fraction::denom = denom;
	shorten_fraction();
}

int fraction::get_denom() const
{
	return fraction::denom;
}



fraction fraction::operator+(const fraction rhs) const
{
	int nom = get_counter()*rhs.get_denom() + rhs.get_counter()*get_denom();
	int denom = get_denom()*rhs.get_denom();

	return fraction(nom, denom);
}

fraction fraction::operator-(const fraction rhs) const
{
	int nom = get_counter()*rhs.get_denom() - rhs.get_counter()*get_denom();
	int denom = get_denom()*rhs.get_denom();

	return fraction(nom, denom);
}

fraction fraction::operator*(const fraction rhs) const
{
	int nom = get_counter()*rhs.get_counter();
	int denom = get_denom()*rhs.get_denom();

	return fraction(nom, denom);
}

fraction fraction::operator/(const fraction f) const
{
	if(f.get_counter()==0)
	{
		throw division_by_zero;
	}
	int nom = get_counter()*f.get_denom();
	int denom = get_denom()*f.get_counter();

	return fraction(nom, denom);
}

fraction fraction::operator-() const
{
	return fraction(-cntr, denom);
}

fraction fraction::operator+(const int rhs) const
{
	return fraction(cntr, denom) + fraction(rhs);
}

fraction fraction::operator-(const int rhs) const
{
	return fraction(cntr, denom) - fraction(rhs);
}

fraction fraction::operator*(const int rhs) const
{
	return fraction(cntr, denom) * fraction(rhs);
}

fraction fraction::operator/(const int rhs) const
{
	return fraction(cntr,denom) / fraction(rhs);
}

fraction operator+(const int lhs, const fraction rhs)
{
	return fraction(lhs) + fraction(rhs.get_counter(),rhs.get_denom());

}

fraction operator-(const int lhs, const fraction rhs)
{
	return fraction(lhs) - fraction(rhs.get_counter(), rhs.get_denom());
}

fraction operator*(const int lhs, const fraction rhs)
{
	return fraction(lhs) * fraction(rhs.get_counter(), rhs.get_denom());
}

fraction operator/(const int lhs, const fraction rhs)
{
	return fraction(lhs) / fraction(rhs.get_counter(), rhs.get_denom());
}

bool fraction::operator==(const fraction rhs) const
{
	return (denom == rhs.get_denom() && cntr == rhs.get_counter());
}

bool fraction::operator!=(const fraction rhs) const
{
	return !(denom == rhs.get_denom() && cntr == rhs.get_counter());
}

bool fraction::operator<(const fraction rhs) const
{
	return (static_cast<double>(cntr / denom) < static_cast<double>(rhs.get_counter() / rhs.get_denom()));
}

bool fraction::operator>(const fraction rhs) const
{
	return (static_cast<double>(cntr / denom) > static_cast<double>(rhs.get_counter() / rhs.get_denom()));
}

bool fraction::operator<=(const fraction rhs) const
{
	return (static_cast<double>(cntr / denom) <= static_cast<double>(rhs.get_counter() / rhs.get_denom()));
}

bool fraction::operator>=(const fraction rhs) const
{
	return (static_cast<double>(cntr / denom) >= static_cast<double>(rhs.get_counter() / rhs.get_denom()));
}

inline void fraction::check_char(std::istream&is, char ch) {
	char c;
	is >> c;
	if (c != ch)
	{
		is.putback(c);
		is.setstate(std::ios::badbit);
	}
}

std::istream& operator>>(std::istream& is, fraction& f) {
	fraction g(0,1);
	g.check_char(is, '(');
	int temp;
	is >> temp;
	g.set_counter(temp);
	g.check_char(is, '/');
	is >> temp;
	g.set_denom(temp);
	g.check_char(is, ')');
	if (is)
	{
		f = g;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, fraction f) {
	os << '(' << f.get_counter() << '/' << f.get_denom() << ')';
	return os;
}

fraction::operator double() {
	return cntr / denom;
}