#include "Math.h"

namespace ssfw
{
	template<class type>
	Vec3D<type>::Vec3D(type xin, type yin, type zin)
	{
		x = xin;
		y = yin;
		z = zin;
	}

	template<class type>
	Vec3D<type>::Vec3D() { x = y = z = 0; }

	template<class type>
	Vec3D<type>::~Vec3D() {}

	template<class type>
	Vec3D<type> Vec3D<type>::operator+(const Vec3D<type> &vin) const
	{
		return Vec3D<type>(x + vin.x, y + vin.y, z + vin.z);
	}

	template<class type>
	Vec3D<type> Vec3D<type>::operator-(const Vec3D<type> &vin) const
	{
		return Vec3D<type>(x - vin.x, y - vin.y, z - vin.z);
	}

	template<class type>
	Vec3D<type> Vec3D<type>::operator*(const type sin) const
	{
		return Vec3D<type>(x*sin, y*sin, z*sin);
	}

	template<class type>
	Vec3D<type> Vec3D<type>::crossProd(const Vec3D<type> &vin) const
	{
		return Vec3D<type>((y*vin.z) - (z*vin.y), (z*vin.x) - (x*vin.z), (x*vin.y) - (y*vin.x));
	}

	template<class type>
	type Vec3D<type>::dotProd(const Vec3D<type> &vin) const
	{
		return ((x*vin.x) + (y*vin.y) + (z*vin.z));
	}

	template<class type>
	type Vec3D<type>::magSqrd() const
	{
		return ((x*x) + (y*y) + (z*z));
	}

	template<class type>
	type Vec3D<type>::mag() const
	{
		return std::sqrt(magSqrd());
	}

	template<class type>
	void Vec3D<type>::print()
	{
		std::string t = "X : " + std::to_string(x) + " Y : " + std::to_string(y) + " Z : " + std::to_string(z);
		Logger::printMsg(t, 0);
	}

	template<class type>
	Vec4D<type>::Vec4D(type xin, type yin, type zin, type win)
	{
		x = xin;
		y = yin;
		z = zin;
		w = win;
	}

	template<class type>
	Vec4D<type>::Vec4D()
	{
		x = y = z = w = 0;
	}

	template<class type>
	Vec4D<type>::~Vec4D()
	{
	}

	template<class type>
	Vec4D<type> Vec4D<type>::operator+(const Vec4D<type> &vin) const
	{
		return Vec4D<type>(x + vin.x, y + vin.y, z + vin.z, w + vin.w);
	}

	template<class type>
	Vec4D<type> Vec4D<type>::operator-(const Vec4D<type> &vin) const
	{
		return Vec4D<type>(x - vin.x, y - vin.y, z - vin.z, w - vin.w);
	}

	template<class type>
	Vec4D<type> Vec4D<type>::operator*(const type sin) const
	{
		return Vec4D<type>(x*sin, y*sin, z*sin, w*sin);
	}

	template<class type>
	type Vec4D<type>::dotProd(const Vec4D<type> &vin) const
	{
		return ((x*vin.x) + (y*vin.y) + (z*vin.z) + (w*vin.w));
	}

	template<class type>
	type Vec4D<type>::magSqrd() const
	{
		return ((x*x) + (y*y) + (z*z) + (w*w));
	}

	template<class type>
	type Vec4D<type>::mag() const
	{
		return std::sqrt(magSqrd());
	}

	template<class type>
	void Vec4D<type>::print()
	{
		std::string t = "X : " + std::to_string(x) + " Y : " + std::to_string(y) + " Z : " + std::to_string(z) + " W : " + std::to_string(w);
		Logger::printMsg(t, 0);
	}

	template<class type>
	Mat3x3<type>::Mat3x3(type ein[][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = ein[i][j];
	}

	template<class type>
	Mat3x3<type>::Mat3x3()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = 0;
	}

	template<class type>
	Mat3x3<type>::~Mat3x3() { }

	template<class type>
	Mat3x3<type> Mat3x3<type>::operator+(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] + min.element[i][j];
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::operator-(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] - min.element[i][j];
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::operator*(Mat3x3<type> &min) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					mout.element[i][j] += element[i][k] * min.element[k][j];
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::operator*(type sin) const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[i][j] * sin;
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::transpose() const
	{
		Mat3x3<type> mout;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				mout.element[i][j] = element[j][i];
		return mout;
	}

