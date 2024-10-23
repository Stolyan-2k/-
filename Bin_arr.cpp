#include "Bit_arr.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>

BitArray::BitArray() : bits_(nullptr), num_bits_(0) {}

BitArray::BitArray(int num_bits, uint64_t default_value) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits must be non-negative.");
    }

    num_bits_ = num_bits;
    size_t array_size = (num_bits + 63) / 64;  // Количество 64-битных слов для хранения битов
    bits_ = new uint64_t[array_size];

    // Инициализируем массив
    bits_[0] = default_value;
}


BitArray::~BitArray() {
    delete[] bits_;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits == 0) {
        clear();  // Очищаем массив
        return;
    }

    // Новый размер массива в 64-битных словах
    int new_size = (num_bits + 63) / 64;
    int prev_size = (num_bits_ + 63) / 64;

    // Создаем новый массив битов
    uint64_t* new_bits = new uint64_t[new_size];
    std::memset(new_bits, 0, sizeof(uint64_t) * new_size);

    // Копируем старые данные
    if (bits_ != nullptr) {
        std::copy(bits_, bits_ + std::min(prev_size, new_size), new_bits);
        delete[] bits_;  // Освобождаем старый массив
    }

    // Если нужно дополнить массив новыми единицами
    if (num_bits > num_bits_ && value == true) {
        for (int i = num_bits_; i < num_bits; ++i) {
            int num_word = i / 64;
            int num_bit = i % 64;
            new_bits[num_word] |= (1ULL << num_bit);  // Устанавливаем биты в 1
        }
    }

    // Обновляем указатель на новый массив и количество битов
    bits_ = new_bits;
    num_bits_ = num_bits;
}


BitArray& BitArray::operator<<=(int n) {
    if (n <= 0) {
        return *this;
    }

    if (n >= size()) {
        reset();
        return *this;
    }

    for (int i = size() - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }

    for (int i = 0; i < n; ++i) {
        set(i, false);
    }

    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n <= 0) {
        return *this;
    }

    if (n >= size()) {
        clear();
        return *this;
    }

    for (int i = 0; i < size() - n; ++i) {
        set(i, (*this)[i + n]);
    }

    for (int i = size() - n; i < size(); ++i) {
        set(i, false);
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must match for bitwise AND.");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] & b2[i]);
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must match for bitwise OR.");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] | b2[i]);
    }
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must match for bitwise XOR.");
    }
    BitArray result(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] ^ b2[i]);
    }
    return result;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    *this = *this & b;
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    *this = *this | b;
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    *this = *this ^ b;
    return *this;
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

void BitArray::push_back(bool bit) {
    resize(num_bits_ + 1);
    set(num_bits_ - 1, bit);
}

bool BitArray::empty() const {
    return num_bits_ == 0;
}

BitArray BitArray::operator~() const {
    BitArray inverted(num_bits_);
    for (int i = 0; i < num_bits_; ++i) {
        inverted.set(i, !operator[](i));
    }
    return inverted;
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        delete[] bits_;
        num_bits_ = b.num_bits_;
        size_t array_size = (num_bits_ + 63) / 64;
        bits_ = new uint64_t[array_size];
        std::memcpy(bits_, b.bits_, array_size * sizeof(uint64_t));
    }
    return *this;
}

void BitArray::swap(BitArray& b) {
    std::swap(bits_, b.bits_);
    std::swap(num_bits_, b.num_bits_);
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Index out of bounds.");
    }
    if (val) {
        bits_[n / 64] |= (1ULL << (n % 64));
    }
    else {
        bits_[n / 64] &= ~(1ULL << (n % 64));
    }
    return *this;
}

BitArray& BitArray::set() {
    std::memset(bits_, 0xFF, (num_bits_ + 63) / 64 * sizeof(uint64_t));
    return *this;
}

BitArray& BitArray::reset(int n) {
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Index out of bounds.");
    }
    bits_[n / 64] &= ~(1ULL << (n % 64));
    return *this;
}

BitArray& BitArray::reset() {
    std::memset(bits_, 0, (num_bits_ + 63) / 64 * sizeof(uint64_t));
    return *this;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= num_bits_) {
        throw std::out_of_range("Index out of range");
    }
    return (bits_[i / 64] & (1ULL << (i % 64))) != 0;
}

bool BitArray::any() const {
    for (size_t i = 0; i < (num_bits_ + 63) / 64; ++i) {
        if (bits_[i] != 0) return true;
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

int BitArray::count() const {
    int total_count = 0;
    for (size_t i = 0; i < (num_bits_ + 63) / 64; ++i) {
        total_count += popcount(bits_[i]);
    }
    return total_count;
}

std::string BitArray::to_string() const {
    std::ostringstream oss;
    for (int i = num_bits_ - 1; i >= 0; --i) {
        oss << (operator[](i) ? '1' : '0');
    }
    return oss.str();
}

void BitArray::clear() {
    delete[] bits_;
    bits_ = nullptr;
    num_bits_ = 0;
}

int BitArray::size() const {
    return num_bits_;
}

int BitArray::popcount(uint64_t value) const {
    int count = 0;
    while (value) {
        count += value & 1;
        value >>= 1;
    }
    return count;
}
