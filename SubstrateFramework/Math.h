#pragma once

#include <cmath>

#include "Logger.h"

constexpr float PI = 3.14159265f;

template<class type>
class Vec3D
{
private:
	type x;
	type y;
	type z;

public:
	Vec3D<type>(type xin, type yin, type zin);

	Vec3D<type>();

	virtual ~Vec3D<type>() {}

	Vec3D<type> operator+(const Vec3D<type> &vin) const;

	Vec3D<type> operator-(const Vec3D<type> &vin) const;

	Vec3D<type> operator*(const type sin) const;

	Vec3D<type> crossProd(const Vec3D<type> &vin) const;

	type dotProd(const Vec3D<type> &vin) const;

	type magSqrd() const;

	type mag() const;

	void print();
};

template<class type>
class Vec4D
{
private:
	type x;
	type y;
	type z;
	type w;
	
public:
	Vec4D<type>(type xin, type yin, type zin, type win);

	Vec4D<type>();

	virtual ~Vec4D<type>();

	Vec4D<type> operator+(const Vec4D<type> &vin) const;

	Vec4D<type> operator-(const Vec4D<type> &vin) const;

	Vec4D<type> operator*(const type sin) const;

	type dotProd(const Vec4D<type> &vin) const;
	
	type magSqrd() const;

	type mag() const;

	void print();
};

template<class type>
class Mat3x3
{
private:
	type element[3][3];
public:
	Mat3x3(type ein[][3]);
	
	Mat3x3();

	virtual ~Mat3x3();

	Mat3x3<type> operator+(Mat3x3<type> &min) const;

	Mat3x3<type> operator-(Mat3x3<type> &min) const;

	Mat3x3<type> operator*(Mat3x3<type> &min) const;

	Mat3x3<type> operator*(type sin) const;

	Mat3x3<type> transpose() const;

	void print() const;

	static Mat3x3 getRotX(type thetaDeg);

	static Mat3x3 getRotY(type thetaDeg);

	static Mat3x3 getRotZ(type thetaDeg);
};