	template<class type>
	void Mat3x3<type>::print() const
	{
		std::string msg;
		for (int i = 0; i < 3; i++)
		{
			msg.append("|\t");
			for (int j = 0; j < 3; j++)
			{
				msg.append(std::to_string(element[i][j]));
				msg.append("\t");
			}
			msg.append("|\n");
		}
		Logger::printMsg(msg, 1);
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::getRotX(type thetaDeg)
	{
		type thetaRad = thetaDeg * PI / 180.f;
		Mat3x3<type> mout;
		mout.element[0][0] = 1;
		mout.element[1][1] = cos(thetaRad);
		mout.element[1][2] = -sin(thetaRad);
		mout.element[2][1] = sin(thetaRad);
		mout.element[2][2] = cos(thetaRad);
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::getRotY(type thetaDeg)
	{
		type thetaRad = thetaDeg * PI / 180.f;
		Mat3x3<type> mout;
		mout.element[0][0] = cos(thetaRad);
		mout.element[0][2] = sin(thetaRad);
		mout.element[1][1] = 1;
		mout.element[2][0] = -sin(thetaRad);
		mout.element[2][2] = cos(thetaRad);
		return mout;
	}

	template<class type>
	Mat3x3<type> Mat3x3<type>::getRotZ(type thetaDeg)
	{
		type thetaRad = thetaDeg * PI / 180.f;
		Mat3x3<type> mout;
		mout.element[0][0] = cos(thetaRad);
		mout.element[0][1] = -sin(thetaRad);
		mout.element[1][0] = sin(thetaRad);
		mout.element[1][1] = cos(thetaRad);
		mout.element[2][2] = 1;
		return mout;
	}

	template<class type>
	Mat4x4<type>::Mat4x4(type ein[][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				element[i][j] = ein[i][j];
	}

	template<class type>
	Mat4x4<type>::Mat4x4()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				element[i][j] = 0;
	}

	//This constructor assumes the 4x4 matrix will be a tranformation matrix
	template<class type>
	Mat4x4<type>::Mat4x4(Mat3x3<type> min, Vec3D<type> vin)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = min.getElement(i, j);
		
		element[3][0] = element[3][1] = element[3][2] = 0;
		
		element[0][3] = vin.getX();
		element[1][3] = vin.getY();
		element[2][3] = vin.getZ();
		element[3][3] = 1;
	}

	template<class type>
	Mat4x4<type>::Mat4x4(Mat3x3<type> min, Vec4D<type> vin)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				element[i][j] = min.getElement(i, j);

		element[3][0] = element[3][1] = element[3][2] = 0;

		element[0][3] = vin.getX();
		element[1][3] = vin.getY();
		element[2][3] = vin.getZ();
		element[3][3] = vin.getW();
	}

	template<class type>
	Mat4x4<type>::~Mat4x4() { }

	template<class type>
	Mat4x4<type> Mat4x4<type>::operator+(Mat4x4<type> &min) const
	{
		Mat4x4<type> mout;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mout.element[i][j] = element[i][j] + min.element[i][j];
		return mout;
	}

	template<class type>
	Mat4x4<type> Mat4x4<type>::operator-(Mat4x4<type> &min) const
	{
		Mat4x4<type> mout;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mout.element[i][j] = element[i][j] - min.element[i][j];
		return mout;
	}

	template<class type>
	Mat4x4<type> Mat4x4<type>::operator*(Mat4x4<type> &min) const
	{
		Mat4x4<type> mout;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					mout.element[i][j] += element[i][k] * min.element[k][j];
		return mout;
	}

	template<class type>
	Mat4x4<type> Mat4x4<type>::operator*(type sin) const
	{
		Mat4x4<type> mout;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mout.element[i][j] = element[i][j] * sin;
		return mout;
	}

	template<class type>
	Mat4x4<type> Mat4x4<type>::transpose() const
	{
		Mat4x4<type> mout;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mout.element[i][j] = element[j][i];
		return mout;
	}

	template<class type>
	void Mat4x4<type>::print() const
	{
		std::string msg;
		for (int i = 0; i < 4; i++)
		{
			msg.append("|\t");
			for (int j = 0; j < 4; j++)
			{
				msg.append(std::to_string(element[i][j]));
				msg.append("\t");
			}
			msg.append("|\n");
		}
		Logger::printMsg(msg, 1);
	}

	template class Vec3D<float>;
	template class Vec4D<float>;
	template class Mat3x3<float>;
	template class Mat4x4<float>;
	template class Vec3D<int>;
	template class Vec4D<int>;
	template class Mat3x3<int>;
	template class Mat4x4<int>;
}