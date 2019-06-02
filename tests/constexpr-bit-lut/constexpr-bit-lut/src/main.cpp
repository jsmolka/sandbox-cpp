#include <array>
#include <cinttypes>
#include <string_view>

using u8 = std::uint8_t;

enum BitPattern : u8
{
    Invalid,
    Pattern1,
    Pattern2,
    Pattern3
};

constexpr bool matches(const std::string_view& pattern, std::size_t bits)
{
    for (auto it = pattern.crbegin(); it != pattern.crend(); ++it)
    {
        switch (*it)
        {
        case '0': if ((bits & 0x1) == 1) return false; break;
        case '1': if ((bits & 0x1) == 0) return false; break;
        }
        bits >>= 1;
    }
    return true;
}

constexpr BitPattern decode(std::size_t bits)
{
    if (matches("0xxxxxxx", bits)) return BitPattern::Pattern1;
    if (matches("1xxxxxx1", bits)) return BitPattern::Pattern2;
    if (matches("1xxxxxx0", bits)) return BitPattern::Pattern3;

    return BitPattern::Invalid;
}

using ByteLut = std::array<BitPattern, 256>;

constexpr ByteLut generateLut()
{
    ByteLut lut = { BitPattern::Invalid };

    for (std::size_t i = 0; i < lut.size(); ++i)
        lut[i] = decode(i);

    return lut;
}

constexpr ByteLut pattern_lut = generateLut();

int main(int argc, char* argv[])
{
    constexpr BitPattern bp = pattern_lut[0b10101010];

    return 0;
}
