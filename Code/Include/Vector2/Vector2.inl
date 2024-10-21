#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector2.hpp"

inline constexpr Vector2::Vector2() : x(0.f), y(0.f) {}
inline constexpr Vector2::Vector2(const float& _XY) : x(_XY), y(_XY) {}
inline constexpr Vector2::Vector2(const float& _X, const float& _Y) : x(_X), y(_Y) {}

inline Vector2::Vector2(const Vector2& _Other) : x(_Other.x), y(_Other.y) {}
inline Vector2::Vector2(Vector2&& _Other) noexcept :x(_Other.x), y(_Other.y)
{
	_Other.x = 0.f;
	_Other.y = 0.f;
}

inline Vector2 Vector2::Add(const Vector2& _A, const float& _Factor)
{
	return Vector2(_A.x + _Factor, _A.y + _Factor);
}

inline Vector2 Vector2::AddComponentWise(const Vector2& _A, const Vector2& _B)
{
	return Vector2(_A.x + _B.x, _A.y + _B.y);
}

inline Vector2 Vector2::Subtract(const Vector2& _A, const float& _Factor)
{
	return Vector2(_A.x - _Factor, _A.y - _Factor);
}

inline Vector2 Vector2::SubtractComponentWise(const Vector2& _A, const Vector2& _B)
{
	return Vector2(_A.x - _B.x, _A.y - _B.y);
}

inline Vector2 Vector2::Scale(const Vector2& _A, const float& _Factor)
{
	return Vector2(_A.x * _Factor, _A.y * _Factor);
}

inline Vector2 Vector2::ScaleComponentWise(const Vector2& _A, const Vector2& _B)
{
	return Vector2(_A.x * _B.x, _A.y * _B.y);
}

inline Vector2 Vector2::Divide(const Vector2& _V, const float& _Factor)
{
	if (_Factor != 0.f) {
		return Scale(_V, 1.f / _Factor);
	}
	return Vector2(0.f, 0.f);
}

inline Vector2 Vector2::DivideComponentWise(const Vector2& _A, const Vector2& _B)
{
	return Vector2(
		(_B.x != 0.f) ? _A.x / _B.x : 0.f,
		(_B.y != 0.f) ? _A.y / _B.y : 0.f
	);
}

inline float Vector2::DotProduct(const Vector2& _A, const Vector2& _B)
{
	return (_A.x * _B.x + _A.y * _B.y);
}

inline float Vector2::CrossProduct(const Vector2& _A, const Vector2& _B)
{
	return (_A.x * _B.y - _A.y * _B.x);
}

inline const Vector2 Vector2::Lerp(const Vector2& _From, const Vector2& _To, const float& _T)
{
	// Clamp _T between 0 and 1
	float t = (_T < 0.f) ? 0.f : (_T > 1.f) ? 1.f : _T;
	return _From + (_To - _From) * t;
}

inline const Vector2 Vector2::LerpUnclamped(const Vector2& _From, const Vector2& _To, const float& _T)
{
	return _From + (_To - _From) * _T;
}

inline const Vector2 Vector2::Project(const Vector2& _ToProject, const Vector2& _Base)
{
	return (_Base * (DotProduct(_Base, _ToProject) / _Base.SquaredMagnitude()));
}

inline const Vector2 Vector2::ClampMagnitude(const Vector2& _V, const float& _MaxLength)
{
	if (_V.SquaredMagnitude() > _MaxLength * _MaxLength) {
		float scale = _MaxLength / _V.Magnitude();      // Calculate scale factor
		return Vector2(_V.x * scale, _V.y * scale); // Scale the vector
	}
	return _V; // Return the original vector if it's within the limit
}

inline const Vector2 Vector2::Perpendicular(const Vector2& _V)
{
	return Vector2(-_V.y, _V.x);
}

inline const Vector2 Vector2::Reflect(const Vector2& _Incoming, const Vector2& _Normal)
{
	return _Incoming - (_Normal * (2.f * DotProduct(_Incoming, _Normal)));
}

inline const Vector2 Vector2::Min(const Vector2& _A, const Vector2& _B)
{
	return Vector2(
		_A.x < _B.x ? _A.x : _B.x,  // Minimum x-component
		_A.y < _B.y ? _A.y : _B.y   // Minimum y-component
	);
}

