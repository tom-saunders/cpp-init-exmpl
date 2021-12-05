#include <cstdio>
#include <memory>
#include <sstream>

class Base {
public:
    Base();
    Base(Base const & b);
    Base(Base && b);

    Base & operator=(Base const & b);
    Base & operator=(Base && b);

    virtual ~Base();

    std::string ident() const;

private:
    std::string _ident;

protected:
    virtual std::string const & type() const;
};

class InitList {};
class Ctor {};
class Deferred {};

class Holder final {
public:
    Holder(Base b, InitList);
    Holder(Base b, Ctor);
    Holder(Deferred);
    ~Holder();

    void init(Base b);
    void copy_init(Base const & b);
    void move_init(Base && b);

    std::string ident() const;

private:
    Base _b;
};

/*
class RefHolder {
public:
    RefHolder(Base & b);
    virtual ~RefHolder();

private:
    Base & _b;
};

class RefHolder {
public:
    RefHolder(Base & b);
    virtual ~RefHolder();

private:
    Base & _b;
};

class SPtrHolder {
public:
    virtual ~SPtrHolder();
    SPtrHolder(std::shared_ptr<Base> b);

private:
    std::shared_ptr<Base> _b;
};

class UPtrHolder {
public:
    UPtrHolder(std::unique_ptr<Base> b);
    virtual ~UPtrHolder();

private:
    std::unique_ptr<Base> _b;
};
*/
