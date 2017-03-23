#pragma once
#ifndef Fle_Size_h__
#define Fle_Size_h__

/*********************************************************************************
created:	2017/03/23   05:03PM
filename: 	Fle_Size.h
file base:	Fle_Size
file ext:	h
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	Template class for size with width and height as data members.

/**********************************************************************************
FL-ESSENTIALS (FLE) - FLTK Utility Widgets
Copyright (C) 2017 REAL3D

This file and its content is protected by a software license.
You should have received a copy of this license with this file.
If not, please contact Dr. Furqan Ullah immediately:
**********************************************************************************/

#include "Fle_Export.h"
#include <vector>
#include <sstream>
#include <ostream>
#include <iostream>
#include <algorithm>

namespace R3D
{

template <typename _T>
class FL_ESSENTIALS_EXPORT Fle_Size2
{
public:
	_T width, height;

	// Description:
	// Default constructor.
	inline Fle_Size2() : width(0), height(0)
	{
	}
	// Description:
	// Constructor for 2 inputs.
	inline Fle_Size2(const _T _w, const _T _h) : width(_w), height(_h)
	{
	}
	// Description:
	// Constructor for 2 inputs.
	template<typename _other>
	inline Fle_Size2(const _other _w, const _other _h) : width(static_cast<_T>(_w)), height(static_cast<_T>(_h))
	{
	}
	// Description:
	// Constructor for array of 2 elements.
	inline Fle_Size2(const _T _s[2]) : width(_s[0]), height(_s[1])
	{
	}
	// Description:
	// Constructor for array of 2 elements.
	template<typename _other>
	inline Fle_Size2(const _other _s[2]) : width(static_cast<_T>(_s[0])), height(static_cast<_T>(_s[1]))
	{
	}
	// Description:
	// Copy constructor
	inline Fle_Size2(const Fle_Size2<_T>& _s) : width(_s.width), height(_s.height)
	{
	}
	// Description:
	// Copy constructor for different data type.
	template<typename _other>
	inline Fle_Size2(const Fle_Size2<_other>& _s) : width(static_cast<_T>(_s.width)), height(static_cast<_T>(_s.height))
	{
	}
	// Description:
	// Constructor for a scalar.
	inline explicit Fle_Size2(const _T _s) : width(_s), height(_s)
	{
	}
	// Description:
	// Function to set the input value to width.
	inline void setWidth(const _T _w) { width = _w; }
	// Description:
	// Function to set the input value to height.
	inline void setHeight(const _T _h) { height = _h; }
	// Description:
	// Function to set width and height.
	inline void set(const _T _w, const _T _h)
	{
		width = _w;
		height = _h;
	}
	// Description:
	// Function to set a array of 2 elements.
	inline void set(const _T _s[2])
	{
		width = _s[0];
		height = _s[1];
	}
	// Description:
	// Template function to set a array of 2 elements.
	template<typename _other>
	inline void set(const _other _s[2])
	{
		width = static_cast<_T>(_s[0]);
		height = static_cast<_T>(_s[1]);
	}
	// Description:
	// Function to set the same data type.
	inline void set(const Fle_Size2<_T>& _s)
	{
		width = _s.width;
		height = _s.height;
	}
	// Description:
	// Function to set the different data type.
	template<typename _other>
	inline void set(const Fle_Size2<_other>& _s)
	{
		width = static_cast<_T>(_s.width);
		height = static_cast<_T>(_s.height);
	}
	// Description:
	// Function to set the scalar value to width and height.
	inline void set(const _T _s)
	{
		set(_s, _s);
	}
	// Description:
	// Function to set 0.0 to width and height.
	inline void setZero()
	{
		width = 0;
		height = 0;
	}
	// Description:
	// Function to scale width and height.
	inline void scale(const _T _s)
	{
		width *= _s;
		height *= _s;
	}
	// Description:
	// Function to get the area which is (width x height).
	inline const _T area() const
	{
		return width * height;
	}
	// Description:
	// Function to get width.
	inline const _T& getWidth() const { return width; }
	// Description:
	// Function to get height.
	inline const _T& getHeight() const { return height; }
	// Description:
	// Function to get width and height.
	inline void get(_T& _w, _T& _h) const { _w = width; _h = height; }
	// Description:
	// Function to get width and height.
	inline void get(_T _s[2]) const { _s[0] = width; _s[1] = height; }
	// Description:
	// Function to get the maximum axis between width and height.
	inline const _T getMax() const
	{
		return std::max(width, height);
	}
	// Description:
	// Function to get the minimum axis between width and height.
	inline const _T getMin() const
	{
		return std::min(width, height);
	}
	// Description:
	// Function to print width and height values.
	void print()
	{
#ifdef _DEBUG
		std::cout << *this << std::endl;
#endif // _DEBUG
	}
	// Description:
	// Function to get width and height as string.
	inline std::string toString() const
	{
		std::ostringstream ss;
		ss << "(" << width << ", " << height << ")";
		return ss.str();
	}
	/************************************************************************/
	/* Operators                                                            */
	/************************************************************************/
	inline friend std::ostream& operator << (std::ostream& _out, const Fle_Size2<_T>& _s)
	{
		_out << "(" << _s.width << ", " << _s.height << ")" << std::endl; return _out;
	}
	inline friend std::ostream& operator << (std::ostream& _s, const std::vector<Fle_Size2<_T>>& _a)
	{
		for (auto &it : _a)
			_s << it << ' ';
		_s << std::endl;
		return _s;
	}
	inline const Fle_Size2<_T> operator * (const Fle_Size2<_T>& _s) const
	{
		return Fle_Size2<_T>(width * _s.width, height * _s.height);
	}
	inline const Fle_Size2<_T> operator + (const Fle_Size2<_T>& _s) const
	{
		return Fle_Size2<_T>(width + _s.width, height + _s.height);
	}
	inline const Fle_Size2<_T> operator - (const Fle_Size2<_T>& _s) const
	{
		return Fle_Size2<_T>(width - _s.width, height - _s.height);
	}
	inline const Fle_Size2<_T> operator / (const Fle_Size2<_T>& _s) const
	{
		return Fle_Size2<_T>(width / _s.width, height / _s.height);
	}
	inline const bool operator == (const Fle_Size2<_T>& _s) const
	{
		if (_s.width == width && _s.height == height)
			return true;
		return false;
	}
	inline const bool operator < (const Fle_Size2<_T>& _s) const
	{
		if (width < _s.width) return true;
		if (width > _s.width) return false;
		return height < _s.height;
	}
	inline const bool operator > (const Fle_Size2<_T>& _s) const
	{
		if (width < _s.width) return false;
		if (width > _s.width) return true;
		return height > _s.height;
	}
	inline const bool operator >= (const Fle_Size2<_T>& _s) const
	{
		if (width >= _s.width && height >= _s.height)
			return true;
		return false;
	}
	inline const bool operator <= (const Fle_Size2<_T>& _s) const
	{
		if (width <= _s.width && height <= _s.height)
			return true;
		return false;
	}
	inline const bool operator != (const Fle_Size2<_T>& _s) const
	{
		return !(_s == *this);
	}
	inline const Fle_Size2<_T>& operator = (const Fle_Size2<_T>& _s)
	{
		if (this == &_s)
			return *this; // return reference to this (no copy)

		width = _s.width;
		height = _s.height;
		return *this;
	}
	inline const Fle_Size2<_T>& operator += (const Fle_Size2<_T>& _s)
	{
		width += _s.width;
		height += _s.height;
		return *this;
	}
	inline const Fle_Size2<_T>& operator -= (const Fle_Size2<_T>& _s)
	{
		width -= _s.width;
		height -= _s.height;
		return *this;
	}
	inline const Fle_Size2<_T>& operator *= (const _T& _v)
	{
		width *= _v;
		height *= _v;
		return *this;
	}
	inline const Fle_Size2<_T>& operator /= (const _T& _v)
	{
		const _T r = static_cast<_T>(1 / _v);
		width *= r;
		height *= r;
		return *this;
	}
	inline const Fle_Size2<_T> operator * (const _T _v) const
	{
		return Fle_Size2<_T>(width * _v, height * _v);
	}
	inline friend const Fle_Size2<_T> operator * (const _T& _value, const Fle_Size2<_T>& _s)
	{
		return _value * _s;
	}
	inline const Fle_Size2<_T> operator + (const _T _v) const
	{
		return Fle_Size2<_T>(width + _v, height + _v);
	}
	inline const Fle_Size2<_T> operator - (const _T _v) const
	{
		return Fle_Size2<_T>(width - _v, height - _v);
	}
	inline const Fle_Size2<_T> operator / (_T _v) const
	{
		_v = static_cast<_T>(1 / _v);
		return Fle_Size2<_T>(width * _v, height * _v);
	}

