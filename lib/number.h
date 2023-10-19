#pragma once
#include <cinttypes>
#include <iostream>


struct int2023_t {
    uint8_t storage[253]; //от 0 до 255 storage [0] = 0b0111111, storage[1-252] - 0b1111111
    void Fill(){
        for (int i = 0; i<253; ++i){
            storage[i] = 0;
        }
    }

};

struct Result {
    std::string digit;
    std::string bit;
};

const int NumberSystem = 256;
const int ArraySize = 253;
const int ByteSize = 8;
const int NegativeValue = 128;
const int ST[8] {128, 64, 32, 16, 8, 4, 2, 1};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator>(const int2023_t& lhs, const int2023_t& rhs);

bool operator>=(const int2023_t& lhs, const int2023_t& rhs);

bool operator<(const int2023_t& lhs, const int2023_t& rhs);

bool operator<=(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);
