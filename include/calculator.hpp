#include "language_t.hpp"
#include <ctype.h>

#define INF_LIMIT 50


class calculator_t {
private:
  language_t l1_;
  language_t l2_;
  language_t result_;
  string input_;

public:

  calculator_t (void);
  ~calculator_t (void);

  void menu (void);

  void reverse (void);
  void concatenation (void);
  void join (void);
  void intersection (void);
  void difference (void);
  void sublanguage (void);
  void equal (void);
  void power (void);
  void kleene (void);
private:
  language_t split (const string& s);
  bool is_integer (void);
  void choose1 (void);
  void choose2 (void);
};