	inline const bool operator >= (_T _v) const
	{
		if (width >= _v && height >= _v)
			return true;
		return false;
	}
	inline const bool operator <= (_T _v) const
	{
		if (width <= _v && height <= _v)
			return true;
		return false;
	}
	inline const bool operator == (_T _v) const
	{
		if (width == _v && height == _v)
			return true;
		return false;
	}
	inline const bool operator != (_T _v) const
	{
		if ((width != _v) && (height != _v))
			return true;
		return false;
	}
	inline const bool operator > (_T _v) const
	{
		if (width > _v && height > _v)
			return true;
		return false;
	}
	inline const bool operator < (_T _v) const
	{
		if (width < _v && height < _v)
			return true;
		return false;
	}
	inline _T& operator [](long _i)
	{
		return ((&width)[_i]);
	}
	inline const _T& operator [](long _i) const
	{
		return ((&width)[_i]);
	}

	// Description:
	// Prefix increment operator.
	const Fle_Size2<_T>& operator ++ ()
	{
		width++; height++;
		return *this;
	}
	// Description:
	// Postfix increment operator.
	const Fle_Size2<_T> operator ++ (int)
	{
		Fle_Size2<_T> temp(*this);
		++*this;
		return temp;
	}
	// Description:
	// Prefix decrement operator.
	const Fle_Size2<_T>& operator -- ()
	{
		width--; height--;
		return *this;
	}
	// Description:
	// Postfix decrement operator.
	const Fle_Size2<_T> operator -- (int)
	{
		Fle_Size2<_T> temp(*this);
		--*this;
		return temp;
	}
};

template FL_ESSENTIALS_EXPORT class Fle_Size2<int>;
template FL_ESSENTIALS_EXPORT class Fle_Size2<unsigned int>;
template FL_ESSENTIALS_EXPORT class Fle_Size2<float>;
template FL_ESSENTIALS_EXPORT class Fle_Size2<double>;

typedef Fle_Size2<int> Fle_Size2i;
typedef Fle_Size2<unsigned int> Fle_Size2u;
typedef Fle_Size2<float> Fle_Size2f;
typedef Fle_Size2<double> Fle_Size2d;
typedef Fle_Size2i Fle_Size;

}

#endif // Fle_Size_h__