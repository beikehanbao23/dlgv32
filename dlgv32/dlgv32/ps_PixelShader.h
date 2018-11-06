
#ifndef INCLUDED_PIXELSHADER_H
#define INCLUDED_PIXELSHADER_H

#include "ps_Vector.h"

class ps_Pixel
{
   public:

      ps_Pixel();
      ps_Pixel(unsigned char gray);
      ps_Pixel(unsigned char r,
               unsigned char g,
               unsigned char b);

      unsigned char getGray() const;

      unsigned char red;
      unsigned char green;
      unsigned char blue;
};


class ps_PixelShaderInfo
{
   public:
      ps_Pixel pixel;
      float pixelZ;
      float minZ;
      float maxZ;
      bool  bUseColor;
      unsigned char intensity;
};


class ps_PixelShader
{
   public:

      // Construction
      ps_PixelShader();

      // Modifiers
      void setAmbientLightLevel( float ambient );

      void enableLighting( bool bEnable = true );

      void enableWater( bool bEnable = true );

      void setLightDirection( const ps_Vector& lightDir );
         // lightDir is a vector pointing in
         // the direction the light is shining.
         // The light is assumed to be infinitely
         // far away.

      void setLightDirection( float altitude, float azimuth );

      void setWaterAlpha( unsigned char waterAlpha );

      void setWaterColor( const ps_Pixel& waterColor );

      void setWaterLevel( float waterLevel );

      // Accessors
      float getAmbientLightLevel() const;

      bool isLightingEnabled() const;

      bool isWaterEnabled() const;
      
      const ps_Vector& getLightDirection() const;

      void  getLightDirection( float& altitude, float& azimuth );

      unsigned char getWaterAlpha() const;

      const ps_Pixel& getWaterColor() const;

      float getWaterLevel() const;

      // Shading function - must be overwritten in subclasses
      virtual void shade(ps_PixelShaderInfo& info) const = 0;

      float getIntensity( const ps_Vector& normal ) const;

   protected:
      // Helper functions
      void  addWater( ps_PixelShaderInfo& info ) const;

      // Data members
      float         _ambientLightLevel;
      bool          _bLightingEnabled;
      bool          _bWaterEnabled;
      ps_Vector     _lightDirection;
      unsigned char _waterAlpha;
      ps_Pixel      _waterColor;
      float         _waterLevel;      
};

inline void 
ps_PixelShader::setAmbientLightLevel( float ambient )
{
   _ambientLightLevel = ambient;

   // Make sure the value is between 0.0 and 1.0
   if ( _ambientLightLevel < 0.0 )
   {
       _ambientLightLevel = 0.0;
   }
   else if ( _ambientLightLevel > 1.0 )
   {
       _ambientLightLevel = 1.0;
   }
}

inline void 
ps_PixelShader::enableLighting( bool bEnable )
{
   _bLightingEnabled = bEnable;
}

inline void 
ps_PixelShader::enableWater( bool bEnable )
{
   _bWaterEnabled = bEnable;
}

inline void 
ps_PixelShader::setLightDirection( const ps_Vector& lightDir )
{
   _lightDirection = lightDir * -1.0;
   _lightDirection.normalize();
}

inline void 
ps_PixelShader::setWaterAlpha( unsigned char waterAlpha )
{
   _waterAlpha = waterAlpha;
}

inline void 
ps_PixelShader::setWaterColor( const ps_Pixel& waterColor )
{
   _waterColor = waterColor;
}

inline void 
ps_PixelShader::setWaterLevel( float waterLevel )
{
   _waterLevel = waterLevel;
}

inline float 
ps_PixelShader::getAmbientLightLevel() const
{
   return _ambientLightLevel;
}

inline bool 
ps_PixelShader::isLightingEnabled() const
{
   return _bLightingEnabled;
}

inline bool 
ps_PixelShader::isWaterEnabled() const
{
   return _bWaterEnabled;
}
      
