#pragma once

#include <set>
#include "chain_t.hpp"

#define INF_LIMIT 5

class language_t : set<chain_t> {
private:
  bool is_regular_mode;
  bool is_inf;
  string regular_;
public:

  language_t (void) : set<chain_t>(), is_regular_mode(false), regular_(), is_inf(false) {}

  language_t (const language_t& lan, const bool regular = false, const bool inf = false) : set<chain_t>(), is_regular_mode(regular), regular_(), is_inf(inf) {
    for (set<chain_t>::iterator it = lan.begin(); it != lan.end(); it++) {
      insert(*it);
    }
  }

  language_t (const string s, const bool regular = false) : set<chain_t>(), is_regular_mode(regular), regular_(s), is_inf(false) {
    dev(s);
  }

  ~language_t (void) { clear(); }

  void insert_chain (const string& s) {
    chain_t chain(s);
    insert(chain);
  }

  void dev (string s) {
    char op;
    string izq, der;
    language_t lang;
    language_t laux1, laux2;
    char par_op;

    if (s.find('(') != string::npos && s.find(')') != string::npos) {
      string aux = s.substr(s.find('(')+1, s.find(')')-s.find('(')-1);
      laux1 = *(new language_t (aux));
      s.erase(s.find('('), s.find(')')+1-s.find('('));
      if (!c_is_valid(s[0])) {
        par_op = s[0];
        s.erase(s.begin());
      } else if (s.length() != 0){
        par_op = '.';
      }
    }
    if (s.length() != 0) {
      if (s.find('|') != string::npos) {
        op = '|';
        izq = s.substr(0, s.find('|'));
        der = s.substr(s.find('|')+1, s.length()-s.find('|')-1);
        dev(izq, op, der, laux2);
      } else if (is_concatenation(s) != -1) {
        op = '.';
        izq = s.substr(0, is_concatenation(s)+1);
        der = s.substr(is_concatenation(s)+1, s.length()-(is_concatenation(s)+1));
        dev(izq, op, der, laux2);
      } else if (s.find('*') != string::npos) {
        if (s.find('*')+1 < s.length() && c_is_valid(s.find('*')+1)) {
          op = '.';
          izq = s.substr(0, s.find('*')+1);
          der = s.substr(s.find('*')+1, s.length()-(s.find('*')+1));
        } else {
          op = '*';
          izq = s.substr(0, s.find('*'));
          der = "NULL";
        }
        dev(izq, op, der, laux2);
      } else {
        laux2.insert_chain(s);
      }
    }
    if (laux1.empty()) {
      lang = laux2;
    } else {
      if (par_op == '|') {
        lang = laux1.join(laux2);
      } else if (par_op == '.') {
        lang = laux1.concatenation(laux2);
      } else if (par_op == '*') {
        lang = laux1.kleene(INF_LIMIT);
      } else {
        lang = laux1;
      }
    }
    *this = lang;
  }

  void dev (string izq, char op, string der, language_t& l) {

    string cizq, cder;
    char cop;

    language_t izq_lang;
    izq_lang.insert_chain(izq);
    if (izq.length() > 1) {
      if (izq.find('|') != string::npos) {
        cop = '|';
        cizq = izq.substr(0, izq.find('|'));
        cder = izq.substr(izq.find('|')+1, izq.length()-izq.find('|')-1);
      } else if (is_concatenation(izq) != -1) {
        cop = '.';
        cizq = izq.substr(0, is_concatenation(izq)+1);
        cder = izq.substr(is_concatenation(izq)+1, izq.length()-(is_concatenation(izq)+1));
      } else if (izq.find('*') != string::npos) {
        if (izq.find('*')+1 < izq.length() && c_is_valid(izq.find('*')+1)) {
          cop = '.';
          cizq = izq.substr(0, izq.find('*')+1);
          cder = izq.substr(izq.find('*')+1, izq.length()-(izq.find('*')+1));
        } else {
          cop = '*';
          cizq = izq.substr(0, izq.find('*'));
          cder = "NULL";
        }
      }
      dev(cizq, cop, cder, izq_lang);
    }

    language_t der_lang;
    der_lang.insert_chain(der);
    if (der.length() > 1) {
      if (der != "NULL") {
        if (der.find('|') != string::npos) {
          cop = '|';
          cizq = der.substr(0, der.find('|'));
          cder = der.substr(der.find('|')+1, der.length()-der.find('|')-1);
        } else if (is_concatenation(der) != -1) {
          cop = '.';
          cizq = der.substr(0, is_concatenation(der)+1);
          cder = der.substr(is_concatenation(der)+1, der.length()-(is_concatenation(der)+1));
        } else if (der.find('*') != string::npos) {
          if (der.find('*')+1 < der.length() && c_is_valid(der.find('*')+1)) {
            cop = '.';
            cizq = der.substr(0, der.find('*')+1);
            cder = der.substr(der.find('*')+1, der.length()-(der.find('*')+1));
          } else {
            cop = '*';
            cizq = der.substr(0, der.find('*'));
            cder = "NULL";
          }
        }
        dev(cizq, cop, cder, der_lang);
      }
    }

    if (op == '*') {
      l = izq_lang.kleene(INF_LIMIT);
    } else if (op == '|') {
      l = izq_lang.join(der_lang);
    } else if (op == '.') {
      l = izq_lang.concatenation(der_lang);
    }
  }

