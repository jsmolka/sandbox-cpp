#include <array>
#include <iostream>

template<typename T>
using Executor = void(*)(T);

using IntExecutor = Executor<int>;

template<int arg>
void exec(int value)
{
    std::cout << (arg * value) << std::endl;
}

template<int value>
constexpr IntExecutor emitExecutor()
{
    return exec<value>;
}

template<typename T, class Func, std::size_t ...Is>
constexpr std::array<T, sizeof...(Is)> makeArrayImpl(Func&& func, std::index_sequence<Is...>)
{
    return { func(std::integral_constant<std::size_t, Is>{})... };
}

template<typename T, std::size_t N, class Func>
constexpr std::array<T, N> makeArray(Func&& func)
{
    return makeArrayImpl<T>(std::forward<Func>(func), std::make_index_sequence<N>{});
}

constexpr auto executors = makeArray<IntExecutor, 0x1000>([&](auto x) {
    return emitExecutor<static_cast<int>(x)>();
});

int main(int argc, char* argv[])
{
    for (const auto& executor : executors)
    {
        executor(10);
    }
    return 0;
}
