// ps_WaterShader.h - ps_WaterShader class interface
//
// Developed by: Mike Childs
//      Started: 2/4/98

#ifndef _PS_WATERSHADER_H_
#define _PS_WATERSHADER_H_

#include "ps_PixelShader.h"

class ps_WaterShader : public ps_PixelShader
{
public:
    // Constructor
    ps_WaterShader( float waterLevel = 0.0 );

    // Accessors
    float getWaterLevel() const;

    // Modifiers
    void setWaterLevel( float waterLevel );

    // Overrides
    void shade( ps_PixelShaderInfo& info );

protected:
    float d_waterLevel;
};

inline float
ps_WaterShader::getWaterLevel() const
{
    return d_waterLevel;
}

inline void
ps_WaterShader::setWaterLevel( float waterLevel )
{
    d_waterLevel = waterLevel;
}

#endif