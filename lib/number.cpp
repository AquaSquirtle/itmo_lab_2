#include "number.h"
#include <math.h>
#include <string>


int2023_t ReversedCode (int2023_t num){
    int2023_t result;
    for (int i = 0; i < ArraySize; ++i) {
        result.storage[i] = NumberSystem - num.storage[i] - 1;
    }
    for (int i = ArraySize - 1; i > -1; --i) {
        if (result.storage[i] + 1 > NumberSystem - 1) {
            result.storage[i] = 0;
        } else {
            result.storage[i] += 1;
            break;
        }
    }
    return result;

}

uint8_t BinToUint(short* byte){
    uint8_t result = 0;
    for (short i = 0; i < ByteSize; ++i) {
        if (byte[i] == 1) {
            result += ST[i];
        }
    }
    return result;
}

int2023_t from_int(int32_t i) {
    int2023_t number;
    number.Fill();
    short byte[ByteSize];
    for (short x = 0; x < ByteSize; ++x) {
        byte[x] = 0;
    }
    if (i < 0) {
        number.storage[0] = NegativeValue;
        i = i * -1;
    }
    short j = ArraySize - 1;
    short cur_position = ByteSize-1;
    while (j > -1 and i > 0) {
        if (cur_position == -1) {
            number.storage[j] += BinToUint(byte);
            for (short x = 0; x < ByteSize; ++x) {
                byte[x] = 0;
            }
            --j;
            cur_position = ByteSize - 1;
        } else {
            short temporary_value = i % 2;
            i = i / 2;
            byte[cur_position] = temporary_value;
            --cur_position;
        }
    }
    if (j > -1) {
        number.storage[j] += BinToUint(byte);
    }
    if (number.storage[0] >= NegativeValue) {
        number.storage[0] -= NegativeValue;
        number = ReversedCode(number);
    }
    return number;
}

Result Division (int bit, int digit){
    Result res;
    res.bit = std::to_string((bit*10+digit)%2);
    res.digit = std::to_string((bit*10+digit)/2);
    return res;
}

std::string StrToBin (std::string bits, char digit){
    std::string result_bits;
    Result res;
    res.digit = digit;
    int bit = 0;
    while (bits[bit] != '\0') {
        if (bits[bit] == '0') {
            res = Division(0, std::stoi(res.digit));
        }
        else if (bits[bit] == '1') {
            res = Division(1, std::stoi(res.digit));
        }
        result_bits += res.bit;
        ++bit;
    }
    while (res.digit != "0") {
        res = Division(0, std::stoi(res.digit));
        result_bits += res.bit;
    }
    return result_bits;
}

int2023_t DivideByTwo (int2023_t num){
    int2023_t result;
    int temp = 0;
    for (int i = 0; i < ArraySize; ++i) {
        result.storage[i] = (num.storage[i] + NumberSystem * temp) / 2;
        temp =  num.storage[i] % 2;
    }
    return result;
}

