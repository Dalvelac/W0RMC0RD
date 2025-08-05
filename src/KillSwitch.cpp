#include "KillSwitch.hpp"
#include <chrono>
#include <filesystem>

KillSwitch::KillSwitch(const std::string& path) : path_(path) {}
KillSwitch::~KillSwitch() { stop(); }

void KillSwitch::start() {
    running_ = true;
    worker_ = std::thread(&KillSwitch::watch, this);
}

void KillSwitch::stop() {
    running_ = false;
    if (worker_.joinable()) {
        worker_.join();
    }
}

void KillSwitch::watch() {
    using namespace std::chrono_literals;
    while (running_) {
        if (std::filesystem::exists(path_)) {
            triggered_ = true;
            running_ = false;
            break;
        }
        std::this_thread::sleep_for(500ms);
    }
}

