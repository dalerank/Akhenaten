#pragma once

#include <cstdint>
#include <cstring>
#include <memory>
#include <cassert>

inline uint8_t bitwise_count_bits(uint8_t v) {
    v = (v & 0x55) + ((v >> 1) & 0x55);
    v = (v & 0x33) + ((v >> 2) & 0x33);
    return (v & 0x0f) + ((v >> 4) & 0x0f);
}

template <typename parent_type>
struct bitarray_base {
    typedef parent_type self_type;
    static const uint32_t size_of_int = sizeof(uint32_t) * 8;

    inline self_type &set_one() { memset(ptr(), 0xff, size_in_bytes()); return self(); }
    inline self_type &set_zero() { memzero(ptr(), size_in_bytes()); return self(); }

    inline self_type &assign(const self_type &o) { memcpy(ptr(), o.ptr(), this->size_in_bytes()); return self(); }

    template < typename other_type >
    inline self_type &assign(const other_type &o) {
        zero();
        memcpy(ptr(), o.ptr(), _min(this->size_in_bytes(), o.size_in_bytes()));
        return self();
    }

    inline uint32_t size_in_bits() const { return self().sizeinbits(); }
    inline uint32_t size_in_bytes() const { return size_in_ints() * sizeof(uint32_t); }
    inline uint32_t size_in_ints() const { return size_in_ints(this->size_in_bits()); }

    inline self_type &one(const uint32_t id) {
        assert(id < size_in_bits());
        ptr()[id / 32] |= (1 << (id % 32));
        return self();
    }

    inline self_type &zero(const uint32_t id) {
        assert(id < size_in_bits());
        ptr()[id / 32] &= ~(1 << (id % 32));
        return self();
    }

    inline self_type &flip(const uint32_t id) {
        bool r = is_set(id);
        set(id, !r);
        return self();
    }

    inline self_type &set(const uint32_t id, bool value) {
        assert(id < size_in_bits());

        uint32_t &item = ptr()[id / 32];
        const uint32_t mask(1 << (id % 32));
        item = (item & ~mask) | (-(value != 0) & mask);

        return self();
    }

    inline self_type &zeroes(const uint32_t count) {
        assert(count <= size_in_bits());

        const uint32_t bsize = count;
        const uint32_t isize = (bsize / 32);
        for (uint32_t i = 0; i < isize; ++i) { ptr()[i] = 0; }
        for (uint32_t i = isize * 32; i < bsize; ++i) { this->zero(i); }
        return self();
    }

    inline self_type &ones(const uint32_t count) {
        assert(count <= size_in_bits());

        const uint32_t bsize = count;
        const uint32_t isize = (bsize / 32);
        for (uint32_t i = 0; i < isize; ++i) {
            ptr()[i] = uint32_t(-1);
        }
        for (uint32_t i = isize * 32; i < bsize; ++i) {
            this->one(i);
        }
        return self();
    }

    inline uint32_t test(const uint32_t id) const {
        assert(id < size_in_bits());
        return (ptr()[id / 32] & (1 << (id % 32)));
    }

    inline uint32_t is_set(const uint32_t id) const { return test(id); }
    inline uint32_t is_unset(const uint32_t id) const { return !test(id); }

    inline self_type &_or(const self_type &other) {
        verify_no_crash(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr(),
            *src_end = src_cur + other.size_in_ints();
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur) *dst_cur++ |= *src_cur++;

        return self();
    }

    inline self_type &_and(const self_type &other) {
        assert(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr(),
            *src_end = src_cur + other.size_in_ints();
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur)
            *
            dst_cur++ &= *src_cur++;
        return self();
    }
    inline self_type &neg_and(const self_type &other) {
        assert(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr(),
            *src_end = src_cur + other.size_in_ints();
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur)
            *
            dst_cur++ &= ~(*src_cur++);
        return self();
    }
    inline self_type &negate(const self_type &other) {
        assert(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr(),
            *src_end = src_cur + other.size_in_ints();
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur)
            *
            dst_cur++ = ~(*src_cur++);
        return self();
    }

