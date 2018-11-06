// RasterPlugin.h - interface for RasterPlugin DLL exports
//
// Developed by: Mike Childs
//      Started: 4/11/98

#ifndef _RASTERPLUGINTEST_H_
#define _RASTERPLUGINTEST_H_

#include "ProjectionTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

// Exported function definitions for Plugin Type functions
__declspec(dllexport) const char* getName();
__declspec(dllexport) const char* getMasks();

// Exported function definitions
__declspec(dllexport) void destroyOverlay( int layerID );
__declspec(dllexport) void getBadElevationColor( int layerID, 
                                                 unsigned char* pR,
                                                 unsigned char* pG,
                                                 unsigned char* pB );
__declspec(dllexport) void getBoundingRect( int layerID, double* pLeft,
                                            double* pBottom,
                                            double* pRight, double* pTop );
__declspec(dllexport) const char* getDescription( int layerID );
__declspec(dllexport) bool getElevation( int layerID, long row, long col,
                                         float* pElev );
__declspec(dllexport) long getImageHeight( int layerID );
__declspec(dllexport) long getImageWidth( int layerID );
__declspec(dllexport) void getMinMaxSampleValue( int layerID, float* pMin, 
                                                 float* pMax );
__declspec(dllexport) void getProjection( int layerID, PROJSYS* pProjSys,
                                          DATUM* pDatum, UNIT* pUnit,
                                          int* pZone, double* pParams );
__declspec(dllexport) bool getRowColColor( int layerID, long row, long col,
                                           unsigned char* pR, 
                                           unsigned char* pG,
                                           unsigned char* pB );
__declspec(dllexport) UNIT getVerticalUnits( int layerID );
__declspec(dllexport) bool isVertical( int layerID );
__declspec(dllexport) bool loadOverlay( int layerID, const char* strFilename );
__declspec(dllexport) bool showBadElevations( int layerID );

// Only uncomment these lines if you have provided meaningful implementations.  The
// defaults will handle most cases
//__declspec(dllexport) float getVerticalPixelScale( int layerID );
//__declspec(dllexport) bool showOptionsDialog( int layerID );
__declspec(dllexport) void showPropertiesDialog( int layerID );

#ifdef __cplusplus
}
#endif

#endif