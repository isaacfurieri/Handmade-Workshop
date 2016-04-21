#include <iostream>
#include <math.h>
#include "Color.h"

//******************************************************************************************************
//GLOBAL functions
//******************************************************************************************************

//------------------------------------------------------------------------------------------------------
//function that adds a Color object to a value
//------------------------------------------------------------------------------------------------------
Color operator+(const float lhs, Color& rhs)
{

	//use the class object's + operator function to avoid duplicate code
	return rhs + lhs;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a Color object to a value
//------------------------------------------------------------------------------------------------------
Color operator*(const float lhs, Color& rhs)
{

	//use the class object's * operator function to avoid duplicate code
	return rhs * lhs;

}

//******************************************************************************************************
//COLOR class member functions
//******************************************************************************************************

//------------------------------------------------------------------------------------------------------
//constructor that assigns RGBA components of color based on values passed 
//------------------------------------------------------------------------------------------------------
Color::Color(float r, float g, float b, float a)
{
	
	R = r;
	G = g;
	B = b;
	A = a;

	//make sure RGBA values fall within their range
	Cap();

}
//------------------------------------------------------------------------------------------------------
//second constructor that assigns color and alpha values based on color enum type passed
//------------------------------------------------------------------------------------------------------
Color::Color(ColorType colorType)
{

	//based on color type assign the RGB values accordingly
	//the alpha channel is automatically assigned to 1 by default
	switch (colorType)
	{
		case WHITE:   { R = 1.0f; G = 1.0f; B = 1.0f; A = 1.0f; break; }
		case BLACK:	  { R = 0.0f; G = 0.0f; B = 0.0f; A = 1.0f; break; }
		case GREY:	  { R = 0.5f; G = 0.5f; B = 0.5f; A = 1.0f; break; }
		case RED:	  { R = 1.0f; G = 0.0f; B = 0.0f; A = 1.0f; break; }
		case GREEN:	  { R = 0.0f; G = 1.0f; B = 0.0f; A = 1.0f; break; }
		case BLUE:	  { R = 0.0f; G = 0.0f; B = 1.0f; A = 1.0f; break; }
		case YELLOW:  { R = 1.0f; G = 1.0f; B = 0.0f; A = 1.0f; break; }
		case MAGENTA: { R = 1.0f; G = 0.0f; B = 1.0f; A = 1.0f; break; }
		case CYAN:    { R = 0.0f; G = 1.0f; B = 1.0f; A = 1.0f; break; }
	}

}
//------------------------------------------------------------------------------------------------------
//function that assigns color values based on color enum type passed
//------------------------------------------------------------------------------------------------------
Color& Color::operator=(const ColorType rhs)
{

	//based on color type assign the RGB values accordingly
	//the alpha channel is ignored because we are only assigning the color
	switch (rhs)
	{
		case WHITE:   { R = 1.0f; G = 1.0f; B = 1.0f; break; }
		case BLACK:	  { R = 0.0f; G = 0.0f; B = 0.0f; break; }
		case GREY:	  { R = 0.5f; G = 0.5f; B = 0.5f; break; }
		case RED:	  { R = 1.0f; G = 0.0f; B = 0.0f; break; }
		case GREEN:	  { R = 0.0f; G = 1.0f; B = 0.0f; break; }
		case BLUE:	  { R = 0.0f; G = 0.0f; B = 1.0f; break; }
		case YELLOW:  { R = 1.0f; G = 1.0f; B = 0.0f; break; }
		case MAGENTA: { R = 1.0f; G = 0.0f; B = 1.0f; break; }
		case CYAN:    { R = 0.0f; G = 1.0f; B = 1.0f; break; }
	}

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds two Color objects together using the += overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator+(const Color& rhs)
{

	Color result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds a value to a Color object using the += overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator+(const float rhs)
{

	Color result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds a color enum value to a Color object using the += overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator+(const ColorType rhs)
{

	Color result(*this);
	return (result += rhs);

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a Color to another Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator+=(const Color& rhs)
{

	//add and assign RGB values using the two color objects 
	//ignore the alpha channel, only the color values are needed
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;

	//make sure RGB values do not exceed 1
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator+=(const float rhs)
{

	//add and assign RGB values using the color object and passed value 
	//ignore the alpha channel, only the color values are needed
	R += rhs;
	G += rhs;
	B += rhs;

	//make sure RGB values do not exceed 1
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that adds and assigns a color enum value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator+=(const ColorType rhs)
{

	//temp color object created using the color enum value passed
	Color temp(rhs);
	
	//use the other += operator function to avoid duplicate code
	return *this += temp;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts one Color objects from another using the -= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator-(const Color& rhs)
{

	Color result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a value from a Color object using the -= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator-(const float rhs)
{

	Color result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts a color enum value from a Color object using the -= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator-(const ColorType rhs)
{

	Color result(*this);
	return (result -= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a Color to another Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator-=(const Color& rhs)
{

	//subtract and assign RGB values using the two color objects 
	//ignore the alpha channel, only the color values are needed
	R -= rhs.R;
	G -= rhs.G;
	B -= rhs.B;

	//make sure RGB values do not fall below 0
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator-=(const float rhs)
{

	//subtract and assign RGB values using the color object and passed value 
	//ignore the alpha channel, only the color values are needed
	R -= rhs;
	G -= rhs;
	B -= rhs;

	//make sure RGB values do not fall below 0
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that subtracts and assigns a color enum value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator-=(const ColorType rhs)
{

	//temp color object created using the color enum value passed
	Color temp(rhs);

	//use the other -= operator function to avoid duplicate code
	return *this -= temp;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies two Color objects together using the *= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator*(const Color& rhs)
{

	Color result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a value with a Color object using the *= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator*(const float rhs)
{

	Color result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies a color enum value with a Color object using the *= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator*(const ColorType rhs)
{

	Color result(*this);
	return (result *= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a Color to another Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator*=(const Color& rhs)
{

	//multiply and assign RGB values using the two color objects 
	//ignore the alpha channel, only the color values are needed
	R *= rhs.R;
	G *= rhs.G;
	B *= rhs.B;

	//make sure RGB values do not exceed 1
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator*=(const float rhs)
{

	//multiply and assign RGB values using the color object and passed value 
	//ignore the alpha channel, only the color values are needed
	R *= rhs;
	G *= rhs;
	B *= rhs;

	//make sure RGB values do not exceed 1
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that multiplies and assigns a color enum value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator*=(const ColorType rhs)
{

	//temp color object created using the color enum value passed
	Color temp(rhs);

	//use the other *= operator function to avoid duplicate code
	return *this *= temp;

}
//------------------------------------------------------------------------------------------------------
//function that divides a Color object with another using the /= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator/(const Color& rhs)
{

	Color result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides a Color object by a value using the /= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator/(const float rhs)
{

	Color result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides a Color object by a color enum value using the /= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator/(const ColorType rhs)
{

	Color result(*this);
	return (result /= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a Color to another Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator/=(const Color& rhs)
{

	//divide and assign RGB values using the two color objects 
	//first make sure that we do not divide by 0!
	//ignore the alpha channel, only the color values are needed
	if(rhs.R != 0.0f) R /= rhs.R;
	if(rhs.G != 0.0f) G /= rhs.G;
	if(rhs.B != 0.0f) B /= rhs.B;

	//make sure RGB values do not fall below 0
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator/=(const float rhs)
{

	//divide and assign RGB values using the color object and passed value 
	//first make sure that we do not divide by 0!
	//ignore the alpha channel, only the color values are needed
	if (rhs != 0.0f) R /= rhs;
	if (rhs != 0.0f) G /= rhs;
	if (rhs != 0.0f) B /= rhs;

	//make sure RGB values do not fall below 0
	Cap();

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that divides and assigns a color enum value to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator/=(const ColorType rhs)
{

	//temp color object created using the color enum value passed
	Color temp(rhs);

	//use the other /= operator function to avoid duplicate code
	return *this /= temp;

}
//------------------------------------------------------------------------------------------------------
//function that applies a power value to the Color object using the ^= overloaded function
//------------------------------------------------------------------------------------------------------
Color Color::operator^(const float rhs)
{

	Color result(*this);
	return (result ^= rhs);

}
//------------------------------------------------------------------------------------------------------
//function that applies a power value and assigns the result to Color object
//------------------------------------------------------------------------------------------------------
Color& Color::operator^=(const float rhs)
{

	//apply power value to RGB values using the color object and passed value 
	//ignore the alpha channel, only the color values are needed
	R = pow(R, rhs);
	G = pow(G, rhs);
	B = pow(B, rhs);

	//return a reference of the color object so that 
	//assignment chaining can be used as well
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that checks if color object is the same as another color object
//------------------------------------------------------------------------------------------------------
bool Color::operator==(const Color& rhs)
{

	//return true or false if all RGBA values are the same
	//the alpha channel is taken into consideration because we are comparing the entire object
	return (R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A);

}
//------------------------------------------------------------------------------------------------------
//function that checks if color object is a certain color based on color enum type passed
//------------------------------------------------------------------------------------------------------
bool Color::operator==(const ColorType rhs)
{

	//check the RGB values individually to see if that color is active
	//the alpha channel is ignored because we are only interested in the color
	switch (rhs)
	{
		case WHITE:   { return (R == 1.0f && G == 1.0f && B == 1.0f); }
		case BLACK:	  { return (R == 0.0f && G == 0.0f && B == 0.0f); }
		case GREY:	  { return (R == 0.5f && G == 0.5f && B == 0.5f); }
		case RED:	  { return (R == 1.0f && G == 0.0f && B == 0.0f); }
		case GREEN:	  { return (R == 0.0f && G == 1.0f && B == 0.0f); }
		case BLUE:	  { return (R == 0.0f && G == 0.0f && B == 1.0f); }
		case YELLOW:  { return (R == 1.0f && G == 1.0f && B == 0.0f); }
		case MAGENTA: { return (R == 1.0f && G == 0.0f && B == 1.0f); }
		case CYAN:    { return (R == 0.0f && G == 1.0f && B == 1.0f); }
	}

	return false;

}
//------------------------------------------------------------------------------------------------------
//function that checks if color object is not the same as another color object
//------------------------------------------------------------------------------------------------------
bool Color::operator!=(const Color& rhs)
{

	//use the == overloaded function and negate its result
	//this will oppose the == functionality and prevent repetitive code  
	return !(*this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that checks if color object is not a certain color based on color enum type passed
//------------------------------------------------------------------------------------------------------
bool Color::operator!=(const ColorType rhs)
{

	//use the == overloaded function and negate its result
	//this will oppose the == functionality and prevent repetitive code
	return !(*this == rhs);

}
//------------------------------------------------------------------------------------------------------
//function that performs linear interpolation between two Color objects 
//------------------------------------------------------------------------------------------------------
Color& Color::Lerp(Color& secondColor, float delta, float epsilon)
{

	//use a simple algorithm to create the new lerped color value
	*this = (*this * (1.0f - delta)) + (secondColor * delta);

	//check if the difference between the RGB components of the source and destination color
	//are within the epsilon range. If they are, make them both equal. This ensures that the source
	//color will reach the destination value as quick as the epsilon value states. The smaller the 
	//epsilon value, the longer it will take to reach the destination color.
	if (abs(secondColor.R - R) <= epsilon)
	{
		R = secondColor.R;
	}

	if (abs(secondColor.G - G) <= epsilon)
	{
		G = secondColor.G;
	}

	if (abs(secondColor.B - B) <= epsilon)
	{
		B = secondColor.B;
	}

	//return a reference of the color object because
	//it has directly been changed and could be used in an assignment
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that performs linear interpolation between a Color object and a color enum value
//------------------------------------------------------------------------------------------------------
Color& Color::Lerp(ColorType secondColor, float delta, float epsilon)
{

	//temp color object created using the color enum value passed
	Color temp(secondColor);

	//use other Lerp function to avoid repetitive code
	return Lerp(temp, delta, epsilon);

}
//------------------------------------------------------------------------------------------------------
//function that performs linear interpolation between two Color objects' alpha channel
//------------------------------------------------------------------------------------------------------
Color& Color::Lerp(float secondAlpha, float delta, float epsilon)
{

	//first check if float value being lerped TO is within the range of 0 and 1 and return 
	//the object without doing anything because lerping beyond this range is not supported
	if (secondAlpha > 1.0f || secondAlpha < 0.0f )
	{
		return *this;
	}

	//use a simple algorithm to create the new lerped alpha value
	A = (A * (1.0f - delta)) + (secondAlpha * delta);

	//check if the difference between the alpha component of the source and destination alpha
	//are within the epsilon range. If they are, make them both equal. This ensures that the source
	//alpha will reach the destination value as quick as the epsilon value states. The smaller the 
	//epsilon value, the longer it will take to reach the destination alpha.
	if (abs(A - secondAlpha) <= epsilon)
	{
		A = secondAlpha;
	}

	//return a reference of the color object because
	//it has directly been changed and could be used in an assignment
	return *this;

}
//------------------------------------------------------------------------------------------------------
//function that makes sure RGBA values remain in the range 0 to 1
//------------------------------------------------------------------------------------------------------
void Color::Cap()
{

	((R < 0.0f) ? R = 0.0f : (R > 1.0f) ? R = 1.0f : R = R);
	((G < 0.0f) ? G = 0.0f : (G > 1.0f) ? G = 1.0f : G = G);
	((B < 0.0f) ? B = 0.0f : (B > 1.0f) ? B = 1.0f : B = B);
	((A < 0.0f) ? A = 0.0f : (A > 1.0f) ? A = 1.0f : A = A);

}
//------------------------------------------------------------------------------------------------------
//function that displays R, G, B and A values of color object
//DEBUG purposes only
//------------------------------------------------------------------------------------------------------
void Color::Output()
{

	std::cout << "R = " << R << " <<>> " << "G = " << G << " <<>> " 
		      << "B = " << B << " <<>> " << "A = " << A << std::endl;

}