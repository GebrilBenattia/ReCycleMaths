#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <ostream>

class Vector2;

class Vector3 // ~1-2 HOURS
{
private:

	mutable float m_SquaredMagnitude = 0.f;
	mutable float m_Magnitude = 0.f;
	mutable float m_IMagnitude = 0.f;
	mutable bool m_IsMagnitudeDirty = true;

	[[nodiscard]] const float ComputeSquaredMagnitude() const;
	[[nodiscard]] const float ComputeMagnitude() const;
	[[nodiscard]] const Vector3 ComputeNormalized() const;

public:

	float x, y, z;

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 left;
	static const Vector3 right;
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 front;
	static const Vector3 back;
	static const Vector3 negativeInfinity;
	static const Vector3 positiveInfinity;

	constexpr Vector3();
	constexpr Vector3(const float& _XYZ);
	constexpr Vector3(const float& _X, const float& _Y);
	constexpr Vector3(const float& _X, const float& _Y, const float& _Z);
	constexpr Vector3(const Vector2& _V);
	constexpr Vector3(const Vector2& _V, const float& _Z);
	constexpr Vector3(const float& _X, const Vector2& _V);
	Vector3(const Vector3& _Other);
	Vector3(Vector3&& _Other) noexcept;

	~Vector3() = default;

	[[nodiscard]] static Vector3 Add(const Vector3& _V, const float& _Factor);
	[[nodiscard]] static Vector3 AddComponentWise(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] static Vector3 Subtract(const Vector3& _V, const float& _Factor);
	[[nodiscard]] static Vector3 SubtractComponentWise(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] static Vector3 Scale(const Vector3& _V, const float& _Factor);
	[[nodiscard]] static Vector3 ScaleComponentWise(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] static Vector3 Divide(const Vector3& _V, const float& _Factor);
	[[nodiscard]] static Vector3 DivideComponentWise(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] static float DotProduct(const Vector3& _A, const Vector3& _B);
	[[nodiscard]] static Vector3 CrossProduct(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] static const float Angle(const Vector3& _From, const Vector3& _To);
	[[nodiscard]] static const float SignedAngle(const Vector3& _From, const Vector3& _To, const Vector3& _Axis);

	[[nodiscard]] static const Vector3 Lerp(const Vector3& _From, const Vector3& _To, const float& _T);
	[[nodiscard]] static const Vector3 LerpUnclamped(const Vector3& _From, const Vector3& _To, const float& _T);

	[[nodiscard]] static const Vector3 Project(const Vector3& _v, const Vector3& _u);

	[[nodiscard]] static const Vector3 ClampMagnitude(const Vector3& _V, const float& _MaxLength);

	[[nodiscard]] static const Vector3 Perpendicular(const Vector3& _V);
	[[nodiscard]] static const Vector3 Reflect(const Vector3& _Incoming, const Vector3& _Normal);

	[[nodiscard]] static const Vector3 Min(const Vector3& _A, const Vector3& _B);
	[[nodiscard]] static const Vector3 Max(const Vector3& _A, const Vector3& _B);

	[[nodiscard]] const float SquaredMagnitude() const;
	[[nodiscard]] const float Magnitude() const;

	[[nodiscard]] const float SquaredDistance() const;
	[[nodiscard]] const float Distance() const;

	[[nodiscard]] const Vector3 Normalize() const;

	static const void OrthoNormalize(Vector3& _Normal, Vector3& _Tangent);
	static const void OrthoNormalize(Vector3& _Normal, Vector3& _Tangent, Vector3& _Binormal);

	[[nodiscard]] static const Vector3 ProjectOnPlane(const Vector3& _V, const Vector3& _PlaneNormal);

	[[nodiscard]] Vector3 operator+(const float& _Factor) const;
	[[nodiscard]] Vector3 operator+(const Vector3& _Other) const;
	Vector3& operator+=(const float& _Factor);
	Vector3& operator+=(const Vector3& _Other);

	[[nodiscard]] Vector3 operator-(const float& _Factor) const;
	[[nodiscard]] Vector3 operator-(const Vector3& _Other) const;
	Vector3& operator-=(const float& _Factor);
	Vector3& operator-=(const Vector3& _Other);

	[[nodiscard]] Vector3 operator*(const float& _Factor) const;
	[[nodiscard]] Vector3 operator*(const Vector3& _Other) const;
	Vector3& operator*=(const float& _Factor);
	Vector3& operator*=(const Vector3& _Other);

	[[nodiscard]] Vector3 operator/(const float& _Factor) const;
	[[nodiscard]] Vector3 operator/(const Vector3& _Other) const;
	Vector3& operator/=(const float& _Factor);
	Vector3& operator/=(const Vector3& _Other);

	[[nodiscard]] bool operator<(const Vector3& _Other) const;
	[[nodiscard]] bool operator>(const Vector3& _Other) const;

	[[nodiscard]] bool operator<=(const Vector3& _Other) const;
	[[nodiscard]] bool operator>=(const Vector3& _Other) const;

	[[nodiscard]] bool operator==(const Vector3& _Other) const;
	[[nodiscard]] bool operator!=(const Vector3& _Other) const;

	Vector3& operator=(Vector3&& _Other) noexcept;
	Vector3& operator=(const Vector3& _Other);

	[[nodiscard]] const float& operator[](int _Index) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector3& _V)
	{
		return os << "( " << _V.x << ", " << _V.y << ", " << _V.z << " )";
	}
};

#include "Vector3.inl"

#endif