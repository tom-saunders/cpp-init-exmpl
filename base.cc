#include "base.h"

#include <atomic>
#include <cstdio>
#include <sstream>

#define F() f(this, __PRETTY_FUNCTION__)


namespace {
    std::atomic<uint32_t> base_ident{0};

    std::string convert(uint32_t const i) {
        std::ostringstream ss;
        ss << i;
        return ss.str();
    }

    template <typename P>
    void f(P p, char const * const fn) {
        std::ostringstream os;
        os << "f\t" << p << "\t" << fn;
        printf("%s\n", os.str().c_str());
    }
}

Base::Base():
        _ident(convert(base_ident++))
{
    F();
}

Base::Base(Base const & b)
{
    F();

    _ident = b._ident;
}

Base::Base(Base && b)
{
    F();

    _ident = std::move(b._ident);
}

Base &
Base::operator=(Base const & b)
{
    F();

    _ident = b._ident;
    return *this;
}

Base &
Base::operator=(Base && b)
{
    F();

    if (this != &b)
    {
        _ident = std::move(b._ident);
    }
    return *this;
}

Base::~Base()
{
    F();
}

std::string
Base::ident() const
{
    F();

    std::ostringstream ss;
    ss << this << " [" << type() << "] [" << _ident << "]";
    return ss.str();
}

namespace {
    std::string const base_type("Base");
}
std::string const &
Base::type() const
{
    return base_type;
}

Holder::Holder(Base b, InitList) :
        _b(b)
{
    F();
}

Holder::Holder(Base b, Ctor)
{
    F();

    _b = b;
}

Holder::Holder(Deferred)
{
    F();
}

Holder::~Holder()
{
    F();
}

void
Holder::init(Base b) {
    F();

    _b = b;
}

void
Holder::copy_init(Base const & b) {
    F();

    _b = b;
}

void
Holder::move_init(Base && b) {
    F();

    _b = std::move(b);
}

std::string
Holder::ident() const
{
    F();

    std::ostringstream ss;
    ss << this << " _b: [" << _b.ident() << "]";
    return ss.str();
}
