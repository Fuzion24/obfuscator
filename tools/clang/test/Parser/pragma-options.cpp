// RUN: %clang_cc1 -triple i386-apple-darwin9 -fsyntax-only -verify %s

class C {
#pragma options align=natural
};
