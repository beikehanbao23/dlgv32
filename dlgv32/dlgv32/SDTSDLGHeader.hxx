#ifndef _SDTSDLGHEADER_HXX_
#define _SDTSDLGHEADER_HXX_

#ifdef _WIN32 
#else
#endif

#include <afx.h>

struct SDTSDLGControlPoint
{
   long id;
   CString label;
   double latitude;
   double longitude;
   double x;
   double y;
};

class SDTSDLGHeader
{
   public:
      SDTSDLGHeader();
      SDTSDLGHeader(CString& filename);
      SDTSDLGHeader(const SDTSDLGHeader& header);
      virtual ~SDTSDLGHeader();

      virtual SDTSDLGHeader& operator=(const SDTSDLGHeader& header);
      virtual bool operator==(const SDTSDLGHeader& header);
      
   private:
      SDTSDLGControlPoint  _controlPoints[4];
            // These are in the AHDR file.
            // Some of these are in the SPDM file.
            // Need to be stored SW,NW,NE,SE


      double               _resolution;
            // This is in the IREF file.

      long                 _horizDatum;
            // This is in the XREF file.

      long                 _grndRefSys;
            // This is in the XREF file.

      long                 _grndRefSysZone;
            // This is in the XREF file.







#endif // _SDTSDLGHEADER_HXX_