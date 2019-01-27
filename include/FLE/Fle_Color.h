#pragma once
#ifndef Fle_Color_h__
#define Fle_Color_h__

/*********************************************************************************
created:	2017/03/23   05:47PM
filename: 	Fle_Color.h
file base:	Fle_Color
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Template class for color ranges 0 ~ 255.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2014-2019 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include <FLE/Fle_Export.h>
#include <vector>
#include <sstream>
#include <ostream>
#include <iostream>
#include <algorithm>

namespace R3D
{

template <typename _T>
class FL_ESSENTIALS_EXPORT Fle_Color4
{
public:
	_T r, g, b, a;

	// Description:
	// Default constructor.
	inline Fle_Color4() : r(0), g(0), b(0), a(255)
	{
	}
	// Description:
	// Constructor for 4 inputs.
	inline Fle_Color4(const _T _r, const _T _g, const _T _b, const _T _a) : r(_r), g(_g), b(_b), a(_a)
	{
	}
	// Description:
	// Constructor for 4 inputs.
	template<typename _other>
	inline Fle_Color4(const _other _r, const _other _g, const _other _b, const _other _a) : r(static_cast<_T>(_r)), g(static_cast<_T>(_g)), b(static_cast<_T>(_b)), a(static_cast<_T>(_a))
	{
	}
	// Description:
	// Constructor for 3 inputs. 1.0 will be assigned to Alpha element.
	inline Fle_Color4(const _T _r, const _T _g, const _T _b) : r(_r), g(_g), b(_b), a(255)
	{
	}
	// Description:
	// Constructor for 3 inputs.
	template<typename _other>
	inline Fle_Color4(const _other _r, const _other _g, const _other _b) : r(static_cast<_T>(_r)), g(static_cast<_T>(_g)), b(static_cast<_T>(_b)), a(255)
	{
	}
	// Description:
	// Constructor for array of 4 elements.
	inline Fle_Color4(const _T _v[4]) : r(_v[0]), g(_v[1]), b(_v[2]), a(_v[3])
	{
	}
	// Description:
	// Constructor for array of 4 elements.
	template<typename _other>
	inline Fle_Color4(const _other _v[4]) : r(static_cast<_T>(_v[0])), g(static_cast<_T>(_v[1])), b(static_cast<_T>(_v[2])), a(static_cast<_T>(_v[3]))
	{
	}
	// Description:
	// Copy constructor
	inline Fle_Color4(const Fle_Color4<_T>& _v) : r(_v.r), g(_v.g), b(_v.b), a(_v.a)
	{
	}
	// Description:
	// Copy constructor for different data type.
	template<typename _other>
	inline Fle_Color4(const Fle_Color4<_other>& _v) : r(static_cast<_T>(_v.r)), g(static_cast<_T>(_v.g)), b(static_cast<_T>(_v.b)), a(static_cast<_T>(_v.a))
	{
	}
	// Description:
	// Constructor for a scalar.
	inline explicit Fle_Color4(const _T _v) : r(_v), g(_v), b(_v), a(_v)
	{
	}
	// Description:
	// Function to set the input value to Red.
	inline void setR(const _T _r) { r = _r; }
	// Description:
	// Function to set the input value to Green.
	inline void setG(const _T _g) { g = _g; }
	// Description:
	// Function to set the input value to Blue.
	inline void setB(const _T _b) { b = _b; }
	// Description:
	// Function to set the input value to Alpha.
	inline void setA(const _T _a) { a = _a; }
	// Description:
	// Function to set R, G, B, and A.
	inline void set(const _T _r, const _T _g, const _T _b, const _T _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	// Description:
	// Function to set R, G, and B. Alpha will be the same.
	inline void set(const _T _r, const _T _g, const _T _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
	// Description:
	// Function to set a array of 4 elements.
	inline void set(const _T _v[4])
	{
		r = _v[0];
		g = _v[1];
		b = _v[2];
		a = _v[3];
	}
	// Description:
	// Function to set a array of 3 elements and the value of alpha channel.
	inline void set(const _T _v[3], const _T _a)
	{
		r = _v[0];
		g = _v[1];
		b = _v[2];
		a = _a;
	}
	// Description:
	// Function to set the same data type.
	inline void set(const Fle_Color4<_T>& _v)
	{
		r = _v.r;
		g = _v.g;
		b = _v.b;
		a = _v.a;
	}
	// Description:
	// Function to set the different data type.
	template<typename _other>
	inline void set(const Fle_Color4<_other>& _v)
	{
		r = static_cast<_T>(_v.r);
		g = static_cast<_T>(_v.g);
		b = static_cast<_T>(_v.b);
		a = static_cast<_T>(_v.a);
	}
	// Description:
	// Function to set the scalar value to R, G, B, and A.
	inline void set(const _T _v)
	{
		set(_v, _v, _v, _v);
	}
	// Description:
	// Function to set the color value as a 32 bit combined red / green / blue / alpha value.
	// Each component is 8 bit wide(i.e.from 0x00 to 0xff), and the red
	// value should be stored leftmost, like this: 0xRRGGBBAA.
	void setPackedValue(unsigned int _rgba)
	{
		r = static_cast<_T>((_rgba & 0xFF000000) >> 24);
		g = static_cast<_T>((_rgba & 0x00FF0000) >> 16);
		b = static_cast<_T>((_rgba & 0x0000FF00) >> 8);
		a = static_cast<_T>(_rgba & 0x000000FF);
	}
	// Description:
	// Function that returns color as a 32 bit packed unsigned int in the form 0xRRGGBBAA.
	_T getPackedValue() const
	{
		return (
			static_cast<_T>(r) << 24 |
			static_cast<_T>(g) << 16 |
			static_cast<_T>(b) << 8 |
			static_cast<_T>(a));
	}
	// Description:
	// Function to set 0.0 to R, G, B, and 1.0 to A.
	inline void setZero()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}
	// Description:
	// Function to get R.
	inline const _T& R() const { return r; }
	// Description:
	// Function to get G.
	inline const _T& G() const { return g; }
	// Description:
	// Function to get B.
	inline const _T& B() const { return b; }
	// Description:
	// Function to get A.
	inline const _T& A() const { return a; }
	// Description:
	// Function to get R.
	inline const _T& getR() const { return r; }
	// Description:
	// Function to get G.
	inline const _T& getG() const { return g; }
	// Description:
	// Function to get B.
	inline const _T& getB() const { return b; }
	// Description:
	// Function to get A.
	inline const _T& getA() const { return a; }
	// Description:
	// Function to get R, G, B, and A.
	inline void get(_T& _r, _T& _g, _T& _b, _T& _a) const { _r = r; _g = g; _b = b; _a = a; }
	// Description:
	// Function to get R, G, B, and A.
	inline void get(_T _v[4]) const { _v[0] = r; _v[1] = g; _v[2] = b; _v[3] = a; }
	// Description:
	// Function to get the maximum axis between R, G, B, and A.
	inline const _T getMax() const
	{
		return std::max(std::max(std::max(r, g), b), a);
	}
	// Description:
	// Function to get the minimum axis between R, G, B, and A.
	inline const _T getMin() const
	{
		return std::min(std::min(std::min(r, g), b), a);
	}
	// Description:
	// Function to clamp the color values.
	inline Fle_Color4<_T> clamp0To255()
	{
		if (r > 255) r = 255;
		if (r < 0) r = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (b > 255) b = 255;
		if (b < 0) b = 0;
		if (a > 255) a = 255;
		if (a < 0) a = 0;
		return (*this);
	}
	// Description:
	// Function to get the luminosity.
	inline _T computeLuminosity() const
	{
		return static_cast<_T>(0.2126 * 255 * r + 0.7152 * 255 * g + 0.0722 * 255 * b);
	}
	// Description:
	// Function to print vector values.
	inline void print()
	{
#ifdef _DEBUG
		std::cout << *this << std::endl;
#endif // _DEBUG
	}
	// Description:
	// Function to get the string of this vector.
	inline std::string toString() const
	{
		std::ostringstream ss;
		ss << "(" << r << ", " << g << ", " << b << ", " << a << ")";
		return ss.str();
	}

	/************************************************************************/
	/* Static Functions                                                     */
	/************************************************************************/

	// Description:
	// Function that returns the number of elements this class contained.
	// For this class, it will return 4.
	inline static int getElements() { return 4; }

	static _T getRandom(_T _smallNum, _T _bigNum)
	{
		return (static_cast<_T>(std::rand()) / 0x7fff * (_bigNum - _smallNum)) + _smallNum;
	}
	static Fle_Color4<_T> getRandomColor()
	{
		return Fle_Color4<_T>(getRandom(0, 255), getRandom(0, 255), getRandom(0, 255), 255);
	}
	static Fle_Color4<_T> getRandomColor(_T _smallNum, _T _bigNum)
	{
		return Fle_Color4<_T>(getRandom(_smallNum, _bigNum), getRandom(_smallNum, _bigNum), getRandom(_smallNum, _bigNum), 255);
	}
	inline static Fle_Color4<_T> getBlack()
	{
		return Fle_Color4<_T>(0, 0, 0, 255);
	}
	inline static Fle_Color4<_T> getWhite()
	{
		return Fle_Color4<_T>(255, 255, 255, 255);
	}
	inline static Fle_Color4<_T> getRed()
	{
		return Fle_Color4<_T>(255, 0, 0, 255);
	}
	inline static Fle_Color4<_T> getGreen()
	{
		return Fle_Color4<_T>(0, 255, 0, 255);
	}
	inline static Fle_Color4<_T> getBlue()
	{
		return Fle_Color4<_T>(0, 0, 255, 255);
	}
	inline static Fle_Color4<_T> getDeepSkyBlue()
	{
		return Fle_Color4<_T>(0, static_cast<_T>(0.749 * 255), 255, 255);
	}
	inline static Fle_Color4<_T> getYellow()
	{
		return Fle_Color4<_T>(255, 255, 0, 255);
	}
	inline static Fle_Color4<_T> getCyan()
	{
		return Fle_Color4<_T>(0, 255, 255, 255);
	}
	inline static Fle_Color4<_T> getPurple()
	{
		return Fle_Color4<_T>(static_cast<_T>(0.62745 * 255), static_cast<_T>(0.12549 * 255), static_cast<_T>(0.94117 * 255), 255);
	}
	inline static Fle_Color4<_T> getOrange()
	{
		return Fle_Color4<_T>(255, static_cast<_T>(0.64705 * 255), 0, 255);
	}
	inline static Fle_Color4<_T> getGrey(_T _shade)
	{ 
		return Fle_Color4<_T>(_shade, _shade, _shade, 255);
	}

	/************************************************************************/
	/* Operators                                                            */
	/************************************************************************/
	inline friend std::ostream& operator << (std::ostream& _out, const Fle_Color4<_T>& _v)
	{
		_out << "(" << _v.r << ", " << _v.g << ", " << _v.b << ", " << _v.a << ")" << std::endl; return _out;
	}
	inline friend std::ostream& operator << (std::ostream& _s, const std::vector<Fle_Color4<_T>>& _v)
	{
		for (auto &it : _v)
			_s << it << ' ';
		_s << std::endl;
		return _s;
	}
	inline const Fle_Color4<_T> operator * (const Fle_Color4<_T>& _v) const
	{
		return Fle_Color4<_T>(r * _v.r, g * _v.g, b * _v.b, a * _v.a);
	}
	inline const Fle_Color4<_T> operator + (const Fle_Color4<_T>& _v) const
	{
		return Fle_Color4<_T>(r + _v.r, g + _v.g, b + _v.b, a + _v.a);
	}
	inline const Fle_Color4<_T> operator - (const Fle_Color4<_T>& _v) const
	{
		return Fle_Color4<_T>(r - _v.r, g - _v.g, b - _v.b, a - _v.a);
	}
	inline const Fle_Color4<_T> operator - () const
	{
		return Fle_Color4<_T>(-r, -g, -b, -a);
	}
	inline const Fle_Color4<_T> operator / (const Fle_Color4<_T>& _v) const
	{
		return Fle_Color4<_T>(r / _v.r, g / _v.g, b / _v.b, a / _v.a);
	}
	inline const bool operator == (const Fle_Color4<_T>& _v) const
	{
		return ((std::abs(_v.r - r) < 0.0000001f) && (std::abs(_v.g - g) < 0.0000001f) && (std::abs(_v.b - b) < 0.0000001f) && (std::abs(_v.a - a) < 0.0000001f));
	}
	inline const bool operator < (const Fle_Color4<_T>& _v) const
	{
		if (r < _v.r) return true;
		if (r > _v.r) return false;
		if (g < _v.g) return true;
		if (g > _v.g) return false;
		if (b < _v.b) return true;
		if (b > _v.b) return false;
		return a < _v.a;
	}
	inline const bool operator >(const Fle_Color4<_T>& _v) const
	{
		if (r < _v.r) return false;
		if (r > _v.r) return true;
		if (g < _v.g) return false;
		if (g > _v.g) return true;
		if (b < _v.b) return false;
		if (b > _v.b) return true;
		return a > _v.a;
	}
	inline const bool operator >= (const Fle_Color4<_T>& _v) const
	{
		if (r >= _v.r && g >= _v.g && b >= _v.b && a >= _v.a)
			return true;
		return false;
	}
	inline const bool operator <= (const Fle_Color4<_T>& _v) const
	{
		if (r <= _v.r && g <= _v.g && b <= _v.b && a <= _v.a)
			return true;
		return false;
	}
	inline const bool operator != (const Fle_Color4<_T>& _v) const
	{
		return !(_v == *this);
	}
	inline const Fle_Color4<_T>& operator = (const Fle_Color4<_T>& _v)
	{
		if (this == &_v)
			return *this; // return reference to this (no copy)

		r = _v.r;
		g = _v.g;
		b = _v.b;
		a = _v.a;
		return *this;
	}
	inline const Fle_Color4<_T>& operator += (const Fle_Color4<_T>& _v)
	{
		r += _v.r;
		g += _v.g;
		b += _v.b;
		a += _v.a;
		return *this;
	}
	inline const Fle_Color4<_T>& operator -= (const Fle_Color4<_T>& _v)
	{
		r -= _v.r;
		g -= _v.g;
		b -= _v.b;
		a -= _v.a;
		return *this;
	}
	inline const Fle_Color4<_T>& operator *= (const _T& _v)
	{
		r *= _v;
		g *= _v;
		b *= _v;
		a *= _v;
		return *this;
	}
	inline const Fle_Color4<_T>& operator /= (const _T& _v)
	{
		const _T _r = static_cast<_T>(1 / _v);
		r *= _r;
		g *= _r;
		b *= _r;
		a *= _r;
		return *this;
	}
	inline const Fle_Color4<_T> operator * (const _T _v) const
	{
		return Fle_Color4<_T>(r * _v, g * _v, b * _v, a * _v);
	}
	friend inline const Fle_Color4<_T> operator * (const _T& _s, const Fle_Color4<_T>& _v)
	{
		return _v * _s;
	}
	inline const Fle_Color4<_T> operator + (const _T _v) const
	{
		return Fle_Color4<_T>(r + _v, g + _v, b + _v, a + _v);
	}
	inline const Fle_Color4<_T> operator - (const _T _v) const
	{
		return Fle_Color4<_T>(r - _v, g - _v, b - _v, a - _v);
	}
	inline const Fle_Color4<_T> operator / (_T _v) const
	{
		_v = static_cast<_T>(1 / _v);
		return Fle_Color4<_T>(r * _v, g * _v, b * _v, a * _v);
	}

	inline const bool operator >= (_T _v) const
	{
		if (r >= _v && g >= _v && b >= _v && a >= _v)
			return true;
		return false;
	}
	inline const bool operator <= (_T _v) const
	{
		if (r <= _v && g <= _v && b <= _v && a <= _v)
			return true;
		return false;
	}
	inline const bool operator == (_T _v) const
	{
		if ((std::abs(_v - r) < 0.0000001f) && (std::abs(_v - g) < 0.0000001f) && (std::abs(_v - b) < 0.0000001f) && (std::abs(_v - a) < 0.0000001f))
			return true;
		return false;
	}
	inline const bool operator != (_T _v) const
	{
		if ((r != _v) && (g != _v) && (b != _v) && (a != _v))
			return true;
		return false;
	}
	inline const bool operator > (_T _v) const
	{
		if (r > _v && g > _v && b > _v && a > _v)
			return true;
		return false;
	}
	inline const bool operator < (_T _v) const
	{
		if (r < _v && g < _v && b < _v && a < _v)
			return true;
		return false;
	}
	inline _T& operator [](long _i)
	{
		return ((&r)[_i]);
	}
	inline const _T& operator [](long _i) const
	{
		return ((&r)[_i]);
	}

	const _T* ptr() const { return &r; }
	_T* ptr() { return &r; }
};

template FL_ESSENTIALS_EXPORT class Fle_Color4<int>;
template FL_ESSENTIALS_EXPORT class Fle_Color4<unsigned char>;

typedef Fle_Color4<int> Fle_Color4i;
typedef Fle_Color4<unsigned char> Fle_Color4uc;
typedef Fle_Color4uc Fle_Color;

}

#endif // Fle_Color_h__