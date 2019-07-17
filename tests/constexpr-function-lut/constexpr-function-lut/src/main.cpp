#include <array>
#include <memory>
#include <iostream>

template<typename T>
using Executor = void(*)(T);

using IntExecutor = Executor<int>;

template<int arg>
void func(int value)
{
    std::cout << (arg * value) << std::endl;
}

// Static for https://codereview.stackexchange.com/a/173570/160845

template<typename T, T Begin, class Func, T ...Is>
constexpr void static_for_impl(Func&& f, std::integer_sequence<T, Is...>)
{
    (f(std::integral_constant<T, Begin + Is>{ }), ...);
}

template<typename T, T Begin, T End, class Func>
constexpr void static_for(Func&& f)
{
    static_for_impl<T, Begin>(std::forward<Func>(f), std::make_integer_sequence<T, End - Begin>{ });
}

template<int N>
constexpr std::array<IntExecutor, N> makeLut()
{
    std::array<IntExecutor, N> lut = {};
    static_for<size_t, 0, N>([&](auto x) {
        lut[x] = func<x>;
    });
    return lut;
}

// MSVC has a fucking stack overflow when going higher...
constexpr auto lut = makeLut<0x250>();

int main(int argc, char* argv[])
{
    for (const auto& func : lut) 
        func(10);

    return 0;
}