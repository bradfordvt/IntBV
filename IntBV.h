/* IntBV -- Integer / Bit Vector

   Copyright (C) 2020 VT Enterprises Consulting Services

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/*
 *  Created on: Oct 29, 2020
 *      Author: Bradford G. Van Treuren
 *
 *  Motivation for this class is to provide a C++ class with similar behavior
 *  to the intbv class from the myHDL package for Python.
 *
 *  This class was developed to support system modeling experiments for the
 *  IEEE P2654 and P1687.1 Working Groups as they prepare and define these new
 *  testing standards.
 */

#ifndef INTBV_H_
#define INTBV_H_

#include <exception>
#include "ipint.h"  // Infinite precision integer type used as single point of change


class IntbvException: public std::exception
{
public:
	IntbvException(const std::string& txt) throw ();
    ~IntbvException() throw ();
    const char* what() const throw ();
private:
    std::string txt;
};

inline IntbvException::IntbvException(const std::string& txt) throw () :
std::exception(), txt(txt)
{
}

inline IntbvException::~IntbvException() throw ()
{
}

inline const char* IntbvException::what() const throw ()
{
    return txt.c_str();
}


class IntBV {
public:
	IntBV();
	IntBV(const ipint& val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(int val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(const IntBV& val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(const std::string& val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(const char* val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(long val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(long long val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(unsigned int val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(unsigned long val, ipint min=0, ipint max=0, unsigned int _nrbits=0);
	IntBV(unsigned long long val, ipint min=0, ipint max=0, unsigned int _nrbits=0);

    /* assignment operators */
    const IntBV& operator=(const char* c);
    const IntBV& operator=(const std::string& s);
    const IntBV& operator=(int l);
    const IntBV& operator=(long l);
    const IntBV& operator=(long long l);
    const IntBV& operator=(unsigned int l);
    const IntBV& operator=(unsigned long l);
    const IntBV& operator=(unsigned long long l);
    const IntBV& operator=(const IntBV& l);
    const IntBV& operator=(const ipint& l);

    /* unary increment/decrement operators */
    const IntBV& operator++();
    const IntBV& operator--();
    IntBV operator++(int);
    IntBV operator--(int);

    /* operational assignments */
    const IntBV& operator+=(const IntBV& rhs);
    const IntBV& operator-=(const IntBV& rhs);
    const IntBV& operator*=(const IntBV& rhs);
    const IntBV& operator/=(const IntBV& rhs);
    const IntBV& operator%=(const IntBV& rhs);
    const IntBV& operator<<=(size_t shamt);
    const IntBV& operator>>=(size_t shamt);
    const IntBV& operator&=(const IntBV& rhs);
    const IntBV& operator|=(const IntBV& rhs);
    const IntBV& operator^=(const IntBV& rhs);

    /* operations */
    IntBV operator+(const IntBV& rhs) const;
    IntBV operator-(const IntBV& rhs) const;
    IntBV operator*(const IntBV& rhs) const;
    IntBV operator/(const IntBV& rhs) const;
    IntBV operator%(const IntBV& rhs) const;
    IntBV operator^(const IntBV& rhs) const;
    IntBV operator<<(size_t rhs) const;
    IntBV operator>>(size_t rhs) const;
    IntBV operator&(const IntBV& rhs) const;
    IntBV operator|(const IntBV& rhs) const;
    IntBV operator~() const;
    IntBV operator-() const;
//    operator int() const { return this->toInt(); }
//    operator long() const { return this->toLong(); }

    /* relational operations */
    bool operator==(const IntBV& rhs) const;
    bool operator!=(const IntBV& rhs) const;
    bool operator<(const IntBV& rhs) const;
    bool operator<=(const IntBV& rhs) const;
    bool operator>(const IntBV& rhs) const;
    bool operator>=(const IntBV& rhs) const;

    /* size in bytes */
    size_t size() const;

    /* string conversion */
    std::string toString() const;

    /* conversion to primitive types */
    ipint to_ipint() const { return __val; };
    int toInt() const;
    long toLong() const;
    long long toLongLong() const;
    unsigned int toUnsignedInt() const;
    unsigned long toUnsignedLong() const;
    unsigned long long toUnsignedLongLong() const;

    IntBV pow(size_t exp) const;

    IntBV get_slice(size_t start_bit_index, size_t end_bit_index) const;
    IntBV get_slice(size_t start_bit_index) const;
    IntBV get_slice_e(size_t end_bit_index) const;
    bool get_bit(size_t bit_index) const;

    void set_slice(size_t start_bit_index, size_t end_bit_index, const IntBV& val);
    void set_slice(size_t start_bit_index, const IntBV& val);
    void set_slice_e(size_t end_bit_index, const IntBV& val);
    void set_bit(size_t bit_index, int val);

    const ipint& get_min() const { return __min; };
	const ipint& get_max() const { return __max; };
	const unsigned int get_nrbits() const { return __nrbits; };
	virtual ~IntBV() { };

	friend std::string _int2bitstring(const IntBV& num);
	friend std::string _int2hexstring(const IntBV& num);
protected:
	IntBV _copy_();
	IntBV _deepcopy_();
private:
	void __common_init(const ipint _min, const ipint _max, unsigned int _nrbits);
	void __handleBounds();
	bool __hasFullRange();
	ipint __min;
	ipint __max;
	ipint __val;
	unsigned int __nrbits;
};

std::string bin(const IntBV& num, ipint width=0);
std::string hex(const IntBV& num, ipint width=0);
std::string dec(const IntBV& num);

IntBV abs(const IntBV& num);

#endif /* INTBV_H_ */
