#ifndef FRATION_H
#define FRATION_H
#include <iostream>

using namespace std;


class Fraction
{
    public:
        int numerator;
        int denominator;
        Fraction (int a, int b):numerator(a), denominator(b){};
        Fraction (int a):numerator(a), denominator(1){};
        void print()const;
        int findNOD();

        const Fraction operator*(const Fraction &secondFract);
        const Fraction operator/(const Fraction &secondFract);
        const Fraction operator+(const Fraction &secondFract);
        const Fraction operator-(const Fraction &secondFract);

        ///перегрузить *,/,+,-,++,--
        ///рассчитать число Пи
};

#endif // FRATION_H
