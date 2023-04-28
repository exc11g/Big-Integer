#include "number.h"
#include <cstring>
#include <cmath>

uint2022_t from_uint(uint32_t i) {
    uint2022_t num;
    num.nums[0] = i % MAX_DIGIT;
    num.nums[1] = i / MAX_DIGIT;

    return num;
}

uint2022_t from_string(const char* buff) {
    uint16_t len = std::strlen(buff);
    if (len > MAX_LEN_OF_NUM) {
        std::cout << "Undefined Behavior" << std::endl;
        len = MAX_LEN_OF_NUM;
    }

    uint2022_t result;
    uint8_t index = 0;
    uint8_t count = 0;

    for (uint16_t i = len; i > 0; --i) {
        if (((int)buff[i - 1] - 48) != 0) {
            result.nums[index] += ((int) buff[i - 1] - 48) * (int) pow(10, count);
        }
        ++count;
        if (count == 9) {
            count = 0;
            ++index;
        }
    }

    return result;
}

void print_struct(uint2022_t num) {
    for (uint8_t i = 0; i < SIZE; ++i) {
        std::cout << num.nums[i] << " ";
    }
    std::cout << std::endl;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    for (uint8_t i = 0; i < SIZE; ++i) {
        if (lhs.nums[i] + rhs.nums[i] >= MAX_DIGIT) {
            result.nums[i] += (lhs.nums[i] + rhs.nums[i]) % MAX_DIGIT;
            if (i + 1 == SIZE) {
                std::cout << "Undefined Behavior" << std::endl;
            } else {
                result.nums[i + 1] = 1;
            }
        } else {
            result.nums[i] += (lhs.nums[i] + rhs.nums[i]);
        }
    }

    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint2022_t copyLhs = lhs;
    for (uint8_t i = 0; i < SIZE; ++i) {
        if (copyLhs.nums[i] < rhs.nums[i]) {
            result.nums[i] = MAX_DIGIT - (rhs.nums[i] - copyLhs.nums[i]);
            copyLhs.nums[i + 1] -= 1;
        } else {
            result.nums[i] = copyLhs.nums[i] - rhs.nums[i];
        }
    }

    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    for (uint8_t i = 0; i < SIZE; ++i) {
        for (uint8_t j = 0; j < SIZE; ++j) {
            uint64_t ans = (uint64_t)lhs.nums[i] * rhs.nums[j];
            result.nums[i + j] += ans % MAX_DIGIT;
            result.nums[i + j + 1] += ans / MAX_DIGIT;
        }
    }
    for (int i = 0; i < SIZE - 1; ++i) {
        result.nums[i + 1] += result.nums[i] / MAX_DIGIT;
        result.nums[i] %= MAX_DIGIT;
    }

    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint2022_t current;
    for (uint8_t i = SIZE; i > 0; --i) {
        for (uint8_t j = SIZE; j > 0; --j) {
            current.nums[j - 1] = current.nums[j - 1 - 1];
        }
        current.nums[0] = lhs.nums[i - 1];
        uint32_t x = 0;
        uint32_t l = 0;
        uint32_t r = MAX_DIGIT;
        while (l <= r) {
            uint32_t m = (l + r) / 2;
            uint2022_t tmp = from_uint(m) * rhs;
            if (tmp < current || tmp == current) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        result.nums[i - 1] = x;
        current = current - (rhs * from_uint(x));
    }

    return result;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (uint8_t i = 0; i < SIZE; ++i) {
        if (lhs.nums[i] != rhs.nums[i]) {
            return false;
        }
    }

    return true;
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (uint8_t i = SIZE; i > 0; --i) {
        if (lhs.nums[i - 1] < rhs.nums[i - 1]) {
            return true;
        } else if (lhs.nums[i - 1] > rhs.nums[i - 1]) {
            return false;
        }
    }

    return false;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

uint8_t GetNumLen(uint32_t num) {
    int numCopy = (int)num;
    if (numCopy == 0) {
        return 1;
    }
    uint8_t len = 0;
    while (numCopy != 0) {
        numCopy /= 10;
        ++len;
    }

    return len;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    uint8_t len = 0;
    for (uint8_t i = SIZE; i > 0; --i) {
        if (value.nums[i - 1] > 0) {
            len = i;
            break;
        }
    }
    stream << value.nums[len - 1];
    for (uint8_t i = len - 1; i > 0; --i) {
        for (uint8_t j = 0; j < (9 - GetNumLen(value.nums[i - 1])); ++j) {
            stream << '0';
        }
        stream << value.nums[i - 1];
    }

    return stream;
}
