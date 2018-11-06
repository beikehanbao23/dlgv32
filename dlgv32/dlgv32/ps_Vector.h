#ifndef INCLUDED_PS_VECTOR_H
#define INCLUDED_PS_VECTOR_H

class ps_Vector
{
   public:
      ps_Vector();
      ps_Vector(double i, double j, double k);
      ps_Vector(ps_Vector const& rhs);
      ps_Vector const& operator=(ps_Vector const& rhs);

      ps_Vector const operator+(ps_Vector const& rhs) const;

      ps_Vector const operator-(ps_Vector const& rhs) const;

      ps_Vector const operator*(double s) const;
         // Scalar product

      ps_Vector const cross(ps_Vector const& rhs) const;
         // Cross product

      double dot(ps_Vector const& rhs) const;

      void normalize();

      void getComponents(double& i, double& j, double& k) const;

   private:
      static double fastSquareRoot( double n );
      double _i,_j,_k;
};

#endif  // INCLUDED_PS_VECTOR_H






