#include "pv/Vec3.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <stdexcept>
#include <cstdlib>
#include <array>
#include <type_traits>
TEST_CASE("Vec3 can be made at compile time", "[Vec3]") {
    pv::Vec3 v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.x == 1.0f);    // 
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3 default constructor", "[Vec3]") {   
    SECTION("Default constructor initializes with zero values") {
        pv::Vec3 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
        REQUIRE(v.z == 0.0f);
    }

    SECTION("Default constructor initializes with array") {
        std::array<pv::Vec3, 4> arr;
        REQUIRE(arr[0].x == 0.0f);
        REQUIRE(arr[0].y == 0.0f);
        REQUIRE(arr[0].z == 0.0f);
        
        REQUIRE(arr[1].x == 0.0f);
        REQUIRE(arr[1].y == 0.0f);
        REQUIRE(arr[1].z == 0.0f);
        
        REQUIRE(arr[2].x == 0.0f);
        REQUIRE(arr[2].y == 0.0f);
        REQUIRE(arr[2].z == 0.0f);
        
        REQUIRE(arr[3].x == 0.0f);
        REQUIRE(arr[3].y == 0.0f);
        REQUIRE(arr[3].z == 0.0f);
  
    }
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
    SECTION("Vec3 v * 2.0f"){
        constexpr pv::Vec3 scaled = []() {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            float scalar = 2.0f;
            return v * scalar;
        }();

        STATIC_REQUIRE(scaled.x == 2.0f);
        STATIC_REQUIRE(scaled.y == 4.0f);
        STATIC_REQUIRE(scaled.z == 6.0f);
    }

    SECTION("Vec3 2.0f * v"){
        constexpr pv::Vec3 scaled = []() {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            float scalar = 2.0f;
            return scalar * v;
        }();
        
        STATIC_REQUIRE(scaled.x == 2.0f);
        STATIC_REQUIRE(scaled.y == 4.0f);
        STATIC_REQUIRE(scaled.z == 6.0f);
    }

    SECTION("Vec3 v / 2.0f"){
        constexpr pv::Vec3 scaled = []() {
            pv::Vec3 v(2.0f, 4.0f, 6.0f);
            float scalar = 2.0f;
            return v / scalar;
        }();

        STATIC_REQUIRE(scaled.x == 1.0f);
        STATIC_REQUIRE(scaled.y == 2.0f);
        STATIC_REQUIRE(scaled.z == 3.0f);
    }
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
    constexpr pv::Vec3 a(3.0f, 4.0f, 5.0f);
    constexpr float length_squared = a.lengthSquared();
    STATIC_REQUIRE(length_squared == 50.0f);
}