inline const ps_Vector& 
ps_PixelShader::getLightDirection() const
{
   return _lightDirection;
}

inline unsigned char
ps_PixelShader::getWaterAlpha() const
{
   return _waterAlpha;
}

inline const ps_Pixel& 
ps_PixelShader::getWaterColor() const
{
   return _waterColor;
}

inline float 
ps_PixelShader::getWaterLevel() const
{
   return _waterLevel;
}

inline float 
ps_PixelShader::getIntensity( const ps_Vector& normal ) const
{
    float inten = normal.dot( _lightDirection ) + _ambientLightLevel;
    if ( inten < 0.0 )
    {
        inten = 0.0;
    }
    else if ( inten > 1.0 )
    {
        inten = 1.0;
    }

   return ( inten );
}


class ps_DaylightShader : public ps_PixelShader
{
   public:
      // Constructor
      ps_DaylightShader();

      // Overidden shade function
      void shade(ps_PixelShaderInfo& info) const;

      // Modifiers
      void setColor( const ps_Pixel&  color);

      // Accessors
      const ps_Pixel& getColor() const;

   protected:

      ps_Pixel _color;
};

inline void
ps_DaylightShader::setColor( const ps_Pixel& color )
{
   _color = color;
}

inline const ps_Pixel& 
ps_DaylightShader::getColor() const
{
   return _color;
}

class ps_GradientShader : public ps_PixelShader
{
   public:

      ps_GradientShader();

      void shade(ps_PixelShaderInfo& info) const;

      void setLowColor(ps_Pixel const& lowColor);
      void setHighColor(ps_Pixel const& highColor);
      const ps_Pixel& getLowColor() const;
      const ps_Pixel& getHighColor() const;

   protected:

      ps_Pixel _lowColor;
      ps_Pixel _highColor;
};

inline void
ps_GradientShader::setLowColor(ps_Pixel const& lowColor)
{
   _lowColor = lowColor;
}

inline void
ps_GradientShader::setHighColor(ps_Pixel const& highColor)
{
   _highColor = highColor;
}

inline const ps_Pixel&
ps_GradientShader::getLowColor() const
{
   return _lowColor;
}

inline const ps_Pixel&
ps_GradientShader::getHighColor() const
{
   return _highColor;
}

class ps_HSVShader : public ps_PixelShader
{
   public:

      ps_HSVShader();

      void shade(ps_PixelShaderInfo& info) const;

      void setLowColorStart(double deg);
         // 0.0 <= deg <= 360.0.  Controls where the color mapped to the
         // lowest elevation starts in HSV space.
         // Default: 0.0

      void setSaturation(double sat);
         // 0.0 <= sat <= 1.0
         // Default: 1.0

      void setValue(double val);
         // 0.0 <= val <= 1.0
         // Default: 1.0

      void setRange(double range);
         // 1.0 < range;
         // Default: 360.0

      double getLowColorStart() const;
      double getSaturation() const;
      double getValue() const;
      double getRange() const;

   protected:

      double _lowColorStart;
      double _saturation;
      double _value;
      double _range;
};

inline void
ps_HSVShader::setLowColorStart(double deg)
{
   _lowColorStart = deg;
}

inline void
ps_HSVShader::setSaturation(double sat)
{
   _saturation = sat;
}

inline void
ps_HSVShader::setValue(double val)
{
   _value = val;
}

inline void
ps_HSVShader::setRange(double range)
{
   _range = range;
}

inline double
ps_HSVShader::getLowColorStart() const
{
   return _lowColorStart;
}

inline double
ps_HSVShader::getSaturation() const
{
   return _saturation;
}

inline double
ps_HSVShader::getValue() const
{
   return _value;
}

inline double
ps_HSVShader::getRange() const
{
   return _range;
}

class ps_ColorRampShader : public ps_PixelShader
{
   public:

      ps_ColorRampShader();

      void shade(ps_PixelShaderInfo& info) const;
};

#endif // INCLUDED_PIXELSHADER_H