  int is_concatenation(string& s) {
    char c;
    for (int i = 0; i < s.length(); i++) {
      if (c_is_valid(s[i]) && i+1 != s.length() && c_is_valid(s[i+1])) {
        return i;
      }
    }
    return -1;
  }

  bool c_is_valid (char c) {
    if (c == '|' || c == '*' || c == '(' || c == ')' || c == ',' || c == '{' || c == '}' || c == ' ') {
      return false;
    } else {
      return true;
    }
  }

  void set_regular (string& s) {
    assert(is_regular_mode);
    regular_ = s;
  }

  void set_inf (const bool b) {
    is_inf = b;
  }

  string get_regular (void) const {
    assert(is_regular_mode);
    return regular_;
  }


  bool is_regular (void) const {
    return is_regular_mode;
  }

  bool is_INF (void) const {
    return is_inf;
  }

  void set_regular_mode (bool b) {
    is_regular_mode = b;
  }

  language_t kleene (int num) {
    language_t result;
    for (int i = 0; i <= num; i++) {
      result = result.join(power(i));
    }
    if (is_regular_mode) {
      result.set_regular_mode(true);
      string aux = "";
      aux += "(";
      aux += regular_;
      aux += ")*";
      result.set_regular(aux);
    }
    result.set_inf(true);
    return result;
  }

  language_t reverse (void) {
    language_t result;
    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      result.insert(it->reverse());
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
    if (is_regular_mode) {
      string aux = regular_;
      if (regular_.find('|') != string::npos) {
        aux.insert(0,string("(")); aux.insert(aux.length(), string(")"));
      }
      if (l.get_regular().find('|') != string::npos || is_concatenation(aux)) {
        aux += '(';
        aux += l.get_regular();
        aux += ')';
      } else {
        aux += l.get_regular();
      }
      result.set_regular_mode(true);
      result.set_regular(aux);
    }
    if (is_inf || l.is_INF()) { result.set_inf(true); }
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
    language_t result;
    result = l;
    for (set<chain_t>::iterator it = begin(); it != end(); it++) {
      result.insert(*it);
    }
    if (is_regular_mode) {
      string aux = regular_;
      if (regular_.find('|') != string::npos) {
        aux.insert(0,string("(")); aux.insert(aux.length(), string(")"));
      }
      if (l.get_regular().find('|') != string::npos || is_concatenation(aux)) {
        aux += '(';
        aux += '|'+l.get_regular();
        aux += ')';
      } else {
        aux += l.get_regular();
      }
      result.set_regular_mode(true);
    }
    if (is_inf || l.is_INF()) result.set_inf(true);
    return result;
  }

  language_t intersection (const language_t& l) {
    language_t result;

    for (set<chain_t>::iterator it = l.begin(); it != l.end(); it++) {
      if (find(*it) != set::end()) { result.insert(*it); }
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

      int cont = 0;
      cout << "{";
      while (i != end() && cont <= 10) {
        (i++)->write();
        cout << (i == end() && !is_inf ? "" : ", ");
        cont++;
      }
      if (is_inf) cout << "...";
      cout << "}";
    }
    return cout;
  }

  ostream& write (ostream& os) const {
    if (empty()) { os << "{}"; } else {
      set<chain_t>::iterator i = begin();

      int cont = 0;
      os << "{";
      while (i != end() && cont <= 10) {
        (i++)->write();
        os << (i == end() && !is_inf ? "" : ", ");
        cont++;
      }
      if (is_inf) os << "...";
      os << "}";
    }
    return os;
  }

  void operator= (const language_t& l) {
    clear();
    for (set<chain_t>::iterator it = l.begin(); it != l.end(); it++) {
      insert(*it);
    }
    is_inf = l.is_INF();
    is_regular_mode = l.is_regular();
    if (is_regular_mode) regular_ = l.get_regular();
  }

};
