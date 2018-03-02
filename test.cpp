#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include <memory>
#include <cstdint>

#include "catch.hpp"

#include "matrix.h"


TEST_CASE("1x1", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[1] {0x50});
    Matrix m(std::move(raw_image), 1);

    REQUIRE(m.size() == 1);
    REQUIRE(m.side() == 1);
    REQUIRE(m(0, 0) == 5);

    m.rot90();
    REQUIRE(m.size() == 1);
    REQUIRE(m.side() == 1);
    REQUIRE(m(0, 0) == 5);
}

TEST_CASE("2x2", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[2] {
        0x12, 
        0x35
    });

    Matrix m(std::move(raw_image), 2);

    REQUIRE(m.size() == 4);
    REQUIRE(m.side() == 2);
    REQUIRE(m(0, 0) == 1);
    REQUIRE(m(0, 1) == 2);
    REQUIRE(m(1, 0) == 3);
    REQUIRE(m(1, 1) == 5);

    m.rot90();
    REQUIRE(m.size() == 4);
    REQUIRE(m.side() == 2);
    REQUIRE(m(0, 0) == 3);
    REQUIRE(m(0, 1) == 1);
    REQUIRE(m(1, 0) == 5);
    REQUIRE(m(1, 1) == 2);
}

TEST_CASE("3x3", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[5] {
        0x12, 0x34,  
        0x56, 0x78,
        0x90
    });

    Matrix m(std::move(raw_image), 3);

    REQUIRE(m.size() == 9);
    REQUIRE(m.side() == 3);

    REQUIRE(m(0, 0) == 1);
    REQUIRE(m(0, 1) == 2);
    REQUIRE(m(0, 2) == 3);

    REQUIRE(m(1, 0) == 4);
    REQUIRE(m(1, 1) == 5);
    REQUIRE(m(1, 2) == 6);

    REQUIRE(m(2, 0) == 7);
    REQUIRE(m(2, 1) == 8);
    REQUIRE(m(2, 2) == 9);

    m.rot90();
    REQUIRE(m.size() == 9);
    REQUIRE(m.side() == 3);

    REQUIRE(m(0, 0) == 7);
    REQUIRE(m(0, 1) == 4);
    REQUIRE(m(0, 2) == 1);

    REQUIRE(m(1, 0) == 8);
    REQUIRE(m(1, 1) == 5);
    REQUIRE(m(1, 2) == 2);

    REQUIRE(m(2, 0) == 9);
    REQUIRE(m(2, 1) == 6);
    REQUIRE(m(2, 2) == 3);
}

TEST_CASE("4x4", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[8] {
        0x01, 0x23, 
        0x45, 0x67,
        0x89, 0xAB,
        0xCD, 0xEF,
    });

    Matrix m(std::move(raw_image), 4);

    REQUIRE(m.size() == 16);
    REQUIRE(m.side() == 4);

    REQUIRE(m(0, 0) == 0);
    REQUIRE(m(0, 1) == 1);
    REQUIRE(m(0, 2) == 2);
    REQUIRE(m(0, 3) == 3);

    REQUIRE(m(1, 0) == 4);
    REQUIRE(m(1, 1) == 5);
    REQUIRE(m(1, 2) == 6);
    REQUIRE(m(1, 3) == 7);

    REQUIRE(m(2, 0) == 8);
    REQUIRE(m(2, 1) == 9);
    REQUIRE(m(2, 2) == 0xA);
    REQUIRE(m(2, 3) == 0xB);

    REQUIRE(m(3, 0) == 0xC);
    REQUIRE(m(3, 1) == 0xD);
    REQUIRE(m(3, 2) == 0xE);
    REQUIRE(m(3, 3) == 0xF);

    m.rot90();

    REQUIRE(m.size() == 16);
    REQUIRE(m.side() == 4);

    REQUIRE(m(0, 0) == 0xC);
    REQUIRE(m(0, 1) == 8);
    REQUIRE(m(0, 2) == 4);
    REQUIRE(m(0, 3) == 0);

    REQUIRE(m(1, 0) == 0xD);
    REQUIRE(m(1, 1) == 9);
    REQUIRE(m(1, 2) == 5);
    REQUIRE(m(1, 3) == 1);

    REQUIRE(m(2, 0) == 0xE);
    REQUIRE(m(2, 1) == 0xA);
    REQUIRE(m(2, 2) == 6);
    REQUIRE(m(2, 3) == 2);

    REQUIRE(m(3, 0) == 0xF);
    REQUIRE(m(3, 1) == 0xB);
    REQUIRE(m(3, 2) == 7);
    REQUIRE(m(3, 3) == 3);
}

