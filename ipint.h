/* ipint -- Infinite Precision Integer

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
 *  Motivation for this class is to provide a similar behavior for the IntBV class
 *  modeled after the Python language integer.  The Python integer is used by the
 *  myHDL package intbv class to represent both integers and bit vectors.  MyHDL
 *  is a hardware simulation package written in Python.  intbv is used to represent
 *  the equivalent of the std_vector data type in VHDL or the vector in Verilog.
 *  It works by leveraging the built-in features for arithmetic and bit logic found
 *  in the integer data type in Python.  Python implements an infinite precision
 *  form of integer so it is not limited to hardware bit architectures of the hosting
 *  system.  Thus, it is not limited to 32 or 64 bit maximum size restrictions.
 *  The use of an infinite precision integer allows for very large bit representations
 *  doubling to support data vectors used to stimulate hardware registers and simulation
 *  test generators and retargeters used in EDA test generation and diagnostic tools.
 *  The use of C++ for this class is based on the need to support multiple native
 *  languages used by various EDA tools.  These languages could be supported by this
 *  C++ class through the use of the Simplified Wrapper and Interface Generator (SWIG)
 *  tool that can be found at: http://www.swig.org/.  The myHDL documentation may
 *  be found at: http://www.myhdl.org/.
 *
 *  Inspiration for this class was found reading material from Donald Knuth and two
 *  GitHub projects on the subject of infinite precision integers.  Unfortunately,
 *  none of the projects implementing infinite precision integers provided sufficient
 *  behaviors to support all the features required for the IntBV class to leverage.
 *  Therefore, these projects could not be reused directly as is.  The GitHub projects
 *  providing useful inspiration may be found at:
 *  https://sercantutar.github.io/infint/
 *  https://github.com/michaeljclark/bignum
 *
 *  This class was developed to support system modeling experiments for the
 *  IEEE P2654 and P1687.1 Working Groups as they prepare and define these new
 *  testing standards.
 */

#ifndef IPINT_H_
#define IPINT_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <climits>
#include <string>
#include <algorithm>
#include <utility>
#include <exception>
#include <cassert>

#include <stdlib.h>
#include "bits.h"

//#define min(a,b) a<b?a:b
//#define max(a,b) a>b?a:b


typedef uint32_t ELEM_TYPE;
typedef uint64_t ELEM_TYPE2;
static const ELEM_TYPE ELEM_MASK = 0xFFFFFFFF;
typedef long long PRODUCT_TYPE;
static const ELEM_TYPE BASE = 1000000000;
static const ELEM_TYPE UPPER_BOUND = 999999999;
// static const ELEM_TYPE DIGIT_COUNT = 9;
static const size_t ELEM_BITS = sizeof(ELEM_TYPE) * 8;
static const size_t ELEM_SIZE = sizeof(ELEM_TYPE);
static const ELEM_TYPE ELEM_SHIFT = 5;

class IpIntException: public std::exception
{
public:
    IpIntException(const std::string& txt) throw ();
    ~IpIntException() throw ();
    const char* what() const throw ();
private:
    std::string txt;
};

inline IpIntException::IpIntException(const std::string& txt) throw () :
std::exception(), txt(txt)
{
}

inline IpIntException::~IpIntException() throw ()
{
}

inline const char* IpIntException::what() const throw ()
{
    return txt.c_str();
}

