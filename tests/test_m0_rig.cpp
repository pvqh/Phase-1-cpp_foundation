// M0 -- proof that the rig works.
//
// This is the only test file I write for you. It exists to show you the Catch2
// idiom; every assertion from M1 onward is yours.
//
// Read it, then do the exercise at the bottom before you move on to M1.

#include <catch2/catch_test_macros.hpp>

// A TEST_CASE is a function Catch2 finds and runs for you. The second argument
// is a tag -- `ctest -R` and `tests.exe "[m0]"` can filter on it.
TEST_CASE("the rig builds and runs", "[m0]")
{
    // REQUIRE aborts this test case on failure.
    REQUIRE(1 + 1 == 2);

    // CHECK reports the failure and keeps going. Use CHECK when several
    // independent things are worth knowing about in one run, REQUIRE when
    // everything after it would be meaningless anyway.
    CHECK(2 * 3 == 6);
}

// SECTIONs re-run the whole enclosing TEST_CASE once per section, from the top.
// That means setup written above the sections is FRESH for each one -- no
// shared state between them, no setUp/tearDown ceremony. This is the single
// best feature Catch2 has and it is why it beats GoogleTest for this kind of
// work.
TEST_CASE("sections give each branch a clean slate", "[m0]")
{
    int value = 10;   // runs again for every SECTION below

    SECTION("one branch mutates it")
    {
        value += 5;
        REQUIRE(value == 15);
    }

    SECTION("the other branch does not see that mutation")
    {
        REQUIRE(value == 10);
    }

    SECTION("third branch also mutates it")
    {
        REQUIRE(value * 2 == 20);
    }
}

// ---------------------------------------------------------------------------
// M0 EXERCISE -- do this before starting M1.
//
// 1. Build and run. Everything above should pass.
//
// 2. Break it deliberately: change `REQUIRE(1 + 1 == 2)` to `== 3`, rebuild,
//    and run. Read the failure output carefully -- Catch2 prints the actual
//    values on both sides of the operator without you telling it to. Work out
//    how a macro could possibly know that. (Search: "Catch2 expression
//    decomposition".) Then change it back.
//
// 3. Add a THIRD section to the second test case that also starts from
//    value == 10, and make it assert something different. Confirm it passes.
//
// 4. Run the suite four ways and note what each gives you:
//        ctest --test-dir build
//        ctest --test-dir build --output-on-failure
//        ctest --test-dir build -R sections
//        .\build\bin\Debug\tests.exe "[m0]" --success
//
// 5. Delete this comment block when you have done all five. That is your
//    commit: "test(m0): prove the rig works".
// ---------------------------------------------------------------------------
