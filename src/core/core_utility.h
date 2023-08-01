#pragma once

#if !defined(_MSC_VER) && __cplusplus < 201703L
namespace std {

template <class _Ty, size_t _Size>
constexpr size_t size(const _Ty (&)[_Size]) noexcept {
    return _Size;
}

} // namespace std
#endif
