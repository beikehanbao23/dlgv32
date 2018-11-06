// USGSDEMLayer.h - interface for USGSDEMLayer class
//
// Developed by: Mike Childs
//      Started: 4/18/98

#ifndef _USGSDEMLAYER_H_
#define _USGSDEMLAYER_H_

// DEM library includes
#include "DEMGrid.hxx"

#include "RasterPluginLayer.h"

class USGSDEMLayer : public RasterPluginLayer
{
public:
	// Constructors/Destructors
	USGSDEMLayer( int layerID, const char* strFilename, HINSTANCE hInst );
	virtual ~USGSDEMLayer();

	// Overrides
  const char* getDescription() const;
  bool isVertical() const;
	bool load();
	void getBoundingRect( double& left, double& bottom, double& right, double& top ) const;
  long getImageHeight() const;
  long getImageWidth() const;
  void getProjection( PROJSYS& projSys, DATUM& datum, UNIT& unit, int& zone, double* pParams ) const;
  UNIT getVerticalUnits() const;

protected:
    // Overrides
    void getMinMaxSampleValue( float& min, float& max ) const;
    bool getElevation( long row, long col, float& elev ) const;

private:
    // Member data
    DEMGrid   d_grid;
    float     d_spatialResZ;
};

inline void
USGSDEMLayer::getMinMaxSampleValue( float& min, float& max ) const
{
  // Took out the multiplicatoin by d_spatialResZ since thats bad
  // BGM 3 Aug 1998
  min = d_grid.getHeader().getMinimumElev();
  max = d_grid.getHeader().getMaximumElev();
}

inline long
USGSDEMLayer::getImageHeight() const
{
    return d_grid.getHeight();
}

inline long
USGSDEMLayer::getImageWidth() const
{
    return d_grid.getWidth();
}

inline bool
USGSDEMLayer::isVertical() const
{
    return true;
}

#endif