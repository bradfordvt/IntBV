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
 */

#include "ipint.h"


/* constructors */
ipint::ipint() : val{0}, pos(true), bits(0)
{
	assert(val.size() == 1);
}

ipint::ipint(const char* c, const uint32_t bits) : val{0}, pos(true), bits(bits)
{
    __fromString(std::string(c));
}

ipint::ipint(const std::string& s, const uint32_t bits) : val{0}, pos(true), bits(bits)
{
    __fromString(s);
}

ipint::ipint(int l, const uint32_t bits) : pos(l >= 0), bits(bits)
{
    val.push_back((ELEM_TYPE)l);
}

ipint::ipint(long l, const uint32_t bits) : pos(l >= 0), bits(bits)
{
    val.push_back((ELEM_TYPE)l);
}

ipint::ipint(long long l, const uint32_t bits) : pos(l >= 0), bits(bits)
{
	for(size_t i = sizeof(l); i > 0; i -= ELEM_SIZE) {
		val.push_back((ELEM_TYPE)(l & ELEM_MASK));
		l >>= ELEM_BITS;
	}
}

ipint::ipint(unsigned int l, const uint32_t bits) : pos(true), bits(bits)
{
    val.push_back((ELEM_TYPE)l);
}

ipint::ipint(unsigned long l, const uint32_t bits) : pos(true), bits(bits)
{
    val.push_back((ELEM_TYPE)l);
}

ipint::ipint(unsigned long long l, const uint32_t bits) : pos(true), bits(bits)
{
	for(size_t i = sizeof(l); i > 0; i -= ELEM_SIZE) {
		val.push_back((ELEM_TYPE)(l & ELEM_MASK));
		l >>= ELEM_BITS;
	}
}

ipint::ipint(const ipint& l) : val(l.val), pos(l.pos), bits(l.bits)
{
}

ipint::ipint(const std::initializer_list<ELEM_TYPE> l, const uint32_t bits) : val(l), pos(true), bits(bits)
{
}

/* move constructor  */
ipint::ipint(const ipint&& operand) noexcept
	: val(std::move(operand.val)),  bits(operand.bits)
{
	contract();
}

