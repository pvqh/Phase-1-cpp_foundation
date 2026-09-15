#include "pv/Vec3.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Vec3 can be made at compile time", "[Vec3]") {
    constexpr pv::Vec3 v(1.0f, 2.0f, 3.0f);
    STATIC_REQUIRE(v.x == 1.0f);    // 
    STATIC_REQUIRE(v.y == 2.0f);
    STATIC_REQUIRE(v.z == 3.0f);
}

TEST_CASE("Vec3 addition and subtraction", "[Vec3]"){
    pv::Vec3 a(1.0f, 2.0f, 3.0f);
    pv::Vec3 b(4.0f, 5.0f, 6.0f);

    SECTION("Addition"){
        pv::Vec3 c = a + b;
        REQUIRE(c.x == 5.0f);
        REQUIRE(c.y == 7.0f);
        REQUIRE(c.z == 9.0f);
        REQUIRE(a.x == 1.0f);    
        REQUIRE(a.y == 2.0f);
        REQUIRE(a.z == 3.0f);
    }

    SECTION("Subtraction"){
        pv::Vec3 d = a - b;
        REQUIRE(d.x == -3.0f);
        REQUIRE(d.y == -3.0f);
        REQUIRE(d.z == -3.0f);
        REQUIRE(a.x == 1.0f);    
        REQUIRE(a.y == 2.0f);
        REQUIRE(a.z == 3.0f);
    }
    
}