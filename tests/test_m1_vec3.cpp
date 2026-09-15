#include "pv/Vec3.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <stdexcept>

TEST_CASE("Vec3 can be made at compile time", "[Vec3]") {
    constexpr pv::Vec3 v(1.0f, 2.0f, 3.0f);
    STATIC_REQUIRE(v.x == 1.0f);    // 
    STATIC_REQUIRE(v.y == 2.0f);
    STATIC_REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3 addition, subtraction, multiplication, division", "[Vec3]"){
    constexpr pv::Vec3 a(1.0f, 2.0f, 3.0f);
    constexpr pv::Vec3 b(4.0f, 5.0f, 6.0f);

    STATIC_REQUIRE(a.x == 1.0f);    // 
    STATIC_REQUIRE(a.y == 2.0f);    // 
    STATIC_REQUIRE(a.z == 3.0f);    // 
    STATIC_REQUIRE(b.x == 4.0f);
    STATIC_REQUIRE(b.y == 5.0f);
    STATIC_REQUIRE(b.z == 6.0f);

    SECTION("Addition"){
        constexpr pv::Vec3 c = a + b;
        STATIC_REQUIRE(c.x == 5.0f);
        STATIC_REQUIRE(c.y == 7.0f);
        STATIC_REQUIRE(c.z == 9.0f);
    }

    SECTION("Subtraction"){
        constexpr pv::Vec3 d = a - b;
        STATIC_REQUIRE(d.x == -3.0f);
        STATIC_REQUIRE(d.y == -3.0f);
        STATIC_REQUIRE(d.z == -3.0f);
    }

    SECTION("Mutiplication"){
        constexpr pv::Vec3 e = a * b;
        STATIC_REQUIRE(e.x == 4.0f);
        STATIC_REQUIRE(e.y == 10.0f);
        STATIC_REQUIRE(e.z == 18.0f);
    }

    SECTION("Division"){
        constexpr pv::Vec3 f = a / b;
        STATIC_REQUIRE(f.x == 0.25f);
        STATIC_REQUIRE(f.y == 0.4f);
        STATIC_REQUIRE(f.z == 0.5f);
    }
}
      

TEST_CASE("Vec3 dot and cross products", "[Vec3]"){
    constexpr pv::Vec3 a(1.0f, 2.0f, 3.0f);
    constexpr pv::Vec3 b(4.0f, 5.0f, 6.0f);

    SECTION("Dot product") {
        constexpr float dot_product = pv::dot(a, b);
        STATIC_REQUIRE(dot_product == 32.0f);
    }

    SECTION("Cross product") {
        constexpr pv::Vec3 cross_product = pv::cross(a, b);
        STATIC_REQUIRE(cross_product.x == -3.0f);
        STATIC_REQUIRE(cross_product.y == 6.0f);
        STATIC_REQUIRE(cross_product.z == -3.0f);
    }
}
    
TEST_CASE("Vec3 length", "[Vec3]") {
    pv::Vec3 a(3.0f, 4.0f, 5.0f);
    float length = a.length();
    REQUIRE_THAT(length, Catch::Matchers::WithinAbs(7.0710678118654755f, 1e-6f));
}