/* assignment operators */
const ipint& ipint::operator=(const char* c)
{
	val.clear();
	val.push_back(0);
    __fromString(c);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(const std::string& s)
{
	val.clear();
	val.push_back(0);
    __fromString(s);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(int l)
{
    pos = l >= 0;
	val.clear();
    val.push_back((ELEM_TYPE)l);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(long l)
{
    pos = l >= 0;
    val.clear();
    val.push_back((ELEM_TYPE)l);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(long long l)
{
    pos = l >= 0;
    val.clear();
	for(size_t i = sizeof(l); i > 0; i -= ELEM_SIZE) {
		val.push_back((ELEM_TYPE)(l & ELEM_MASK));
		l >>= ELEM_BITS;
	}
	bits = 0;
    return *this;
}

const ipint& ipint::operator=(unsigned int l)
{
    pos = true;
    val.clear();
    val.push_back((ELEM_TYPE)l);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(unsigned long l)
{    bits = num_bits();
    pos = true;
    val.clear();
    val.push_back((ELEM_TYPE)l);
    bits = 0;
    return *this;
}

const ipint& ipint::operator=(unsigned long long l)
{
	if(ipint::debug) printf("op=ULL: **********************************************************************************************\n");
	if(ipint::debug) dump();
    pos = true;
    val.clear();
	for(size_t i = sizeof(l); i > 0; i -= ELEM_SIZE) {
		val.push_back((ELEM_TYPE)(l & ELEM_MASK));
		l >>= ELEM_BITS;
	}
	bits = 0;
	if(ipint::debug) dump();
    return *this;
}

const ipint& ipint::operator=(const ipint& l)
{
    pos = l.pos;
    val = l.val;
    bits = l.bits;
    return *this;
}

/* ipint move assignment operator */
ipint& ipint::operator=(ipint &&operand)
{
	val = std::move(operand.val);
	if (bits == 0) bits = operand.bits;
	return *this;
}

/* unary increment/decrement operators */
const ipint& ipint::operator++()
{
    *this += 1;
    return *this;
}

const ipint& ipint::operator--()
{
    *this -= 1;
    return *this;
}

ipint ipint::operator++(int)
{
    ipint result = *this;
    result += 1;
    return result;
}

ipint ipint::operator--(int)
{
    ipint result = *this;
    result -= 1;
    return result;
}

/* operational assignments */
const ipint& ipint::operator+=(const ipint& rhs)
{
	expand(rhs);
	ELEM_TYPE carry = 0;
	for (size_t i = 0; i < num_elements(); i++) {
		ELEM_TYPE old_val = val[i];
		if(ipint::debug) printf("new_val = %x + %x + %x\n", old_val, rhs.element_at(i), carry);
		ELEM_TYPE new_val = old_val + rhs.element_at(i) + carry;
		val[i] = new_val;
		carry = new_val < old_val;
	}
	if (carry && num_elements() < max_val()) {
		val.push_back(1);
	}
	return *this;
}

const ipint& ipint::operator-=(const ipint& rhs)
{
	expand(rhs);
	uint32_t borrow = 0;
	for (size_t i = 0; i < num_elements(); i++) {
		uint32_t old_val = val[i];
		uint32_t new_val = old_val - rhs.element_at(i) - borrow;
		val[i] = new_val;
		borrow = new_val > old_val;
	}
	contract();
	return *this;
}

const ipint& ipint::operator*=(const ipint& rhs)
{
    ipint result = *this * rhs;
    _resize(result.num_elements());
    *this = std::move(result);
    return *this;
}

const ipint& ipint::operator/=(const ipint& rhs)
{
	ipint result = *this / rhs;
	*this = std::move(result);
	return *this;
}

const ipint& ipint::operator%=(const ipint& rhs)
{
    ipint result = *this % rhs;
    *this = std::move(result);
    return *this;
}

const ipint& ipint::operator<<=(size_t shamt)
{
	*this *= ipint(2).pow(shamt);  // shift by shamt bits
	return *this;
}

const ipint& ipint::operator>>=(size_t shamt)
{
	*this /= ipint(2).pow(shamt);  // shift by shamt bits
	return *this;
}

const ipint& ipint::operator&=(const ipint &rhs)
{
	if(ipint::debug) printf("operator&=**********************************************************************************************************\n");
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz = std::min(num_elements(), rhs.num_elements());
	for (size_t i = 0; i < sz; i++) {
		ELEM_TYPE old_val = val[i];
		ELEM_TYPE new_val = old_val & rhs.element_at(i);
		val[i] = new_val;
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz1 = num_elements() - rhs.num_elements();
	size_t sz2 = rhs.num_elements() - num_elements();
	if(sz1 > 0) {
		val[rhs.num_elements()] = 0;
	}
	else if(sz2 > 0){
		for(size_t i = num_elements(); i < rhs.num_elements(); i++) {
			val.push_back(0);
		}
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	if(ipint::debug) printf("Returning from operator&=().\n");
	return *this;
}

const ipint& ipint::operator|=(const ipint &rhs)
{
	if(ipint::debug) printf("operator|=**********************************************************************************************************\n");
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz = std::min(num_elements(), rhs.num_elements());
	for (size_t i = 0; i < sz; i++) {
		ELEM_TYPE old_val = val[i];
		ELEM_TYPE new_val = old_val | rhs.element_at(i);
		val[i] = new_val;
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz1 = num_elements() - rhs.num_elements();
	size_t sz2 = rhs.num_elements() - num_elements();
	if(sz1 > 0) {
//		val[rhs.num_elements()] = 0;
	}
	else if(sz2 > 0){
		for(size_t i = num_elements(); i < rhs.num_elements(); i++) {
			val.push_back(0);
		}
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	if(ipint::debug) printf("Returning from operator|=().\n");
	return *this;
}

const ipint& ipint::operator^=(const ipint &rhs)
{
	if(ipint::debug) printf("operator^=**********************************************************************************************************\n");
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz = std::min(num_elements(), rhs.num_elements());
	for (size_t i = 0; i < sz; i++) {
		ELEM_TYPE old_val = val[i];
		ELEM_TYPE new_val = old_val ^ rhs.element_at(i);
		val[i] = new_val;
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	size_t sz1 = num_elements() - rhs.num_elements();
	size_t sz2 = rhs.num_elements() - num_elements();
	if(sz1 > 0) {
		val[rhs.num_elements()] = 0;
	}
	else if(sz2 > 0){
		for(size_t i = num_elements(); i < rhs.num_elements(); i++) {
			val.push_back(0);
		}
	}
	if(ipint::debug) dump();
	if(ipint::debug) printf("rhs.");
	if(ipint::debug) rhs.dump();
	if(ipint::debug) printf("Returning from operator^=().\n");
	return *this;
}

ipint ipint::operator&(const ipint& operand) const
{
    ipint result(*this);
    result &= operand;
    return result;
}

ipint ipint::operator|(const ipint& operand) const
{
    ipint result(*this);
    result |= operand;
    return result;
}

ipint ipint::operator^(const ipint& operand) const
{
    ipint result(*this);
    result ^= operand;
    return result;
}

/* operations */
ipint ipint::operator~() const
{
	ipint result = *this;
    for (size_t i = 0; i < val.size(); ++i)
    {
    	result.val[i] = ~val[i];
    }
    return result;
}

bool ipint::operator!() const { return (this->toInt()) == 0 ? false : true; }

ipint ipint::operator-() const
{
	// Make twos complement
    ipint result = ~(*this);
    result += 1;
    result.pos = !pos;
    return result;
}

ipint ipint::operator+(const ipint& operand) const
{
	ipint result(*this);
	return result += operand;
}

ipint ipint::operator-(const ipint& operand) const
{
	ipint result(*this);
	return result -= operand;
}

ipint ipint::operator*(const ipint& operand) const
{
	ipint result(0);
	__mult(*this, operand, result);
	// result.contract();
	return result;
}

ipint ipint::operator/(const ipint& divisor) const
{
    if (divisor.isZero())
    {
    	throw IpIntException("division by zero");
    }
	ipint quotient(0), remainder(0);
	__divrem(*this, divisor, quotient, remainder);
	return quotient;
}

ipint ipint::operator%(const ipint& divisor) const
{
    if (divisor.isZero())
    {
        throw IpIntException("division by zero");
    }
	ipint quotient(0), remainder(0);
	__divrem(*this, divisor, quotient, remainder);
	return remainder;
}

ipint ipint::operator<<(size_t shamt) const
{
    ipint result(*this);
    result <<= shamt;
    return result;
}

ipint ipint::operator>>(size_t shamt) const
{
    ipint result(*this);
    result >>= shamt;
    return result;
}

/* relational operations */
bool ipint::operator==(const ipint& rhs) const
{
	if(ipint::debug) printf("op==: this::val = [");
	for(size_t i = 0; i < num_elements(); i++) {
		if(ipint::debug) printf(", %x", val[i]);
	}
	if(ipint::debug) printf("]\n");
	if(ipint::debug) printf("op==: rhs::val = [");
	for(size_t i = 0; i < rhs.num_elements(); i++) {
		if(ipint::debug) printf(", %x", rhs.val[i]);
	}
	if(ipint::debug) printf("]\n");
	if(ipint::debug) printf("this.val.size() = %d, rhs.val.size() = %d\n", val.size(), rhs.val.size());
	if(ipint::debug) printf("this.pos = %d, rhs.pos = %d\n", pos ? 1 : 0, rhs.pos ? 1 : 0);
	if(ipint::debug) printf("num_elements() = %d\n", num_elements());
	if(ipint::debug) fflush(stdout);
//    if (pos != rhs.pos || val.size() != rhs.val.size())
//    {
//        return false;
//    }
//    for (size_t i = 0; i < num_elements(); i++)
//    {
//        if (val[i] != rhs.val[i])
//        {
//            return false;
//        }
//    }
//    return true;
	if(pos != rhs.pos) {
		return false;
	}
	size_t sz1 = num_elements() - rhs.num_elements();
	size_t sz2 = rhs.num_elements() - num_elements();
	if(sz1 > 0) {
		for (size_t i = 0; i < rhs.num_elements(); i++) {
			if (val[i] != rhs.val[i]) {
				return false;
			}
		}
		for (size_t i = rhs.num_elements(); i < num_elements(); i++) {
			if (pos ? val[i] != 0 : val[0] != 0xFFFFFFFF) {
				return false;
			}
		}
		return true;
	}
	if(sz2 > 0) {
		for (size_t i = 0; i < num_elements(); i++) {
			if (val[i] != rhs.val[i]) {
				return false;
			}
		}
		for (size_t i = num_elements(); i < rhs.num_elements(); i++) {
			if (rhs.pos ? rhs.val[i] != 0 : rhs.val[0] != 0xFFFFFFFF) {
				return false;
			}
		}
		return true;
	}
	for (size_t i = 0; i < num_elements(); i++) {
		if (val[i] != rhs.val[i]) {
			return false;
		}
	}
	return true;
}

bool ipint::operator!=(const ipint& rhs) const
{
	if(pos != rhs.pos) {
		return true;
	}
	size_t sz1 = num_elements() - rhs.num_elements();
	size_t sz2 = rhs.num_elements() - num_elements();
	if(sz1 > 0) {
		for (size_t i = 0; i < rhs.num_elements(); i++) {
			if (val[i] != rhs.val[i]) {
				return true;
			}
		}
		for (size_t i = rhs.num_elements(); i < num_elements(); i++) {
			if (pos ? val[i] != 0 : val[0] != 0xFFFFFFFF) {
				return true;
			}
		}
		return false;
	}
	if(sz2 > 0) {
		for (size_t i = 0; i < num_elements(); i++) {
			if (val[i] != rhs.val[i]) {
				return true;
			}
		}
		for (size_t i = num_elements(); i < rhs.num_elements(); i++) {
			if (rhs.pos ? rhs.val[i] != 0 : rhs.val[0] != 0xFFFFFFFF) {
				return true;
			}
		}
		return false;
	}
	for (size_t i = 0; i < num_elements(); i++) {
		if (val[i] != rhs.val[i]) {
			return true;
		}
	}
	return false;
//    if (pos != rhs.pos || val.size() != rhs.val.size())
//    {
//        return true;
//    }
//    for (int i = (int) val.size() - 1; i >= 0; --i)
//    {
//        if (val[i] != rhs.val[i])
//        {
//            return true;
//        }
//    }
//    return false;
}

bool ipint::operator<(const ipint& rhs) const
{
    if (pos && !rhs.pos)
    {
        return false;
    }
    if (!pos && rhs.pos)
    {
        return true;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? false : true;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? true : false;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? true : false;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? false : true;
        }
    }
    return false;
}

bool ipint::operator<=(const ipint& rhs) const
{
	if(this->operator==(rhs)) return true;
	if(this->operator<(rhs)) return true;
	return false;
//    if (pos && !rhs.pos)
//    {
//        return false;
//    }
//    if (!pos && rhs.pos)
//    {
//        return true;
//    }
//    if (val.size() > rhs.val.size())
//    {
//        return pos ? false : true;
//    }
//    if (val.size() < rhs.val.size())
//    {
//        return pos ? true : false;
//    }
//    for (int i = (int) val.size() - 1; i >= 0; --i)
//    {
//        if (val[i] < rhs.val[i])
//        {
//            return pos ? true : false;
//        }
//        if (val[i] > rhs.val[i])
//        {
//            return pos ? false : true;
//        }
//    }
//    return true;
}

bool ipint::operator>(const ipint& rhs) const
{
    if (pos && !rhs.pos)
    {
        return true;
    }
    if (!pos && rhs.pos)
    {
        return false;
    }
    if (val.size() > rhs.val.size())
    {
        return pos ? true : false;
    }
    if (val.size() < rhs.val.size())
    {
        return pos ? false : true;
    }
    for (int i = (int) val.size() - 1; i >= 0; --i)
    {
        if (val[i] < rhs.val[i])
        {
            return pos ? false : true;
        }
        if (val[i] > rhs.val[i])
        {
            return pos ? true : false;
        }
    }
    return false;
}

bool ipint::operator>=(const ipint& rhs) const
{
	if(this->operator==(rhs)) return true;
	if(this->operator>(rhs)) return true;
	return false;
//    if (pos && !rhs.pos)
//    {
//        return true;
//    }
//    if (!pos && rhs.pos)
//    {
//        return false;
//    }
//    if (val.size() > rhs.val.size())
//    {
//        return pos ? true : false;
//    }
//    if (val.size() < rhs.val.size())
//    {
//        return pos ? false : true;
//    }
//    for (int i = (int) val.size() - 1; i >= 0; --i)
//    {
//        if (val[i] < rhs.val[i])
//        {
//            return pos ? false : true;
//        }
//        if (val[i] > rhs.val[i])
//        {
//            return pos ? true : false;
//        }
//    }
//    return true;
}

/* size in bytes */
size_t ipint::size() const
{
    return val.size() * sizeof(ELEM_TYPE) + sizeof(bool);
}

///*! helper for recursive divide and conquer conversion to string */
//static ptrdiff_t _to_string_c(const ipint &val, std::string &s, ptrdiff_t offset)
//{
//	uint32_t v = uint64_t(val.element_at(0)) | (uint64_t(val.element_at(1)) << ELEM_BITS);
//	do {
//		s[--offset] = '0' + char(v % 10);
//	} while ((v /= 10) != 0);
//	return offset;
//}
//
///*! helper for recursive divide and conquer conversion to string */
//static ptrdiff_t _to_string_r(const ipint &val, const std::vector<ipint> &sq, size_t level,
//	std::string &s, size_t digits, ptrdiff_t offset)
//{
//	ipint q, r;
//	ipint::__divrem(val, sq[level], q, r);
//	if (level > 0) {
//		if (r != 0) {
//			if (q != 0) {
//				_to_string_r(r, sq, level-1, s, digits >> 1, offset);
//				return _to_string_r(q, sq, level-1, s, digits >> 1, offset - digits);
//			} else {
//				return _to_string_r(r, sq, level-1, s, digits >> 1, offset);
//			}
//		}
//	} else {
//		if (r != 0) {
//			if (q != 0) {
//				_to_string_c(r, s, offset);
//				offset = _to_string_c(q, s, offset - digits);
//			} else {
//				offset = _to_string_c(r, s, offset);
//			}
//		}
//	}
//	return offset;
//}

/* string conversion */
std::string ipint::toString(size_t radix) const
{
	static const char* hexdigits = "0123456789ABCDEF";
	static const char* negative = "-";

	switch (radix) {
		case 10: {
		    ipint temp = *this;
	        temp.contract();
			if (temp == 0) return "0";

		    std::string s;

		    // Initializing base value to 1, i.e 2^0
		    ipint base = 1;
		    ipint ten(10);
		    ipint two(2);
		    if (!pos)
		    {
		        temp = -temp;
		    }
		    while (temp != 0) {
		    	// printf("toString(): temp = %s\n", temp.toString(16).c_str());
		        ipint last_digit = temp % ten;
		        s.insert(0, 1, hexdigits[last_digit.toInt()]);
		        temp /= ten;
		        temp.contract();
		    }
		    if(!pos) {
		    	s.insert(0, 1, negative[0]);
		    }
		    return s;

		}
		case 2: {
			if (*this == ipint(0)) return "0b0";

			std::string s("0b");
			uint32_t l1 = val.back();
			size_t n = ELEM_BITS - clz(l1);
			size_t t = n + ((num_elements() - 1) << ELEM_SHIFT);
			s.resize(t + 2);
			auto i = s.begin() + 2;
			for (ptrdiff_t k = n - 1; k >= 0; k--) {
				*(i++) = '0' + ((l1 >> k) & 1);
			}
			for (ptrdiff_t j = num_elements() - 2; j >= 0; j--) {
				uint32_t l = val[j];
				for (ptrdiff_t k = ELEM_BITS - 1; k >= 0; k--) {
					*(i++) = '0' + ((l >> k) & 1);
				}
			}
			return s;
		}
		case 16: {
			if (*this == ipint(0)) return "0x0";

			std::string s("0x");
			uint32_t l1 = val.back();
			size_t n = ((ELEM_BITS >> 2) - (clz(l1) >> 2));
			size_t t = n + ((num_elements() - 1) << (ELEM_SHIFT - 2));
			s.resize(t + 2);
			auto i = s.begin() + 2;
			for (ptrdiff_t k = n - 1; k >= 0; k--) {
				*(i++) = hexdigits[(l1 >> (k << 2)) & 0xf];
			}
			for (ptrdiff_t j = num_elements() - 2; j >= 0; j--) {
				uint32_t l = val[j];
				for (ptrdiff_t k = (ELEM_BITS >> 2) - 1; k >= 0; k--) {
					*(i++) = hexdigits[(l >> (k << 2)) & 0xf];
				}
			}
			return s;
		}
		default: {
			return std::string();
		}
	}
}

void ipint::__fromString(const std::string& cs)
{
	static const ipint tenp18{0xa7640000, 0xde0b6b3};
	static const ipint twop64{0,0,1};
	int radix = 0;
	std::string s(cs);
	std::remove( s.begin(), s.end(), '_');
	const char* str = s.c_str();
	size_t len = s.length();
	if (s.length() > 2) {
		if (s.compare(0, 2, "0b") == 0) {
			radix = 2;
			str += 2;
			len -= 2;
		} else if (s.compare(0, 2, "0x") == 0) {
			radix = 16;
			str += 2;
			len -= 2;
		}
	}
	if (radix == 0) {
		radix = 10;
	}
	switch (radix) {
		case 10: {
			for (size_t i = 0; i < len; i += 18) {
				size_t chunklen = i + 18 < len ? 18 : len - i;
				std::string chunk(str + i, chunklen);
				ELEM_TYPE2 num = strtoull(chunk.c_str(), nullptr, 10);
				if (chunklen == 18) {
					*this *= tenp18;
				} else {
					*this *= ipint(10).pow(chunklen);
				}
				*this += ipint{ELEM_TYPE(num), ELEM_TYPE(num >> ELEM_BITS)};
			}
			break;
		}
		case 2: {
			for (size_t i = 0; i < len; i += 64) {
				size_t chunklen = i + 64 < len ? 64 : len - i;
				std::string chunk(str + i, chunklen);
				if(ipint::debug) printf("chunk = %s\n", chunk.c_str());
				ELEM_TYPE2 num = strtoull(chunk.c_str(), nullptr, 2);
				if(ipint::debug) printf("num = %x\n", ELEM_TYPE(num));
				if(ipint::debug) printf("num>> = %x\n", ELEM_TYPE(num >> ELEM_BITS));
				if (chunklen == 64) {
					*this *= twop64;  // shift by 64 bits
				} else {
					*this *= ipint(2).pow(chunklen);  // shift by remainder bits
				}
				*this += ipint{ELEM_TYPE(num), ELEM_TYPE(num >> ELEM_BITS)};
			}
			break;
		}
		case 16: {
			for (size_t i = 0; i < len; i += 16) {
				size_t chunklen = i + 16 < len ? 16 : len - i;
				std::string chunk(str + i, chunklen);
				if(ipint::debug) printf("chunk = %s\n", chunk.c_str());
				ELEM_TYPE2 num = strtoull(chunk.c_str(), nullptr, 16);
				if(ipint::debug) printf("num = %x\n", ELEM_TYPE(num));
				if(ipint::debug) printf("num>> = %x\n", ELEM_TYPE(num >> ELEM_BITS));
				if (chunklen == 16) {
					*this *= twop64;
				} else {
					if(ipint::debug) printf("ipint(16).pow(chunklen) = %x\n", ipint(16).pow(chunklen).toInt());
					if(ipint::debug) dump();
					*this *= ipint(16).pow(chunklen);
					if(ipint::debug) printf("**");
					if(ipint::debug) dump();
				}
				*this += ipint{ELEM_TYPE(num), ELEM_TYPE(num >> ELEM_BITS)};
				if(ipint::debug) printf("Bottom of loop\n");
				if(ipint::debug) dump();
			}
			break;
		}
		default: {
			val.push_back(0);
		}
	}
}

int ipint::toInt() const {
	bool tpos = val[0] & 0x80000000 ? false : true;
	ELEM_TYPE sign_val;
	if(tpos) sign_val = 0x00000000;
	else sign_val = 0xFFFFFFFF;
	for(size_t i = num_elements() - 1; i > 0; i--) {
		if(val[i] != sign_val) {
			throw IpIntException("ipint is larger than an integer.");
		}
	}
	return int(val[0]);
}
long ipint::toLong() const {
	bool tpos = val[0] & 0x80000000 ? false : true;
	ELEM_TYPE sign_val;
	if(tpos) sign_val = 0x00000000;
	else sign_val = 0xFFFFFFFF;
	for(size_t i = num_elements() - 1; i > 0; i--) {
		if(val[i] != sign_val) {
			throw IpIntException("ipint is larger than a long.");
		}
	}
	return long(val[0]);
}

int64_t ipint::toInt64() const {
	int ndx = num_elements() > 1 ? 1 : 0;
	bool tpos = val[ndx] & 0x80000000 ? false : true;
	ELEM_TYPE sign_val;
	if(tpos) sign_val = 0x00000000;
	else sign_val = 0xFFFFFFFF;
	for(size_t i = num_elements() - 1; i > 1; i--) {
		if(val[i] != sign_val) {
			throw IpIntException("ipint is larger than a int64_t.");
		}
	}
	int64_t x(0);
	if(num_elements() == 1) {
		x += val[0];
	}
	else if(num_elements() == 2) {
		x = val[1];
		x <<= ELEM_BITS;
		x += val[0];
	}
	return x;
}

unsigned int ipint::toUnsignedInt() const {
	if(num_elements() > 1) {
		throw IpIntException("ipint is larger than an unsigned integer.");
	}
	return int(val[0]);
}
unsigned long ipint::toUnsignedLong() const {
	if(num_elements() > 1) {
		throw IpIntException("ipint is larger than an unsigned long.");
	}
	return uint32_t(val[0]);
}

uint64_t ipint::toUInt64() const {
	if(num_elements() > 2) {
		throw IpIntException("ipint is larger than a uint64_t.");
	}
	uint64_t x(0);
	if(num_elements() == 1) {
		x += val[0];
	}
	else if(num_elements() == 2) {
		x = val[1];
		x <<= ELEM_BITS;
		x += val[0];
	}
	return x;
}

/* base 2^val_bits division */
void ipint::__divrem(const ipint &dividend, const ipint &divisor, ipint &quotient, ipint &remainder)
{
	/* This routine is derived from Hacker's Delight,
	 * and possibly originates from Knuth */

	quotient = 0;
	remainder = 0;
	ptrdiff_t m = dividend.num_elements(), n = divisor.num_elements();
	quotient._resize(std::max(m - n + 1, ptrdiff_t(1)));
	remainder._resize(n);
	ELEM_TYPE *q = (ELEM_TYPE*)(quotient.val.data()), *r = (ELEM_TYPE*)(remainder.val.data());
	const ELEM_TYPE *u = (ELEM_TYPE*)(dividend.val.data()), *v = (ELEM_TYPE*)(divisor.val.data());

	const ELEM_TYPE2 b = (1ULL << ELEM_BITS); // Number base
	ELEM_TYPE *un, *vn;                       // Normalized form of u, v.
	ELEM_TYPE2 qhat;                          // Estimated quotient digit.
	ELEM_TYPE2 rhat;                          // A remainder.

	if (m < n || n <= 0 || v[n-1] == 0) {
		quotient = 0;
		remainder = dividend;
		return;
	}

	// Single digit divisor
	if (n == 1) {
		ELEM_TYPE2 k = 0;
		for (ptrdiff_t j = m - 1; j >= 0; j--) {
			q[j] = ELEM_TYPE((k*b + u[j]) / v[0]);
			k = (k*b + u[j]) - q[j]*v[0];
		}
		r[0] = ELEM_TYPE(k);
		quotient.contract();
		remainder.contract();
		return;
	}

	// Normalize by shifting v left just enough so that
	// its high-order bit is on, and shift u left the
	// same amount. We may have to append a high-order
	// digit on the dividend; we do that unconditionally.

	int s = clz(v[n-1]); // 0 <= s <= ELEM_BITS.
	vn = (ELEM_TYPE *)alloca(sizeof(ELEM_TYPE) * n);
	for (ptrdiff_t i = n - 1; i > 0; i--) {
		vn[i] = (v[i] << s) | (v[i-1] >> (ELEM_BITS-s));
	}
	vn[0] = v[0] << s;

	un = (ELEM_TYPE *)alloca(sizeof(ELEM_TYPE) * (m + 1));
	un[m] = u[m-1] >> (ELEM_BITS-s);
	for (ptrdiff_t i = m - 1; i > 0; i--) {
		un[i] = (u[i] << s) | (u[i-1] >> (ELEM_BITS-s));
	}
	un[0] = u[0] << s;
	for (ptrdiff_t j = m - n; j >= 0; j--) { // Main loop.
		// Compute estimate qhat of q[j].
		qhat = (un[j+n]*b + un[j+n-1]) / vn[n-1];
		rhat = (un[j+n]*b + un[j+n-1]) - qhat * vn[n-1];
	again:
		if (qhat >= b || qhat*vn[n-2] > b*rhat + un[j+n-2]) {
			qhat = qhat - 1;
			rhat = rhat + vn[n-1];
			if (rhat < b) goto again;
		}
		// Multiply and subtract.
		ELEM_TYPE2 k = 0;
		ELEM_TYPE2 t = 0;
		for (ptrdiff_t i = 0; i < n; i++) {
			unsigned long long p = qhat*vn[i];
			t = un[i+j] - k - (p & ((1ULL<<ELEM_BITS)-1));
			un[i+j] = ELEM_TYPE(t);
			k = (p >> ELEM_BITS) - (t >> ELEM_BITS);
		}
		t = un[j+n] - k;
		un[j+n] = ELEM_TYPE(t);

		q[j] = ELEM_TYPE(qhat); // Store quotient digit.
		if (t < 0) {         // If we subtracted too
			q[j] = q[j] - 1; // much, add back.
			k = 0;
			for (ptrdiff_t i = 0; i < n; i++) {
				t = un[i+j] + vn[i] + k;
				un[i+j] = ELEM_TYPE(t);
				k = t >> ELEM_BITS;
			}
			un[j+n] = ELEM_TYPE(un[j+n] + k);
		}
	}

	// normalize remainder
	for (ptrdiff_t i = 0; i < n; i++) {
		r[i] = (un[i] >> s) | (un[i + 1] << (ELEM_BITS - s));
	}

	quotient.contract();
	remainder.contract();
}

/* expand val to match operand */
void ipint::expand(const ipint &operand)
{
	size_t mxv = max_val();
	size_t ne = num_elements();
	size_t one = operand.num_elements();
	val.resize(std::min(mxv, std::max(ne, one)));
}

/* contract zero big end limbs */
void ipint::contract()
{
	while (bits > 0 && num_elements() > max_val()) {
		val.pop_back();
	}
	while(num_elements() > 1 && val.back() == 0) {
		val.pop_back();
	}
	if (bits > 0 && num_elements() == max_val()) {
		val.back() &= val_mask(num_elements() - 1);
	}
	pos = val[num_elements() - 1] & 0x8000000 ? false : true;
}

/* resize number of val */
void ipint::_resize(size_t n)
{
	val.resize(n);
}


size_t ipint::max_val() const { return ((bits - 1) >> ELEM_SHIFT) + 1; }

/* access word at val offset */
ELEM_TYPE ipint::element_at(size_t n) const { return n < num_elements() ? val[n] : 0; }

/* val_mask at val offset */
ELEM_TYPE ipint::val_mask(const ipint &n) const
{
    if (bits == 0) return -1;
    if (n.toUnsignedInt() < (bits >> ELEM_SHIFT)) return -1;
    if (n.toUnsignedInt() > (bits >> ELEM_SHIFT)) return 0;
	else return ((1 << (bits & ((1ULL << ELEM_BITS) - 1))) - 1);
}

ipint ipint::pow(size_t exp) const
{
	if (exp == 0) return 1;
	ipint x = *this, y = 1;
	while (exp > 1) {
		if ((exp & 1) == 0) {
			exp >>= 1;
		} else {
			y *= x;
			exp = (exp - 1) >> 1;
		}
		x *= x;
	}
	return x * y;
}


/* base 2^limb_bits multiply */
void ipint::__mult(const ipint &multiplicand, const ipint multiplier, ipint &result) const
{
	if(ipint::debug) printf("__mult *********************************************************************************************\n");
	if(ipint::debug) printf("multiplicand = [");
	for(size_t x = 0; x < multiplicand.num_elements(); x++) {
		if(ipint::debug) printf("%x, ", multiplicand.val[x]);
	}
	if(ipint::debug) printf("]\n");
	if(ipint::debug) printf("multiplier = [");
	for(size_t x = 0; x < multiplier.num_elements(); x++) {
		if(ipint::debug) printf("%x, ", multiplier.val[x]);
	}
	if(ipint::debug) printf("]\n");
	if(ipint::debug) printf("result = [");
	for(size_t x = 0; x < result.num_elements(); x++) {
		if(ipint::debug) printf("%x, ", result.val[x]);
	}
	if(ipint::debug) printf("]\n");
	size_t m = multiplicand.num_elements(), n = multiplier.num_elements();
	if(ipint::debug) printf("__mult: m = %d, n = %d\n", m, n);
	size_t k = std::min(multiplicand.max_val(), m + n);
	if(ipint::debug) printf("__mult: result.resize(%d);\n", m + n);
	result._resize(m + n);
	for(size_t i = 0; i  < k; i++) {
		result.val[i] = 0;
	}
	ELEM_TYPE carry = 0;
	size_t j, i;
	for (j = 0; j < n; j++) {
		if(ipint::debug) printf("__mult: for j = %d\n", j);
		carry = 0;
		for (i = 0; i < m; i++) {
			if(ipint::debug) printf("for i = %d\n", i);
			if(ipint::debug) printf("__mult: t = %I64x * %x + %x[%d + %d] + %x\n", ELEM_TYPE2(multiplicand.val[i]), multiplier.val[j], result.val[i + j], i, j, carry);
			ELEM_TYPE2 t = ELEM_TYPE2(multiplicand.val[i]) * multiplier.val[j] + result.val[i + j] + carry;
			if(ipint::debug) printf("__mult: t = %I64x\nmult: ELEM_TYPE(t & ELEM_MASK) = %x\n", t, ELEM_TYPE(t & ELEM_MASK));
			result.val[i + j] = ELEM_TYPE(t & ELEM_MASK);
			if(ipint::debug) printf("result.val[%d + %d] = %x\n", i, j, result.val[i + j]);
			carry = ELEM_TYPE(t >> ELEM_BITS);
			if(ipint::debug) printf("__mult: carry = %x\n", carry);
		}
		result.val[j + m] = carry;
		if(ipint::debug) printf("__mult:: result.val[%d + %d] = %x\n", j, m, result.val[j + m]);
	}
	result.contract();
	if(ipint::debug) printf("__mult: result = [");
	for(size_t x = 0; x < result.size(); x++) {
		if(ipint::debug) printf("%x, ", result.val[x]);
	}
	if(ipint::debug) printf("]\n");
	if(ipint::debug) fflush(stdout);
}

/* return number of bits */
size_t ipint::num_bits() const
{
	if (bits > 0) return bits;
	if (val.size() == 1 && val[0] == 0) return 0;
	return (ELEM_BITS - clz(val.back())) + (num_elements() - 1) * ELEM_BITS;
}

void ipint::dump() const {
	printf("dump(): [pos=%s", pos ? "true" : "false");
	for(size_t i = 0; i < num_elements(); i++) {
		printf(", %x", val[i]);
	}
	printf("]\n");
	fflush(stdout);
}

/* test bit at bit offset */
int ipint::test_bit(size_t n) const
{
	size_t word = n >> ELEM_SHIFT;
	if (word < num_elements()) return (val[word] >> (n & (ELEM_BITS-1))) & 1;
	else return 0;
}

/* set bit at bit offset */
void ipint::set_bit(size_t n)
{
	size_t word = n >> ELEM_SHIFT;
	if (word >= num_elements()) _resize(word + 1);
	val[word] |= (1ULL << (n & (ELEM_BITS-1)));
}

bool ipint::isZero() const {
	for(size_t i = 0; i < num_elements(); i++) {
		if(val[i] != 0) return false;
	}
	return true;
}
