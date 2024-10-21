#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.hpp"
#include "Vector2/Vector2.hpp"

inline constexpr Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {}
inline constexpr Vector3::Vector3(const float& _XYZ) : x(_XYZ), y(_XYZ), z(_XYZ) {}
inline constexpr Vector3::Vector3(const float& _X, const float& _Y) : x(_X), y(_Y), z(0.f) {}
inline constexpr Vector3::Vector3(const float& _X, const float& _Y, const float& _Z) : x(_X), y(_Y), z(_Z) {}
inline constexpr Vector3::Vector3(const Vector2& _V) : x(_V.x), y(_V.y), z(0.f) {}
inline constexpr Vector3::Vector3(const Vector2& _V, const float& _Z)	:x(_V.x), y(_V.y), z(_Z) {}
inline constexpr Vector3::Vector3(const float& _X, const Vector2& _V) : x(_X), y(_V.x), z(_V.y) {}

inline Vector3::Vector3(const Vector3& _Other) : x(_Other.x), y(_Other.y), z(_Other.z) {}
inline Vector3::Vector3(Vector3&& _Other) noexcept :x(_Other.x), y(_Other.y), z(_Other.z)
{
	_Other.x = 0.f;
	_Other.y = 0.f;
	_Other.z = 0.f;
}

inline Vector3 Vector3::Add(const Vector3& _A, const float& _Factor)
{
	return Vector3(_A.x + _Factor, _A.y + _Factor, _A.z + _Factor);
}

inline Vector3 Vector3::AddComponentWise(const Vector3& _A, const Vector3& _B)
{
	return Vector3(_A.x + _B.x, _A.y + _B.y, _A.z + _B.z);
}

inline Vector3 Vector3::Subtract(const Vector3& _A, const float& _Factor)
{
	return Vector3(_A.x - _Factor, _A.y - _Factor, _A.z - _Factor);
}

inline Vector3 Vector3::SubtractComponentWise(const Vector3& _A, const Vector3& _B)
{
	return Vector3(_A.x - _B.x, _A.y - _B.y, _A.z - _B.z);
}

inline Vector3 Vector3::Scale(const Vector3& _A, const float& _Factor)
{
	return Vector3(_A.x * _Factor, _A.y * _Factor, _A.z * _Factor);
}

inline Vector3 Vector3::ScaleComponentWise(const Vector3& _A, const Vector3& _B)
{
	return Vector3(_A.x * _B.x, _A.y * _B.y, _A.z * _B.z);
}

inline Vector3 Vector3::Divide(const Vector3& _V, const float& _Factor)
{
	if (_Factor != 0.f) {
		return Scale(_V, 1.f / _Factor);
	}
	return Vector3::zero;
}

inline Vector3 Vector3::DivideComponentWise(const Vector3& _A, const Vector3& _B)
{
	return Vector3(
		(_B.x != 0.f) ? _A.x / _B.x : 0.f,
		(_B.y != 0.f) ? _A.y / _B.y : 0.f,
		(_B.z != 0.f) ? _A.z / _B.z : 0.f
	);
}

inline float Vector3::DotProduct(const Vector3& _A, const Vector3& _B)
{
	return (_A.x * _B.x + _A.y * _B.y + _A.z * _B.z);
}

inline Vector3 Vector3::CrossProduct(const Vector3& _A, const Vector3& _B)
{
	return Vector3(
		_A.y * _B.z - _A.z * _B.y,
		_A.z * _B.x - _A.x * _B.z,
		_A.x * _B.y - _A.y * _B.x
	);
}

inline const Vector3 Vector3::Lerp(const Vector3& _From, const Vector3& _To, const float& _T)
{
	// Clamp _T between 0 and 1
	float t = (_T < 0.f) ? 0.f : (_T > 1.f) ? 1.f : _T;
	return _From + (_To - _From) * t;
}

inline const Vector3 Vector3::LerpUnclamped(const Vector3& _From, const Vector3& _To, const float& _T)
{
	return _From + (_To - _From) * _T;
}

inline const Vector3 Vector3::Project(const Vector3& _ToProject, const Vector3& _Base)
{
	return (_Base * (DotProduct(_Base, _ToProject) / _Base.SquaredMagnitude()));
}

inline const Vector3 Vector3::ClampMagnitude(const Vector3& _V, const float& _MaxLength)
{
	if (_V.SquaredMagnitude() > _MaxLength * _MaxLength) {
		float scale = _MaxLength / _V.Magnitude();      // Calculate scale factor
		return _V * scale; // Scale the vector
	}
	return _V; // Return the original vector if it's within the limit
}

inline const Vector3 Vector3::Perpendicular(const Vector3& _V)
{
	return Vector3(-_V.y, _V.x);
}

inline const Vector3 Vector3::Reflect(const Vector3& _Incoming, const Vector3& _Normal)
{
	return _Incoming - (_Normal * (2.f * DotProduct(_Incoming, _Normal)));
}

inline const Vector3 Vector3::Min(const Vector3& _A, const Vector3& _B)
{
	return Vector3(
		_A.x < _B.x ? _A.x : _B.x,  // Minimum x-component
		_A.y < _B.y ? _A.y : _B.y,   // Minimum y-component
		_A.z < _B.z ? _A.z : _B.z   // Minimum z-component
	);
}

inline const Vector3 Vector3::Max(const Vector3& _A, const Vector3& _B)
{
	return Vector3(
		_A.x > _B.x ? _A.x : _B.x,  // Maximum x-component
		_A.y > _B.y ? _A.y : _B.y,   // Maximum y-component
		_A.z > _B.z ? _A.z : _B.z   // Maximum z-component
	);
}

