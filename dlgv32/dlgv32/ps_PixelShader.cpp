#include <iostream.h>
#include <math.h>
#include "ps_PixelShader.h"

#define PI 3.14159265
#define DEGTORAD(x) ( (x) * PI / 180.0 )
#define RADTODEG(x) ( (x) * 180.0 / PI )

ps_Pixel::ps_Pixel()
        : red(0), green(0), blue(0)
{
}

ps_Pixel::ps_Pixel(unsigned char gray)
        : red(gray), green(gray), blue(gray)
{
}

ps_Pixel::ps_Pixel(unsigned char r,
                   unsigned char g,
                   unsigned char b)
        : red(r), green(g), blue(b)
{
}

unsigned char
ps_Pixel::getGray() const
{
   short val = (red + green + blue) / (3 * 255);
   return (unsigned char) val;
}


ps_PixelShader::ps_PixelShader()
              : _ambientLightLevel(0.0),
                _bLightingEnabled(true),
                _bWaterEnabled(true),
                _waterAlpha(128),
                _waterColor(0,0,255),
                _waterLevel(0.0)
{
    setLightDirection( 45, 45 );
}

void
ps_PixelShader::setLightDirection( float altitude, float azimuth )
{
    // Convert azimuth to regular from cartographer
    azimuth = 90 - azimuth;
    if ( azimuth < 0.0 )
    {
        azimuth += 360.0;
    }

    // Convert altitude to regular from cartographer
    altitude = 90 - altitude;

    // Convert the altitude and azimuth to radians
    altitude = DEGTORAD( altitude );
    azimuth  = DEGTORAD( azimuth );

    double x = sin( altitude ) * cos( azimuth );
    double y = sin( altitude ) * sin( azimuth );
    double z = cos( altitude );

    setLightDirection( ps_Vector( -x, y, -z ) );
}

void
ps_PixelShader::getLightDirection( float& altitude, float& azimuth )
{
    double i, j, k;
    _lightDirection.getComponents( i, j, k );

    altitude = acos( k );
    if ( altitude > 0.0 && altitude <= 1.0 )
    {
        azimuth  = asin( -j / sin( altitude ) );
    }
    else
    {
        azimuth = 0;
    }

    // Convert the altitude and azimuth to degrees
    altitude = RADTODEG( altitude );
    azimuth =  RADTODEG( azimuth );

    if ( i < 0.0 && j <  0.0  )
    {
        azimuth = 180 - azimuth;
    }
    else if ( i < 0.0 && j > 0.0 )
    {
        azimuth = 180 - azimuth;
    }

    // Convert the azimuth to cartographer degrees
    azimuth = 90 - azimuth;
    if ( azimuth < 0.0 )
    {
        azimuth += 360.0;
    }

    // Convert the altitude to cartographer degrees
    altitude = 90 - altitude;
}

void  
ps_PixelShader::addWater( ps_PixelShaderInfo& info ) const
{
   // Apply water if necessary
   if ( _bWaterEnabled && info.pixelZ <= _waterLevel )
   {
       // Check to see if water alpha should be applied
       if ( 0 != _waterAlpha )
       {
           // Apply water alpha
           info.pixel.red   = ( _waterColor.red - info.pixel.red ) * _waterAlpha / 255 +
                              info.pixel.red;
           info.pixel.blue  = ( _waterColor.blue - info.pixel.blue ) * _waterAlpha / 255 +
                              info.pixel.blue;
           info.pixel.green = ( _waterColor.green - info.pixel.green ) * _waterAlpha / 255 +
                              info.pixel.green;
       }
   }
}

//
// Daylight Shader
//

ps_DaylightShader::ps_DaylightShader()
                 : ps_PixelShader(), _color(0,255,255)
{
}

static
unsigned char clamp(float val)
{
   if (val < 0.0)
   {
      return 0;
   }
   else if (val > 255.0)
   {
       return 255;
   }

   return static_cast<unsigned char> (val);
}

void
ps_DaylightShader::shade(ps_PixelShaderInfo& info) const
{
   ps_Pixel color = _color;
   if ( info.bUseColor )
   {
       color = info.pixel;
   }

   // Apply the intensity if necessary
   if ( isLightingEnabled() )
   {
      info.pixel.red   = info.intensity * color.red / 255;
      info.pixel.green = info.intensity * color.green / 255;
      info.pixel.blue  = info.intensity * color.blue / 255;
   }
   else
   {
       info.pixel = color;
   }

   // Apply the water to the pixel
   addWater( info );
}

//
// Gradient shader
//

ps_GradientShader::ps_GradientShader()
                 : ps_PixelShader(),
                   _lowColor(0,0,0),
                   _highColor(255,255,255)
{
}

