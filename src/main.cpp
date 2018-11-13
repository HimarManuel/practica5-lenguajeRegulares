#include "../include/calculator_t.hpp"

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

/*
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
*/
/*while (true) {
  cout << "----------------------------------------------\n";
  string s;
  cin >> s;
  language_t l1(s);
  cout << "Resultado: "; l1.write(); cout << "\n";
}*/
/*
string s;
cin >> s;
language_t l1;
l1 = l1.split(s);
l1.kleene(INF_LIMIT).write();*/

calculator_t cal;

int opt;
while (opt != 10) {
    cout << "1. Inversa\n";
    cout << "2. Concatenacion\n";
    cout << "3. Union\n";
    cout << "4. Interseccion\n";
    cout << "5. Diferencia\n";
    cout << "6. Sublenguajes\n";
    cout << "7. Igualdad de lenguajes\n";
    cout << "8. Potencia\n";
    cout << "9. Cierre de Kleene\n";
    cout << "10. Salir\n";
    cout << "\n";
    cout << ">>> Introduzca una opcion: ";
    cin >> opt;

    switch (opt) {
      case 1:
        cal.reverse();
        break;
      case 2:
        cal.concatenation();
        break;
      case 3:
        cal.join();
        break;
      case 4:
        cal.intersection();
        break;
      case 5:
        cal.difference();
        break;
      case 6:
        cal.sublanguage(); //booleano
        break;
      case 7:
        cal.equal(); //booleano
        break;
      case 8:
        cal.power();
        break;
      case 9:
        cal.kleene();
        break;
      case 10:
        cout << "Ha salido del programa...\n";
        break;
      deafult:
        cerr << "ERROR. No ha seleccionado ningun valor de entre los disponibles." << "\n";
    }
    if (opt != 6 && opt != 7 && opt != 10) {
      cout << "\n------------------------------------------------------------------\n";
      cal.show_result();
      cout << "\n------------------------------------------------------------------\n";
    }
  }
}
