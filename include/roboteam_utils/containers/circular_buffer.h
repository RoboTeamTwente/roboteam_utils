//
// Created by rolf on 26-09-20.
//

#ifndef RTT_CIRCULAR_BUFFER_H
#define RTT_CIRCULAR_BUFFER_H
#include <iterator>
#include <stdexcept>
namespace rtt::collections {
    template<typename Tp, std::size_t Size>
    class circular_buffer_iterator_type {
    private:
        Tp *const buffer;
        std::size_t offset;
    public:
        circular_buffer_iterator_type(Tp *buffer, std::size_t offset) : buffer{buffer}, offset{offset} {}

        bool operator==(const circular_buffer_iterator_type &other) {
            return other.buffer == buffer &&
                   other.offset == offset; //TODO: iterators invalidated by pushing back elements now?
        }

        bool operator!=(const circular_buffer_iterator_type &other) {
            return *this != other;
        }

        circular_buffer_iterator_type &operator++() {
            ++offset;
            return *this;
        }

        circular_buffer_iterator_type &operator--() {
            --offset;
            return *this;
        }

        std::ptrdiff_t operator-(circular_buffer_iterator_type const &other) const {
            return offset - other.offset;
        }

        circular_buffer_iterator_type &operator+=(int amount) {
            offset += amount;
            return *this;
        }

        circular_buffer_iterator_type &operator-=(int amount) {
            offset -= amount;
            return *this;
        }

        Tp &operator*() const {
            return buffer[offset % Size];
        }
    };



/**
 * @brief A standard container for Circular buffers
 * @tparam _Tp
 * @tparam _Size
 */
    template<typename Tp, std::size_t Size>
    class circular_buffer {
    public:
        typedef Tp value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef circular_buffer_iterator_type<Tp, Size> iterator;
        typedef circular_buffer_iterator_type<const Tp, Size> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    private:
        // the internal array that actually stores the values
        Tp _m_buff[Size];

        //The virtual beginning of the circular buffer
        size_type _current_offset;

        //The current size of the circular buffer
        size_type _current_size;

        Tp &last_value() {
            return _m_buff[(_current_offset + _current_size - 1) % Size];
        }

    public:
        //Default constructor
        circular_buffer() : _current_offset(0), _current_size(0) {

        }

        //modifying functions
        Tp &pop_front() {
            Tp &ret = _m_buff[_current_offset++];
            _current_offset %= Size;
            --_current_size;
            return ret;
        }

        void push_back(const Tp &value) {
            if (_current_size < max_size()) {
                ++_current_size;
            } else {
                ++_current_offset %= Size;
            }
            last_value() = value;
        }

        void push_back(Tp &&value) {
            if (_current_size < max_size()) {
                ++_current_size;
            } else {
                ++_current_offset %= Size;
            }
            last_value() = std::move(value);
        }

        //iterator functions
        constexpr iterator begin() noexcept {
            return iterator{_m_buff, _current_offset};
        }

        constexpr const_iterator begin() const noexcept {
            return const_iterator{_m_buff, _current_offset};
        }

        constexpr iterator end() noexcept { return iterator{_m_buff, _current_offset + Size}; }

        constexpr const_iterator end() const noexcept { return const_iterator{_m_buff, _current_offset + Size}; }

        constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

        constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

        constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

        constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

        constexpr const_iterator cbegin() const noexcept { return const_iterator(begin()); }

        constexpr const_iterator cend() const noexcept { return const_iterator(end()); }

        constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }

        constexpr const_reverse_iterator crend() const noexcept { return rend(); }

        //Capacity functions
        [[nodiscard]] constexpr size_type size() const noexcept { return _current_size; }

        [[nodiscard]] constexpr size_type max_size() const noexcept { return Size; }

        [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

        [[nodiscard]] constexpr bool full() const noexcept { return size() == Size; }

        //Element access
        constexpr reference operator[](size_type n) noexcept {
            return _m_buff[(_current_offset + n) % Size];
        }

        constexpr const_reference operator[](size_type n) const noexcept {
            return _m_buff[(_current_offset + n) % Size];
        }

        constexpr reference at(size_type n) {
            if (n >= Size) {
                throw std::out_of_range("index out of range of circular buffer size!");
            }
            return _m_buff[(_current_offset + n) % Size];
        }

        //Result of expression must be lvalue so we use inline boolean as follows:
        constexpr const_reference at(size_type n) const {
            if (n >= Size) {
                throw std::out_of_range("index out of range of circular buffer size!");
            }
            return _m_buff[(_current_offset + n) % Size];
        }

        constexpr reference front() noexcept { return _m_buff[_current_offset]; }

        constexpr const_reference front() const noexcept { return _m_buff[_current_offset]; }

        constexpr reference back() noexcept { return last_value(); }

        constexpr const_reference back() const noexcept {
            return _m_buff[(_current_offset + _current_size - 1) % Size];
        }

    };
}
#endif //RTT_CIRCULAR_BUFFER_H
