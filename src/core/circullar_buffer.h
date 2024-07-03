#pragma once

#include <cstdint>
#include <cassert>

struct	thread_unsafe_incdec {
    typedef	uint32_t counter_t;
    static inline void inc (counter_t &val) { ++val; }
    static inline void dec (counter_t &val) { --val; }
    static inline void zero (counter_t &val) { val = 0; }
};

template<class T, int number_of_elements_pow2, typename incdec = thread_unsafe_incdec>
class circular_buffer {
public:
    enum {
        bufsize = 1 << number_of_elements_pow2,
        mask = bufsize - 1,
        u32_max = uint32_t(-1)
    };

    uint32_t readptr, writeptr;
    typename incdec::counter_t counter;
    T buffer[bufsize];

public:
    inline	circular_buffer	() : readptr(0), writeptr(0), counter(0)	{}

    uint32_t size () const { return counter; }
    bool empty() const { return 0 == counter; }
    bool full() const { return bufsize == counter; }

    inline	const T &operator[](uint32_t index) const {
        assert(index < counter);
        return this->buffer[(this->readptr + index) & mask];
    }

    inline T &operator[](uint32_t index) {
        assert(index < counter);
        return this->buffer[(this->readptr + index) & mask];
    }

    bool write_head(const T &e) {
        if (counter == bufsize) {
            return false;
        }

        readptr = (readptr - 1)&mask;
        buffer[readptr]	= e;
        incdec::inc(counter);
        return true;
    }

    bool write_tail(const T &e) {
        if (counter == bufsize) {
            return false;
        }

        buffer[writeptr] = e;
        writeptr = (writeptr + 1)&mask;
        incdec::inc(counter);
        return true;
    }

    bool write_tail() {
        if (counter == bufsize) {
            return false;
        }
        writeptr = (writeptr + 1)&mask;
        incdec::inc(counter);
        return true;
    }

    bool push_tail(const T &e) {
        if (full()) {
            advance();
        }
        return write_tail(e);
    }

    void write_or_swap_tail(const T &e) {
        if (!write_tail(e)) {
            buffer[tail_idx()] = e;
        }
    }

    bool read(T &e) {
        if (empty()) {
            return false;
        }
        e = buffer[readptr];
        readptr = (readptr + 1)&mask;
        incdec::dec(counter);
        return true;
    }

    bool read_swap(T &e) {
        if (empty()) {
            return false;
        }
        std::swap(e, buffer[readptr]);
        readptr = (readptr + 1)&mask;
        incdec::dec(counter);
        return true;
    }

    bool swap_tail(const T &e) {
        if (empty()) {
            return false;
        }
        buffer[tail_idx()] = e;
        return true;
    }

    uint32_t tail_idx() const { return ((writeptr - 1)&mask); }
    uint32_t head_idx() const { return (readptr); }
    uint32_t write_idx() const { return (writeptr); }
    T &tail () {
        assert(!empty());
        return (buffer[tail_idx()]);
    }
    const T &tail () const {
        assert(!empty());
        return (buffer[tail_idx()]);
    }

    T &head() {
        assert(!empty());
        return (buffer[head_idx()]);
    }

    const T &head() const {
        assert(!empty());
        return (buffer[head_idx()]);
    }

    bool try_head(T &e) {
        if (empty()) {
            return false;
        }
        e					= buffer[head_idx()];
        return				true;
    }

    void advance() {
        assert(!empty());
        readptr = (readptr + 1)&mask;
        incdec::dec(counter);
    }

    void remove_tail() {
        verify(!empty());
        writeptr = (writeptr - 1)&mask;
        incdec::dec(counter);
    }

    void clear() {
        readptr = 0;
        writeptr = 0;
        incdec::zero(counter);
    }

    /// run functor on each element
    template <class F>
    void for_each(const F &func) {
        for (uint32_t i = 0; i < counter; ++i)	{
            uint32_t rptr = (readptr + i) & mask;
            func (buffer[rptr]);
        }
    }

    /// remove element ~O(n)
    void remove(const T &e) {
        if (empty()) {
            return;
        }

        for (uint32_t i = 0; i < counter; ++i)	{
            uint32_t rptr = (readptr + i) & mask;
            // first occurance found, continue copy & remove
            if (e == buffer[rptr]) {
                remove_and_shrink(e, rptr);
                return;
            }
        }
    }

    /// remove element ~O(n), using predicate
    template <class P>
    void remove_if(const P pred) {
        if (empty()) {
            return;
        }

        for (uint32_t i = 0; i < counter; ++i)	{
            uint32_t rptr = (readptr + i) & mask;
            // first occurance found, continue copy & remove
            if (pred(buffer[rptr])) {
                remove_and_shrink_if(pred, rptr);
                return;
            }
        }
    }

    /// O(n)
    bool exist(const T &e) {
        for (uint32_t i = 0; i < counter; ++i)	{
            uint32_t rptr = (readptr + i) & mask;
            if (e == buffer[rptr]) {
                return	true;
            }
        }
        return false;
    }

    /// O(n)
    template <typename Pred>
    bool exist(const Pred &pred) {
        for (uint32_t i = 0; i < counter; ++i)	{
            uint32_t rptr = (readptr + i) & mask;
            if (pred(buffer[rptr])) {
                return	true;
            }
        }
        return false;
    }

private:
    void adjust_writeptr	(uint32_t wptr) {
        // could be done much more optimal
        wptr &= mask;
        while (wptr != writeptr) {
            writeptr--;
            writeptr &= mask;
            counter--;
        }
    }

    void remove_and_shrink(const T &e, uint32_t first_occurance) {
        uint32_t wptr = first_occurance & mask;
        uint32_t rptr = (first_occurance + 1) & mask;
        for (; rptr != writeptr; rptr = (rptr + 1)&mask)	{
            if (e != buffer[rptr])		{
                buffer[wptr & mask] = buffer[rptr];
                wptr++;
            }
        }
        adjust_writeptr(wptr);
    }

    template <class P>
    void remove_and_shrink_if(P pred, uint32_t first_occurance) {
        uint32_t wptr = first_occurance & mask;
        uint32_t rptr = (first_occurance + 1) & mask;
        for (; rptr != writeptr; rptr = (rptr + 1)&mask)	{
            if (!pred(buffer[rptr])) {
                buffer[wptr & mask] = buffer[rptr];
                wptr++;
            }
        }
        adjust_writeptr(wptr);
    }
};
