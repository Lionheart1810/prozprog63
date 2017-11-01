#include <stdio.h>				// Die Headerdatei stdio.h wird durch den Preprocessor hier hereinkopiert

int main() {
  int a, b;					// Integer a und b werden deklariert

  printf("\n\n Hallo TUTOR! \n\n");		// Die Zeichenkette "HALLO TUTOR!", umgeben von jeweils einem Leerzeichen und zwei Zeilenumbrüchen
  a = 22;					// a wird der Wert 22 zugewiesen
  b = 20;					// b wird der Wert 20 zugewiesen
  printf("Die Antwort ist: \t %d \n\n", a + b);	// Die Zeichenkette wird durch die Funktion printf in den Output stream geschrieben.
						// Dabei wird auch formatiert. Anstelle des %d wird die numerische Zahl aus dem nächsten Parameter gerückt.
  return 0;					// Die Funktion gibt die Konstante 0 zurück
}
