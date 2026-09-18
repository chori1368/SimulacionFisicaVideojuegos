#pragma once

#include <cmath>
#include <cassert>
#include <PxPhysics.h>

class Vector3D
{
private:
	float x, y, z;
public:
	Vector3D() noexcept: x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) noexcept : x(x), y(y), z(z) {};
	Vector3D(float v) noexcept : x(v), y(v), z(v) {};
	Vector3D(physx::PxVec3 pvec) noexcept : x(pvec.x), y(pvec.y), z(pvec.z) {};

	void setX(float _x) noexcept { x = _x; }
	void setY(float _y) noexcept { y = _y; }
	void setZ(float _z) noexcept { z = _z; }
	float getX() const noexcept { return x; }
	float getY() const noexcept { return y; }
	float getZ() const noexcept { return z; }

	float magnitude()		const noexcept { return std::sqrt(x * x + y * y + z * z); }
	//float magnitudeSqr()	const noexcept { return x * x + y * y + z * z; }

	void normalizethis() {

		float mod = magnitude();
		assert(mod != 0, "Can't normalize vector with module = 0");

		x /= mod; y /= mod; z /= mod;
	}
	Vector3D normalize() const {

		float mod = magnitude();
		assert(mod != 0, "Can't normalize vector with module = 0");

		return Vector3D(x / mod, y / mod, z / mod);
	}
	float dot(const Vector3D& v) const {
			return x * v.x + y * v.y + z * v.z;
	}
	Vector3D cross(const Vector3D& v) const {
		return Vector3D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}
	Vector3D& operator= (const Vector3D& v) noexcept
	{
		if (&v == this) return *this;

		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}
	Vector3D& operator+ (const Vector3D& v) noexcept
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	Vector3D& operator- (const Vector3D& v) noexcept
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}
	Vector3D& operator* (float scalar) noexcept
	{
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}
	void operator +=(const Vector3D& v) noexcept
	{
		x = x + v.x;
		y = y + v.y;
		z = z + v.z;
	}
	operator physx::PxVec3 () {
		return physx::PxVec3(x, y, z);
	}
	//physx::PxVec3& Vec3toPxVec3(const Vector3D& v) {
	//	return physx::PxVec3(x, y, z);
	//}
};