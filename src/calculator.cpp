#include "calculator_t.hpp"

calculator_t::calculator_t (void) : l1_(), l2_(), input_() {}
calculator_t::~calculator_t (void) {}

void calculator_t::menu (void) {
  int opt;
  while (true) {
    cout << "1. Inversa\n";
    cout << "2. Concatenacion\n";
    cout << "3. Union\n";
    cout << "4. Interseccion\n";
    cout << "5. Diferencia\n";
    cout << "6. Sublenguajes\n";
    cout << "7. Igualdad de lenguajes\n";
    cout << "8. Potencia\n";
    cout << "9. Cierre de Kleene\n";
    cout << "\n";
    cout << ">>> Introduzca una opcion: ";
    cin >> opt;

    switch (opt) {
      case 1:
        reverse();
        break;
      case 2:
        concatenation();
        break;
      case 3:
        join();
        break;
      case 4:
        intersection();
        break;
      case 5:
        difference();
        break;
      case 6:
        sublanguage(); //booleano
        break;
      case 7:
        equal(); //booleano
        break;
      case 8:
        power();
        break;
      case 9:
        kleene();
        break;
      deafult:
        cerr << "ERROR. No ha seleccionado ningun valor de entre los disponibles." << "\n";
    }
    cout << "Resultado: ";
    result_.write();
    cout << "\n";
  }
}

void calculator_t::choose2 (void) {
  cout << "Indique el primer lenguaje: ";
  cin >> input_;
  l1_ = split(input_);
  cout << "Indique el segundo lenguaje: ";
  cin >> input_;
  l2_ = split(input_);
}

void calculator_t::choose1 (void) {
  cout << "Indique un lenguaje: ";
  cin >> input_;
  l1_ = split(input_);
}

language_t calculator_t::split (const string& s) {

  if (0 != s.find("{") && (s.length()-1 != s.find("}"))) {
    cerr << "ERROR: El lenguaje debe estar definido entre corchetes.\n";
  }
  assert(0 == s.find("{") && (s.length()-1 == s.find("}")));

  language_t result;

  if (s == "{}") { return result; }

  string aux;
  int init = 1;
  int last = (s.find(",") == string::npos ? s.length()-1 : s.find(",")) ;
   while (init != s.length()) {
    aux = s.substr(init, last-init);
    if (aux.find('{') != string::npos || aux.find('}') != string::npos) { cerr << "ERROR: Las llaves no esta permitido en las cadenas del lenguaje.\n"; }
    if (aux.find('*') != string::npos) { cerr << "ERROR: El símbolo '*' no esta permitido en las cadenas del lenguaje.\n"; }
    if (aux.find('|') != string::npos) { cerr << "ERROR: El símbolo '|' no esta permitido en las cadenas del lenguaje.\n"; }
    assert(aux.find('{') == string::npos && aux.find('}') == string::npos && aux.find('*') == string::npos && aux.find('|') == string::npos);
    if (aux->data() == '&') result.insert(string("")); else result.insert(aux);
    init = last+1;
    last = s.find(",", init);
    if (last == string::npos) { last = s.find("}"); }
  }
  return result;
}

void calculator_t::reverse (void) {
  choose1();
  result_ = l1_.reverse();
}

void calculator_t::concatenation (void) {
  choose2();
  result_ = l1_.concatenation(l2_);
}

void calculator_t::join (void) {
  choose2();
  result_ = l1_.join(l2_);
}

void calculator_t::intersection (void) {
  choose2();
  result_ = l1_.intersection(l2_);
}

void calculator_t::difference (void) {
  choose2();
  result_ = l1_.difference(l2_);
}

void calculator_t::sublanguage (void) {
  choose2();
  l2_.write();
  cout << (l1_.is_sublanguage(l2_) ? " es " : " no es ") << "sublenguaje de ";
  l1_.write();
  cout << "\n";
}

void calculator_t::equal (void) {
  choose2();
  l1_.write();
  cout << " y ";
  l2_.write();
  cout << (l1_.is_equal(l2_) ? " son " : " no son ") << "iguales.\n";
}

void calculator_t::power (void) {
  choose1();
  cout << "Indica un valor: ";
  cin >> input_;
  assert(is_integer());

  result_ = l1_.power(input_);
}

void calculator_t::kleene (void) {
  choose1();
  result_ = l1_.power(INF_LIMIT);
}

bool calculator_t::is_integer (void) {
  for (int i = 0; i < input_.length(); i++) {
    if (!isdigit(input_[i])) return false;
  }
  return true;
}
