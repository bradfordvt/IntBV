/* Unit test cases for the IntBV and ipint classes

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
 * testIntBV.cpp
 *
 *  Created on: Nov 6, 2020
 *      Author: Bradford G. Van Treuren
 */
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#ifdef __MINGW32__
#define sleep(seconds) Sleep((seconds)*1000)
#elif _MSC_VER >= 1900
#define sleep(seconds) Sleep((seconds)*1000)
#include "pch.h"
#endif


#include "ipint.h"
#include "IntBV.h"

using namespace CppUnit;
using namespace std;

const int64_t ELEM_BITS_NUM = 0xFFFFFFFF;
const int64_t ELEM_BITS_NUM2 = 0xFFFFFFFFFFFFFFFF;

//-----------------------------------------------------------------------------

class TestIntBV : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestIntBV);
    CPPUNIT_TEST(test_IpIntConstructors001);
    CPPUNIT_TEST(test_IpIntConstructors002);
    CPPUNIT_TEST(test_IpIntConstructors003);
    CPPUNIT_TEST(test_IpIntConstructors004);
    CPPUNIT_TEST(test_IpIntConstructors005);
    CPPUNIT_TEST(test_IpIntConstructors006);
    CPPUNIT_TEST(test_IpIntConstructors007);
    CPPUNIT_TEST(test_IpIntConstructors008);
    CPPUNIT_TEST(test_IpIntConstructors009);
    CPPUNIT_TEST(test_IpIntConstructors010);
    CPPUNIT_TEST(test_IpIntOpPlusEq001);
    CPPUNIT_TEST(test_IpIntOpMultEq001);
    CPPUNIT_TEST(test_IpIntOpPlusPlus001);
    CPPUNIT_TEST(test_IpIntOpMinusMinus001);
    CPPUNIT_TEST(test_IpIntOpMinusEq001);
    CPPUNIT_TEST(test_IpIntOpMinusEq002);
    CPPUNIT_TEST(test_IpIntOpDivEq001);
    CPPUNIT_TEST(test_IpIntOpModEq001);
    CPPUNIT_TEST(test_IpIntOpLShiftEq001);
    CPPUNIT_TEST(test_IpIntOpRShiftEq001);
    CPPUNIT_TEST(test_IpIntOpAndEq001);
    CPPUNIT_TEST(test_IpIntOpTilde001);
    CPPUNIT_TEST(test_IpIntOpNotEq001);
    CPPUNIT_TEST(test_IpIntOpNeg001);
    CPPUNIT_TEST(test_IpIntOpPlus001);
    CPPUNIT_TEST(test_IpIntOpMinus001);
    CPPUNIT_TEST(test_IpIntOpMult001);
    CPPUNIT_TEST(test_IpIntOpDiv001);
    CPPUNIT_TEST(test_IpIntOpMod001);
    CPPUNIT_TEST(test_IpIntOpLShift001);
    CPPUNIT_TEST(test_IpIntOpRShift001);
    CPPUNIT_TEST(test_IpIntOpLT001);
    CPPUNIT_TEST(test_IpIntOpGT001);
    CPPUNIT_TEST(test_IpIntOpLTEq001);
    CPPUNIT_TEST(test_IpIntOpGTEq001);
    CPPUNIT_TEST(test_IpIntToString001);
    CPPUNIT_TEST(test_IpIntToInt001);
    CPPUNIT_TEST(test_IpIntToLong001);
    CPPUNIT_TEST(test_IpIntToInt64001);
    CPPUNIT_TEST(test_IpIntToUInt001);
    CPPUNIT_TEST(test_IpIntToULong001);
    CPPUNIT_TEST(test_IpIntToUInt64001);
    CPPUNIT_TEST(test_IpIntOpAnd001);
    CPPUNIT_TEST(test_IpIntOpOrEq001);
    CPPUNIT_TEST(test_IpIntOpOr001);
    CPPUNIT_TEST(test_IpIntOpXorEq001);
    CPPUNIT_TEST(test_IpIntOpXor001);
    CPPUNIT_TEST(test_IntbvConstructors001);
    CPPUNIT_TEST(test_IntbvConstructors002);
    CPPUNIT_TEST(test_IntbvConstructors003);
    CPPUNIT_TEST(test_IntbvConstructors004);
    CPPUNIT_TEST(test_IntbvConstructors005);
    CPPUNIT_TEST(test_IntbvConstructors006);
    CPPUNIT_TEST(test_IntbvConstructors007);
    CPPUNIT_TEST(test_IntbvConstructors008);
    CPPUNIT_TEST(test_IntbvConstructors009);
    CPPUNIT_TEST(test_IntbvConstructors010);
    CPPUNIT_TEST(test_IntbvOpPlusEq001);
    CPPUNIT_TEST(test_IntbvOpMultEq001);
    CPPUNIT_TEST(test_IntbvOpPlusPlus001);
    CPPUNIT_TEST(test_IntbvOpMinusMinus001);
    CPPUNIT_TEST(test_IntbvOpMinusEq001);
    CPPUNIT_TEST(test_IntbvOpDivEq001);
    CPPUNIT_TEST(test_IntbvOpModEq001);
    CPPUNIT_TEST(test_IntbvOpLShiftEq001);
    CPPUNIT_TEST(test_IntbvOpRShiftEq001);
    CPPUNIT_TEST(test_IntbvOpAndEq001);
    CPPUNIT_TEST(test_IntbvOpTilde001);
    CPPUNIT_TEST(test_IntbvOpNotEq001);
    CPPUNIT_TEST(test_IntbvOpNeg001);
    CPPUNIT_TEST(test_IntbvOpPlus001);
    CPPUNIT_TEST(test_IntbvOpMinus001);
    CPPUNIT_TEST(test_IntbvOpMult001);
    CPPUNIT_TEST(test_IntbvOpDiv001);
    CPPUNIT_TEST(test_IntbvOpMod001);
    CPPUNIT_TEST(test_IntbvOpLShift001);
    CPPUNIT_TEST(test_IntbvOpRShift001);
    CPPUNIT_TEST(test_IntbvOpLT001);
    CPPUNIT_TEST(test_IntbvOpGT001);
    CPPUNIT_TEST(test_IntbvOpLTEq001);
    CPPUNIT_TEST(test_IntbvOpGTEq001);
    CPPUNIT_TEST(test_IntbvToString001);
    CPPUNIT_TEST(test_IntbvToInt001);
    CPPUNIT_TEST(test_IntbvToLong001);
    CPPUNIT_TEST(test_IntbvToInt64001);
    CPPUNIT_TEST(test_IntbvToUInt001);
    CPPUNIT_TEST(test_IntbvToULong001);
    CPPUNIT_TEST(test_IntbvToUInt64001);
    CPPUNIT_TEST(test_IntbvOpAnd001);
    CPPUNIT_TEST(test_IntbvOpOrEq001);
    CPPUNIT_TEST(test_IntbvOpOr001);
    CPPUNIT_TEST(test_IntbvOpXorEq001);
    CPPUNIT_TEST(test_IntbvOpXor001);
    CPPUNIT_TEST(test_IntbvGetSlice001);
    CPPUNIT_TEST(test_IntbvGetSlice002);
    CPPUNIT_TEST(test_IntbvGetSlice003);
    CPPUNIT_TEST(test_IntbvBin001);
    CPPUNIT_TEST(test_IntbvHex001);
    CPPUNIT_TEST(test_IntbvSetSlice001);
    CPPUNIT_TEST(test_IntbvSetSlice002);
    CPPUNIT_TEST(test_IntbvGetSliceE001);
    CPPUNIT_TEST(test_IntbvSetSliceE001);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void test_IpIntConstructors001(void);
    void test_IpIntConstructors002(void);
    void test_IpIntConstructors003(void);
    void test_IpIntConstructors004(void);
    void test_IpIntConstructors005(void);
    void test_IpIntConstructors006(void);
    void test_IpIntConstructors007(void);
    void test_IpIntConstructors008(void);
    void test_IpIntConstructors009(void);
    void test_IpIntConstructors010(void);
    void test_IpIntOpPlusEq001(void);
    void test_IpIntOpMultEq001(void);
    void test_IpIntOpPlusPlus001(void);
    void test_IpIntOpMinusMinus001(void);
    void test_IpIntOpMinusEq001(void);
    void test_IpIntOpMinusEq002(void);
    void test_IpIntOpDivEq001(void);
    void test_IpIntOpModEq001(void);
    void test_IpIntOpLShiftEq001(void);
    void test_IpIntOpRShiftEq001(void);
    void test_IpIntOpAndEq001(void);
    void test_IpIntOpTilde001(void);
    void test_IpIntOpNotEq001(void);
    void test_IpIntOpNeg001(void);
    void test_IpIntOpPlus001(void);
    void test_IpIntOpMinus001(void);
    void test_IpIntOpMult001(void);
    void test_IpIntOpDiv001(void);
    void test_IpIntOpMod001(void);
    void test_IpIntOpLShift001(void);
    void test_IpIntOpRShift001(void);
    void test_IpIntOpLT001(void);
    void test_IpIntOpGT001(void);
    void test_IpIntOpLTEq001(void);
    void test_IpIntOpGTEq001(void);
    void test_IpIntToString001(void);
    void test_IpIntToInt001(void);
    void test_IpIntToLong001(void);
    void test_IpIntToInt64001(void);
    void test_IpIntToUInt001(void);
    void test_IpIntToULong001(void);
    void test_IpIntToUInt64001(void);
    void test_IpIntOpAnd001(void);
    void test_IpIntOpOrEq001(void);
    void test_IpIntOpOr001(void);
    void test_IpIntOpXorEq001(void);
    void test_IpIntOpXor001(void);
    void test_IntbvConstructors001(void);
    void test_IntbvConstructors002(void);
    void test_IntbvConstructors003(void);
    void test_IntbvConstructors004(void);
    void test_IntbvConstructors005(void);
    void test_IntbvConstructors006(void);
    void test_IntbvConstructors007(void);
    void test_IntbvConstructors008(void);
    void test_IntbvConstructors009(void);
    void test_IntbvConstructors010(void);
    void test_IntbvOpPlusEq001(void);
    void test_IntbvOpMultEq001(void);
    void test_IntbvOpPlusPlus001(void);
    void test_IntbvOpMinusMinus001(void);
    void test_IntbvOpMinusEq001(void);
    void test_IntbvOpDivEq001(void);
    void test_IntbvOpModEq001(void);
    void test_IntbvOpLShiftEq001(void);
    void test_IntbvOpRShiftEq001(void);
    void test_IntbvOpAndEq001(void);
    void test_IntbvOpTilde001(void);
    void test_IntbvOpNotEq001(void);
    void test_IntbvOpNeg001(void);
    void test_IntbvOpPlus001(void);
    void test_IntbvOpMinus001(void);
    void test_IntbvOpMult001(void);
    void test_IntbvOpDiv001(void);
    void test_IntbvOpMod001(void);
    void test_IntbvOpLShift001(void);
    void test_IntbvOpRShift001(void);
    void test_IntbvOpLT001(void);
    void test_IntbvOpGT001(void);
    void test_IntbvOpLTEq001(void);
    void test_IntbvOpGTEq001(void);
    void test_IntbvToString001(void);
    void test_IntbvToInt001(void);
    void test_IntbvToLong001(void);
    void test_IntbvToInt64001(void);
    void test_IntbvToUInt001(void);
    void test_IntbvToULong001(void);
    void test_IntbvToUInt64001(void);
    void test_IntbvOpAnd001(void);
    void test_IntbvOpOrEq001(void);
    void test_IntbvOpOr001(void);
    void test_IntbvOpXorEq001(void);
    void test_IntbvOpXor001(void);
    void test_IntbvGetSlice001(void);
    void test_IntbvGetSlice002(void);
    void test_IntbvGetSlice003(void);
    void test_IntbvBin001(void);
    void test_IntbvHex001(void);
    void test_IntbvSetSlice001(void);
    void test_IntbvSetSlice002(void);
    void test_IntbvGetSliceE001(void);
    void test_IntbvSetSliceE001(void);

