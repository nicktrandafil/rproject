struct /*0*/ [[deprecated]] x0;

struct /*1*/ [[using foo: boo]] x1;

struct /*2*/ [[foo::boo]] x2;

struct /*3*/ [[foo("]]")]] x3;

struct /*4*/ [[foo("]]" + (11_f))]] x4;

struct /*5*/ [[foo(x3)]] x5;

struct /*6*/ [[foo([x3 (10_z)])]] x6;

struct /*7*/ [[foo, boo]] x7;

struct /*8*/ [[foo,]] x8;

struct /*9*/ [[]] x9;

struct /*10*/ [[foo(boo doo)]] x10;
