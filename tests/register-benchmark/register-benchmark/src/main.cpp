#include <chrono>
#include <cinttypes>
#include <iostream>
#include <functional>
#include <string>

using namespace std::chrono;

using u32 = std::uint32_t;

using FunctionPtr = void(*)(int);

union RealBitField
{
    u32 data;
    struct
    {
        u32 a : 8;
        u32 b : 8;
        u32 c : 8;
        u32 d : 8;
    };
};

template<int position, int size>
class FakeBitField
{
public:
    FakeBitField(u32& data) : data(data) { }

    inline FakeBitField& operator=(u32 value)
    {
        data = (data & ~(mask << position)) | ((value & mask) << position);
        return *this;
    }

    inline operator u32() const
    {
        return (data >> position) & mask;
    }

private:
    enum { mask = (1ull << size) - 1 };
    u32& data;
};

void benchmark(FunctionPtr func, int times, const std::string& name)
{
    auto start = high_resolution_clock::now();

    for (int i = 0; i < times; ++i)
    {
        func(times);
    }

    std::cout
        << (times * times)
        << " iterations of '"
        << name
        << "' took "
        << duration_cast<milliseconds>(high_resolution_clock::now() - start).count()
        << "ms\n";
}

void bm_real(int times)
{
    RealBitField field;
    field.data = 0xAABBCCDD;

    for (int i = 0; i < times; ++i)
    {
        // 10 reads
        volatile int av = field.a;
        volatile int bv = field.b;
        volatile int cv = field.c;
        volatile int dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;
        av = field.a; bv = field.b; cv = field.c; dv = field.d;

        // 10 writes
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
        field.a = av; field.b = bv; field.c = cv; field.d = dv;
    }
}

void bm_fake(int times)
{
    u32 data = 0xAABBCCDD;

    FakeBitField< 0, 8> a(data);
    FakeBitField< 8, 8> b(data);
    FakeBitField<16, 8> c(data);
    FakeBitField<24, 8> d(data);

    for (int i = 0; i < times; ++i)
    {
        // 10 reads
        volatile int av = a;
        volatile int bv = b;
        volatile int cv = c;
        volatile int dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;
        av = a; bv = b; cv = c; dv = d;

        // 10 writes
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
        a = av; b = bv; c = cv; d = dv;
    }
}

void bm_loop(int times)
{
    for (int i = 0; i < times; ++i)
    {
        volatile int vi = i;
    }
}

int main(int argc, char* argv[])
{
    benchmark(bm_real, 10000, "Real bitfield");
    benchmark(bm_fake, 10000, "Fake bitfield");
    benchmark(bm_loop, 10000, "Empty loop");

    /**
     * 100.000.000 iterations:
     * Debug:
     *     real:   7229ms
     *     fake: 153479ms
     *     loop:    153ms
     * Release (with debug information, less optimization)
     *     real:  7283ms
     *     fake: 10810ms
     *     loop:   152ms
     * Release (full optimization)
     *     real: 1521ms
     *     fake: 1470ms
     *     loop:   22ms
     */

    return 0;
}