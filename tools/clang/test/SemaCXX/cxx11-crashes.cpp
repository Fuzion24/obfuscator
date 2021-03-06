// RUN: %clang_cc1 -std=c++11 -verify %s

// rdar://12240916 stack overflow.
namespace rdar12240916 {

struct S2 {
  S2(const S2&);
  S2();
};

struct S { // expected-note {{not complete}}
  S x; // expected-error {{incomplete type}}
  S2 y;
};

S foo() {
  S s;
  return s;
}

struct S3; // expected-note {{forward declaration}}

struct S4 {
  S3 x; // expected-error {{incomplete type}}
  S2 y;
};

struct S3 {
  S4 x;
  S2 y;
};

S4 foo2() {
  S4 s;
  return s;
}

}

// rdar://12542261 stack overflow.
namespace rdar12542261 {

template <class _Tp>
struct check_complete
{
  static_assert(sizeof(_Tp) > 0, "Type must be complete.");
};


template<class _Rp>
class function // expected-note 2 {{candidate}}
{
public:
  template<class _Fp>
  function(_Fp, typename check_complete<_Fp>::type* = 0);  // expected-note {{candidate}}
};

void foobar()
{
  auto LeftCanvas = new Canvas(); // expected-error {{unknown type name}}
  function<void()> m_OnChange = [&, LeftCanvas]() { }; // expected-error {{no viable conversion}}
}

}
