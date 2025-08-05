#include <catch2/catch_test_macros.hpp>
#include "TokenLoader.hpp"
#include <fstream>

TEST_CASE("TokenLoader filters invalid tokens", "[TokenLoader]") {
    std::ofstream file("test_tokens.txt");
    file << "validtoken1\n";
    file << "bad token\n";
    file << "validtoken2\n";
    file.close();

    TokenLoader loader("test_tokens.txt");
    auto tokens = loader.load();
    REQUIRE(tokens.size() == 2);
    std::remove("test_tokens.txt");
}

