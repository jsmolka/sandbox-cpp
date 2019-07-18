#include <array>
#include <iostream>

template<typename T>
using Executor = void(*)(T);

using IntExecutor = Executor<int>;

template<int arg>
void func(int value)
{
    std::cout << (arg * value) << std::endl;
}

template<int arg>
constexpr IntExecutor emitExecutor()
{
    // Do something with arg and return a matching executor function
    return func<arg>;
}

// My hero: https://stackoverflow.com/a/57092468/7057528

template <std::size_t ... Is>
constexpr std::array<IntExecutor, sizeof...(Is)> makeLutHelper(std::index_sequence<Is...>)
{
    return { emitExecutor<(int)Is>()... };
}

template <std::size_t N>
constexpr auto makeLut()
{
    return makeLutHelper(std::make_index_sequence<N>{});
}

constexpr auto lut = makeLut<0x1100>();

int main(int argc, char* argv[])
{
    for (const auto& func : lut) 
        func(10);

    return 0;
}