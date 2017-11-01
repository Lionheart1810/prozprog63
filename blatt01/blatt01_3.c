#include <stdio.h>                                      // Die Headerdatei sdtio.h wird durch den Preprocessor hier hereinkopiert
#include <stdint.h>                                     // Die Headerdatei sdtint.h wird durch den Preprocessor hier hereinkopiert

int main() {                                            // Funktion Main wird als Typ Integer definiert
  int16_t y = 1024, z = 65;                             // auch "short" als Datentyp verwendbar, Integer 16Bit singed werden deklariert

  y = y * z;                                            // Produkt der beiden Interger wird in die Variable y gespeichert
  printf("1. Ausgabe: %d\n", y);                        // Die Variable y wird in der Zeichenkette "1.Ausgabe:" + y + "" augegeben
  printf("2. Ausgabe: %d\n", y / 3 * 3 - 3 * y / 3);    // Die Zeichenkette der Rechnung wird ausgegeben
  printf("\n");                                         // Ein Zeilenumbruch wird hinzugefügt 

  return 0;                                             // Gibt an die Funktion den Wert 0 zurück
}
