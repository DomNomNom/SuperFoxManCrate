/**********************************************\
| This code is adapted from SFML 2.            |
| Here is it's license:                        |
\**********************************************/

////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////


/*=============== Constructors ===============*/
template <typename T>
inline vector2<T>::vector2() : x(0), y(0) { }

template <typename T>
inline vector2<T>::vector2(T X, T Y) : x(X), y(Y) { }

template <typename T>
template <typename U>
inline vector2<T>::vector2(const vector2<U>& vector) :
 x(static_cast<T>(vector.x)), 
 y(static_cast<T>(vector.y))
{ }


/*=============== Angle functions ===============*/

template <typename T>
void vector2<T>::add(T dX, T dY, int angle) {
  switch (angle) {
    case 0*90:
      x += dX;
      y += dY;
      break;
    case 1*90:
      x += dY;
      y -= dX;
      break;
    case 2*90:
      x -= dX;
      y -= dY;
      break;
    case 3*90:
      x -= dY;
      y += dX;
      break;    
  }
}

template <typename T>
void vector2<T>::set(T X, T Y, int angle) {
  setX(X, angle);
  setY(Y, angle);
}

template <typename T>
void vector2<T>::setX(T X, int angle) {
  switch (angle) {
    case 0*90:  x =  X;  break;
    case 1*90:  y = -X;  break;
    case 2*90:  x = -X;  break;
    case 3*90:  y =  X;  break;
  }
}

template <typename T>
void vector2<T>::setY(T Y, int angle) {
  switch (angle) {
    case 0*90:  y =  Y;  break;
    case 1*90:  x = -Y;  break;  
    case 2*90:  y = -Y;  break;
    case 3*90:  x =  Y;  break;
  }
}

template <typename T>
T vector2<T>::getX(int angle) {
  switch (angle) {
    case 0*90:  return  x;
    case 1*90:  return  y;
    case 2*90:  return -x;
    case 3*90:  return -y;
  }
}

template <typename T>
T vector2<T>::getY(int angle) {
  switch (angle) {
    case 0*90:  return  y;
    case 1*90:  return  x;
    case 2*90:  return -y;
    case 3*90:  return -x;
  }
}



/*=============== Operator defenitions ===============*/

template <typename T>
inline vector2<T> operator -(const vector2<T>& right) {
  return vector2<T>(-right.x, -right.y);
}

template <typename T>
inline vector2<T>& operator +=(vector2<T>& left, const vector2<T>& right) {
  left.x += right.x;
  left.y += right.y;

  return left;
}

template <typename T>
inline vector2<T>& operator -=(vector2<T>& left, const vector2<T>& right) {
  left.x -= right.x;
  left.y -= right.y;

  return left;
}

template <typename T>
inline vector2<T> operator +(const vector2<T>& left, const vector2<T>& right) {
  return vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline vector2<T> operator -(const vector2<T>& left, const vector2<T>& right) {
  return vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline vector2<T> operator *(const vector2<T>& left, T right) {
  return vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline vector2<T> operator *(T left, const vector2<T>& right) {
  return vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline vector2<T>& operator *=(vector2<T>& left, T right) {
  left.x *= right;
  left.y *= right;

  return left;
}

template <typename T>
inline vector2<T> operator /(const vector2<T>& left, T right) {
  return vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline vector2<T>& operator /=(vector2<T>& left, T right) {
  left.x /= right;
  left.y /= right;

  return left;
}


/*=============== Comparator defenitions ===============*/

template <typename T>
inline bool operator ==(const vector2<T>& left, const vector2<T>& right) {
  return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const vector2<T>& left, const vector2<T>& right) {
  return (left.x != right.x) || (left.y != right.y);
}

template <typename T>
void vector2<T>::add(const vector2<T> &v, int angle) {
  add(v.x, v.y, angle);
}
