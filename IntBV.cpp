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
 */

#include <algorithm>
#include <string>
#include<bits/stdc++.h>
#include "IntBV.h"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b


IntBV::IntBV(): __val(0) {
	__common_init(0, 0, 0);
}


IntBV::IntBV(const ipint& val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(int val, ipint min, ipint max, unsigned int _nrbits): __val(val, _nrbits) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(const IntBV& val, ipint min, ipint max, unsigned int _nrbits): __val(val.__val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(const std::string& val, ipint min, ipint max, unsigned int _nrbits): __val(val, _nrbits) {
	__common_init(min, max, _nrbits);
	std::string mval = std::string(val);
	std::remove( mval.begin(), mval.end(), '_');
	if(__nrbits == 0) {
		if (mval.compare(0, 2, "0b") == 0) {
			__nrbits = mval.length() - 2;
		} else if (mval.compare(0, 2, "0x") == 0) {
			__nrbits = (mval.length() - 2) * 4;
		}
	}
}


IntBV::IntBV(const char* val, ipint min, ipint max, unsigned int _nrbits): __val(val, _nrbits) {
	__common_init(min, max, _nrbits);
	std::string mval = std::string(val);
	std::remove( mval.begin(), mval.end(), '_');
	if(__nrbits == 0) {
		if (mval.compare(0, 2, "0b") == 0) {
			__nrbits = mval.length() - 2;
		} else if (mval.compare(0, 2, "0x") == 0) {
			__nrbits = (mval.length() - 2) * 4;
		}
	}
}


IntBV::IntBV(long val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(long long val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(unsigned int val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(unsigned long val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


IntBV::IntBV(unsigned long long val, ipint min, ipint max, unsigned int _nrbits): __val(val) {
	__common_init(min, max, _nrbits);
}


void
IntBV::__common_init(const ipint _min, const ipint _max, unsigned int _nrbits) {
//	printf("__common_init: __val = %s\n", __val.toString(16).c_str());
	if(_nrbits) {
		__min = 0;
		__max = long(::pow(2,_nrbits));
		__nrbits = _nrbits;
//		printf("__common_init: _nrbits = %d\n", _nrbits);
	}
	else {
		__min = 0;
		__max = 0;
		__nrbits = _nrbits;
		if(_max != ipint(0) && _min != ipint(0)) {
			if(_min >= ipint(0)) {
				__nrbits = bin(IntBV(_max) + IntBV(1)).length() - 2;
			}
			else if(_max <= ipint(1)) {
				__nrbits = bin(IntBV(_min)).length() - 2;
			}
			else {
				// make sure there is a leading zero bit in positive numbers
				__nrbits = max(bin(IntBV(_max - ipint(1))).length() - 2, bin(IntBV(_min)).length() - 2);
			}
		}
	}
}


void
IntBV::__handleBounds() {
	if(__max != ipint(0)) {
		if(__val >= __max) {
			throw IntbvException("val >= max");
		}
	}
	if(__min != ipint(0)) {
		if(__val < __min) {
			throw IntbvException("val < min");
		}
	}
}


bool
IntBV::__hasFullRange() {
	ipint _min = __min;
	ipint _max = __max;
	if(_max <= ipint(0)) {
		return false;
	}
	if(_min < ipint(0) && _min > -_max) {
		return false;
	}
	return (_max & (_max - ipint(1))) == ipint(0);
}


IntBV
IntBV::_copy_() {
	IntBV c = IntBV(__val, __min, __max, __nrbits);
	return c;
}


IntBV
IntBV::_deepcopy_() {
	IntBV c = IntBV(__val, __min, __max, __nrbits);
	return c;
}


const IntBV&
IntBV::operator=(const char* c) {
	std::string mval = std::string(c);
	std::remove( mval.begin(), mval.end(), '_');
	__val = mval;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(const std::string& s) {
	std::string mval = std::string(s);
	std::remove( mval.begin(), mval.end(), '_');
	__val = mval;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(int l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(long l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(long long l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(unsigned int l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(unsigned long l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(unsigned long long l) {
	__val = l;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(const IntBV& l) {
	__val = l.__val;
	__min = l.__min;
	__max = l.__max;
	__nrbits = l.__nrbits;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator=(const ipint& l) {
	__val = l;
	__handleBounds();
	return *this;
}



const IntBV&
IntBV::operator++() {
	__val += 1;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator--() {
	__val -= 1;
	__handleBounds();
	return *this;
}


IntBV
IntBV::operator++(int) {
	IntBV result = *this;
	result += 1;
	return result;
}


IntBV
IntBV::operator--(int) {
	IntBV result = *this;
	result -= 1;
	return result;
}


const IntBV&
IntBV::operator+=(const IntBV& rhs) {
	__val += rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator-=(const IntBV& rhs) {
	__val -= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator*=(const IntBV& rhs) {
	__val *= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator/=(const IntBV& rhs) {
	__val /= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator%=(const IntBV& rhs) {
	__val %= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator<<=(size_t shamt) {
	__val <<= shamt;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator>>=(size_t shamt) {
	__val >>= shamt;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator&=(const IntBV& rhs) {
	__val &= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator|=(const IntBV& rhs) {
	__val |= rhs.__val;
	__handleBounds();
	return *this;
}


const IntBV&
IntBV::operator^=(const IntBV& rhs) {
	__val ^= rhs.__val;
	__handleBounds();
	return *this;
}


IntBV
IntBV::operator+(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val + rhs.__val;
	return result;
}


IntBV
IntBV::operator-(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val - rhs.__val;
	return result;
}


IntBV
IntBV::operator*(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val * rhs.__val;
	return result;
}


IntBV
IntBV::operator/(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val / rhs.__val;
	return result;
}


IntBV
IntBV::operator%(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val % rhs.__val;
	return result;
}


IntBV
IntBV::operator^(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val ^ rhs.__val;
	return result;
}


IntBV
IntBV::operator<<(size_t rhs) const {
	IntBV result;
	result.__val = this->__val;
	result.__val <<= rhs;
	return result;
}


IntBV
IntBV::operator>>(size_t rhs) const {
	IntBV result;
	result.__val = this->__val;
	result.__val >>= rhs;
	return result;
}


IntBV
IntBV::operator&(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val & rhs.__val;
	return result;
}


IntBV
IntBV::operator|(const IntBV& rhs) const {
	IntBV result;
	result.__val = this->__val | rhs.__val;
	return result;
}

IntBV
IntBV::operator~() const {
	IntBV result;
	result.__val = ~(this->__val);
	return result;
}


IntBV
IntBV::operator-() const {
	IntBV result;
	result.__val = -(this->__val);
	return result;
}


bool
IntBV::operator==(const IntBV& rhs) const {
	return this->__val == rhs.__val;
}


bool
IntBV::operator!=(const IntBV& rhs) const {
	return this->__val != rhs.__val;
}


bool
IntBV::operator<(const IntBV& rhs) const {
	return this->__val < rhs.__val;
}


bool
IntBV::operator<=(const IntBV& rhs) const {
	return this->__val <= rhs.__val;
}


bool
IntBV::operator>(const IntBV& rhs) const {
	return this->__val > rhs.__val;
}


bool
IntBV::operator>=(const IntBV& rhs) const {
	return this->__val >= rhs.__val;
}


size_t
IntBV::size() const {
	size_t ipint_sz = sizeof(__val);
	size_t minsz = ipint_sz;
	size_t maxsz = ipint_sz;
	size_t sz = ipint_sz + minsz + maxsz + sizeof(int);
	return sz;
}


std::string
IntBV::toString() const {
	return this->__val.toString(10);
}


int
IntBV::toInt() const {
	// printf("toInt() => %d\n", this->__val.toInt());
	try {
		return this->__val.toInt();
	} catch(const IpIntException& e) {
//		printf("IntBV::toInt(): __nrbits = %d\n", __nrbits);
		if(__nrbits && __nrbits < 33) {
			ipint lim(1 << __nrbits);
//			printf("IntBV::toInt(): lim = %d\n", lim.toInt());
			ipint mask(lim - 1);
			ipint temp(__val.element_at(0));
			temp &= mask;
			temp.contract();
//			printf("IntBV::toInt(): temp = %s\n", hex(temp).c_str());
			return temp.toInt();
		} else {
			throw e;
		}
	}
}


long
IntBV::toLong() const {
	return this->__val.toLong();
}


long long
IntBV::toLongLong() const {
	return this->__val.toInt64();
}


unsigned int
IntBV::toUnsignedInt() const {
	return this->__val.toUnsignedInt();
}


unsigned long
IntBV::toUnsignedLong() const {
	return this->__val.toUnsignedLong();
}


unsigned long long
IntBV::toUnsignedLongLong() const {
	return this->__val.toUInt64();
}

std::string
_int2bitstring(const IntBV& num) {
	std::string bits;
	if(num == IntBV(0)) {
		bits = '0';
		return bits;
	}
	if(abs(num) == IntBV(1)) {
		bits = '1';
		return bits;
	}
	ipint p = num.to_ipint() / ipint(2);
	ipint q = num.to_ipint() % ipint(2);
	bits += q.toString(2);
	while( !(abs(IntBV(p)) == IntBV(1))) {
		p = p / ipint(2);
		q = q % ipint(2);
		bits += q.toString(2);
	}
	bits += '1';
	reverse(bits.begin(), bits.end());
//	bits = num.__val.toString(2);
	return bits;
}


std::string
_int2hexstring(const IntBV& num) {
	const char *values = "0123456789ABCDEF";
	std::string digits;
	if(num == IntBV(0)) {
		digits = '0';
		return digits;
	}
	if(abs(num) == IntBV(15)) {
		digits = 'F';
		return digits;
	}
	ipint p = num.to_ipint() / ipint(16);
	ipint q = num.to_ipint() % ipint(16);
	digits += values[q.toInt()];
	while(abs(IntBV(p)) != IntBV(0)) {
		p = p / ipint(2);
		q = q % ipint(2);
		digits += values[q.toInt()];
	}
	reverse(digits.begin(), digits.end());
//	digits = num.__val.toString(16);
	return digits;
}


std::string
bin(const IntBV& num, ipint width) {
	std::string s(num.to_ipint().toString(2));
//	printf("bin() => s = %s\n", s.c_str());
//	printf("bin() => s.length() = %d\n", s.length());
//	printf("bin() => width = %d\n", width.toUnsignedInt());
//	printf("bin() => (width + 2 - s.length()) = %d\n", width.toInt() + 2 - s.length());
//	printf("bin() => num.get_nrbits() = %d\n", num.get_nrbits());
	if(width > ipint(0)) {
		if(s.length() > width.toUnsignedInt()) {
			s = s.substr(s.length()-width.toInt(), std::string::npos);
			s.insert(0, "0b");
			return s;
		}
		else {
			s.insert(2, width.toInt()+2-s.length(), (num < IntBV(0) ? '1' : '0'));
			return s;
		}
	}
	else if(num.get_nrbits() > 0) {
		if(s.length()-2 > num.get_nrbits()) {
//			printf("s.length()-2 > num.get_nrbits()\n");
			s = s.substr(s.length()-num.get_nrbits(), std::string::npos);
			s.insert(0, "0b");
			return s;
		}
		else if(s.length()-2 < num.get_nrbits()) {
//			printf("s.length()-2 < num.get_nrbits()\n");
			s.insert(2, num.get_nrbits()+2-s.length(), (num < IntBV(0) ? '1' : '0'));
			return s;
		}
		return s;
	}
	else {
		return s;
	}
//	if(width > 0) {
//		ipint w(width.toInt() + 2 - s.length());
//		printf("bin() => w = %s\n", w.toString().c_str());
//		s.insert(2, width.toInt()+2-s.length(), (num < 0 ? '1' : '0'));
//		return s;
//	}
//	else if(num.get_nrbits() > 0) {
//		printf("bin() => num_get_nrbits = %d\n", num.get_nrbits());
//		ipint w(num.get_nrbits() + 2 - s.length());
//		s.insert(2, w.toInt(), (num < 0 ? '1' : '0'));
//		return s;
//	}
//	return s;
}


std::string
hex(const IntBV& num, ipint width) {
	std::string s(num.to_ipint().toString(16));
	size_t nrbits = num.get_nrbits();
//	printf("hex() => s = %s\n", s.c_str());
//	printf("hex() => s.length() = %d\n", s.length());
//	printf("hex() => width = %d\n", width.toUnsignedInt());
//	printf("hex() => (width + 2 - s.length()) = %d\n", width.toUnsignedInt() + 2 - s.length());
//	printf("hex() => num.get_nrbits() = %d\n", num.get_nrbits());
//	fflush(stdout);
	if(width > ipint(0)) {
		if(s.length() > width.toUnsignedInt()) {
			s = s.substr(s.length()-width.toUnsignedInt(), std::string::npos);
			s.insert(0, "0x");
			return s;
		}
		else {
			s.insert(2, width.toUnsignedInt()+2-s.length(), (num < IntBV(0) ? 'F' : '0'));
			return s;
		}
	}
	else if(nrbits > 0) {
		IntBV temp(bin(num, nrbits), 0, 0, nrbits);
		return hex(temp, (nrbits + 3)/4);
	}
	else return s;
//	//std::string su = _int2hexstring(num);
//	// printf("hex() => num = %s\n", num.toString().c_str());
//	std::string su(num.to_ipint().toString(16));
//	// printf("hex() => su = %s\n", su.c_str());
//	transform(su.begin(), su.end(), su.begin(), ::toupper);
//	su[1] = 'x';
//	// printf("hex() => su = %s\n", su.c_str());
//	if(width > 0) {
//		IntBV w(width - su.length());
//		su.insert(2, std::stoi(width.toString().c_str())+2-su.length(), (num < 0 ? 'F' : '0'));
//		return su;
//	}
//	else if(num.get_nrbits() > 0) {
//		IntBV w(num.get_nrbits() - su.length());
//		su.insert(2, (num.get_nrbits()/4)+2-su.length(), (num < 0 ? 'F' : '0'));
//		return su;
//	}
//	return su;
}


std::string
dec(const IntBV& num) {
	return num.toString();
}


IntBV
abs(const IntBV& num) {
	return num < IntBV(0) ? -num : num;
}


IntBV
IntBV::pow(size_t exp) const {
	IntBV result;
	result.__val = this->__val.pow(exp);
	return result;
}


IntBV
IntBV::get_slice(size_t start_bit_index, size_t end_bit_index) const {
	if(end_bit_index < 0) {
		throw IntbvException("IntBV requires end_bit_index to be >= 0.");
	}
	if(start_bit_index == 0) {
		return IntBV(this->__val >> end_bit_index);
	}
	if(start_bit_index <= end_bit_index) {
		throw IntbvException("IntBV requires start > end for bit slicing.");
	}
	ipint v(__val);
//	printf("get_slice: v = %s\n", v.toString(16).c_str());
	ipint mask(1);
//	printf("get_slice: mask = %s\n", mask.toString(16).c_str());
	mask.expand(v);
//	printf("get_slice: mask = %s\n", mask.toString(16).c_str());
	mask <<= start_bit_index;
//	printf("get_slice: mask = %s\n", mask.toString(16).c_str());
	mask -= ipint(1);
//	printf("get_slice: mask = %s\n", mask.toString(16).c_str());
	v &= mask;
//	printf("get_slice: v = %s\n", v.toString(16).c_str());
	v >>= end_bit_index;
//	printf("get_slice: v = %s\n", v.toString(16).c_str());
	v.contract();
//	printf("get_slice: v = %s\n", v.toString(16).c_str());
//	IntBV res((__val & ((1 << start_bit_index) - 1)), 0, 0, start_bit_index);
	IntBV res(v, 0, 0, start_bit_index - end_bit_index);
	return res;
}


IntBV
IntBV::get_slice(size_t start_bit_index) const {
	if(start_bit_index <= 0) {
		throw IntbvException("IntBV requires start > end for bit slicing.");
	}
	ipint v(__val);
	ipint mask(1);
	mask.expand(__val);
	mask <<= start_bit_index;
	mask -= ipint(1);
	v &= mask;
//	IntBV res((__val & ((1 << start_bit_index) - 1)), 0, 0, start_bit_index);
	IntBV res(v, 0, 0, start_bit_index);
	return res;
}


IntBV
IntBV::get_slice_e(size_t end_bit_index) const {
	return IntBV(this->__val >> end_bit_index);
}


bool
IntBV::get_bit(size_t bit_index) const {
	return __val.test_bit(bit_index) ? true : false;
}


void
IntBV::set_slice(size_t start_bit_index, size_t end_bit_index, const IntBV& val) {
	ipint ipval(val.__val);
	ipval.expand(__val);
//	printf("set_slice() => *this = %s\n", hex(__val).c_str());
//	printf("set_slice() => start_bit_index = %d\n", start_bit_index);
//	printf("set_slice() => end_bit_index = %d\n", end_bit_index);
//	printf("set_slice() => ipval = %s\n", ipval.toString(16).c_str());
//	printf("set_slice() => ipval = %s\n", ipval.toString().c_str());
	if(end_bit_index < 0) {
		throw IntbvException("IntBV requires end_bit_index >= 0.");
	}
	if(start_bit_index <= end_bit_index) {
		throw IntbvException("IntBV requires start_bit_index > end_bit_index.");
	}
	ipint lim((ipint(1) << (start_bit_index - end_bit_index)));
	lim.expand(__val);
//	printf("set_slice() => lim = %s\n", lim.toString().c_str());
//	printf("set_slice() => lim = %s\n", lim.toString(16).c_str());
	ipint neglim(0);
	neglim -= lim;
//	printf("set_slice() => neglim = %s\n", neglim.toString().c_str());
	if(ipval >= lim || ipval < neglim) {
		throw IntbvException("abs(val) too large.");
	}
	ipint mask((lim - ipint(1)) << end_bit_index);
	mask.expand(__val);
//	printf("set_slice() => *this = %s\n", hex(__val).c_str());
//	printf("set_slice() => mask = %s\n", hex(mask).c_str());
	__val &= ~mask;
//	printf("set_slice() => __val = %s\n", hex(__val).c_str());
	ipval.expand(__val);
	__val |= (ipval << end_bit_index);
//	__val.dump();
//	printf("set_slice() => __val = %s\n", hex(__val).c_str());
	__handleBounds();
}


void
IntBV::set_slice(size_t start_bit_index, const IntBV& val) {
	ipint ipval(val.__val);
	//	printf("set_slice() => *this = %s\n", hex(__val).c_str());
	ipint j(0);
	ipint i(start_bit_index);
//	printf("set_slice() => start_bit_index = %d\n", start_bit_index);
//	printf("set_slice() => ipval = %s\n", ipval.toString(16).c_str());
//	printf("set_slice() => ipval = %s\n", ipval.toString().c_str());
	if(start_bit_index <= 0) {
		throw IntbvException("IntBV requires start_bit_index > 0.");
	}
	ipint lim((ipint(1) << start_bit_index));
//	printf("set_slice() => lim = %s\n", lim.toString().c_str());
	ipint neglim(0);
	neglim -= lim;
//	printf("set_slice() => neglim = %s\n", neglim.toString().c_str());
//	printf("set_slice() => neglim = ");
//	neglim.dump();
	if(ipval >= lim || ipval < neglim) {
		throw IntbvException("abs(val) too large.");
	}
	ipint mask(lim - ipint(1));
	mask.expand(__val);
//	printf("set_slice() => mask = %s\n", hex(mask).c_str());
//	printf("set_slice() => *this = %s\n", hex(__val).c_str());
//	printf("set_slice() => ~mask = %s\n", hex(~mask).c_str());
	__val &= ~mask;
//	printf("set_slice() => __val = %s\n", hex(__val).c_str());
//	printf("set_slice() => ipval = %s\n", hex(ipval).c_str());
	ipval.expand(__val);
	__val |= ipval;
//	printf("set_slice() => __val = %s\n", hex(__val).c_str());
	__handleBounds();
}


void
IntBV::set_slice_e(size_t end_bit_index, const IntBV& val) {
	ipint ipval(val.__val);
//	printf("set_slice() => end_bit_index = %d\n", end_bit_index);
//	printf("set_slice() => ipval = %s\n", ipval.toString(16).c_str());
//	printf("set_slice() => ipval = %s\n", ipval.toString().c_str());
	ipint q(__val % ipint(1 << end_bit_index));
	__val = ipval * ipint(1 << end_bit_index) + q;
	__handleBounds();

}


void
IntBV::set_bit(size_t bit_index, int val) {
	if(val) {
		__val.set_bit(bit_index);
	}
	else {
		set_slice(bit_index+1, bit_index, 0);
	}
}