TEST_CASE("Vec3 equality and inequality operators", "[Vec3]") {
    const pv::Vec3 a(1.0f, 2.0f, 3.0f);
    const pv::Vec3 same(1.0f, 2.0f, 3.0f);
    // Each differs from a in exactly one component, so == has to check all three
    const pv::Vec3 diff_x(9.0f, 2.0f, 3.0f);
    const pv::Vec3 diff_y(1.0f, 9.0f, 3.0f);
    const pv::Vec3 diff_z(1.0f, 2.0f, 9.0f);

    SECTION("Equal vectors") {
        REQUIRE(a == same);
        REQUIRE(same == a);
        REQUIRE_FALSE(a != same);
    }

    SECTION("Differ in x only") {
        REQUIRE_FALSE(a == diff_x);
        REQUIRE_FALSE(diff_x == a);
        REQUIRE(a != diff_x);
        REQUIRE(diff_x != a);
    }

    SECTION("Differ in y only") {
        REQUIRE_FALSE(a == diff_y);
        REQUIRE_FALSE(diff_y == a);
        REQUIRE(a != diff_y);
        REQUIRE(diff_y != a);
    }

    SECTION("Differ in z only") {
        REQUIRE_FALSE(a == diff_z);
        REQUIRE_FALSE(diff_z == a);
        REQUIRE(a != diff_z);
        REQUIRE(diff_z != a);
    }

    SECTION("Same components in a different order are not equal") {
        const pv::Vec3 permuted(3.0f, 2.0f, 1.0f);
        REQUIRE_FALSE(a == permuted);
        REQUIRE(a != permuted);
    }

    SECTION("Usable at compile time") {
        constexpr pv::Vec3 ca(1.0f, 2.0f, 3.0f);
        constexpr pv::Vec3 cz(1.0f, 2.0f, 4.0f);
        STATIC_REQUIRE(ca == ca);
        STATIC_REQUIRE_FALSE(ca == cz);
        STATIC_REQUIRE(ca != cz);
        STATIC_REQUIRE_FALSE(ca != ca);
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

TEST_CASE("Vec3 *= and /= operators at runtime", "[Vec3]") {
    pv::Vec3 a(1.0f, 2.0f, 3.0f);
    const pv::Vec3 b(4.0f, 5.0f, 6.0f);

    REQUIRE(a.x == 1.0f);
    REQUIRE(a.y == 2.0f);
    REQUIRE(a.z == 3.0f);
    REQUIRE(b.x == 4.0f);
    REQUIRE(b.y == 5.0f);
    REQUIRE(b.z == 6.0f);

    SECTION("Operator *="){
        a *= b;

        REQUIRE(a.x == 4.0f);
        REQUIRE(a.y == 10.0f);
        REQUIRE(a.z == 18.0f);
        REQUIRE(b.x == 4.0f);    
        REQUIRE(b.y == 5.0f);
        REQUIRE(b.z == 6.0f);
    }

    SECTION("Operator /="){
        a /= b;
        REQUIRE(a.x == 0.25f);
        REQUIRE(a.y == 0.4f);
        REQUIRE(a.z == 0.5f);
        REQUIRE(b.x == 4.0f);
        REQUIRE(b.y == 5.0f);
        REQUIRE(b.z == 6.0f);
    }
}
     
TEST_CASE("Vec3 *= and /= operators at compile time", "[Vec3]") {
    constexpr pv::Vec3 b(4.0f, 5.0f, 6.0f);

    SECTION("Operator *="){
        // The lambda runs during compilation; only its result needs to be constexpr
        constexpr pv::Vec3 a = [b] {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            v *= b;
            return v;
        }();

        STATIC_REQUIRE(a.x == 4.0f);
        STATIC_REQUIRE(a.y == 10.0f);
        STATIC_REQUIRE(a.z == 18.0f);
    }

    SECTION("Operator /="){
        constexpr pv::Vec3 a = [b] {
            pv::Vec3 v(1.0f, 2.0f, 3.0f);
            v /= b;
            return v;
        }();

        STATIC_REQUIRE(a.x == 0.25f);
        STATIC_REQUIRE(a.y == 0.4f);
        STATIC_REQUIRE(a.z == 0.5f);
    }
}

TEST_CASE("Vec3 is trivially copyable and tightly packed", "[Vec3]") {
    SECTION("Trivially copyable") {
        // Trivially copyable means the compiler is allowed to move a Vec3 around
        // with a raw byte copy. That is what lets an array of them be memcpy'd
        // straight into a GPU buffer or a file, with no per-element work.
        STATIC_REQUIRE(std::is_trivially_copyable_v<pv::Vec3>);
        STATIC_REQUIRE(std::is_trivially_copy_constructible_v<pv::Vec3>);
        STATIC_REQUIRE(std::is_trivially_copy_assignable_v<pv::Vec3>);
        STATIC_REQUIRE(std::is_trivially_move_constructible_v<pv::Vec3>);
        STATIC_REQUIRE(std::is_trivially_move_assignable_v<pv::Vec3>);
        STATIC_REQUIRE(std::is_trivially_destructible_v<pv::Vec3>);

        // Standard layout too, so the members are laid out in declaration order
        // and the address of a Vec3 is the address of its x.
        STATIC_REQUIRE(std::is_standard_layout_v<pv::Vec3>);
    }

    SECTION("The hand-written default constructor is the one thing that is not trivial") {
        // Vec3() zeroes the members, so default construction has to run code.
        // That costs is_trivial_v, which is (trivially copyable AND trivially
        // default constructible) -- but it does NOT cost trivial copyability.
        // Zero-initialised by default is worth that trade; see the std::array
        // test above, which relies on it.
        STATIC_REQUIRE_FALSE(std::is_trivially_default_constructible_v<pv::Vec3>);
        STATIC_REQUIRE_FALSE(std::is_trivial_v<pv::Vec3>);
    }

    SECTION("No padding") {
        // 12, not 16: three floats with nothing wasted between or after them.
        STATIC_REQUIRE(sizeof(pv::Vec3) == 3 * sizeof(float));
        STATIC_REQUIRE(sizeof(pv::Vec3) == 12);
        STATIC_REQUIRE(alignof(pv::Vec3) == alignof(float));

        // An array is therefore a flat run of floats, with no gaps at the seams.
        STATIC_REQUIRE(sizeof(std::array<pv::Vec3, 4>) == 12 * sizeof(float));
        STATIC_REQUIRE(sizeof(pv::Vec3[8]) == 8 * sizeof(pv::Vec3));
    }
}


