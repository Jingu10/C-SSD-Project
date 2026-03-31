#pragma once
#include <cstdint>
#include <array>
#include <string>

class SSDMemory {
public:
    static constexpr size_t SIZE = 100;
private:
    std::array<uint32_t, SIZE> _memory;

public:
    
    SSDMemory();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    uint32_t read(size_t addr) const;
    void write(size_t addr, uint32_t value);
};