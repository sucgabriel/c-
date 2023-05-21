#include "particules/abstract_part.hxx"

void Flag::set(uint8_t n) {
    this->bits.set(n);
}

void Flag::set(const Flag &multi_flag) {
    this->bits |= multi_flag.bits;
}

void Flag::unset(uint8_t n) {
    this->bits.set(n, 0);
}

void Flag::unset(const Flag &multi_flag) {
    this->bits &= ~multi_flag.bits;
}

void Flag::flip(uint8_t n) {
    this->bits.flip(n);
}

void Flag::flip(const Flag &multi_flag) {
    this->bits ^= multi_flag.bits;
}

bool Flag::operator[](uint8_t n) const {
    return this->bits.test(n);
}

bool Flag::operator[](const Flag &multi_flag) const {
    return (this->bits & multi_flag.bits).any();
}

uint8_t Flag::operator()() const {
    return this->bits.to_ulong();
}

Flag Flag::operator|(const Flag &other) const {
    return Flag(this->bits | other.bits);
}

Flag &Flag::operator|=(const Flag &other) {
    this->bits |= other.bits;
    return *this; 
}

Flag Flag::operator&(const Flag &other) const {
    return Flag(this->bits & other.bits);
}

Flag &Flag::operator&=(const Flag &other) {
    this->bits &= other.bits;
    return *this; 
}

bool Flag::operator==(uint8_t n) const {
    return this->bits.to_ulong() == n;
}

bool Flag::operator==(const Flag &f) const {
    return this->bits.to_ulong() == f.bits.to_ulong();
}

Flag::Flag(std::bitset<NB_CAT> bits) : bits(bits) {}

Flag::Flag(uint8_t n) {
    std::bitset<NB_CAT> bits(n);
    this->bits = bits;
}