inline static div_t _idiv(int num, int denom)
{
    div_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

inline static ldiv_t _ldiv(long num, long denom)
{
    ldiv_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

inline static lldiv_t _lldiv(long long num, long long denom)
{
    lldiv_t result;
    result.quot = num / denom;
    result.rem = num - denom * result.quot;
    return result;
}

class ipint
{
    friend std::ostream& operator<<(std::ostream &s, const ipint &n);
    friend std::istream& operator>>(std::istream &s, ipint &val);
    bool debug = false;

public:
    /* constructors */
    ipint();
    ipint(const char* c, const uint32_t bits = 0);
    ipint(const std::string& s, const uint32_t bits = 0);
    ipint(int l, const uint32_t bits = 0);
    ipint(long l, const uint32_t bits = 0);
    ipint(long long l, const uint32_t bits = 0);
    ipint(unsigned int l, const uint32_t bits = 0);
    ipint(unsigned long l, const uint32_t bits = 0);
    ipint(unsigned long long l, const uint32_t bits = 0);
    ipint(const ipint& l);
    ipint(const std::initializer_list<ELEM_TYPE> l, const uint32_t bits = 0);
	/* move constructor */
	ipint(const ipint&& operand) noexcept;


    /* assignment operators */
    const ipint& operator=(const char* c);
    const ipint& operator=(const std::string& s);
    const ipint& operator=(int l);
    const ipint& operator=(long l);
    const ipint& operator=(long long l);
    const ipint& operator=(unsigned int l);
    const ipint& operator=(unsigned long l);
    const ipint& operator=(unsigned long long l);
    const ipint& operator=(const ipint& l);
	/* ipint move assignment operator */
    ipint& operator=(ipint &&operand);


    /* unary increment/decrement operators */
    const ipint& operator++();
    const ipint& operator--();
    ipint operator++(int);
    ipint operator--(int);

    /* operational assignments */
    const ipint& operator+=(const ipint& rhs);
    const ipint& operator-=(const ipint& rhs);
    const ipint& operator*=(const ipint& rhs);
    const ipint& operator/=(const ipint& rhs);
    const ipint& operator%=(const ipint& rhs);
    const ipint& operator<<=(size_t shamt);
    const ipint& operator>>=(size_t shamt);
    const ipint& operator&=(const ipint &rhs);
    const ipint& operator|=(const ipint &rhs);
    const ipint& operator^=(const ipint &rhs);

    /* operations */
    bool operator!() const;
    ipint operator~() const;
    ipint operator-() const;
    ipint operator+(const ipint& operand) const;
    ipint operator-(const ipint& operand) const;
    ipint operator*(const ipint& operand) const;
    ipint operator/(const ipint& divisor) const;
    ipint operator%(const ipint& operand) const;
    ipint operator<<(size_t shamt) const;
    ipint operator>>(size_t shamt) const;
    ipint operator&(const ipint& operand) const;
    ipint operator|(const ipint& operand) const;
    ipint operator^(const ipint& operand) const;

    /* relational operations */
    bool operator==(const ipint& rhs) const;
    bool operator!=(const ipint& rhs) const;
    bool operator<(const ipint& rhs) const;
    bool operator<=(const ipint& rhs) const;
    bool operator>(const ipint& rhs) const;
    bool operator>=(const ipint& rhs) const;

    /* size in bytes */
    size_t size() const;

    /* string conversion */
    std::string toString(size_t radix=10) const;

    /* conversion to primitive types */
    int toInt() const;
    long toLong() const;
    int64_t toInt64() const;
    unsigned int toUnsignedInt() const;
    unsigned long toUnsignedLong() const;
    uint64_t toUInt64() const;

    /* helper methods */
    size_t num_elements() const { return val.size(); };
 	size_t max_val() const;
    size_t num_bits() const;
	ELEM_TYPE element_at(size_t n) const;
	ELEM_TYPE val_mask(const ipint &n) const;
	ipint pow(size_t exp) const;
	int test_bit(size_t n) const;
	void set_bit(size_t n);
	void setDebug(bool v) { debug = v; };
	bool isZero() const;
    void dump() const;
    /* expand val to match operand */
	void expand(const ipint &operand);
	/* contract zero big end val */
	void contract();

protected:
	/* resize number of val */
	void _resize(size_t n);

private:
    static void __divrem(const ipint &dividend, const ipint &divisor, ipint &quotient, ipint &remainder);
	void __mult(const ipint &multiplicand, const ipint multiplier, ipint &result) const;
    void __fromString(const std::string& s);

    std::vector<ELEM_TYPE> val; // number with base FACTOR
    bool pos = true; // true if number is positive
    uint32_t bits; // number of bits in the vector
};

#endif
