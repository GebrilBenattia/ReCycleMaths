#include <Vector3/Vector3.hpp>

const Vector3 Vector3::zero(0.f, 0.f, 0.f);
const Vector3 Vector3::one(1.f, 1.f, 1.f);
const Vector3 Vector3::left(-1.f, 0.f, 0.f);
const Vector3 Vector3::right(1.f, 0.f, 0.f);
const Vector3 Vector3::up(0.f, 1.f, 0.f);
const Vector3 Vector3::down(0.f, -1.f, 0.f);
const Vector3 Vector3::front(0.f, 0.f, 1.f);
const Vector3 Vector3::back(0.f, 0.f, -1.f);
const Vector3 Vector3::negativeInfinity(-INFINITY, -INFINITY, -INFINITY);
const Vector3 Vector3::positiveInfinity(INFINITY, INFINITY, INFINITY);

[[nodiscard]] const float Vector3::SquaredMagnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_SquaredMagnitude;
}

[[nodiscard]] const float Vector3::Magnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_Magnitude;
}

[[nodiscard]] const float Vector3::SquaredDistance() const
{
	return SquaredMagnitude();
}

[[nodiscard]] const float Vector3::Distance() const
{
	return Magnitude();
}

[[nodiscard]] const Vector3 Vector3::Normalize() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
		return ComputeNormalized();
	}

	if (m_Magnitude == 0.f) {
		return Vector3::zero;
	}

	return ComputeNormalized();
}

const float Vector3::Angle(const Vector3& _From, const Vector3& _To)
{
	float dot = DotProduct(_From, _To);
	float squaredMagnitudeFrom = _From.SquaredMagnitude();
	float squaredMagnitudeTo = _To.SquaredMagnitude();

	float magnitudeProduct = sqrtf(squaredMagnitudeFrom * squaredMagnitudeTo);

	// Clamp the dot product to avoid floating-point errors
	float cosTheta = dot / magnitudeProduct;
	cosTheta = fmaxf(-1.0f, fminf(1.0f, cosTheta)); // Clamping the value to [-1, 1]

	return acosf(cosTheta);
}

const float Vector3::SignedAngle(const Vector3& _From, const Vector3& _To, const Vector3& _Axis)
{
	return atan2f(DotProduct(CrossProduct(_From, _To), _Axis), DotProduct(_From, _To));
}