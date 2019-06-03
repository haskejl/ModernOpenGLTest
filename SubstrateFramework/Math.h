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
	Vec3D<type>(type xin, type yin, type zin)
	{
		x = xin;
		y = yin;
		z = zin;
	}

	Vec3D<type>() { x = y = z = 0; }

	virtual ~Vec3D<type>() {}

	Vec3D<type> operator+(const Vec3D<type> &vin) const
	{
		return Vec3D<type>(x + vin.x, y + vin.y, z + vin.z);
	}

	Vec3D<type> operator-(const Vec3D<type> &vin) const
	{
		return Vec3D<type>(x - vin.x, y - vin.y, z - vin.z);
	}

	Vec3D<type> operator*(const type sin) const
	{
		return Vec3D<type>(x*sin, y*sin, z*sin);
	}

	Vec3D<type> crossProd(const Vec3D<type> &vin) const
	{
		return Vec3D<type>((y*vin.z) - (z*vin.y), (z*vin.x) - (x*vin.z), (x*vin.y) - (y*vin.x));
	}

	type dotProd(const Vec3D<type> &vin) const
	{
		return ((x*vin.x) + (y*vin.y) + (z*vin.z));
	}

	type magSqrd() const
	{
		return ((x*x) + (y*y) + (z*z));
	}

	type mag() const
	{
		return std::sqrt(magSqrd());
	}

	void print()
	{
		std::string t = "X : " + std::to_string(x) + " Y : " + std::to_string(y) + " Z : " + std::to_string(z);
		Logger::printMsg(t, 0);
	}
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
	Vec4D<type>(type xin, type yin, type zin, type win)
	{
		x = xin;
		y = yin;
		z = zin;
		w = win;
	}

	Vec4D<type>()
	{
		x = y = z = w = 0;
	}

	virtual ~Vec4D<type>()
	{
	}

	Vec4D<type> operator+(const Vec4D<type> &vin) const
	{
		return Vec4D<type>(x + vin.x, y + vin.y, z + vin.z, w + vin.w);
	}

	Vec4D<type> operator-(const Vec4D<type> &vin) const
	{
		return Vec4D<type>(x - vin.x, y - vin.y, z - vin.z, w - vin.w);
	}

	Vec4D<type> operator*(const type sin) const
	{
		return Vec4D<type>(x*sin, y*sin, z*sin, w*sin);
	}

	type dotProd(const Vec4D<type> &vin) const
	{
		return ((x*vin.x) + (y*vin.y) + (z*vin.z) + (w*vin.w));
	}
	
	type magSqrd() const
	{
		return ((x*x) + (y*y) + (z*z) + (w*w));
	}

	type mag() const
	{
		return std::sqrt(magSqrd());
	}

	void print()
	{
		std::string t = "X : " + std::to_string(x) + " Y : " + std::to_string(y) + " Z : " + std::to_string(z) + " W : " + std::to_string(w);
		Logger::printMsg(t, 0);
	}
};

template<class type>
class Mat3x3
{
private:
	type element[3][3];
public:
	Mat3x3(type ein[][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = ein[i][j];
	}
	
	Mat3x3()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = 0;
	}

	virtual ~Mat3x3() { }

	Mat3x3<type> operator+(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] + min.element[i][j];
		return mout;
	}

	Mat3x3<type> operator-(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] - min.element[i][j];
		return mout;
	}

	Mat3x3<type> operator*(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for(int k=0; k<3; k++)
					mout.element[i][j] += element[i][k] * min.element[k][j];
		return mout;
	}

	Mat3x3<type> operator*(type sin) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] * sin;
		return mout;
	}

	Mat3x3<type> transpose() const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout[i][j] = element[j][i];
		return mout;
	}

	void print() const
	{
		std::string msg;
		for (int i = 0; i < 3; i++)
		{
			msg.append("|\t");
			for (int j = 0; j < 3; j++)
			{
				msg.append( std::to_string(element[i][j]) );
				msg.append("\t");
							}
			msg.append("|\n");
		}
		Logger::printMsg(msg, 1);
	}

	static Mat3x3 getRotX(type thetaDeg)
	{
		type thetaRad = thetaDeg * PI / 180;
		Mat3x3<type> mout;
		mout.element[0][0] = 1;
		mout.element[1][1] = cos(thetaRad);
		mout.element[1][2] = -sin(thetaRad);
		mout.element[2][1] = sin(thetaRad);
		mout.element[2][2] = cos(thetaRad);
		return mout;
	}
};