private:


};

//-----------------------------------------------------------------------------

void
TestIntBV::test_IpIntConstructors001(void)
{
	try {
		ipint a1;
		CPPUNIT_ASSERT(a1.toInt() == 0);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors002(void)
{
	try {
		ipint a1(0);
		CPPUNIT_ASSERT(a1.toInt() == 0);
		ipint a2(1);
		CPPUNIT_ASSERT(a2.toInt() == 1);
		ipint a3(1024);
		CPPUNIT_ASSERT(a3.toInt() == 1024);
		ipint a4(ELEM_BITS_NUM + 1);
		CPPUNIT_ASSERT(a4 == ipint(ELEM_BITS_NUM + 1));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors003(void)
{
	try {
		ipint a1(long(0));
		CPPUNIT_ASSERT(a1.toInt() == 0);
		ipint a2(long(1));
		CPPUNIT_ASSERT(a2.toInt() == 1);
		ipint a3(long(1024));
		CPPUNIT_ASSERT(a3.toInt() == 1024);
		ipint a4(0x7FFFFFFFL);
		CPPUNIT_ASSERT(a4.toLong() == 0x7FFFFFFFL);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors004(void)
{
	try {
		ipint a1(uint32_t(0));
		CPPUNIT_ASSERT(a1.toInt() == 0);
		ipint a2(uint32_t(1));
		CPPUNIT_ASSERT(a2.toInt() == 1);
		ipint a3(uint32_t(1024));
		CPPUNIT_ASSERT(a3.toInt() == 1024);
		ipint a4(uint32_t(0xFFFFFFFFUL));
		CPPUNIT_ASSERT(a4.toUnsignedLong() == 0xFFFFFFFFUL);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors005(void)
{
	try {
		ipint a1(int64_t(0));
		CPPUNIT_ASSERT(a1.toInt64() == int64_t(0));
		ipint a2(int64_t(1));
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(1));
		ipint a3(int64_t(1024));
		CPPUNIT_ASSERT(a3.toInt64() == int64_t(1024));
		ipint a4(ELEM_BITS_NUM + 1);
		CPPUNIT_ASSERT(a4.toInt64() == ELEM_BITS_NUM + 1);
		ipint a5(ELEM_BITS_NUM2);
		CPPUNIT_ASSERT(a5.toInt64() == ELEM_BITS_NUM2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors006(void)
{
	try {
		ipint a1(uint64_t(0));
		CPPUNIT_ASSERT(a1.toUInt64() == uint64_t(0));
		ipint a2(uint64_t(1));
		CPPUNIT_ASSERT(a2.toUInt64() == uint64_t(1));
		ipint a3(uint64_t(1024));
		CPPUNIT_ASSERT(a3.toUInt64() == uint64_t(1024));
		ipint a4(ELEM_BITS_NUM);
		CPPUNIT_ASSERT(a4.toUInt64() == ELEM_BITS_NUM);
		ipint a5(ELEM_BITS_NUM2 - 1);
		CPPUNIT_ASSERT(a5.toUInt64() == uint64_t(ELEM_BITS_NUM2 - 1));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors007(void)
{
	try {
		ipint a1(uint64_t((ELEM_BITS_NUM2) - 1));
		CPPUNIT_ASSERT(a1.toUInt64() == uint64_t((ELEM_BITS_NUM2) - 1));
		ipint a2(a1);
		CPPUNIT_ASSERT(a2.toUInt64() == uint64_t((ELEM_BITS_NUM2) - 1));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors008(void)
{
	try {
		ipint a1{0xFFFFFFFF, 0};
		uint64_t l = 0xFFFFFFFF;
		CPPUNIT_ASSERT(a1.toUInt64() == l);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors009(void)
{
	try {
		ipint a1("123456789");
		CPPUNIT_ASSERT(a1.toUInt64() == uint64_t(123456789));
		ipint a2("0x12345678FEFEAA55");
		CPPUNIT_ASSERT(a2.toUInt64() == int64_t(0x12345678FEFEAA55));
		ipint a3("0b00001011101011011101111010101101");
		CPPUNIT_ASSERT(a3.toUInt64() == int64_t(0x0BADDEAD));
		ipint a4("0x123456789ABCDEFFEDCBA9876543210A5ED");
		ipint a5{0x3210A5ED, 0xBA987654, 0xCDEFFEDC, 0x456789AB, 0x123};
		CPPUNIT_ASSERT(a4 == a5);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntConstructors010(void)
{
	try {
		ipint a1(std::string("123456789"));
		CPPUNIT_ASSERT(a1.toUInt64() == uint64_t(123456789));
		ipint a2(std::string("0x12345678FEFEAA55"));
		CPPUNIT_ASSERT(a2.toUInt64() == int64_t(0x12345678FEFEAA55));
		ipint a3(std::string("0b00001011101011011101111010101101"));
		CPPUNIT_ASSERT(a3.toUInt64() == int64_t(0x0BADDEAD));
		ipint a4(std::string("0x123456789ABCDEFFEDCBA9876543210A5ED"));
		ipint a5{0x3210A5ED, 0xBA987654, 0xCDEFFEDC, 0x456789AB, 0x123};
		CPPUNIT_ASSERT(a4 == a5);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpPlusEq001(void)
{
	try {
		ipint a1(0);
		a1 += 5;
		CPPUNIT_ASSERT(a1 == ipint(5));
		ipint a2(int64_t(0x12345678FEFEAA55));
		a2 += 6;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678FEFEAA5B));
		a2 += "0x65";
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678FEFEAAC0));
		a2 += std::string("0x35");
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678FEFEAAF5));
		a2 += 0x5555L;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678FEFF004A));
		a2 += int64_t(0x5555AAAAAAAA5555);
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x678a0123a9a9559f));
		a2 += uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x678a01240403aff9));
		a2 += uint64_t(0xAAAAAAAA5555AAAA);
		ipint a2a{0x59595aa3, 0x1234abce, 0x1};
		CPPUNIT_ASSERT(a2 == a2a);
		ipint a3(0x12345678);
		ipint a4(0x12345678);
		CPPUNIT_ASSERT(a3 == a4);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMultEq001(void)
{
	try {
		ipint a1(5);
		a1 *= 5;
		CPPUNIT_ASSERT(a1 == ipint(25));
		ipint a2(int64_t(0x123456789ABCDEF));
		a2 *= 6;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x6D3A06D3A06D39A));
		a2 *= 8;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x369D0369D0369CD0));
		a2 *= 0x64;
		ipint a2a{0x55554140, 0x55555555, 0x15};
		// CPPUNIT_ASSERT(a2 == int64_t(0x5555555555554140));
		CPPUNIT_ASSERT(a2 == a2a);
		a2 *= 256;
		ipint a3{0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a3);
		a2 *= 65536;
		ipint a4{0x40000000, 0x55555541, 0x15555555};
		CPPUNIT_ASSERT(a2 == a4);
		a2 *= 65536;
		ipint a5{0x00000000, 0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a5);
		a2 *= 65536;
		ipint a6{0x00000000, 0x40000000, 0x55555541, 0x15555555};
		CPPUNIT_ASSERT(a2 == a6);
		a2 *= 65536;
		ipint a7{0x00000000, 0x00000000, 0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a7);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpPlusPlus001(void)
{
	try {
		ipint a1(5);
		CPPUNIT_ASSERT(++a1 == ipint(6));
		++a1;
		CPPUNIT_ASSERT(a1 == ipint(7));
		ipint a2(0);
		a2 = a1++;
		CPPUNIT_ASSERT(a2 == ipint(8));
		CPPUNIT_ASSERT(a1 == ipint(7));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMinusMinus001(void)
{
	try {
		ipint a1(8);
		CPPUNIT_ASSERT(--a1 == ipint(7));
		--a1;
		CPPUNIT_ASSERT(a1 == ipint(6));
		ipint a2(0);
		a2 = a1--;
		CPPUNIT_ASSERT(a2 == ipint(5));
		CPPUNIT_ASSERT(a1 == ipint(6));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMinusEq001(void)
{
	try {
		ipint a1(9);
		a1 -= 5;
		CPPUNIT_ASSERT(a1 == ipint(4));
		ipint a2(int64_t(0x12345678FEFEAA55));
		a2 -= 3;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678fefeaa52));
		a2 -= "0x2";
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678FEFEAA50));
		a2 -= std::string("0x35");
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678fefeaa1b));
		a2 -= 0x5555L;
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12345678fefe54c6));
		a2 -= int64_t(0x00100000AAAA5555);
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x122456785453ff71));
		a2 -= uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2.toInt64() == int64_t(0x12245677f9f9a517));
		a2 -= uint64_t(0x0000AAAA5555AAAA);
		ipint a2a("0x1223abcda4a3fa6d");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMinusEq002(void)
{
	try {
		ipint a0(-1);
//		printf("test_IpIntOpMinusEq002: a0 = %s\n", hex(a0).c_str());
//		a0.dump();
		CPPUNIT_ASSERT(a0.toUnsignedInt() == 0xFFFFFFFF);
		CPPUNIT_ASSERT(a0.toInt() == -1);
		ipint a1(0);
		a1 -= 1;
		CPPUNIT_ASSERT(a1.toUnsignedInt() == 0xFFFFFFFF);
		CPPUNIT_ASSERT(a1.toInt() == -1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpDivEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 /= ipint(65536);
		CPPUNIT_ASSERT(a1.toInt64() == 0x5555AAAA5555);
		a1 /= ipint(65536);
		CPPUNIT_ASSERT(a1.toInt64() == 0x5555AAAA);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpModEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 %= ipint(65536);
		CPPUNIT_ASSERT(a1.toInt() == 0xAAAA);
		a1 = 0x5555AAAA5555AAAA;
		a1 %= ipint(1024);
		CPPUNIT_ASSERT(a1.toInt() == 0x2AA);
		a1 = 0x5555AAAA5555AAAA;
		a1 %= ipint(0x5555AAAA);
		CPPUNIT_ASSERT(a1 == ipint(0));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpLShiftEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 <<= 8;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA00"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 16;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA0000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 32;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA00000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 64;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA0000000000000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 31;
		CPPUNIT_ASSERT(a1 == ipint("0x2AAAD5552AAAD55500000000"));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpRShiftEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 >>= 8;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AA"));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 16;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555"));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 32;
		CPPUNIT_ASSERT(a1 == ipint{0x5555AAAA});
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 64;
		CPPUNIT_ASSERT(a1 == ipint(0));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 31;
		CPPUNIT_ASSERT(a1 == ipint{0xAAAB5554});
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpAndEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 &= ipint(0xAAAA5555AAAA5555);
		ipint a1a{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 &= ipint(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == ipint(0x5555000055550000));
		a1 = 0x5555AAAA5555AAAA;
		a1 &= ipint(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpTilde001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = ~a1;
		ipint a1a(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 == a1a);
		ipint a2("0x5555AAAA5555AAAA5555AAAA5555AAAA");
		a2 = ~a2;
		ipint a2a("0xAAAA5555AAAA5555AAAA5555AAAA5555");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpNotEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		ipint a1a(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 != a1a);
		ipint a2("0x5555AAAA5555AAAA5555AAAA5555AAAA");
		ipint a2a("0xAAAA5555AAAA5555AAAA5555AAAA5555");
		CPPUNIT_ASSERT(a2 != a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpNeg001(void)
{
	try {
		ipint a1(32768);
		a1 = -a1;
		ipint a1a(0xFFFF8000);
		CPPUNIT_ASSERT(a1 == a1a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpPlus001(void)
{
	try {
		ipint a1(0);
		a1 = a1 + 5;
		CPPUNIT_ASSERT(a1 == 5);
		ipint a2(int64_t(0x12345678FEFEAA55));
		a2 = a2 + 6;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA5B));
		a2 = a2 + "0x65";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAC0));
		a2 = a2 + std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAF5));
		a2 = a2 + 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFF004A));
		a2 = a2 + int64_t(0x5555AAAAAAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a0123a9a9559f));
		a2 = a2 + uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a01240403aff9));
		a2 = a2 + uint64_t(0xAAAAAAAA5555AAAA);
		ipint a2a{0x59595aa3, 0x1234abce, 0x1};
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMinus001(void)
{
	try {
		ipint a1(9);
		a1 = a1 - 5;
		CPPUNIT_ASSERT(a1 == 4);
		ipint a2(int64_t(0x12345678FEFEAA55));
		a2 = a2 - 3;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa52));
		a2 = a2 - "0x2";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA50));
		a2 = a2 - std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa1b));
		a2 = a2 - 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefe54c6));
		a2 = a2 - int64_t(0x00100000AAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x122456785453ff71));
		a2 = a2 - uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x12245677f9f9a517));
		a2 = a2 - uint64_t(0x0000AAAA5555AAAA);
		ipint a2a("0x1223abcda4a3fa6d");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMult001(void)
{
	try {
		ipint a1(5);
		a1 = a1 * 5;
		CPPUNIT_ASSERT(a1 == 25);
		ipint a2(int64_t(0x123456789ABCDEF));
		a2 = a2 *6;
		CPPUNIT_ASSERT(a2 == int64_t(0x6D3A06D3A06D39A));
		a2 = a2 * 8;
		CPPUNIT_ASSERT(a2 == int64_t(0x369D0369D0369CD0));
		a2 = a2 * 0x64;
		ipint a2a{0x55554140, 0x55555555, 0x15};
		// CPPUNIT_ASSERT(a2 == int64_t(0x5555555555554140));
		CPPUNIT_ASSERT(a2 == a2a);
		a2 = a2 * 256;
		ipint a3{0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a3);
		a2 = a2 * 65536;
		ipint a4{0x40000000, 0x55555541, 0x15555555};
		CPPUNIT_ASSERT(a2 == a4);
		a2 = a2 * 65536;
		ipint a5{0x00000000, 0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a5);
		a2 = a2 * 65536;
		ipint a6{0x00000000, 0x40000000, 0x55555541, 0x15555555};
		CPPUNIT_ASSERT(a2 == a6);
		a2 = a2 * 65536;
		ipint a7{0x00000000, 0x00000000, 0x55414000, 0x55555555, 0x1555};
		CPPUNIT_ASSERT(a2 == a7);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpDiv001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 / ipint(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA5555);
		a1 = a1 / ipint(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpMod001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 % ipint(65536);
		CPPUNIT_ASSERT(a1 == 0xAAAA);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 % ipint(1024);
		CPPUNIT_ASSERT(a1 == 0x2AA);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 % ipint(0x5555AAAA);
		CPPUNIT_ASSERT(a1 == 0);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpLShift001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 << 8;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA00"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 16;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA0000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 32;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA00000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 64;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AAAA0000000000000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 31;
		CPPUNIT_ASSERT(a1 == ipint("0x2AAAD5552AAAD55500000000"));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpRShift001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 >> 8;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555AA"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 16;
		CPPUNIT_ASSERT(a1 == ipint("0x5555AAAA5555"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 32;
		CPPUNIT_ASSERT(a1 == ipint{0x5555AAAA});
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 64;
		CPPUNIT_ASSERT(a1 == ipint(0));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 31;
		CPPUNIT_ASSERT(a1 == ipint{0xAAAB5554});
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpLT001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		ipint a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 < a2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpGT001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		ipint a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a2 > a1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpLTEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		ipint a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 <= a2);
		CPPUNIT_ASSERT(a1 <= a1);
		CPPUNIT_ASSERT(a2 <= a2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpGTEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		ipint a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a2 >= a1);
		CPPUNIT_ASSERT(a2 >= a2);
		CPPUNIT_ASSERT(a1 >= a1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToString001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		std::string s1 = a1.toString();
		// printf("s1 = %s\n", s1.c_str());
		CPPUNIT_ASSERT(s1 == "6149008514797120170");
		std::string s1a = a1.toString(10);
		// printf("s1a = %s\n", s1a.c_str());
		CPPUNIT_ASSERT(s1a == "6149008514797120170");
		std::string s1b = a1.toString(2);
		// printf("s1b = %s\n", s1b.c_str());
		CPPUNIT_ASSERT(s1b == "0b101010101010101101010101010101001010101010101011010101010101010");
		std::string s1c = a1.toString(16);
		// printf("s1c = %s\n", s1c.c_str());
		CPPUNIT_ASSERT(s1c == "0x5555AAAA5555AAAA");
		ipint a2(0xAAAA5555AAAA5555);
		std::string s2 = a2.toString();
		// printf("s2 = %s\n", s2.c_str());
		CPPUNIT_ASSERT(s2 == "12297735558912431445");
		std::string s2a = a2.toString(10);
		// printf("s2a = %s\n", s2a.c_str());
		CPPUNIT_ASSERT(s2a == "12297735558912431445");
		std::string s2b = a2.toString(2);
		// printf("s2b = %s\n", s2b.c_str());
		CPPUNIT_ASSERT(s2b == "0b1010101010101010010101010101010110101010101010100101010101010101");
		std::string s2c = a2.toString(16);
		// printf("s2c = %s\n", s2c.c_str());
		CPPUNIT_ASSERT(s2c == "0xAAAA5555AAAA5555");
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToInt001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toInt() == 1024);
		try {
			ipint a2(0xAAAA5555AAAA5555);
			(void) a2.toInt();
			// int i1 = a2.toInt();
			// printf("i1 = %d\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an integer."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToLong001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toLong() == 1024L);
		try {
			ipint a2(0xAAAA5555AAAA5555);
			(void) a2.toLong();
			// long i1 = a2.toLong();
			// printf("i1 = %ld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a long."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToInt64001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toInt64() == int64_t(1024L));
		try {
			ipint a2("0xAAAA5555AAAA5555AAAA5555");
			(void) a2.toInt64();
			// int64_t i1 = a2.toInt64();
			// printf("i1 = %lld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a int64_t."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToUInt001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toUnsignedInt() == 1024);
		try {
			ipint a2(0xAAAA5555AAAA5555);
			(void) a2.toUnsignedInt();
			// unsigned int i1 = a2.toUnsignedInt();
			// printf("i1 = %d\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an unsigned integer."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToULong001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toUnsignedLong() == 1024L);
		try {
			ipint a2(0xAAAA5555AAAA5555);
			(void) a2.toUnsignedLong();
			// unsigned long i1 = a2.toUnsignedLong();
			// printf("i1 = %ld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an unsigned long."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntToUInt64001(void)
{
	try {
		ipint a1(1024);
		CPPUNIT_ASSERT(a1.toUInt64() == uint64_t(1024L));
		try {
			ipint a2("0xAAAA5555AAAA5555AAAA5555");
			(void) a2.toUInt64();
			// uint64_t i1 = a2.toUInt64();
			// printf("i1 = %lld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a uint64_t."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpAnd001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 & ipint(0xAAAA5555AAAA5555);
		ipint a1a{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 & ipint(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == ipint(0x5555000055550000));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 & ipint(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpOrEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 |= ipint(0xAAAA5555AAAA5555);
		ipint a1a{0xFFFFFFFF, 0xFFFFFFFF};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 |= ipint(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == ipint(0x5555FFFF5555FFFF));
		a1 = 0x5555AAAA5555AAAA;
		a1 |= ipint(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
		a1 = 0x5555AAAA5555AAAA;
		a1 |= ipint{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpOr001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 | ipint(0xAAAA5555AAAA5555);
		ipint a1a{0xFFFFFFFF, 0xFFFFFFFF};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 | ipint(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == ipint(0x5555FFFF5555FFFF));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 | ipint(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 | ipint{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpXorEq001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 ^= ipint(0xAAAA5555AAAA5555);
		ipint a1a{0xFFFFFFFF, 0xFFFFFFFF};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 ^= ipint(0x5555555555555555);
		ipint a1b{0x0000FFFF, 0x0000FFFF};
		CPPUNIT_ASSERT(a1 == a1b);
		a1 = 0x5555AAAA5555AAAA;
		a1 ^= ipint(0x5555AAAA5555AAAA);
		ipint a1c{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == a1c);
		a1 = 0x5555AAAA5555AAAA;
		a1 ^= ipint{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IpIntOpXor001(void)
{
	try {
		ipint a1(0x5555AAAA5555AAAA);
		a1 = a1 ^ ipint(0xAAAA5555AAAA5555);
		ipint a1a{0xFFFFFFFF, 0xFFFFFFFF};
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 ^ ipint(0x5555555555555555);
		ipint a1b{0x0000FFFF, 0x0000FFFF};
		CPPUNIT_ASSERT(a1 == a1b);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 ^ ipint(0x5555AAAA5555AAAA);
		ipint a1c{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == a1c);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 ^ ipint{0x00000000, 0x00000000};
		CPPUNIT_ASSERT(a1 == ipint(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

//-----------------------------------------------------------------------------

void
TestIntBV::test_IntbvConstructors001(void)
{
	try {
		IntBV a1;
		CPPUNIT_ASSERT(a1 == 0);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors002(void)
{
	try {
		IntBV a1(0);
		CPPUNIT_ASSERT(a1 == 0);
		IntBV a2(1);
		CPPUNIT_ASSERT(a2 == 1);
		IntBV a3(1024);
		CPPUNIT_ASSERT(a3 == 1024);
		IntBV a4(ELEM_BITS_NUM + 1);
		CPPUNIT_ASSERT(a4 == IntBV(ELEM_BITS_NUM + 1));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors003(void)
{
	try {
		IntBV a1(long(0));
		CPPUNIT_ASSERT(a1 == 0);
		IntBV a2(long(1));
		CPPUNIT_ASSERT(a2 == 1);
		IntBV a3(long(1024));
		CPPUNIT_ASSERT(a3 == 1024);
		IntBV a4(0x7FFFFFFFL);
		CPPUNIT_ASSERT(a4 == 0x7FFFFFFFL);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors004(void)
{
	try {
		IntBV a1(uint32_t(0));
		CPPUNIT_ASSERT(a1 == 0);
		IntBV a2(uint32_t(1));
		CPPUNIT_ASSERT(a2 == 1);
		IntBV a3(uint32_t(1024));
		CPPUNIT_ASSERT(a3 == 1024);
		IntBV a4(uint32_t(0xFFFFFFFFUL));
		CPPUNIT_ASSERT(a4 == 0xFFFFFFFFUL);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors005(void)
{
	try {
		IntBV a1(int64_t(0));
		CPPUNIT_ASSERT(a1 == int64_t(0));
		IntBV a2(int64_t(1));
		CPPUNIT_ASSERT(a2 == int64_t(1));
		IntBV a3(int64_t(1024));
		CPPUNIT_ASSERT(a3 == int64_t(1024));
		IntBV a4(ELEM_BITS_NUM + 1);
		CPPUNIT_ASSERT(a4 == ELEM_BITS_NUM + 1);
		IntBV a5(ELEM_BITS_NUM2);
		CPPUNIT_ASSERT(a5 == ELEM_BITS_NUM2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors006(void)
{
	try {
		IntBV a1(uint64_t(0));
		CPPUNIT_ASSERT(a1 == uint64_t(0));
		IntBV a2(uint64_t(1));
		CPPUNIT_ASSERT(a2 == uint64_t(1));
		IntBV a3(uint64_t(1024));
		CPPUNIT_ASSERT(a3 == uint64_t(1024));
		IntBV a4(ELEM_BITS_NUM);
		CPPUNIT_ASSERT(a4 == ELEM_BITS_NUM);
		IntBV a5(ELEM_BITS_NUM2 - 1);
		CPPUNIT_ASSERT(a5 == ELEM_BITS_NUM2 - 1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors007(void)
{
	try {
		IntBV a1(uint64_t((ELEM_BITS_NUM2) - 1));
		CPPUNIT_ASSERT(a1 == uint64_t((ELEM_BITS_NUM2) - 1));
		IntBV a2(a1);
		CPPUNIT_ASSERT(a2 == uint64_t((ELEM_BITS_NUM2) - 1));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors008(void)
{
	try {
		IntBV a1(uint64_t(0xFFFFFFFF));
		uint64_t l = 0xFFFFFFFF;
		CPPUNIT_ASSERT(a1 == l);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors009(void)
{
	try {
		IntBV a1("123456789");
		CPPUNIT_ASSERT(a1 == uint64_t(123456789));
		IntBV a2("0x12345678FEFEAA55");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA55));
		IntBV a3("0b00001011101011011101111010101101");
		CPPUNIT_ASSERT(a3 == int64_t(0x0BADDEAD));
		IntBV a4("0x123456789ABCDEFFEDCBA9876543210A5ED");
		ipint a5{0x3210A5ED, 0xBA987654, 0xCDEFFEDC, 0x456789AB, 0x123};
		CPPUNIT_ASSERT(a4 == a5);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvConstructors010(void)
{
	try {
		IntBV a1(std::string("123456789"));
		CPPUNIT_ASSERT(a1 == uint64_t(123456789));
		IntBV a2(std::string("0x12345678FEFEAA55"));
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA55));
		IntBV a3(std::string("0b00001011101011011101111010101101"));
		CPPUNIT_ASSERT(a3 == int64_t(0x0BADDEAD));
		IntBV a4(std::string("0x123456789ABCDEFFEDCBA9876543210A5ED"));
		ipint a5{0x3210A5ED, 0xBA987654, 0xCDEFFEDC, 0x456789AB, 0x123};
		CPPUNIT_ASSERT(a4 == a5);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpPlusEq001(void)
{
	try {
		IntBV a1(0);
		a1 += 5;
		CPPUNIT_ASSERT(a1 == 5);
		IntBV a2(int64_t(0x12345678FEFEAA55));
		a2 += 6;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA5B));
		a2 += "0x65";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAC0));
		a2 += std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAF5));
		a2 += 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFF004A));
		a2 += int64_t(0x5555AAAAAAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a0123a9a9559f));
		a2 += uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a01240403aff9));
		a2 += uint64_t(0xAAAAAAAA5555AAAA);
		ipint i2a{0x59595aa3, 0x1234abce, 0x1};
		IntBV a2a(i2a);
		CPPUNIT_ASSERT(a2 == a2a);
		IntBV a3(0x12345678);
		IntBV a4(0x12345678);
		CPPUNIT_ASSERT(a3 == a4);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMultEq001(void)
{
	try {
		IntBV a1(5);
		a1 *= 5;
		CPPUNIT_ASSERT(a1 == 25);
		IntBV a2(int64_t(0x123456789ABCDEF));
		a2 *= 6;
		CPPUNIT_ASSERT(a2 == int64_t(0x6D3A06D3A06D39A));
		a2 *= 8;
		CPPUNIT_ASSERT(a2 == int64_t(0x369D0369D0369CD0));
		a2 *= 0x64;
		ipint i2a{0x55554140, 0x55555555, 0x15};
		IntBV a2a(i2a);
		// CPPUNIT_ASSERT(a2 == int64_t(0x5555555555554140));
		CPPUNIT_ASSERT(a2 == a2a);
		a2 *= 256;
		ipint i3{0x55414000, 0x55555555, 0x1555};
		IntBV a3(i3);
		CPPUNIT_ASSERT(a2 == a3);
		a2 *= 65536;
		ipint i4{0x40000000, 0x55555541, 0x15555555};
		IntBV a4(i4);
		CPPUNIT_ASSERT(a2 == a4);
		a2 *= 65536;
		ipint i5{0x00000000, 0x55414000, 0x55555555, 0x1555};
		IntBV a5(i5);
		CPPUNIT_ASSERT(a2 == a5);
		a2 *= 65536;
		ipint i6{0x00000000, 0x40000000, 0x55555541, 0x15555555};
		IntBV a6(i6);
		CPPUNIT_ASSERT(a2 == a6);
		a2 *= 65536;
		ipint i7{0x00000000, 0x00000000, 0x55414000, 0x55555555, 0x1555};
		IntBV a7(i7);
		CPPUNIT_ASSERT(a2 == a7);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpPlusPlus001(void)
{
	try {
		IntBV a1(5);
		CPPUNIT_ASSERT(++a1 == 6);
		++a1;
		CPPUNIT_ASSERT(a1 == 7);
		IntBV a2(0);
		a2 = a1++;
		CPPUNIT_ASSERT(a2 == 8);
		CPPUNIT_ASSERT(a1 == 7);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMinusMinus001(void)
{
	try {
		IntBV a1(8);
		CPPUNIT_ASSERT(--a1 == 7);
		--a1;
		CPPUNIT_ASSERT(a1 == 6);
		IntBV a2(0);
		a2 = a1--;
		CPPUNIT_ASSERT(a2 == 5);
		CPPUNIT_ASSERT(a1 == 6);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMinusEq001(void)
{
	try {
		IntBV a1(9);
		a1 -= 5;
		CPPUNIT_ASSERT(a1 == 4);
		IntBV a2(int64_t(0x12345678FEFEAA55));
		a2 -= 3;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa52));
		a2 -= "0x2";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA50));
		a2 -= std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa1b));
		a2 -= 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefe54c6));
		a2 -= int64_t(0x00100000AAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x122456785453ff71));
		a2 -= uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x12245677f9f9a517));
		a2 -= uint64_t(0x0000AAAA5555AAAA);
		IntBV a2a("0x1223abcda4a3fa6d");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpDivEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 /= IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA5555);
		a1 /= IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpModEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 %= IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0xAAAA);
		a1 = 0x5555AAAA5555AAAA;
		a1 %= IntBV(1024);
		CPPUNIT_ASSERT(a1 == 0x2AA);
		a1 = 0x5555AAAA5555AAAA;
		a1 %= IntBV(0x5555AAAA);
		CPPUNIT_ASSERT(a1 == 0);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpLShiftEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 <<= 8;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA00"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 16;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA0000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 32;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA00000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 64;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA0000000000000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 <<= 31;
		CPPUNIT_ASSERT(a1 == IntBV("0x2AAAD5552AAAD55500000000"));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpRShiftEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 >>= 8;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AA"));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 16;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555"));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 32;
		CPPUNIT_ASSERT(a1 == IntBV{0x5555AAAA});
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 64;
		CPPUNIT_ASSERT(a1 == IntBV(0));
		a1 = 0x5555AAAA5555AAAA;
		a1 >>= 31;
		CPPUNIT_ASSERT(a1 == IntBV{0xAAAB5554});
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpAndEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 &= ipint(0xAAAA5555AAAA5555);
		ipint i1a{0x00000000, 0x00000000};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 &= ipint(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555000055550000));
		a1 = 0x5555AAAA5555AAAA;
		a1 &= ipint(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpTilde001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = ~a1;
		IntBV a1a(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 == a1a);
		IntBV a2("0x5555AAAA5555AAAA5555AAAA5555AAAA");
		a2 = ~a2;
		IntBV a2a("0xAAAA5555AAAA5555AAAA5555AAAA5555");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpNotEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		IntBV a1a(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 != a1a);
		IntBV a2("0x5555AAAA5555AAAA5555AAAA5555AAAA");
		IntBV a2a("0xAAAA5555AAAA5555AAAA5555AAAA5555");
		CPPUNIT_ASSERT(a2 != a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpNeg001(void)
{
	try {
		IntBV a1(32768);
		a1 = -a1;
		IntBV a1a(0xFFFF8000);
		CPPUNIT_ASSERT(a1 == a1a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpPlus001(void)
{
	try {
		IntBV a1(0);
		a1 = a1 + 5;
		CPPUNIT_ASSERT(a1 == 5);
		IntBV a2(int64_t(0x12345678FEFEAA55));
		a2 = a2 + 6;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA5B));
		a2 = a2 + "0x65";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAC0));
		a2 = a2 + std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAAF5));
		a2 = a2 + 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFF004A));
		a2 = a2 + int64_t(0x5555AAAAAAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a0123a9a9559f));
		a2 = a2 + uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x678a01240403aff9));
		a2 = a2 + uint64_t(0xAAAAAAAA5555AAAA);
		ipint i2a{0x59595aa3, 0x1234abce, 0x1};
		IntBV a2a(i2a);
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMinus001(void)
{
	try {
		IntBV a1(9);
		a1 = a1 - 5;
		CPPUNIT_ASSERT(a1 == 4);
		IntBV a2(int64_t(0x12345678FEFEAA55));
		a2 = a2 - 3;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa52));
		a2 = a2 - "0x2";
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678FEFEAA50));
		a2 = a2 - std::string("0x35");
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefeaa1b));
		a2 = a2 - 0x5555L;
		CPPUNIT_ASSERT(a2 == int64_t(0x12345678fefe54c6));
		a2 = a2 - int64_t(0x00100000AAAA5555);
		CPPUNIT_ASSERT(a2 == int64_t(0x122456785453ff71));
		a2 = a2 - uint32_t(0x5A5A5A5A);
		CPPUNIT_ASSERT(a2 == int64_t(0x12245677f9f9a517));
		a2 = a2 - uint64_t(0x0000AAAA5555AAAA);
		IntBV a2a("0x1223abcda4a3fa6d");
		CPPUNIT_ASSERT(a2 == a2a);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMult001(void)
{
	try {
		IntBV a1(5);
		a1 = a1 * 5;
		CPPUNIT_ASSERT(a1 == 25);
		IntBV a2(int64_t(0x123456789ABCDEF));
		a2 = a2 *6;
		CPPUNIT_ASSERT(a2 == int64_t(0x6D3A06D3A06D39A));
		a2 = a2 * 8;
		CPPUNIT_ASSERT(a2 == int64_t(0x369D0369D0369CD0));
		a2 = a2 * 0x64;
		ipint i2a{0x55554140, 0x55555555, 0x15};
		IntBV a2a(i2a);
		// CPPUNIT_ASSERT(a2 == int64_t(0x5555555555554140));
		CPPUNIT_ASSERT(a2 == a2a);
		a2 = a2 * 256;
		ipint i3{0x55414000, 0x55555555, 0x1555};
		IntBV a3(i3);
		CPPUNIT_ASSERT(a2 == a3);
		a2 = a2 * 65536;
		ipint i4{0x40000000, 0x55555541, 0x15555555};
		IntBV a4(i4);
		CPPUNIT_ASSERT(a2 == a4);
		a2 = a2 * 65536;
		ipint i5{0x00000000, 0x55414000, 0x55555555, 0x1555};
		IntBV a5(i5);
		CPPUNIT_ASSERT(a2 == a5);
		a2 = a2 * 65536;
		ipint i6{0x00000000, 0x40000000, 0x55555541, 0x15555555};
		IntBV a6(i6);
		CPPUNIT_ASSERT(a2 == a6);
		a2 = a2 * 65536;
		ipint i7{0x00000000, 0x00000000, 0x55414000, 0x55555555, 0x1555};
		IntBV a7(i7);
		CPPUNIT_ASSERT(a2 == a7);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpDiv001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 / IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA5555);
		a1 = a1 / IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0x5555AAAA);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpMod001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 % IntBV(65536);
		CPPUNIT_ASSERT(a1 == 0xAAAA);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 % IntBV(1024);
		CPPUNIT_ASSERT(a1 == 0x2AA);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 % IntBV(0x5555AAAA);
		CPPUNIT_ASSERT(a1 == 0);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpLShift001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 << 8;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA00"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 16;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA0000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 32;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA00000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 64;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AAAA0000000000000000"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 << 31;
		CPPUNIT_ASSERT(a1 == IntBV("0x2AAAD5552AAAD55500000000"));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpRShift001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 >> 8;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555AA"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 16;
		CPPUNIT_ASSERT(a1 == IntBV("0x5555AAAA5555"));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 32;
		CPPUNIT_ASSERT(a1 == IntBV{0x5555AAAA});
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 64;
		CPPUNIT_ASSERT(a1 == IntBV(0));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 >> 31;
		CPPUNIT_ASSERT(a1 == IntBV{0xAAAB5554});
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpLT001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		IntBV a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 < a2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpGT001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		IntBV a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a2 > a1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpLTEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		IntBV a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a1 <= a2);
		CPPUNIT_ASSERT(a1 <= a1);
		CPPUNIT_ASSERT(a2 <= a2);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpGTEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		IntBV a2(0xAAAA5555AAAA5555);
		CPPUNIT_ASSERT(a2 >= a1);
		CPPUNIT_ASSERT(a2 >= a2);
		CPPUNIT_ASSERT(a1 >= a1);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToString001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		std::string s1 = a1.toString();
		// printf("s1 = %s\n", s1.c_str());
		CPPUNIT_ASSERT(s1 == "6149008514797120170");
//		std::string s1a = a1.toString(10);
//		printf("s1a = %s\n", s1a.c_str());
//		CPPUNIT_ASSERT(s1a == "6149008514797120170");
//		std::string s1b = a1.toString(2);
//		printf("s1b = %s\n", s1b.c_str());
//		CPPUNIT_ASSERT(s1b == "0b101010101010101101010101010101001010101010101011010101010101010");
//		std::string s1c = a1.toString(16);
//		printf("s1c = %s\n", s1c.c_str());
//		CPPUNIT_ASSERT(s1c == "0x5555AAAA5555AAAA");
		IntBV a2(0xAAAA5555AAAA5555);
		std::string s2 = a2.toString();
		// printf("s2 = %s\n", s2.c_str());
		CPPUNIT_ASSERT(s2 == "12297735558912431445");
//		std::string s2a = a2.toString(10);
//		printf("s2a = %s\n", s2a.c_str());
//		CPPUNIT_ASSERT(s2a == "12297735558912431445");
//		std::string s2b = a2.toString(2);
//		printf("s2b = %s\n", s2b.c_str());
//		CPPUNIT_ASSERT(s2b == "0b1010101010101010010101010101010110101010101010100101010101010101");
//		std::string s2c = a2.toString(16);
//		printf("s2c = %s\n", s2c.c_str());
//		CPPUNIT_ASSERT(s2c == "0xAAAA5555AAAA5555");
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToInt001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toInt() == 1024);
		try {
			IntBV a2(0xAAAA5555AAAA5555);
			(void) a2.toInt();
			// int i1 = a2.toInt();
			// printf("i1 = %d\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an integer."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToLong001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toLong() == 1024L);
		try {
			IntBV a2(0xAAAA5555AAAA5555);
			(void) a2.toLong();
			// long i1 = a2.toLong();
			// printf("i1 = %ld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a long."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToInt64001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toLongLong() == int64_t(1024L));
		try {
			IntBV a2("0xAAAA5555AAAA5555AAAA5555");
			(void) a2.toLongLong();
			// int64_t i1 = a2.toLongLong();
			// printf("i1 = %lld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a int64_t."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToUInt001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toUnsignedInt() == 1024);
		try {
			IntBV a2(0xAAAA5555AAAA5555);
			(void) a2.toUnsignedInt();
			// unsigned int i1 = a2.toUnsignedInt();
			// printf("i1 = %d\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an unsigned integer."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToULong001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toUnsignedLong() == 1024L);
		try {
			IntBV a2(0xAAAA5555AAAA5555);
			(void) a2.toUnsignedLong();
			// unsigned long i1 = a2.toUnsignedLong();
			// printf("i1 = %ld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than an unsigned long."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvToUInt64001(void)
{
	try {
		IntBV a1(1024);
		CPPUNIT_ASSERT(a1.toUnsignedLongLong() == uint64_t(1024L));
		try {
			IntBV a2("0xAAAA5555AAAA5555AAAA5555");
			(void) a2.toUnsignedLongLong();
			// uint64_t i1 = a2.toUnsignedLongLong();
			// printf("i1 = %lld\n", i1);
			// fflush(stdout);
			CPPUNIT_ASSERT(false);
		} catch(const IpIntException& e) {
			// printf("e.what() = %s\n", e.what());
			// fflush(stdout);
			CPPUNIT_ASSERT(std::string(e.what()) == std::string("ipint is larger than a uint64_t."));
		}
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpAnd001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 & ipint(0xAAAA5555AAAA5555);
		ipint i1a{0x00000000, 0x00000000};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 & IntBV(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555000055550000));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 & IntBV(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpOrEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 |= IntBV(0xAAAA5555AAAA5555);
		ipint i1a{0xFFFFFFFF, 0xFFFFFFFF};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 |= IntBV(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555FFFF5555FFFF));
		a1 = 0x5555AAAA5555AAAA;
		a1 |= IntBV(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
		a1 = 0x5555AAAA5555AAAA;
		ipint i1{0x00000000, 0x00000000};
		a1 |= IntBV(i1);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpOr001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 | IntBV(0xAAAA5555AAAA5555);
		ipint i1a{0xFFFFFFFF, 0xFFFFFFFF};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 | IntBV(0x5555555555555555);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555FFFF5555FFFF));
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 | IntBV(0x5555AAAA5555AAAA);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
		a1 = 0x5555AAAA5555AAAA;
		ipint i1{0x00000000, 0x00000000};
		a1 = a1 | IntBV(i1);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpXorEq001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 ^= IntBV(0xAAAA5555AAAA5555);
		ipint i1a{0xFFFFFFFF, 0xFFFFFFFF};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 ^= IntBV(0x5555555555555555);
		ipint i1b{0x0000FFFF, 0x0000FFFF};
		IntBV a1b(i1b);
		CPPUNIT_ASSERT(a1 == a1b);
		a1 = 0x5555AAAA5555AAAA;
		a1 ^= IntBV(0x5555AAAA5555AAAA);
		ipint i1c{0x00000000, 0x00000000};
		IntBV a1c(i1c);
		CPPUNIT_ASSERT(a1 == a1c);
		a1 = 0x5555AAAA5555AAAA;
		ipint i1{0x00000000, 0x00000000};
		a1 ^= IntBV(i1);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvOpXor001(void)
{
	try {
		IntBV a1(0x5555AAAA5555AAAA);
		a1 = a1 ^ IntBV(0xAAAA5555AAAA5555);
		ipint i1a{0xFFFFFFFF, 0xFFFFFFFF};
		IntBV a1a(i1a);
		CPPUNIT_ASSERT(a1 == a1a);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 ^ IntBV(0x5555555555555555);
		ipint i1b{0x0000FFFF, 0x0000FFFF};
		IntBV a1b(i1b);
		CPPUNIT_ASSERT(a1 == a1b);
		a1 = 0x5555AAAA5555AAAA;
		a1 = a1 ^ IntBV(0x5555AAAA5555AAAA);
		ipint i1c{0x00000000, 0x00000000};
		IntBV a1c(i1c);
		CPPUNIT_ASSERT(a1 == a1c);
		a1 = 0x5555AAAA5555AAAA;
		ipint i1{0x00000000, 0x00000000};
		a1 = a1 ^ IntBV(i1);
		CPPUNIT_ASSERT(a1 == IntBV(0x5555AAAA5555AAAA));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvGetSlice001(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210);
		IntBV a1a = a1.get_slice(8);
//		printf("test_IntbvGetSlice001: %s\n", a1a.to_ipint().toString(2).c_str());
//		printf("test_IntbvGetSlice001: %s\n", hex(a1a).c_str());
		CPPUNIT_ASSERT(a1a.toInt() == 16);
		CPPUNIT_ASSERT(a1a.toInt() == 0x10);
//		fflush(stdout);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvGetSlice002(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210);
		IntBV a1a = a1.get_slice(8,4);
//		printf("test_IntbvGetSlice002: %s\n", hex(a1a).c_str());
		CPPUNIT_ASSERT(a1a.toInt() == 0x1);
//		printf("GetSlice002: %s\n", hex(a1.get_slice(42,28), 4).c_str());
		IntBV a1b(a1.get_slice(42,28));
//		printf("GetSlice002: %s\n", hex(a1b, 4).c_str());
		CPPUNIT_ASSERT(a1b.toInt() == 0x2987);
//		fflush(stdout);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvGetSlice003(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210);
		IntBV a1a = a1.get_slice_e(20);
//		printf("test_IntbvGetSlice003: %s\n", hex(a1a).c_str());
		CPPUNIT_ASSERT(a1a == 0xFEDCBA98765);
//		fflush(stdout);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvBin001(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210, 0, 0, 16);
		std::string s = bin(a1);
		CPPUNIT_ASSERT(s == "0b0011001000010000");
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvHex001(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210, 0, 0, 16);
		std::string s = hex(a1);
		CPPUNIT_ASSERT(s == "0x3210");
		IntBV a2(0xFEDCBA9876543210, 0, 0, 34);
		std::string s2 = hex(a2);
		CPPUNIT_ASSERT(s2 == "0x076543210");
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvSetSlice001(void)
{
	try {
		IntBV a1("0xFEDCBA9876543210");
//		printf("test_IntbvSetSlice001: %s\n", hex(a1).c_str());
		a1.set_slice(8, IntBV(0x3F));
//		printf("test_IntbvSetSlice001: %s\n", a1.to_ipint().toString(2).c_str());
//		printf("test_IntbvSetSlice001: %s\n", hex(a1).c_str());
//		fflush(stdout);
		CPPUNIT_ASSERT(a1 == 0xFEDCBA987654323F);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvSetSlice002(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210);
		a1.set_slice(64, 8, IntBV(0x3F));
//		printf("test_IntbvSetSlice002: %s\n", a1.to_ipint().toString(2).c_str());
//		printf("test_IntbvSetSlice002: %s\n", hex(a1).c_str());
//		fflush(stdout);
		CPPUNIT_ASSERT(a1 == 0x3F10);
		IntBV a2(0xFEDCBA9876543210);
		a2.set_slice(63, 8, IntBV(0x3F));
//		printf("test_IntbvSetSlice002: %s\n", a2.to_ipint().toString(2).c_str());
//		printf("test_IntbvSetSlice002: %s\n", hex(a2).c_str());
//		fflush(stdout);
		CPPUNIT_ASSERT(a2 == 0x8000000000003F10);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvGetSliceE001(void)
{
	try {
		IntBV a1(0xFEDCBA9876543210);
		IntBV a1a = a1.get_slice_e(8);
//		printf("test_IntbvGetSliceE001: %s\n", a1a.to_ipint().toString(2).c_str());
//		printf("test_IntbvGetSliceE001: %s\n", hex(a1a).c_str());
		CPPUNIT_ASSERT(a1a == IntBV(0xFEDCBA98765432));
//		fflush(stdout);
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void
TestIntBV::test_IntbvSetSliceE001(void)
{
	try {
		IntBV a1("0xFEDCBA9876543210");
//		printf("test_IntbvSetSliceE001: %s\n", hex(a1).c_str());
		a1.set_slice_e(8, IntBV(0x3F));
//		printf("test_IntbvSetSliceE001: %s\n", a1.to_ipint().toString(2).c_str());
//		printf("test_IntbvSetSliceE001: %s\n", hex(a1).c_str());
//		fflush(stdout);
		CPPUNIT_ASSERT(a1 == IntBV(0x00000000003F10));
	} catch(const IpIntException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	} catch(const IntbvException& e) {
		printf("ERROR: %s\n", e.what());
		CPPUNIT_ASSERT(0 != 0);
	}
}

void TestIntBV::setUp(void)
{
}

void TestIntBV::tearDown(void)
{
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestIntBV );

int main(int argc, char* argv[])
{
try {
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppTestIpIntResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
} catch(const std::exception& e) {
    printf("%s\n", e.what());
}
}




