#include <Vector2/Vector2.hpp>

const Vector2 Vector2::zero(0.f, 0.f);
const Vector2 Vector2::one(1.f, 1.f);
const Vector2 Vector2::left(-1.f, 0.f);
const Vector2 Vector2::right(1.f, 0.f);
const Vector2 Vector2::up(0.f, 1.f);
const Vector2 Vector2::down(0.f, -1.f);
const Vector2 Vector2::negativeInfinity(-INFINITY, -INFINITY);
const Vector2 Vector2::positiveInfinity(INFINITY, INFINITY);

[[nodiscard]] const float Vector2::SquaredMagnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_SquaredMagnitude;
}

[[nodiscard]] const float Vector2::Magnitude() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
	}
	return m_Magnitude;
}

[[nodiscard]] const float Vector2::SquaredDistance() const
{
	return SquaredMagnitude();
}

[[nodiscard]] const float Vector2::Distance() const
{
	return Magnitude();
}

[[nodiscard]] const Vector2 Vector2::Normalize() const
{
	if (m_IsMagnitudeDirty) {
		m_SquaredMagnitude = ComputeSquaredMagnitude();
		m_Magnitude = ComputeMagnitude();
		m_IMagnitude = 1.f / m_Magnitude;
		m_IsMagnitudeDirty = false;
		return ComputeNormalized();
	}

	if (m_Magnitude == 0.f) {
		return Vector2::zero;
	}

	return ComputeNormalized();
}

const float Vector2::Angle(const Vector2& _From, const Vector2& _To)
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

const float Vector2::SignedAngle(const Vector2& _From, const Vector2& _To)
{
	return atan2f(CrossProduct(_From, _To), DotProduct(_From, _To));
}