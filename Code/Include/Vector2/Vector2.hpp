#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <ostream>

class Vector2 // ~7-8 HOURS
{
private:

	mutable float m_SquaredMagnitude = 0.f;
	mutable float m_Magnitude = 0.f;
	mutable float m_IMagnitude = 0.f;
	mutable bool m_IsMagnitudeDirty = true;

	[[nodiscard]] const float ComputeSquaredMagnitude() const;
	[[nodiscard]] const float ComputeMagnitude() const;
	[[nodiscard]] const Vector2 ComputeNormalized() const;

public:

	float x, y;

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 left;
	static const Vector2 right;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 negativeInfinity;
	static const Vector2 positiveInfinity;

	constexpr Vector2();
	constexpr Vector2(const float& _XY);
	constexpr Vector2(const float& _X, const float& _Y);
	Vector2(const Vector2& _Other);
	Vector2(Vector2&& _Other) noexcept;

	~Vector2() = default;

	[[nodiscard]] static Vector2 Add(const Vector2& _V, const float& _Factor);
	[[nodiscard]] static Vector2 AddComponentWise(const Vector2& _A, const Vector2& _B);

	[[nodiscard]] static Vector2 Subtract(const Vector2& _V, const float& _Factor);
	[[nodiscard]] static Vector2 SubtractComponentWise(const Vector2& _A, const Vector2& _B);
	
	[[nodiscard]] static Vector2 Scale(const Vector2& _V, const float& _Factor);
	[[nodiscard]] static Vector2 ScaleComponentWise(const Vector2& _A, const Vector2& _B);

	[[nodiscard]] static Vector2 Divide(const Vector2& _V, const float& _Factor);
	[[nodiscard]] static Vector2 DivideComponentWise(const Vector2& _A, const Vector2& _B);

	[[nodiscard]] static float DotProduct(const Vector2& _A, const Vector2& _B);
	[[nodiscard]] static float CrossProduct(const Vector2& _A, const Vector2& _B);

	[[nodiscard]] static const float Angle(const Vector2& _From, const Vector2& _To);
	[[nodiscard]] static const float SignedAngle(const Vector2& _From, const Vector2& _To);

	[[nodiscard]] static const Vector2 Lerp(const Vector2& _From, const Vector2& _To, const float& _T);
	[[nodiscard]] static const Vector2 LerpUnclamped(const Vector2& _From, const Vector2& _To, const float& _T);

	[[nodiscard]] static const Vector2 Project(const Vector2& _v, const Vector2& _u);

	[[nodiscard]] static const Vector2 ClampMagnitude(const Vector2& _V, const float& _MaxLength);

	[[nodiscard]] static const Vector2 Perpendicular(const Vector2& _V);
	[[nodiscard]] static const Vector2 Reflect(const Vector2& _Incoming, const Vector2& _Normal);

	[[nodiscard]] static const Vector2 Min(const Vector2& _A, const Vector2& _B);
	[[nodiscard]] static const Vector2 Max(const Vector2& _A, const Vector2& _B);

	[[nodiscard]] const float SquaredMagnitude() const;
	[[nodiscard]] const float Magnitude() const;

	[[nodiscard]] const float SquaredDistance() const;
	[[nodiscard]] const float Distance() const;

	[[nodiscard]] const Vector2 Normalize() const;

	[[nodiscard]] Vector2 operator+(const float& _Factor) const;
	[[nodiscard]] Vector2 operator+(const Vector2& _Other) const;
	Vector2& operator+=(const float& _Factor);
	Vector2& operator+=(const Vector2& _Other);
	
	[[nodiscard]] Vector2 operator-(const float& _Factor) const;
	[[nodiscard]] Vector2 operator-(const Vector2& _Other) const;
	Vector2& operator-=(const float& _Factor);
	Vector2& operator-=(const Vector2& _Other);

	[[nodiscard]] Vector2 operator*(const float& _Factor) const;
	[[nodiscard]] Vector2 operator*(const Vector2& _Other) const;
	Vector2& operator*=(const float& _Factor);
	Vector2& operator*=(const Vector2& _Other);

	[[nodiscard]] Vector2 operator/(const float& _Factor) const;
	[[nodiscard]] Vector2 operator/(const Vector2& _Other) const;
	Vector2& operator/=(const float& _Factor);
	Vector2& operator/=(const Vector2& _Other);

	[[nodiscard]] bool operator<(const Vector2& _Other) const;
	[[nodiscard]] bool operator>(const Vector2& _Other) const;

	[[nodiscard]] bool operator<=(const Vector2& _Other) const;
	[[nodiscard]] bool operator>=(const Vector2& _Other) const;

	[[nodiscard]] bool operator==(const Vector2& _Other) const;
	[[nodiscard]] bool operator!=(const Vector2& _Other) const;

	Vector2& operator=(Vector2&& _Other) noexcept;
	Vector2& operator=(const Vector2& _Other);

	[[nodiscard]] const float& operator[](int _Index) const;

	friend std::ostream& operator<<(std::ostream& os, const Vector2& _V)
	{
		return os << "( " << _V.x << ", " << _V.y << " )";
	}
};

#include "Vector2.inl"

#endif