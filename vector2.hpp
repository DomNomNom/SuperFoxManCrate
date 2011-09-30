/**********************************************\
| This code is adapted from SFML 2.            |
| Here is it's license:                        |
\**********************************************/


//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//


#ifndef VECTOR2_HPP
#define VECTOR2_HPP

/////////////////////////////////////////////////////////
///
/// vector2 is a simple class that defines a mathematical
/// vector with two coordinates (x and y). It can be used to
/// represent anything that has two dimensions: a size, a point,
/// a velocity, etc.
///
/// The template parameter T is the type of the coordinates. It
/// can be any type that supports arithmetic operations (+, -, /, *)
/// and comparisons (==, !=), for example int or float.
///
/// You generally don't have to care about the templated form (vector2<T>),
/// the two most common specializations have special typedefs:
/// vector2<float> is vector2f
/// vector2<int> is vector2i
///
/// The vector2 class has a small and simple interface, its x and y members
/// can be accessed directly (there's no accessor like SetX(), GetX()).
///
/// Usage example:
/// vector2f v1(16.5f, 24.f);
/// v1.x = 18.2f;
/// float y = v1.y;
///
/// vector2f v2 = v1 * 5.f;
/// vector2f v3;
/// v3 = v1 + v2;
///
/// bool different = (v2 != v3);
///
/////////////////////////////////////////////////////////

template <typename T>
class vector2{
public :
  // Member data
  T x; // X coordinate of the vector
  T y; // Y coordinate of the vector
  
  // Constructors
  vector2();         // the default constructor
  vector2(T X, T Y); // Construct the vector from its coordinates

  template <typename U>
  explicit vector2(const vector2<U>& vector); // Consruct the vector from another vector and typecast the contents


  /// functions modifying the vector while assuming a rotation by an angle (angle: multiples of 90 within 0-360) 
  void add(const vector2<T> &v, int angle);
  void add(T dX, T dY, int angle);
  
  void set(T X, T Y, int angle);
  void setX(T X, int angle);
  void setY(T Y, int angle);
  
  T getX(int angle);
  T getY(int angle);
};



/*=============== operator declarations ===============*/

/// Overload of unary operator -
template <typename T>
vector2<T> operator -(const vector2<T>& right);

/// Overload of binary operator +=
template <typename T>
vector2<T>& operator +=(vector2<T>& left, const vector2<T>& right);

/// Overload of binary operator -
template <typename T>
vector2<T>& operator -=(vector2<T>& left, const vector2<T>& right);

/// Overload of binary operator +
template <typename T>
vector2<T> operator +(const vector2<T>& left, const vector2<T>& right);

/// Overload of binary operator -
template <typename T>
vector2<T> operator -(const vector2<T>& left, const vector2<T>& right);

/// Overload of binary operator *
template <typename T>
vector2<T> operator *(const vector2<T>& left, T right);

/// Overload of binary operator *
template <typename T>
vector2<T> operator *(T left, const vector2<T>& right);

/// Overload of binary operator *=
template <typename T>
vector2<T>& operator *=(vector2<T>& left, T right);

/// Overload of binary operator /
template <typename T>
vector2<T> operator /(const vector2<T>& left, T right);

/// Overload of binary operator /=
template <typename T>
vector2<T>& operator /=(vector2<T>& left, T right);


/*=============== Comparator declarations ===============*/

/// Overload of binary operator ==
template <typename T>
bool operator ==(const vector2<T>& left, const vector2<T>& right);

/// Overload of binary operator !=
template <typename T>
bool operator !=(const vector2<T>& left, const vector2<T>& right);



#include "vector2.inl"

// Define the most common types
typedef vector2<int>          vector2i;
typedef vector2<unsigned int> vector2u;
typedef vector2<float>        vector2f;



#endif
