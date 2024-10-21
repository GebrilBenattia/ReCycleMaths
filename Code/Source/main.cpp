#include <iostream>

#include <Vector4/Vector4.hpp>

#include <Utils/MathsUtils.hpp>

int main()
{
    /*
	Vector2 v = Vector2::right;
	Vector2 v2 = Vector2::up;

    Vector3 v3 = Vector3::right;
    Vector3 v4 = Vector3::up;
    Vector3 axis = Vector3::up;

	std::cout << "Magnitude Compute : " << v.Magnitude() << std::endl;

	std::cout << "Magnitude Get : " << v.Magnitude() << std::endl;

    std::cout << "Magnitude Recompute : " << v.Magnitude() << std::endl;

    std::cout << "Angle : " << RADIANS_TO_DEGREES(Vector2::SignedAngle(v2, v)) << std::endl;
    
    std::cout << "Test 1 (Expected 0 degrees): " << RADIANS_TO_DEGREES(Vector3::SignedAngle(v3, v4, axis)) << " degrees" << std::endl;

    // Test 2: 90 degrees counterclockwise
    v3 = Vector3::right;            // (1, 0, 0)
    v4 = Vector3::up;               // (0, 1, 0)
    axis = Vector3::back;           // (0, 0, -1)
    std::cout << "Test 2 (Expected -90 degrees): " << RADIANS_TO_DEGREES(Vector3::SignedAngle(v3, v4, axis)) << " degrees" << std::endl;

    // Test 3: 90 degrees clockwise
    v3 = Vector3::right;            // (1, 0, 0)
    v4 = Vector3::down;             // (0, -1, 0)
    axis = Vector3::back;           // (0, 0, -1)
    std::cout << "Test 3 (Expected 90 degrees): " << RADIANS_TO_DEGREES(Vector3::SignedAngle(v3, v4, axis)) << " degrees" << std::endl;

    // Test 4: Opposite directions
    v3 = Vector3::right;            // (1, 0, 0)
    v4 = Vector3::left;             // (-1, 0, 0)
    axis = Vector3::up;             // (0, 1, 0)
    std::cout << "Test 4 (Expected 180 degrees): " << RADIANS_TO_DEGREES(Vector3::SignedAngle(v3, v4, axis)) << " degrees" << std::endl;

    // Test 5: 45 degrees
    v3 = Vector3::right;            // (1, 0, 0)
    v4 = Vector3(Vector2::right);          // 45 degrees above x-axis
    axis = Vector3::back;           // (0, 0, -1)
    std::cout << "Test 5 (Expected -45 degrees): " << RADIANS_TO_DEGREES(Vector3::SignedAngle(v3, v4, axis)) << " degrees" << std::endl;
    */

    Vector4 v1 = Vector4::zero;
    Vector4 v2 = Vector4::one;
    Vector4 v3 = Vector4::negativeInfinity;
    Vector4 v4 = Vector4::positiveInfinity;

    std::cout << "Vector4 : " << v1 << std::endl;
    std::cout << "Vector4 : " << v2 << std::endl;
    std::cout << "Vector4 : " << v3 << std::endl;
    std::cout << "Vector4 : " << v4 << std::endl;

	return 0;
}