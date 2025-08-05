#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include "KillSwitch.hpp"
#include <fstream>
#include <chrono>
#include <thread>

TEST_CASE("KillSwitch detects file", "[KillSwitch]") {
    std::string path = "killswitch_test";
    KillSwitch ks(path);
    ks.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::ofstream(path).close();
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    REQUIRE(ks.triggered());
    ks.stop();
    std::filesystem::remove(path);
}

