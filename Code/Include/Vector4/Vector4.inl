#define _USE_MATH_DEFINES
#include <math.h>
#include <Vector2/Vector2.hpp>
#include <Vector3/Vector3.hpp>
#include <Vector4/Vector4.hpp>

inline constexpr Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}
inline constexpr Vector4::Vector4(const float& _XYZW) : x(_XYZW), y(_XYZW), z(_XYZW), w(_XYZW) {}
inline constexpr Vector4::Vector4(const float& _X, const float& _Y, const float& _Z, const float& _W) : x(_X), y(_Y), z(_Z), w(_W) {}
inline constexpr Vector4::Vector4(const Vector2& _V1, const Vector2& _V2) : x(_V1.x), y(_V1.y), z(_V2.x), w(_V2.y) {}
inline constexpr Vector4::Vector4(const Vector3& _V, const float& _W) : x(_V.x), y(_V.y), z(_V.z), w(_W) {}

inline Vector4::Vector4(const Vector4& _Other) : x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w) {}
inline Vector4::Vector4(Vector4&& _Other) noexcept :x(_Other.x), y(_Other.y), z(_Other.z), w(_Other.w)
{
	_Other.x = 0.f;
	_Other.y = 0.f;
	_Other.z = 0.f;
	_Other.w = 0.f;
}

inline Vector4 Vector4::Add(const Vector4& _A, const float& _Factor)
{
	return Vector4(_A.x + _Factor, _A.y + _Factor, _A.z + _Factor, _A.w + _Factor);
}

inline Vector4 Vector4::AddComponentWise(const Vector4& _A, const Vector4& _B)
{
	return Vector4(_A.x + _B.x, _A.y + _B.y, _A.z + _B.z, _A.w + _B.w);
}

inline Vector4 Vector4::Subtract(const Vector4& _A, const float& _Factor)
{
	return Vector4(_A.x - _Factor, _A.y - _Factor, _A.z - _Factor, _A.w - _Factor);
}

inline Vector4 Vector4::SubtractComponentWise(const Vector4& _A, const Vector4& _B)
{
	return Vector4(_A.x - _B.x, _A.y - _B.y, _A.z - _B.z, _A.w - _B.w);
}

inline Vector4 Vector4::Scale(const Vector4& _A, const float& _Factor)
{
	return Vector4(_A.x * _Factor, _A.y * _Factor, _A.z * _Factor, _A.w * _Factor);
}

inline Vector4 Vector4::ScaleComponentWise(const Vector4& _A, const Vector4& _B)
{
	return Vector4(_A.x * _B.x, _A.y * _B.y, _A.z * _B.z, _A.w * _B.w);
}

inline Vector4 Vector4::Divide(const Vector4& _V, const float& _Factor)
{
	if (_Factor != 0.f) {
		return Scale(_V, 1.f / _Factor);
	}
	return Vector4::zero;
}

inline Vector4 Vector4::DivideComponentWise(const Vector4& _A, const Vector4& _B)
{
	return Vector4(
		(_B.x != 0.f) ? _A.x / _B.x : 0.f,
		(_B.y != 0.f) ? _A.y / _B.y : 0.f,
		(_B.z != 0.f) ? _A.z / _B.z : 0.f,
		(_B.w != 0.f) ? _A.w / _B.w : 0.f
	);
}

inline float Vector4::DotProduct(const Vector4& _A, const Vector4& _B)
{
	return (_A.x * _B.x + _A.y * _B.y + _A.z * _B.z + _A.w * _B.w);
}

inline const Vector4 Vector4::Lerp(const Vector4& _From, const Vector4& _To, const float& _T)
{
	// Clamp _T between 0 and 1
	float t = (_T < 0.f) ? 0.f : (_T > 1.f) ? 1.f : _T;
	return _From + (_To - _From) * t;
}

inline const Vector4 Vector4::LerpUnclamped(const Vector4& _From, const Vector4& _To, const float& _T)
{
	return _From + (_To - _From) * _T;
}

inline const Vector4 Vector4::Project(const Vector4& _ToProject, const Vector4& _Base)
{
	return (_Base * (DotProduct(_Base, _ToProject) / _Base.SquaredMagnitude()));
}

inline const Vector4 Vector4::Min(const Vector4& _A, const Vector4& _B)
{
	return Vector4(
		_A.x < _B.x ? _A.x : _B.x,  // Minimum x-component
		_A.y < _B.y ? _A.y : _B.y,   // Minimum y-component
		_A.z < _B.z ? _A.z : _B.z,   // Minimum z-component
		_A.w < _B.w ? _A.w : _B.w   // Minimum w-component
	);
}

inline const Vector4 Vector4::Max(const Vector4& _A, const Vector4& _B)
{
	return Vector4(
		_A.x > _B.x ? _A.x : _B.x,  // Maximum x-component
		_A.y > _B.y ? _A.y : _B.y,   // Maximum y-component
		_A.z > _B.z ? _A.z : _B.z,   // Maximum z-component
		_A.w > _B.w ? _A.w : _B.w   // Minimum w-component
	);
}

