#pragma once
#include <cmath>

namespace pv{
    struct Vec3 {
        float x;
        float y;
        float z;

        constexpr explicit Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    
        constexpr Vec3& operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        constexpr Vec3& operator-=(const Vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        constexpr Vec3  scale(float scalar) const {
            return Vec3(x * scalar, y * scalar, z * scalar);
        }

        float length() {
            return std::sqrt(x*x + y*y + z*z);
        }
    };

    constexpr Vec3 operator+(Vec3 a, Vec3 b) {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    constexpr Vec3 operator-(Vec3 a, Vec3 b) {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

    constexpr float dot(const Vec3& a, const Vec3& b) {
        return (a.x*b.x + a.y*b.y + a.z*b.z);
    }

    constexpr Vec3 cross(const Vec3& a, const Vec3& b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
}