TEST_CASE("Vec3 scaling", "[Vec3]") {
    constexpr pv::Vec3 a(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    pv::Vec3 scaled = a.scale(scalar);

    STATIC_REQUIRE(a.x == 1.0f);
    STATIC_REQUIRE(a.y == 2.0f);
    STATIC_REQUIRE(a.z == 3.0f);
    
    REQUIRE(scaled.x == 2.0f);
    REQUIRE(scaled.y == 4.0f);
    REQUIRE(scaled.z == 6.0f);
}

TEST_CASE("Vec3 normalization", "[Vec3]") {
    pv::Vec3 a(3.0f, 4.0f, 0.0f);
    pv::Vec3 normalized = a.normalized();

    REQUIRE_THAT(normalized.x, Catch::Matchers::WithinAbs(0.6f, 1e-6f));
    REQUIRE_THAT(normalized.y, Catch::Matchers::WithinAbs(0.8f, 1e-6f));
    REQUIRE_THAT(normalized.z, Catch::Matchers::WithinAbs(0.0f, 1e-6f));
}

TEST_CASE("Vec3 normalization of zero vector", "[Vec3]") {
    pv::Vec3 zero_vector(0.0f, 0.0f, 0.0f);
    pv::Vec3 normalized = zero_vector.normalized();

    REQUIRE(normalized.x == 0.0f);
    REQUIRE(normalized.y == 0.0f);
    REQUIRE(normalized.z == 0.0f);
}

TEST_CASE("Vec3 operator[]", "[Vec3]") {
    SECTION("Read at compile time (const overload)") {
        constexpr pv::Vec3 v(1.0f, 2.0f, 3.0f);
        STATIC_REQUIRE(v[0] == 1.0f);
        STATIC_REQUIRE(v[1] == 2.0f);
        STATIC_REQUIRE(v[2] == 3.0f);
    }

    SECTION("Write at compile time (non-const overload)") {
        constexpr pv::Vec3 v = [] {
            pv::Vec3 t(0.0f, 0.0f, 0.0f);
            t[0] = 1.0f;
            t[1] = 2.0f;
            t[2] = 3.0f;
            return t;
        }();
        STATIC_REQUIRE(v.x == 1.0f);
        STATIC_REQUIRE(v.y == 2.0f);
        STATIC_REQUIRE(v.z == 3.0f);
    }

    SECTION("Read and write at runtime") {
        pv::Vec3 v(1.0f, 2.0f, 3.0f);
        REQUIRE(v[0] == 1.0f);
        REQUIRE(v[1] == 2.0f);
        REQUIRE(v[2] == 3.0f);

        v[1] = 10.0f;
        REQUIRE(v.y == 10.0f);   // writing through [] changed the real member
    }

    SECTION("Out of range throws") {
        pv::Vec3 v(1.0f, 2.0f, 3.0f);
        const pv::Vec3 cv(1.0f, 2.0f, 3.0f);

        REQUIRE_NOTHROW(v[2]);                           // last valid index is fine
        REQUIRE_THROWS_AS(v[3], std::out_of_range);      // non-const overload
        REQUIRE_THROWS_AS(cv[3], std::out_of_range);     // const overload
    }
}

TEST_CASE("Vec3 lengthSquared", "[Vec3]") {
    pv::Vec3 a(3.0f, 4.0f, 5.0f);
    float length_squared = a.lengthSquared();
    REQUIRE(length_squared == 50.0f); // 3^2 + 4^2 + 5^2 = 9 + 16 + 25 = 50
}

TEST_CASE("Vec3 equality and inequality operators", "[Vec3]") {
    pv::Vec3 a(1.0f, 2.0f, 3.0f);
    pv::Vec3 b(1.0f, 2.0f, 3.0f);
    pv::Vec3 c(4.0f, 5.0f, 6.0f);

    SECTION("Equality operator") {
        REQUIRE(a == b); // a and b are equal
    }
    SECTION("Inequality operator") {
        REQUIRE(a != c); // a and c are not equal
    }
}

TEST_CASE("Vec3 += and -= operators at runtime", "[Vec3]") {
    pv::Vec3 a(1.0f, 2.0f, 3.0f);
    const pv::Vec3 b(4.0f, 5.0f, 6.0f);

    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
    REQUIRE(b.x == 4.0f);
    REQUIRE(b.y == 5.0f);
    REQUIRE(b.z == 6.0f);

    SECTION("Operator +="){
        a += b;

        REQUIRE(a.x == 5.0f);
        REQUIRE(a.y == 7.0f);
        REQUIRE(a.z == 9.0f);
        REQUIRE(b.x == 4.0f);    
        REQUIRE(b.y == 5.0f);
        REQUIRE(b.z == 6.0f);
    }

    SECTION("Operator -="){
        a -= b;
        REQUIRE(a.x == -3.0f);
        REQUIRE(a.y == -3.0f);
        REQUIRE(a.z == -3.0f);
        REQUIRE(b.x == 4.0f);
        REQUIRE(b.y == 5.0f);
        REQUIRE(b.z == 6.0f);
    }
}

TEST_CASE("Vec3 += and -= operators at compile time", "[Vec3]") {
    constexpr pv::Vec3 b(4.0f, 5.0f, 6.0f);

    SECTION("Operator +="){
        // The lambda runs during compilation; only its result needs to be constexpr
        constexpr pv::Vec3 a = [b] {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            v += b;
            return v;
        }();

        STATIC_REQUIRE(a.x == 5.0f);
        STATIC_REQUIRE(a.y == 7.0f);
        STATIC_REQUIRE(a.z == 9.0f);
    }

    SECTION("Operator -="){
        constexpr pv::Vec3 a = [b] {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            v -= b;
            return v;
        }();

        STATIC_REQUIRE(a.x == -3.0f);
        STATIC_REQUIRE(a.y == -3.0f);
        STATIC_REQUIRE(a.z == -3.0f);
    }
}