inline const float Vector4::ComputeSquaredMagnitude() const
{
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

inline const float Vector4::ComputeMagnitude() const
{
	if (m_SquaredMagnitude == 0.f || m_SquaredMagnitude == 1.f) {
		return m_SquaredMagnitude;
	}
	return sqrtf(m_SquaredMagnitude);
}

inline const Vector4 Vector4::ComputeNormalized() const
{
	return Vector4(this->x * m_IMagnitude, this->y * m_IMagnitude, this->z * m_IMagnitude, this->w * m_IMagnitude);
}

inline Vector4 Vector4::operator+(const float& _Factor) const
{
	return Add(*this, _Factor);
}

inline Vector4 Vector4::operator+(const Vector4& _Other) const
{
	return AddComponentWise(*this, _Other);
}

inline Vector4& Vector4::operator+=(const float& _Factor)
{
	this->x += _Factor;
	this->y += _Factor;
	this->z += _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4& Vector4::operator+=(const Vector4& _Other)
{
	this->x += _Other.x;
	this->y += _Other.y;
	this->z += _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4 Vector4::operator-(const float& _Factor) const
{
	return Subtract(*this, _Factor);
}

inline Vector4 Vector4::operator-(const Vector4& _Other) const
{
	return SubtractComponentWise(*this, _Other);
}

inline Vector4& Vector4::operator-=(const float& _Factor)
{
	this->x -= _Factor;
	this->y -= _Factor;
	this->z -= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4& Vector4::operator-=(const Vector4& _Other)
{
	this->x -= _Other.x;
	this->y -= _Other.y;
	this->z -= _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4 Vector4::operator*(const float& _Factor) const
{
	return Scale(*this, _Factor);
}

inline Vector4 Vector4::operator*(const Vector4& _Other) const
{
	return ScaleComponentWise(*this, _Other);
}

inline Vector4& Vector4::operator*=(const float& _Factor)
{
	this->x *= _Factor;
	this->y *= _Factor;
	this->z *= _Factor;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4& Vector4::operator*=(const Vector4& _Other)
{
	this->x *= _Other.x;
	this->y *= _Other.y;
	this->z *= _Other.z;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline Vector4 Vector4::operator/(const float& _Factor) const
{
	return Divide(*this, _Factor);
}

inline Vector4 Vector4::operator/(const Vector4& _Other) const
{
	return DivideComponentWise(*this, _Other);
}

inline Vector4& Vector4::operator/=(const float& _Factor)
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

inline Vector4& Vector4::operator/=(const Vector4& _Other)
{
	(_Other.x != 0.f) ? this->x / _Other.x : 0.f;
	(_Other.y != 0.f) ? this->y / _Other.y : 0.f;
	(_Other.z != 0.f) ? this->z / _Other.z : 0.f;

	m_IsMagnitudeDirty = true;

	return *this;
}

inline bool Vector4::operator<(const Vector4& _Other) const
{
	if (this->SquaredMagnitude() < _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector4::operator>(const Vector4& _Other) const
{
	return !(*this < _Other);
}

inline bool Vector4::operator<=(const Vector4& _Other) const
{
	if (this->SquaredMagnitude() <= _Other.SquaredMagnitude())
		return true;
	return false;
}

inline bool Vector4::operator>=(const Vector4& _Other) const
{
	return !(*this <= _Other);
}

inline bool Vector4::operator==(const Vector4& _Other) const
{
	if (this->x == _Other.x && this->y == _Other.y && this->z == _Other.z && this->w == _Other.w)
		return true;
	return false;
}

inline bool Vector4::operator!=(const Vector4& _Other) const
{
	return !(*this == _Other);
}

inline Vector4& Vector4::operator=(Vector4&& _Other) noexcept
{
	if (this != &_Other) {
		// Self-assignment check
		// Move the data
		x = _Other.x;
		y = _Other.y;
		z = _Other.z;
		w = _Other.w;

		// Leave _Other in a valid state
		_Other.x = 0.f;
		_Other.y = 0.f;
		_Other.z = 0.f;
		_Other.w = 0.f;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline Vector4& Vector4::operator=(const Vector4& _Other)
{
	if (this != &_Other) {
		x = _Other.x;
		y = _Other.y;
		z = _Other.z;
		w = _Other.w;

		m_IsMagnitudeDirty = true;
	}
	return *this;
}

inline const float& Vector4::operator[](int _Index) const
{
	int cIndex = (_Index < 0) ? 0 : (_Index > 3) ? 3 : _Index;
	if (cIndex == 0)
		return x;
	if (cIndex == 1)
		return y;
	if (cIndex == 2)
		return z;
	else
		return w;
}