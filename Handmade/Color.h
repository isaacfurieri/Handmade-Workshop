/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2016

  -----------------------------------------------------------------------------------------------

- This class encapsulates RGBA colors with an enumeration for representing six colors and three
  grayscale values based on the additive RGB color model. These colors are the primary base colors 
  and can be blended together using color arithmetic to produce new colors. 

- The RGBA values are all public so that it is easier to access them individually in the client code. 

- The arithmetic operators that represent addition, subtraction, multiplication and division have
  been overloaded to allow for color values to be blended together using mathematic functions. 
  
- Currently the built-in arithmetic only supports two color objects, a color object and a scalar value, 
  and a color object and a color enum value. It does not work with two color enum values, so RED + BLUE 
  for instance will not work, and RED + 0.25f will also not give you what you expect. 
  
- Outside the class declaration are two global functions that will overload the addition and
  multiplication functionality, for Color objects to be added to scalar values, ie 0.5 + C or 0.46 * C.
  Subtraction and division is currently not supported. These functions have to be global and outside of
  the class object, they cannot be static. Something like 0.4f + GREEN or 2.1f * CYAN is not supported.

- The ^ and ^= operators have been overloaded to represent power calculations using the color object and 
  a float power value.

- Three Lerp functions allow for linear interpolation between two colors as well as their alpha channels. 
  These functions should ideally be called from inside some kind of Update routine in the client code. 
  The algorithm used for linear interpolation works with both normalized and non-normalized vector values. 
  Because our color object values are always normalised, this formula is perfect. These Lerp routines
  all change the calling object, which eventually becomes the target color object. This works differently
  to the way the Vector classes handle lerping.

- A Cap() function acts as a minimum and maximum threshold that ensures the RGBA values remain between 
  0.0 and 1.0. If the RGBA values are individually set via their public members then the capping cannot
  be controlled, otherwise capping is controlled internally in the class' definition code.

- The Output() function is for debug purposes and displays the RGBA values on the console window.

- Some parameters are const qualified and others not. The ones that are not const are so because they 
  internally call non-const functions, which causes a conflict. This is not neccessarily a good coding
  practise, and will be amended some other time.

*/

#ifndef COLOR_H
#define COLOR_H
 
class Color
{

public :

	enum ColorType { WHITE, BLACK, GREY, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN };

public :

	Color(float r = 1, float g = 1, float b = 1, float a = 1);
	Color(ColorType colorType);

public :

	Color& operator=(const ColorType rhs);

	Color operator+(const Color& rhs);
	Color operator+(const float rhs);
	Color operator+(const ColorType rhs);

	Color& operator+=(const Color& rhs);
	Color& operator+=(const float rhs);
	Color& operator+=(const ColorType rhs);
	
	Color operator-(const Color& rhs);
	Color operator-(const float rhs);
	Color operator-(const ColorType rhs);

	Color& operator-=(const Color& rhs);
	Color& operator-=(const float rhs);
	Color& operator-=(const ColorType rhs);

	Color operator*(const Color& rhs);
	Color operator*(const float rhs);
	Color operator*(const ColorType rhs);

	Color& operator*=(const Color& rhs);
	Color& operator*=(const float rhs);
	Color& operator*=(const ColorType rhs);

	Color operator/(const Color& rhs);
	Color operator/(const float rhs);
	Color operator/(const ColorType rhs);

	Color& operator/=(const Color& rhs);
	Color& operator/=(const float rhs);
	Color& operator/=(const ColorType rhs);

	Color operator^(const float rhs);
	Color& operator^=(const float rhs);

	bool operator==(const Color& rhs);
	bool operator==(const ColorType rhs);
	bool operator!=(const Color& rhs);
	bool operator!=(const ColorType rhs);

public :

	Color& Lerp(Color& secondColor, float delta, float epsilon = 0.01f);
	Color& Lerp(ColorType secondColor, float delta, float epsilon = 0.01f);
	Color& Lerp(float secondAlpha, float delta, float epsilon = 0.01f);

public :

	void Cap();
	void Output();
	
public :

	float R;
	float G;
	float B;
	float A;

};

//GLOBAL functions
Color operator+(const float lhs, Color& rhs);
Color operator*(const float lhs, Color& rhs);

#endif