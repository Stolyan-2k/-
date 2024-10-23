#ifndef BIT_ARR_H
#define BIT_ARR_H

#include <iostream>
#include <string>
#include <cstdint>

class BitArray {
public:
    BitArray();
    explicit BitArray(int num_bits, uint64_t default_value=0);
    ~BitArray();

    void resize(int num_bits, bool value = false);
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;
    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
    friend bool operator==(const BitArray& a, const BitArray& b);
    friend bool operator!=(const BitArray& a, const BitArray& b);
    void push_back(bool bit);
    bool empty() const;
    BitArray operator~() const;
    BitArray& operator=(const BitArray& b);
    void swap(BitArray& b);
    BitArray& set(int n, bool val = true);
    BitArray& set();
    BitArray& reset(int n);
    BitArray& reset();
    bool operator[](int i) const;
    bool any() const;
    bool none() const;
    int count() const;
    std::string to_string() const;
    void clear();
    int size() const;
private:
    uint64_t* bits_;
    int num_bits_;

    int popcount(uint64_t value) const;
};

#endif