TEST_CASE("5x5", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[13] {
              0x01, 0x23, 
        0x45, 0x67, 0x89,
        0xAB, 0xCD, 0xEF,
        0x01, 0x23, 0x45,
        0xAB, 0xCD
    });

    Matrix m(std::move(raw_image), 5);
    m.rot90();

    REQUIRE(m(0, 0) == 4);
    REQUIRE(m(0, 1) == 0xF);
    REQUIRE(m(0, 2) == 0xA);
    REQUIRE(m(0, 3) == 0x5);
    REQUIRE(m(0, 4) == 0x0);

    REQUIRE(m(1, 0) == 0x5);
    REQUIRE(m(1, 1) == 0x0);
    REQUIRE(m(1, 2) == 0xB);
    REQUIRE(m(1, 3) == 0x6);
    REQUIRE(m(1, 4) == 0x1);

    REQUIRE(m(2, 0) == 0xA);
    REQUIRE(m(2, 1) == 0x1);
    REQUIRE(m(2, 2) == 0xC);
    REQUIRE(m(2, 3) == 0x7);
    REQUIRE(m(2, 4) == 0x2);

    REQUIRE(m(3, 0) == 0xB);
    REQUIRE(m(3, 1) == 0x2);
    REQUIRE(m(3, 2) == 0xD);
    REQUIRE(m(3, 3) == 0x8);
    REQUIRE(m(3, 4) == 0x3);
    
    REQUIRE(m(4, 0) == 0xC);
    REQUIRE(m(4, 1) == 0x3);
    REQUIRE(m(4, 2) == 0xE);
    REQUIRE(m(4, 3) == 0x9);
    REQUIRE(m(4, 4) == 0x4);


    m.rot90();
    REQUIRE(m(0, 0) == 0xC);
    REQUIRE(m(0, 1) == 0xB);
    REQUIRE(m(0, 2) == 0xA);
    REQUIRE(m(0, 3) == 0x5);
    REQUIRE(m(0, 4) == 0x4);

    REQUIRE(m(1, 0) == 0x3);
    REQUIRE(m(1, 1) == 0x2);
    REQUIRE(m(1, 2) == 0x1);
    REQUIRE(m(1, 3) == 0x0);
    REQUIRE(m(1, 4) == 0xF);

    REQUIRE(m(2, 0) == 0xE);
    REQUIRE(m(2, 1) == 0xD);
    REQUIRE(m(2, 2) == 0xC);
    REQUIRE(m(2, 3) == 0xB);
    REQUIRE(m(2, 4) == 0xA);

    REQUIRE(m(3, 0) == 0x9);
    REQUIRE(m(3, 1) == 0x8);
    REQUIRE(m(3, 2) == 0x7);
    REQUIRE(m(3, 3) == 0x6);
    REQUIRE(m(3, 4) == 0x5);
    
    REQUIRE(m(4, 0) == 0x4);
    REQUIRE(m(4, 1) == 0x3);
    REQUIRE(m(4, 2) == 0x2);
    REQUIRE(m(4, 3) == 0x1);
    REQUIRE(m(4, 4) == 0x0);
}

TEST_CASE("invalid access", "[Matrix]") {
    std::unique_ptr<uint8_t[]> raw_image(new uint8_t[2] {
        0x12, 
        0x35
    });

    Matrix m(std::move(raw_image), 2);

    REQUIRE_THROWS_AS(m(0, 2), Matrix::Exception);
}


