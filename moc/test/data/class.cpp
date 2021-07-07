/*0*/ class Class {};

/*1*/ struct Struct {};

/*2*/ union Union {};

/*3*/ class [[a]] [[b]] c1 {};

struct X {
    struct Foo {
        class Boo;
    };
};

/*4*/ class X::Foo::Boo {};

/*5*/ class B final {};

struct A {};
struct A1 {};
struct A2 {};
struct A3 {};

/*6*/ class C : A, protected X::Foo::Boo, virtual A1, protected virtual A2, virtual private A3 {};
