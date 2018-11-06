
#include <math.h>

#ifndef INCLUDED_PS_VECTOR_H
#include "ps_Vector.h"
#endif

ps_Vector::ps_Vector()
         : _i(0.0), _j(0.0), _k(0.0)
{
}

ps_Vector::ps_Vector(double i, double j, double k)
         : _i(i), _j(j), _k(k)
{
}

ps_Vector::ps_Vector(ps_Vector const& rhs)
{
   operator=(rhs);
}

ps_Vector const&
ps_Vector::operator=(ps_Vector const& rhs)
{
   if (this == &rhs)
      return *this;

   _i = rhs._i;
   _j = rhs._j;
   _k = rhs._k;

   return *this;
}

ps_Vector const
ps_Vector::operator+(ps_Vector const& rhs) const
{
   return ps_Vector(_i + rhs._i,
                    _j + rhs._j,
                    _k + rhs._k);   
}

ps_Vector const
ps_Vector::operator-(ps_Vector const& rhs) const
{
   return ps_Vector(_i - rhs._i,
                    _j - rhs._j,
                    _k - rhs._k);   
}

ps_Vector const
ps_Vector::operator*(double s) const
{
   return ps_Vector(s * _i,
                    s * _j,
                    s * _k);
}

ps_Vector const
ps_Vector::cross(ps_Vector const& rhs) const
{
   return ps_Vector((_j * rhs._k) - (_k * rhs._j),
                    (_k * rhs._i) - (_i * rhs._k),
                    (_i * rhs._j) - (_j * rhs._i));
}

double
ps_Vector::dot(ps_Vector const& rhs) const
{
   return (_i * rhs._i) + (_j * rhs._j) + (_k * rhs._k);
}

void
ps_Vector::normalize()
{
   double mag;

   //mag = fastSquareRoot( _i * _i + _j * _j + _k * _k );
   mag = sqrt( _i * _i + _j * _j + _k * _k );

   // changed to take out slow fabs() call --paul     let me know if I should put it back in
   if (mag < 0)
   {
      mag = -mag;
   }

   if (mag > 0.00000001)
      {
         _i = _i / mag;
         _j = _j / mag;
         _k = _k / mag;
      }
}

void
ps_Vector::getComponents(double& i, double& j, double& k) const
{
   i = _i;
   j = _j;
   k = _k;
}

double
ps_Vector::fastSquareRoot( double n )
{
    double x = n / 4.0; // Initial approximation
    for ( int i = 0; i < 9; i++ )
    {
        x = x / 2 + n / ( 2 * x );
    }
    return x;
}