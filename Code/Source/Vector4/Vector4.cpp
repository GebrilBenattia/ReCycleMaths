#include <Vector4/Vector4.hpp>

const Vector4 Vector4::zero(0.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::one(1.f, 1.f, 1.f, 1.f);
const Vector4 Vector4::negativeInfinity(-INFINITY, -INFINITY, -INFINITY, -INFINITY);
const Vector4 Vector4::positiveInfinity(INFINITY, INFINITY, INFINITY, INFINITY);

[[nodiscard]] const float Vector4::SquaredMagnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_SquaredMagnitude;
}

[[nodiscard]] const float Vector4::Magnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_Magnitude;
}

[[nodiscard]] const float Vector4::SquaredDistance() const
{
	return SquaredMagnitude();
}

[[nodiscard]] const float Vector4::Distance() const
{
	return Magnitude();
}

[[nodiscard]] const Vector4 Vector4::Normalize() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
		return ComputeNormalized();
	}

	if (m_Magnitude == 0.f) {
		return Vector4::zero;
	}

	return ComputeNormalized();
}