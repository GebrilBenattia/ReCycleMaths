#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <ostream>

class Vector2;
class Vector3;

class Vector4 // ~15 MINUTES
{
private:

	mutable float m_SquaredMagnitude = 0.f;
	mutable float m_Magnitude = 0.f;
	mutable float m_IMagnitude = 0.f;
	mutable bool m_IsMagnitudeDirty = true;

	[[nodiscard]] const float ComputeSquaredMagnitude() const;
	[[nodiscard]] const float ComputeMagnitude() const;
	[[nodiscard]] const Vector4 ComputeNormalized() const;

public:

	float x, y, z, w;

	static const Vector4 zero;
	static const Vector4 one;
	static const Vector4 negativeInfinity;
	static const Vector4 positiveInfinity;

	constexpr Vector4();
	constexpr Vector4(const float& _XYZW);
	constexpr Vector4(const float& _X, const float& _Y, const float& _Z, const float& _W);
	constexpr Vector4(const Vector2& _V1, const Vector2& _V2);
	constexpr Vector4(const Vector3& _V, const float& _W);
	Vector4(const Vector4& _Other);
	Vector4(Vector4&& _Other) noexcept;

	[[nodiscard]] static Vector4 Add(const Vector4& _V, const float& _Factor);
	[[nodiscard]] static Vector4 AddComponentWise(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] static Vector4 Subtract(const Vector4& _V, const float& _Factor);
	[[nodiscard]] static Vector4 SubtractComponentWise(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] static Vector4 Scale(const Vector4& _V, const float& _Factor);
	[[nodiscard]] static Vector4 ScaleComponentWise(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] static Vector4 Divide(const Vector4& _V, const float& _Factor);
	[[nodiscard]] static Vector4 DivideComponentWise(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] static float DotProduct(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] static const Vector4 Lerp(const Vector4& _From, const Vector4& _To, const float& _T);
	[[nodiscard]] static const Vector4 LerpUnclamped(const Vector4& _From, const Vector4& _To, const float& _T);

	[[nodiscard]] static const Vector4 Project(const Vector4& _v, const Vector4& _u);

	[[nodiscard]] static const Vector4 Min(const Vector4& _A, const Vector4& _B);
	[[nodiscard]] static const Vector4 Max(const Vector4& _A, const Vector4& _B);

	[[nodiscard]] const float SquaredMagnitude() const;
	[[nodiscard]] const float Magnitude() const;

	[[nodiscard]] const float SquaredDistance() const;
	[[nodiscard]] const float Distance() const;

	[[nodiscard]] const Vector4 Normalize() const;

	[[nodiscard]] Vector4 operator+(const float& _Factor) const;
	[[nodiscard]] Vector4 operator+(const Vector4& _Other) const;
	Vector4& operator+=(const float& _Factor);
	Vector4& operator+=(const Vector4& _Other);

	[[nodiscard]] Vector4 operator-(const float& _Factor) const;
	[[nodiscard]] Vector4 operator-(const Vector4& _Other) const;
	Vector4& operator-=(const float& _Factor);
	Vector4& operator-=(const Vector4& _Other);

	[[nodiscard]] Vector4 operator*(const float& _Factor) const;
	[[nodiscard]] Vector4 operator*(const Vector4& _Other) const;
	Vector4& operator*=(const float& _Factor);
	Vector4& operator*=(const Vector4& _Other);

	[[nodiscard]] Vector4 operator/(const float& _Factor) const;
	[[nodiscard]] Vector4 operator/(const Vector4& _Other) const;
	Vector4& operator/=(const float& _Factor);
	Vector4& operator/=(const Vector4& _Other);

	[[nodiscard]] bool operator<(const Vector4& _Other) const;
	[[nodiscard]] bool operator>(const Vector4& _Other) const;

	[[nodiscard]] bool operator<=(const Vector4& _Other) const;
	[[nodiscard]] bool operator>=(const Vector4& _Other) const;

	[[nodiscard]] bool operator==(const Vector4& _Other) const;
	[[nodiscard]] bool operator!=(const Vector4& _Other) const;

	Vector4& operator=(Vector4&& _Other) noexcept;
	Vector4& operator=(const Vector4& _Other);

	[[nodiscard]] const float& operator[](int _Index) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector4& _V)
	{
		return os << "( " << _V.x << ", " << _V.y << ", " << _V.z << ", " << _V.w << " )";
	}
};

#include "Vector4.inl"

#endif