#ifndef INCLUDED_DLGLINE_HXX
#define INCLUDED_DLGLINE_HXX

#ifndef INCLUDED_DLGELEMENT_HXX
#include "DLGElement.hxx"
#endif

#ifndef INCLUDED_DLGPOINT_HXX
#include "DLGPoint.hxx"
#endif

class DLGLine;
ostream& operator<<(ostream& s, DLGLine& le);
istream& operator>>(istream& s, DLGLine& le);

class DLGLine : public DLGElement
{
   public:

      DLGLine(void);
      DLGLine(const DLGLine& le);
      ~DLGLine(void);
      DLGLine& operator=(const DLGLine& le);
      bool operator==(const DLGLine& le);

      friend ostream& operator<<(ostream& s, DLGLine& le);
      friend istream& operator>>(istream& s, DLGLine& le);

      // Accessors
      long getStartNodeID(void) const;
      long getEndNodeID(void) const;
      long getLeftAreaID(void) const;
      long getRightAreaID(void) const;

      // Modifiers 
      vector<DLGPoint>& getPoints(void);

   protected:

      long _startNodeID;
      long _endNodeID;
      long _areaLeftID;
      long _areaRightID;
      vector<DLGPoint> _points;
};

#endif  // INCLUDED_DLGLINE_HXX
