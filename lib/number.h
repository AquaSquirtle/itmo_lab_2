#pragma once
#include <cinttypes>
#include <iostream>

static const int32_t kNumberSystem = 256;
static const uint8_t kSize = 253;
static const uint8_t kByteSize = 8;
static const uint8_t kNegativeValue = 128;
static const uint8_t kSt[8] {128, 64, 32, 16, 8, 4, 2, 1};

struct int2023_t {
    uint8_t bytes[kSize]; //от 0 до 255 storage [0] = 0b0111111, storage[1-252] - 0b1111111
    void Fill(){
        for (int i = 0; i<kSize; ++i){
            bytes[i] = 0;
        }
    }

};

struct Result {
    std::string digit;
    std::string bit;
};



static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator>(const int2023_t& lhs, const int2023_t& rhs);

bool operator>=(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator<=(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
