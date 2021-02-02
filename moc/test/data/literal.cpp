#include <cstddef>

unsigned operator ""_x(char const*);
char const* operator ""_y(char const*, size_t);
char operator ""_z(char);

inline void foo() {
    (void)/*0*/ 0b0101;
    (void)/*1*/ 0B0101'01;

    (void)/*2*/ 0b0u;
    (void)/*3*/ 0b0UL;
    (void)/*4*/ 0b0Ull;
    //(void)/*5*/0b0Uz;

    (void)/*6*/ 07;
    (void)/*7*/ 0'7;

    (void)/*8*/ 9;
    (void)/*9*/ 9'0;

    (void)/*10*/ 0X0;
    (void)/*11*/ 0X0'Ff;

    (void)/*12*/ 'c';
    (void)/*13*/ 'cc';
    (void)/*14*/ '\?';
    (void)/*15*/ '\071';
    (void)/*16*/ '\xf1';
    (void)/*17*/ '\l';
    (void)/*18*/ 0.0;
    (void)/*19*/ 0'1.;
    (void)/*20*/ .0'1;
    (void)/*21*/ 0.e0;
    (void)/*22*/ 0.E+1;
    (void)/*23*/ 0.E+1F;
    (void)/*24*/ 0E+1F;
    (void)/*25*/ 0x.0'1p1f;

    (void)/*26*/ u8"foo";
    (void)/*27*/ "\"";
    (void)/*28*/ R"(")";
    (void)/*29*/ R"y(y)y";
    (void)/*30*/ R"y(y)y)y";

    (void)/*31*/ true;
    (void)/*32*/ nullptr;

    (void)/*33*/ 3_x;
    (void)/*34*/ 03_x;
    (void)/*35*/ 0x3_x;
    (void)/*36*/ 0b1_x;

    (void)/*38*/ 0.1e+2_x;
    (void)/*39*/ 1'1e+2_x;
    (void)/*40*/ 0xff.0p+2_x;
    (void)/*41*/ 0xffp+2_x;

    (void)/*42*/ "foo"_y;

    (void)/*43*/ 'f'_z;
}
