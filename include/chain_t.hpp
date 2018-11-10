#pragma once

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

/*
NO FORMAN PARTE DEL ALFABETO LOS ESPACIOS, LAS COMAS, LOS CORCHETES Y EL &
*/

class chain_t : public string {
public:
//METODOS
  chain_t (void) : string("") {}
  chain_t (string s) : string(s) {}

  ~chain_t (void) { clear(); }

/*  unsigned size (void) {
    return length();
  }*/

  chain_t concatenation (const chain_t& chain) const {
    chain_t aux(data());
    aux += chain;
    return aux;
  }

  chain_t power (unsigned n) {
    assert(n >= 0);
    if (n == 0) { return string("&"); }
    chain_t result;
    for (int i = 0; i < n; i++) {
      result += data();
    }
    return result;
  }

  chain_t reverse (void) {
    if (data() == "&") { return string(data()); }
    chain_t result;
    for (int i = size()-1; i >= 0; i--) {
      result += data()[i];
    }
    return result;
  }

  bool equal (const chain_t& c) const {
    if (length() != c.length()) return false;
    for (int i = 0; i < length(); i++) {
      if (data()[i] != c.data()[i]) return false;
    }
    return true;
  }

  ostream& write (void) const {
    if (empty()) { cout << "&"; } else {
    /*for (const char c: string(data())) {
        cout << c;
      }*/
      cout << *this;
    }
    return cout;
  }

  ostream& write (ostream& os) const {
    for (const char c: string(data())) {
      os << c;
    }
    return os;
  }

};
