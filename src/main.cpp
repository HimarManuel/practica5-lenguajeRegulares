#include "../include/calculator_t.hpp"

int main (void) {

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
