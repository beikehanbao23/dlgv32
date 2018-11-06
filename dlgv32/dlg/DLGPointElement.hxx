#ifndef INCLUDED_DLGPOINTELEMENT_HXX
#define INCLUDED_DLGPOINTELEMENT_HXX

#include "DLGElement.hxx"
#include "DLGPoint.hxx"

class DLGPointElement;
ostream& operator<<(ostream& s, DLGPointElement& pe);
istream& operator>>(istream& s, DLGPointElement& pe);


class DLGPointElement : public DLGElement
{
   public:

      DLGPointElement(void);
      DLGPointElement(const DLGPointElement& pe);
      ~DLGPointElement(void);
      DLGPointElement& operator=(const DLGPointElement& pe);
      bool operator==(DLGPointElement& pe);

      friend ostream& operator<<(ostream& s, DLGPointElement& pe);
      friend istream& operator>>(istream& s, DLGPointElement& pe);

      DLGPoint getPoint(void) const;
      void getPoint(double& x, double& y) const;
         // Coordinates of node point or representative point for and area.

      long getNumberOfLineSegs(void) const;
         // Number of elements in line segment list. 

      vector<long>& getLineSegments(void);
         // The line segment IDs of the line segments that intersect at a node
         // or bound an area.

   private:

      DLGPoint  _point;
      vector<long> _lineSegments;
      long _numIslands;
};

// Inline method definitions

inline
DLGPoint
DLGPointElement::getPoint(void) const
{
   return _point;
}

inline
void
DLGPointElement::getPoint(double& x, double& y) const
{
   _point.getXY(x,y);
}

inline
long
DLGPointElement::getNumberOfLineSegs(void) const
{
   return _lineSegments.size();
}

inline
vector<long>&
DLGPointElement::getLineSegments(void)
{
   return _lineSegments;
}


#endif  // INCLUDED_DLGPOINTELEMENT_HXX