    template < typename other_type > inline self_type &_and(const other_type &other) {
        const uint32_t *src_cur = other.ptr();
        const uint32_t *src_end = src_cur + _min(this->size_in_ints(), other.size_in_ints());
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur) *dst_cur++ &= *src_cur++;
        return self();
    }

    template < typename other_type > inline self_type &neg_and(const other_type &other) {
        const uint32_t *src_cur = other.ptr();
        const uint32_t *src_end = src_cur + _min(this->size_in_ints(), other.size_in_ints());
        uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur) *dst_cur++ &= ~(*src_cur++);
        return self();
    }

    inline self_type &shr(const uint32_t cl) {
        uint32_t *data = this->ptr();
        const uint32_t ints = size_in_ints();

        if (!cl) {
            return (self());
        }

        const uint32_t cli = (cl / 32);
        if (cli >= ints) {
            return this->zero();
        }

        const uint32_t rcl = cl - cli * 32;
        if (rcl) {
            // complex case
            const uint32_t lcl = 32 - rcl;
            // all but the last item
            for (uint32_t i = 0, size = ints - cli - 1; i < size; ++i) {
                data[i] = ((data[i + cli] >> rcl) | (data[i + cli + 1] << lcl));
            }
            // last item
            data[ints - cli - 1] = (data[ints - 1] >> rcl);
        } else {
            // 32bit aligned
            for (uint32_t i = 0, size = ints - cli; i < size; ++i) {
                data[i] = data[i + cli];
            }
        }
        for (uint32_t i = ints - cli; i < ints; ++i) {
            // zero padded
            data[i] = 0;
        }
        return self();
    }

    inline bool isect(const self_type &other) const {
        assert(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr();
        const uint32_t *src_end = src_cur + other.size_in_ints();
        const uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur) {
            if ((*dst_cur++) & (*src_cur++))
                return (true);
        }
        return (false);
    }
    inline bool eq(const self_type &other) const {
        assert(other.size_in_ints() == this->size_in_ints());

        const uint32_t *src_cur = other.ptr();
        const uint32_t *src_end = src_cur + other.size_in_ints();
        const uint32_t *dst_cur = this->ptr();
        while (src_end != src_cur) {
            if ((*dst_cur++) != (*src_cur++))
                return (false);
        }
        return (true);
    }

    inline bool is_zero() const { return !self().is_not_zero(); }
    inline bool is_not_zero() const {
        const uint32_t *cur = this->ptr();
        const uint32_t *end = cur + this->size_in_ints();
        for (; end != cur; ++cur) {
            if (*cur)
                return (true);
        }

        return (false);
    }
    inline bool is_not_zero(uint32_t count) const {
        assert(count <= size_in_bits());

        const uint32_t bsize = count;
        const uint32_t isize = (bsize / 32);
        uint32_t res = 0;
        for (uint32_t i = 0; i < isize; ++i) {
            res |= ptr()[i];
        }
        const uint32_t tail = bsize - isize * 32;
        if (tail)
            res |= ptr()[isize] & ((1 << tail) - 1);

        return !!res;
    }

protected:
    static inline uint32_t size_in_ints(const uint32_t size_in_bits) {
        return ((size_in_bits + size_of_int - 1) / size_of_int);
    }

private:
    inline parent_type &self() {
        return *static_cast <parent_type *> (this);
    }
    inline
        const parent_type &self() const {
        return *static_cast <
            const parent_type *> (this);
    }

public:
    inline uint32_t *ptr() {
        return self().data_ptr();
    }
    inline
        const uint32_t *ptr() const {
        return self().data_ptr();
    }

};

// statically allocated bit array
template<uint32_t bits>
struct sbitarray : public bitarray_base<sbitarray<bits>> {
private:
    typedef sbitarray self_type;

    typedef bitarray_base<sbitarray<bits>> inherited;
    friend struct bitarray_base<sbitarray<bits>>;

public:
    enum {
        capacity = bits
    };
    static const uint32_t ints = ((bits + inherited::size_of_int - 1) / inherited::size_of_int);

public:
    using inherited::one;
    inline self_type &one() {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = uint32_t(-1);
        }
        return *this;
    }

    using inherited::zero;
    inline self_type &zero() {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = 0;
        }
        return *this;
    }

    inline self_type &inv() {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = ~_data[i];
        }
        return *this;
    }

    inline self_type &inv(const uint32_t idx) {
        const bool s = is_set(idx);
        set(idx, !s);
        return *this;
    }

    inline uint32_t data(const uint32_t idx) const {
        verify_no_crash(idx < ints);
        return _data[idx];
    }
    inline self_type &data(const uint32_t idx, const uint32_t value) {
        verify_no_crash(idx < ints);
        _data[idx] = value;
        return *this;
    }

    inline uint32_t count_ones() const {
        uint32_t result = 0;
        for (uint32_t i = 0; i < ints; ++i) {
            result += bw_count_bits(_data[i]);
        }
        return (result);
    }
    inline uint32_t index_of_one(const uint32_t id) const {
        verify_no_crash(0 != this->test(id));

        const uint32_t idx = (id / 32);
        uint32_t result = 0;
        for (uint32_t i = 0; idx != i; ++i) {
            result += bw_count_bits(_data[i]);
        }
        const uint32_t cur = _data[idx] & ((1 << (id % 32)) - 1);
        result += bitwise_count_bits(cur);

        return (result);
    }

    using inherited::assign;
    inline self_type &assign(const self_type &other) {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = other._data[i];
        }
        return *this;
    }

    using inherited::_and;
    inline self_type &_and(const self_type &other) {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] &= other._data[i];
        }
        return *this;
    }
    inline self_type &_and(const self_type &lhs, const self_type &rhs) {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = (lhs._data[i] & rhs._data[i]);
        }
        return *this;
    }

    using inherited::neg_and;
    inline self_type &neg_and(const self_type &lhs, const self_type &rhs) {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = (lhs._data[i] & ~(rhs._data[i]));
        }
        return *this;
    }

    using inherited::_or;
    inline self_type &_or(const self_type &lhs, const self_type &rhs) {
        for (uint32_t i = 0; i < ints; ++i) {
            _data[i] = (lhs._data[i] | rhs._data[i]);
        }
        return *this;
    }

    inline bool is_not_zero() const {
        bool result = 0;
        for (uint32_t i = 0; i < ints; ++i) {
            result |= _data[i];
        }
        return (result);
    }
    inline bool is_not_zero(uint32_t count) const {
        return inherited::is_not_zero(count);
    };

public:
    inline const uint32_t *data_ptr() const { return (_data); }
    inline uint32_t *data_ptr() { return (_data); }
    inline uint32_t sizeinbits() const { return (bits); }

protected:
    uint32_t _data[ints];
};

using sbitarray8 = sbitarray<8>;
using sbitarray16 = sbitarray<16>;
using sbitarray32 = sbitarray<32>;
using sbitarray64 = sbitarray<64>;