inline const float Vector3::ComputeSquaredMagnitude() const
{
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

inline const float Vector3::ComputeMagnitude() const
{
	if (m_SquaredMagnitude == 0.f || m_SquaredMagnitude == 1.f) {
		return m_SquaredMagnitude;
	}
	return sqrtf(m_SquaredMagnitude);
}

inline const Vector3 Vector3::ComputeNormalized() const
{
	return Vector3(this->x * m_IMagnitude, this->y * m_IMagnitude, this->z * m_IMagnitude);
}

inline const void Vector3::OrthoNormalize(Vector3& _Normal, Vector3& _Tangent) 
{
	// Normalize the normal vector
	_Normal = _Normal.Normalize();

	// Project tangent onto normal
	Vector3 tangentProjection = _Normal * DotProduct(_Tangent, _Normal);

	// Make tangent orthogonal to normal
	_Tangent = _Tangent - tangentProjection;

	// Normalize the tangent vector
	_Tangent = _Tangent.Normalize();
}

inline const void Vector3::OrthoNormalize(Vector3& _Normal, Vector3& _Tangent, Vector3& _Binormal) 
{
	// Normalize normal
	_Normal = _Normal.Normalize();

	// Project tangent onto normal
	Vector3 tangentProjection = _Normal * DotProduct(_Tangent, _Normal);
	_Tangent = _Tangent - tangentProjection;
	_Tangent = _Tangent.Normalize();

	// Project binormal onto normal and tangent
	Vector3 binormalProjection = _Normal * DotProduct(_Binormal, _Normal) + _Tangent * DotProduct(_Binormal, _Tangent);
	_Binormal = _Binormal - binormalProjection;
	_Binormal = _Binormal.Normalize();
}

inline const Vector3 Vector3::ProjectOnPlane(const Vector3& _V, const Vector3& _PlaneNormal)
{
	// Compute the projection of the vector onto the plane normal
	float dotProduct = DotProduct(_V, _PlaneNormal);
	Vector3 projection = _PlaneNormal * dotProduct; // Projection onto the normal
	return _V - projection; // Return the vector minus the projection
}

inline Vector3 Vector3::operator+(const float& _Factor) const
{
	return Add(*this, _Factor);
}

inline Vector3 Vector3::operator+(const Vector3& _Other) const
{
	return AddComponentWise(*this, _Other);
}

inline Vector3& Vector3::operator+=(const float& _Factor)
{
	this->x += _Factor;
	this->y += _Factor;
	this->z += _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3& Vector3::operator+=(const Vector3& _Other)
{
	this->x += _Other.x;
	this->y += _Other.y;
	this->z += _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3 Vector3::operator-(const float& _Factor) const
{
	return Subtract(*this, _Factor);
}

inline Vector3 Vector3::operator-(const Vector3& _Other) const
{
	return SubtractComponentWise(*this, _Other);
}

inline Vector3& Vector3::operator-=(const float& _Factor)
{
	this->x -= _Factor;
	this->y -= _Factor;
	this->z -= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& _Other)
{
	this->x -= _Other.x;
	this->y -= _Other.y;
	this->z -= _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3 Vector3::operator*(const float& _Factor) const
{
	return Scale(*this, _Factor);
}

inline Vector3 Vector3::operator*(const Vector3& _Other) const
{
	return ScaleComponentWise(*this, _Other);
}

inline Vector3& Vector3::operator*=(const float& _Factor)
{
	this->x *= _Factor;
	this->y *= _Factor;
	this->z *= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& _Other)
{
	this->x *= _Other.x;
	this->y *= _Other.y;
	this->z *= _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector3 Vector3::operator/(const float& _Factor) const
{
	return Divide(*this, _Factor);
}

inline Vector3 Vector3::operator/(const Vector3& _Other) const
{
	return DivideComponentWise(*this, _Other);
}

inline Vector3& Vector3::operator/=(const float& _Factor)
{
	if (_Factor != 0.f) {
		float IFactor = 1.f / _Factor;
		x *= IFactor;
		y *= IFactor;
		z *= IFactor;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline Vector3& Vector3::operator/=(const Vector3& _Other)
{
	(_Other.x != 0.f) ? this->x / _Other.x : 0.f;
	(_Other.y != 0.f) ? this->y / _Other.y : 0.f;
	(_Other.z != 0.f) ? this->z / _Other.z : 0.f;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline bool Vector3::operator<(const Vector3& _Other) const
{
	if (this->SquaredMagnitude() < _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector3::operator>(const Vector3& _Other) const
{
	return !(*this < _Other);
}

inline bool Vector3::operator<=(const Vector3& _Other) const
{
	if (this->SquaredMagnitude() <= _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector3::operator>=(const Vector3& _Other) const
{
	return !(*this <= _Other);
}

inline bool Vector3::operator==(const Vector3& _Other) const
{
	if (this->x == _Other.x && this->y == _Other.y && this->z == _Other.z)
		return true;
	return false;
}

inline bool Vector3::operator!=(const Vector3& _Other) const
{
	return !(*this == _Other);
}

inline Vector3& Vector3::operator=(Vector3&& _Other) noexcept
{
	if (this != &_Other) {
		// Self-assignment check
		// Move the data
		x = _Other.x;
		y = _Other.y;
		z = _Other.z;
		// Leave _Other in a valid state
		_Other.x = 0.f;
		_Other.y = 0.f;
		_Other.z = 0.f;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline Vector3& Vector3::operator=(const Vector3& _Other)
{
	if (this != &_Other) {
		x = _Other.x;
		y = _Other.y;
		z = _Other.z;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline const float& Vector3::operator[](int _Index) const
{
	int cIndex = (_Index < 0) ? 0 : (_Index > 2) ? 2 : _Index;
	if (cIndex == 0)
		return x;
	if (cIndex == 1)
		return y;
	else
		return z;
}