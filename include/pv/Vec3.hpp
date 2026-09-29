#pragma once
#include <cmath>
#include <cstddef>
#include <stdexcept>
namespace pv{
    struct Vec3 {
        float x;
        float y;
        float z;

        constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

        constexpr Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    
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

        constexpr Vec3& operator*=(const Vec3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        constexpr Vec3& operator*=(const float& scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }
        
        constexpr Vec3& operator/=(const Vec3& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        constexpr Vec3& operator/=(const float& scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        [[nodiscard]] constexpr bool operator==(const Vec3& other) const {
            return (x == other.x && y == other.y && z == other.z);
        }

        [[nodiscard]] constexpr bool operator!=(const Vec3& other) const {
            return !(*this == other);
        }

        [[nodiscard]] float length() const {
            return std::sqrt(lengthSquared());
        }

        [[nodiscard]] constexpr float lengthSquared() const {
            return (x*x + y*y + z*z);
        }

        [[nosdiscard]] Vec3 normalized() const {
            float length = this->length();
            if (length == 0.0f){
                return Vec3(0.0f, 0.0f, 0.0f);
            }
            return Vec3(x/length, y/length, z/length);
        }

        // Non-const: returns a reference so v[0] = 5.0f writes to x
        [[nodiscard]] constexpr float& operator[](std::size_t index){
            switch (index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw std::out_of_range("Index out of range for Vec3");
            }
        }

        // Const: read-only access for const / constexpr vectors
        [[nodiscard]] constexpr float operator[](std::size_t index) const {
            switch (index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: throw std::out_of_range("Index out of range for Vec3");
            }
        }
    };

    [[nodiscard]] constexpr Vec3 operator+(Vec3 a, Vec3 b) {
        a += b;
        return a;
    }

    [[nodiscard]] constexpr Vec3 operator-(Vec3 a, Vec3 b) {
        a -= b;
        return a;
    }
    
    [[nodiscard]] constexpr Vec3 operator*(Vec3 a, Vec3 b) {
        a *= b;
        return a;
    }

    [[nodiscard]] constexpr Vec3 operator*(Vec3 a, const float& scalar) {
        a *= scalar;
        return a;
    }

    [[nodiscard]] constexpr Vec3 operator*(const float& scalar, Vec3 a) {
        a *= scalar;
        return a;
    }
    
    [[nodiscard]] constexpr Vec3 operator/(Vec3 a, Vec3 b) {
        a /= b;
        return a;
    }

    [[nodiscard]] constexpr Vec3 operator/(Vec3 a, const float& scalar) {
        a /= scalar;
        return a;
    }

    [[nosdiscard]] constexpr float dot(const Vec3& a, const Vec3& b) {
        return (a.x*b.x + a.y*b.y + a.z*b.z);
    }

    [[nodiscard]] constexpr Vec3 cross(const Vec3& a, const Vec3& b) {
        return Vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
}

