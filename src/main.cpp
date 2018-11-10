#include "../include/language_t.hpp"

int main (void) {
/*
  string s;
  cout << "Indica una cadena: ";
  cin >> s;
  chain_t chain1 (s);
  chain_t chain2 ("adios");

  cout << "Cadena 1: ";
  chain1.write();
  cout << "\n";

  cout << "Cadena 2: ";
  chain2.write();
  cout << "\n";

  cout << "Concatenacion: ";
  chain1.concatenation(chain2).write();
  cout << "\n";

  cout << "Potencia de la cadena 1 elevada a 3: ";
  chain1.power(3).write();
  cout << "\n";

  cout << "Inversa de la cadena 2: ";
  chain2.reverse().write();
  cout << "\n";
  */


  string s;
  cout << "Indica un lenguaje: ";
  cin >> s;
  language_t l1;
  l1 = l1.split(s);
  cout << "Indica otro lenguaje: ";
  cin >> s;
  language_t l2;
  l2 = l2.split(s);
  int num;
  cout << "Indica un valor: ";
  cin >> num;
  cout << "¿Los lenguajes son iguales?: " << l1.is_equal(l2) << "\n";

  cout << "Derecho: ";
  l1.write();
  cout << "\n";
  cout << "Reves: ";
  l1.reverse().write();
  cout << "\n";

  cout << "l1 elevado a " << num << ": ";
  l1.power(num).write();
  cout << "\n";

  cout << "Concatenacion con l2: ";
  l1.concatenation(l2).write();
  cout << "\n";

  cout << "Union de las dos cadenas: ";
  l1.join(l2).write();
  cout << "\n";

  cout << "Interseccion de las dos cadenas: ";
  l1.intersection(l2).write();
  cout << "\n";

  cout << "Diferencia entre l1 y l2: ";
  l1.difference(l2).write();
  cout << "\n";

  cout << "l2 es sublenguaje de l1? " << l1.is_sublanguage(l2) << "\n";

/*language_t l1;
string s;
cin >> s;
l1.split(s).write();*/
}