int2023_t from_string(const char* buff) {
    int2023_t number;
    number.Fill();
    short byte[ByteSize];
    for (int i = 0; i < ByteSize; ++i) {
        byte[i] = 0;
    }
    if (buff[0] == '-') {
        number.storage[0] = NegativeValue;
        ++buff;
    }
    int i = 0;
    std::string bits;
    while (buff[i] != '\0') {
        bits = StrToBin(bits, buff[i]);
        ++i;
    }
    int j = ArraySize - 1;
    int cur_position = ByteSize - 1;
    unsigned long long pointer = 0;
    while (j > -1 and bits[pointer] != '\0') {
        if (cur_position == -1) {
            number.storage[j] += BinToUint(byte);
            for (int i = 0; i < ByteSize; ++i) {
                byte[i] = 0;
            }
            cur_position = ByteSize - 1;
            --j;
        } else {
            if (bits[pointer] == '0') {
                byte[cur_position] = 0;
            } else {
                byte[cur_position] = 1;
            }
            --cur_position;
            ++pointer;
        }

    }
    if (j > -1) {
        number.storage[j] += BinToUint(byte);
    }
    if (number.storage[0] >= NegativeValue) {
        number.storage[0] -= NegativeValue;
        number = ReversedCode(number);
    }
    return number;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    result.Fill();
    int temp;
    int overlimit = 0;
    for (int i = ArraySize - 1; i > -1; --i) {
        temp = lhs.storage[i] + rhs.storage[i] + overlimit;
        result.storage[i] = temp % NumberSystem;
        overlimit = temp / NumberSystem;
    }
    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t zero = from_int(0);
    if (rhs == zero) {
        return lhs + rhs;
    }
    else {
        int2023_t right_numeber = ReversedCode(rhs);
        return lhs + right_numeber;
    }
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result;
    int2023_t temporary;
    int2023_t temp_lhs = lhs;
    int2023_t temp_rhs = rhs;
    bool is_minus = false;
    if (lhs.storage[0] < NegativeValue and rhs.storage[0] >= NegativeValue) {
        is_minus = true;
        temp_rhs = ReversedCode(temp_rhs);
    }
    else if (lhs.storage[0] >= NegativeValue and rhs.storage[0] < NegativeValue) {
        is_minus = true;
        temp_lhs = ReversedCode(temp_lhs);
    }
    else if (lhs.storage[0] >= NegativeValue and rhs.storage[0] >= NegativeValue) {
        temp_lhs = ReversedCode(temp_lhs);
        temp_rhs = ReversedCode(temp_rhs);
    }
    result.Fill();
    int offset = ArraySize - 1;
    int id;
    for (int i = ArraySize - 1; i >= 0; --i) {
        temporary.Fill();
        id = offset;
        for (int j = ArraySize - 1; j >= 0; --j) {
            int value = temp_rhs.storage[i] * temp_lhs.storage[j] + temporary.storage[id];
            if (value >= NumberSystem) {
                temporary.storage[id] = value % NumberSystem;
                temporary.storage[id - 1] = value / NumberSystem;
            } else {
                temporary.storage[id] = value;
            }
            --id;
        }
        result = result + temporary;
        --offset;
    }
    if (is_minus) {
        return ReversedCode(result);
    }
    return result;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t temp_lhs = lhs;
    int2023_t temp_rhs = rhs;
    int2023_t result;
    bool is_minus = false;
    if (lhs.storage[0] < NegativeValue and rhs.storage[0] >= NegativeValue) {
        is_minus = true;
        temp_rhs = ReversedCode(temp_rhs);
    }
    else if (lhs.storage[0] >= NegativeValue and rhs.storage[0] < NegativeValue) {
        is_minus = true;
        temp_lhs = ReversedCode(temp_lhs);
    }
    else if (lhs.storage[0] >= NegativeValue and rhs.storage[0] >= NegativeValue) {
        temp_lhs = ReversedCode(temp_lhs);
        temp_rhs = ReversedCode(temp_rhs);
    }
    if (temp_rhs == from_int(1)){
        if (is_minus) {
            return ReversedCode(temp_lhs);
        } else {
            return temp_lhs;
        }
    }
    int2023_t mid = from_int(0);
    int2023_t low = from_int(0);
    int2023_t high = from_int(0);

    if (temp_lhs > temp_rhs) {
        high = temp_lhs;
    }
    while (low <= high) {
        mid = low + DivideByTwo(high - low);
        if (mid * temp_rhs > temp_lhs) {
            high = mid - from_int(1);
        } else {
            low = mid + from_int(1);
            result = mid;
        }

    }
    if (is_minus) {
        return ReversedCode(result);
    }
    return result;
}

bool operator>(const int2023_t& lhs, const int2023_t& rhs){
    for (int i = 0; i < ArraySize; ++i) {
        if (lhs.storage[i] > rhs.storage[i]) {
            return true;
        }
        else if (lhs.storage[i] < rhs.storage[i]) {
            return false;
        }
    }
    return false;
}

bool operator<=(const int2023_t& lhs, const int2023_t& rhs){
    return (!(lhs > rhs));
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs){
    for (int i = 0; i < ArraySize; ++i) {
        if (lhs.storage[i] != rhs.storage[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = 0; i < ArraySize; ++i) {
        if (lhs.storage[i] != rhs.storage[i]) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    int2023_t result = value;
    bool is_valueable_zeros = false;
    if (result == from_int(0)) {
        stream << 0;
        return stream;
    }
    if (value.storage[0] >= NegativeValue) {
        stream << "-";
        result = ReversedCode(value);
    }

    for (int i = 0; i < ArraySize; ++i) {
        if (result.storage[i] != 0) {
            is_valueable_zeros = true;
        }
        if (is_valueable_zeros) {
            stream << result.storage[i] + 0 << ' ';
        }

    }
    return stream;
}