inline const Vector2 Vector2::Max(const Vector2& _A, const Vector2& _B)
{
	return Vector2(
		_A.x > _B.x ? _A.x : _B.x,  // Maximum x-component
		_A.y > _B.y ? _A.y : _B.y   // Maximum y-component
	);
}

inline const float Vector2::ComputeSquaredMagnitude() const
{
	return (this->x * this->x) + (this->y * this->y);
}

inline const float Vector2::ComputeMagnitude() const
{
	if (m_SquaredMagnitude == 0.f || m_SquaredMagnitude == 1.f) {
		return m_SquaredMagnitude;
	}
	return sqrtf(m_SquaredMagnitude);
}

inline const Vector2 Vector2::ComputeNormalized() const
{
	return Vector2(this->x * m_IMagnitude, this->y * m_IMagnitude);
}

inline Vector2 Vector2::operator+(const float& _Factor) const
{
	return Add(*this, _Factor);
}

inline Vector2 Vector2::operator+(const Vector2& _Other) const
{
	return AddComponentWise(*this, _Other);
}

inline Vector2& Vector2::operator+=(const float& _Factor)
{
	this->x += _Factor;
	this->y += _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& _Other)
{
	this->x += _Other.x;
	this->y += _Other.y;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2 Vector2::operator-(const float& _Factor) const
{
	return Subtract(*this, _Factor);
}

inline Vector2 Vector2::operator-(const Vector2& _Other) const
{
	return SubtractComponentWise(*this, _Other);
}

inline Vector2& Vector2::operator-=(const float& _Factor)
{
	this->x -= _Factor;
	this->y -= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& _Other)
{
	this->x -= _Other.x;
	this->y -= _Other.y;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2 Vector2::operator*(const float& _Factor) const
{
	return Scale(*this, _Factor);
}

inline Vector2 Vector2::operator*(const Vector2& _Other) const
{
	return ScaleComponentWise(*this, _Other);
}

inline Vector2& Vector2::operator*=(const float& _Factor)
{
	this->x *= _Factor;
	this->y *= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& _Other)
{
	this->x *= _Other.x;
	this->y *= _Other.y;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector2 Vector2::operator/(const float& _Factor) const
{
	return Divide(*this, _Factor);
}

inline Vector2 Vector2::operator/(const Vector2& _Other) const
{
	return DivideComponentWise(*this, _Other);
}

inline Vector2& Vector2::operator/=(const float& _Factor)
{
	if (_Factor != 0.f) {
		float IFactor = 1.f / _Factor;
		x *= IFactor;
		y *= IFactor;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline Vector2& Vector2::operator/=(const Vector2& _Other)
{
	(_Other.x != 0.f) ? this->x / _Other.x : 0.f;
	(_Other.y != 0.f) ? this->y / _Other.y : 0.f;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline bool Vector2::operator<(const Vector2& _Other) const
{
	if (this->SquaredMagnitude() < _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector2::operator>(const Vector2& _Other) const
{
	return !(*this < _Other);
}

inline bool Vector2::operator<=(const Vector2& _Other) const
{
	if (this->SquaredMagnitude() <= _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector2::operator>=(const Vector2& _Other) const
{
	return !(*this <= _Other);
}

inline bool Vector2::operator==(const Vector2& _Other) const
{
	if (this->x == _Other.x && this->y == _Other.y)
		return true;
	return false;
}

inline bool Vector2::operator!=(const Vector2& _Other) const
{
	return !(*this == _Other);
}

inline Vector2& Vector2::operator=(Vector2&& _Other) noexcept
{
	if (this != &_Other) {
		// Self-assignment check
		// Move the data
		x = _Other.x;
		y = _Other.y;
		// Leave _Other in a valid state
		_Other.x = 0.f;
		_Other.y = 0.f;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline Vector2& Vector2::operator=(const Vector2& _Other)
{
	if (this != &_Other) {
		x = _Other.x;
		y = _Other.y;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline const float& Vector2::operator[](int _Index) const
{
	int cIndex = (_Index < 0) ? 0 : (_Index > 1) ? 1 : _Index;
	return (cIndex == 0) ? x : y;
}