void
ps_GradientShader::shade(ps_PixelShaderInfo& info) const
{
   // Calculate the gradient color if a texture mapped color hasn't been specified
   if ( !info.bUseColor )
   {
      unsigned char t = (info.pixelZ - info.minZ) * 255 / (info.maxZ - info.minZ);
      info.pixel.red   = (255 * _lowColor.red   + t * (_highColor.red   - _lowColor.red  ) ) / 255;  
      info.pixel.green = (255 * _lowColor.green + t * (_highColor.green - _lowColor.green) ) / 255;
      info.pixel.blue  = (255 * _lowColor.blue  + t * (_highColor.blue  - _lowColor.blue ) ) / 255;
   }

   // Apply the intensity if necessary
   if ( isLightingEnabled() )
   {
      info.pixel.red   = info.intensity * info.pixel.red / 255;
      info.pixel.green = info.intensity * info.pixel.green / 255;
      info.pixel.blue  = info.intensity * info.pixel.blue / 255;
   }

   // Add water to the pixel
   addWater( info );
}

//
// HSV shader
//

static
void
hsv2rgb(double hue, double saturation, double value,
           double& red, double& green, double& blue)
{
   // 0.0 <= hue <= 360.0
   // 0.0 <= saturation <= 1.0
   // 0.0 <= value <= 1.0
   // 0.0 <= red <= 1.0
   // 0.0 <= green <= 1.0
   // 0.0 <= blue <= 1.0

   // Stolen and modified from xscreensaver 1.22.

   double H, S, V, R, G, B;
   double p1, p2, p3;
   double f;
   int i;

   S = saturation;
   V = value;
   H = hue / 60.0;
   i = H;
   f = H - i;
   p1 = V * (1 - S);
   p2 = V * (1 - (S * f));
   p3 = V * (1 - (S * (1 - f)));
   if      (i == 0) { R = V;  G = p3; B = p1; }
   else if (i == 1) { R = p2; G = V;  B = p1; }
   else if (i == 2) { R = p1; G = V;  B = p3; }
   else if (i == 3) { R = p1; G = p2; B = V;  }
   else if (i == 4) { R = p3; G = p1; B = V;  }
   else             { R = V;  G = p1; B = p2; }

   red = R;
   green = G;
   blue = B;
}

ps_HSVShader::ps_HSVShader()
            : ps_PixelShader(),
              _lowColorStart(0.0),
              _saturation(1.0),
              _value(1.0),
              _range(360.0)
{
}

void
ps_HSVShader::shade(ps_PixelShaderInfo& info) const
{
   // Find the HSV color if a texture mapped color hasn't been specified
   if ( !info.bUseColor )
   {
      double r,g,b;
      double dz = info.maxZ - info.minZ;
      if ( dz < 0.0000001) dz = 1.0;
      double hue = _range * ((info.pixelZ - info.minZ) / dz) + _lowColorStart;

      // Make sure the hue is between 0 and 360
      if (hue >= 360.0)
      {
         hue -= static_cast<int>( hue / 360.0 ) * 360.0;
      }

      hsv2rgb(hue, _saturation, _value,r,g,b);

      info.pixel.red   = clamp(255.0 * r);
      info.pixel.green = clamp(255.0 * g);
      info.pixel.blue  = clamp(255.0 * b);
   }

   // Apply the intensity if necessary
   if ( isLightingEnabled() )
   {
      info.pixel.red   = info.intensity * info.pixel.red / 255;
      info.pixel.green = info.intensity * info.pixel.green / 255;
      info.pixel.blue  = info.intensity * info.pixel.blue / 255;
   }

   // Add water to the pixel
   addWater( info );   
}

// ps_ColorRampShader
ps_ColorRampShader::ps_ColorRampShader()
: ps_PixelShader()
{
}

void
ps_ColorRampShader::shade(ps_PixelShaderInfo& info) const
{
   // Find the color if a texture mapped color hasn't been specified
   if ( !info.bUseColor )
   {
      int zRatio = 1023 * ( info.pixelZ - info.minZ ) / ( info.maxZ - info.minZ );
      if ( zRatio < 256 )
      {
          info.pixel.red = 0;
          info.pixel.green = zRatio & 0xFF;
          info.pixel.blue = 255;
      }
      else if ( zRatio < 512 )
      {
          info.pixel.red = 0;
          info.pixel.green = 255;
          info.pixel.blue = 255 - zRatio & 0xFF;
      }
      else if ( zRatio < 768 )
      {
          info.pixel.red = zRatio & 0xFF;
          info.pixel.green = 255;
          info.pixel.blue = 0;
      }
      else
      {
          info.pixel.red = 255;
          info.pixel.green = 255 - zRatio & 0xFF;
          info.pixel.blue = 0;
      }
   }

   // Apply the intensity if necessary
   if ( isLightingEnabled() )
   {
      info.pixel.red   = info.intensity * info.pixel.red / 255;
      info.pixel.green = info.intensity * info.pixel.green / 255;
      info.pixel.blue  = info.intensity * info.pixel.blue / 255;
   }

   // Add water to the pixel
   addWater( info );   
}