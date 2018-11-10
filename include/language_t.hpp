#pragma once

#include <set>

#include "chain_t.hpp"

class language_t : set<chain_t> {
public:

  language_t (void) : set<chain_t>() {}
  language_t (const language_t& lan) : set<chain_t>() {
    for (set<chain_t>::iterator it = lan.begin(); it != lan.end(); it++) {
      insert(*it);
    }
  }

  ~language_t (void) { clear(); }

  void insert_chain (const string& s) {
    chain_t chain(s);
    insert(chain);
  }

  language_t reverse (void) {
    language_t result;
    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      chain_t c = *it;
      result.insert(c.reverse());
    }
    return result;
  }

  language_t concatenation (const language_t& l) {
    language_t result;
    for (set<chain_t>::iterator i = begin(); i != end(); i++) {
      for (set<chain_t>::iterator j = l.begin(); j != l.end(); j++) {
        result.insert(i->concatenation(*j));
      }
    }
    return result;
  }

  language_t power (unsigned n) {
    assert(n >= 0);

    language_t result;
    if (n > 0) {
      result = *this;
      for (int i = 1; i < n; i++) {
        result = result.concatenation(*this);
      }
    } else if (n == 0) {
      result.insert(string(""));
    }
    return result;
  }

  language_t join (const language_t& l) {
    language_t result(l);
    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      result.insert(*it);
    }
    return result;
  }

  language_t intersection (const language_t& l) {
    language_t result;

    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      if (l.find(*it) != set::end()) { result.insert(*it); }
    }
    return result;
  }

  language_t difference (const language_t& l) {
    language_t result(*this);
    for (set<chain_t>::iterator it = l.begin(); it != l.end(); it++) {
      result.erase(*it);
    }
    return result;
  }

  bool is_sublanguage (language_t& l) {
    for (set<chain_t>::iterator it = l.begin(); it != l.end(); it++) {
      if (find(*it) == end()) return false;
     }
     return true;
  }

  bool is_equal (const language_t& l) {
    if (size() != l.size()) return false;
    cout << "tamaño de l1: " << size() << " y l2: " << l.size() << endl;
    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      if (l.find(*it) == set::end()) return false;
    }
    return true;
  }

  ostream& write (void) const {
    if (empty()) { cout << "{}"; } else {
      set<chain_t>::iterator i = begin();
      cout << "{";
      while (i != end()) {
        (i++)->write();
        cout << (i == end() ? "" : ", ");
      }
      cout << "}";
    }
    return cout;
  }

  ostream& write (ostream& os) const {
    if (empty()) { os << "{}"; } else {
      set<chain_t>::iterator i = begin();
      os << "{";
      while (i != end()) {
        (i++)->write();
        os << (i == end() ? "" : ", ");
      }
      os << "}";
    }
    return os;
  }

  void operator= (const language_t& l) {
    clear();
    for (set<chain_t>::iterator it = l.begin(); it != l.end(); it++) {
      insert(*it);
    }
  }

};
