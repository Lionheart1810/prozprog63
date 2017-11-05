#include <stdio.h>                                                          // Einfügen der Headerdatei durch den Preprocessor.
#include <stdint.h>                                                         // Einfügen der Headerdatei durch den Preprocessor.

int main() {                                                                // Die Funktion main vom Typ (32-Bit signed) Integer wird deklariert und definiert als...
  int16_t a_16, b_16, c_16;                                                 // Die vorzeichenbehafteten 16-Bit Ganzzahlen a_16, b_16 und c_16 werden deklariert.
  int32_t a_32, b_32, c_32;                                                 // Die vorzeichenbehafteten 32-Bit Ganzzahlen a_32, b_32 und c_32 werden deklariert.
  uint16_t a_u16, b_u16, c_u16;                                             // Die vorzeichenlosen 16-Bit Ganzzahlen a_u16, b_u16 und c_u16 werden deklariert.

  b_16 = a_16 = 22222;                                                      // b_16 und a_16 wird der Wert 22222 zugewiesen.
  b_32 = a_32 = 22222;                                                      // b_32 und a_32 wird der Wert 22222 zugewiesen.

  c_32 = a_32 + b_32;                                                       // Die Werte von a_32 und b_32 werden addiert und das Ergebnis wird in c_32 gespeichert.
																			// Somit ist c_32 = 22222 + 22222 = 44444.
  c_16 = a_16 + b_16;                                                       // Die Werte von a_16 und b_16 werden addiert und das Ergebnis wird in c_16 gespeichert.
                                                                            /// Hier kommt es zu einem Überlauf / wrap around!
                                                                            /*
                                                                             *  Die obere Grenze des Wertebereiches einer vorzeichenbehafteten 16-Bit Ganzzahl ist 32767.
                                                                             *  Diese wird durch die Addition 22222 + 22222 = 44444 überschritten.
                                                                             *  Wrap around: Aufgrund der Darstellung im Zweierkomplement fängt die Zählung beim Überschreiten der
                                                                             *  oberen Grenze an der unteren Grenze (-32768) wieder an, da z.B. 01111111 (127) + 1 (1) = 10000000 (-128).
                                                                             *  Somit ergibt sich der Wert für c_16 = -32768 + 44444 - 32768 = -21092.
                                                                             */
  printf("a_32 + b_32 = %d + %d = %d \n\n", a_32, b_32, c_32);              // Die Zeichenkette mit Darstellung der Addition der 32-Bit Ganzzahlen wird in den output stream geschrieben.
  printf("a_16 + b_16 = %hd + %hd = %hd\n\n", a_16, b_16, c_16);            // Die Zeichenkette mit Darstellung der Addition der 16-Bit Ganzzahlen wird in den output stream geschrieben.

  a_u16 = a_16 + c_32;                                                      // Die Werte von a_16 und c_32 werden addiert und das Ergebnis wird in a_u16 gespeichert.
                                                                            /// Hier kommt es zu einem Überlauf / wrap around!
                                                                            /*
                                                                             *  Die obere Grenze des Wertebereiches einer vorzeichenlosen 16-Bit Ganzzahl ist 65535.
                                                                             *  Diese wird durch die Addition 22222 + 44444 = 66666 überschritten.
                                                                             *  Wrap around: Aufgrund der Darstellung im Zweierkomplement fängt die Zählung beim Überschreiten der
                                                                             *  oberen Grenze an der unteren Grenze (0) wieder an.
                                                                             *  Somit ergibt sich der Wert für a_u16 = 0 + 66666 - 65535 = 1130.
                                                                             */
                                                                            /// Hier kommt es zu einer impliziten Typumwandlung!
                                                                            /*
                                                                             *  Der Ausdruck a_16 (16-Bit signed) + c_32 (32-Bit signed) ist vom höchsten Typ der Operanden (32-Bit signed).
                                                                             *  Dieser wird dann jedoch in den Typ 16-Bit unsigned "gepresst" (höherwertige Bits aus dem s32 Bereich fallen weg).
                                                                             */
  printf("a_16 + c_32 = %hd + %d = %hu\n\n", a_16, c_32, a_u16);            /*  
                                                                             *  Die Zeichenkette mit Darstellung der Addition der vorzeichenbehafteten 16-Bit Ganzzahl mit der vorzeichenbehafteten 32-Bit Ganzzahl,
                                                                             *  dessen Ergebnis im Typ einer vorzeichenlosen 16-Bit Ganzzahl gespeichert ist, wird in den output stream geschrieben.
                                                                             */

  a_u16 = 2222;                                                             // a_u16 wird der Wert 2222 zugewiesen.
  b_u16 = -222;                                                             // b_u16 wird der Wert -222 zugewiesen.
                                                                            // Dieser Wert ist vorzeichenbehaftet, liegt außerhalb des Wertebereiches von u16 und es kommt zu einem wrap around.
                                                                            /// Hier kommt es zu einem Überlauf / wrap around!
                                                                            /*
                                                                             *  Die untere Grenze des Wertebereiches einer vorzeichenlosen 16-Bit Ganzzahl ist 0.
                                                                             *  Diese wird durch Zuweisung des Wertes -222 unterschritten.
                                                                             *  Wrap around: Aufgrund der Darstellung im Zweierkomplement fängt die Zählung beim Unterschreiten der
                                                                             *  unteren Grenze an der oberen Grenze (65535) wieder an.
                                                                             *  Somit ergibt sich der Wert für b_u16 = 65536 - 222 = 65313
                                                                             */
  c_u16 = a_u16 + b_u16;                                                    // Die Werte von a_u16 und b_u16 werden addiert und das Ergebnis wird in c_u16 gespeichert.
  printf("a_u16 + b_u16 = %hu(=%hd) + %hu(=%hd) = %hu(=%hd)\n\n", a_u16,
         a_u16, b_u16, b_u16, c_u16, c_u16);                                // Die Zeichenkette mit Darstellung der Addition von a_u16 und b_u16 wird in den output stream geschrieben.
                                                                            /*
                                                                             *  Dabei wird in der Darstellung die jeweiligen Werte durch Formatierungsanweisungen jeweils einmal als vorzeichenlose (%hu)
                                                                             *  und vorzeichenbehaftete (%hd) Dezimalzahlen interpretiert und formatiert.
                                                                             *  Daher wird bei der vorzeichenbehafteten Interpretation auch der vermutlich richtige Wert für b_u16 dargestellt.
                                                                             */

  a_32 = 555;                                                               // a_32 wird der Wert 555 zugewiesen.
  b_32 = 1001;                                                              // b_32 wird der Wert 1001 zugewiesen.
  c_16 = c_32 = a_32 * b_32;                                                // Die Werte von a_32 und b_32 werden multipliziert und das Ergebnis wird in c_32 und c_16 gespeichert.
                                                                            /// Hier kommt es zu einem Überlauf / wrap around!
                                                                            /*
                                                                             *  Die obere Grenze des Wertebereiches einer vorzeichenbehafteten 16-Bit Ganzzahl ist 32767.
                                                                             *  Der s16 Wertebereich wird durch die Multiplikation 555 * 1001 = 555555 mehrmals durchlaufen und die obere Grenze (32767) mehrmals überschritten.
                                                                             *  Wrap around: Aufgrund der Darstellung im Zweierkomplement fängt die Zählung beim Überschreiten der
                                                                             *  oberen Grenze an der unteren Grenze (-32768) wieder an, da z.B. 01111111 (127) + 1 (1) = 10000000 (-128).
                                                                             *  Somit ergibt sich der Wert für c_16 = ((555555 / 65536) - n) * 555555 = ((555555 / 65536) - 8) * 555555 = 31267 (n: Anzahl der Grenzüberschreitungen)
                                                                             *  555555 liegt noch im Wertebereich von s32 drin, daher wird dort der richtige Wert ohne Informationsverlust gespeichert.
                                                                             */
  printf("c_16 = c_32 = a_32 * b_32\n");                                    // Die Zeichenkette mit Darstellung der Multiplikation von a_32 und b_32 wird in den output stream geschrieben.
  printf("%hd = %d = %d * %d\n\n", c_16, c_32, a_32, b_32);                 // Die Zeichenkette mit Darstellung der Multiplikation von a_32 und b_32 wird mit Formatierung der Werte in den output stream geschrieben.
  c_32 = c_16 = a_32 * b_32;                                                // Die Werte von a_32 und b_32 werden multipliziert und das Ergebnis wird zunächst in c_16 gespeichert.
                                                                            /// Hier kommt es zu einem Überlauf / wrap around!
                                                                            /*
                                                                             *  Die obere Grenze des Wertebereiches einer vorzeichenbehafteten 16-Bit Ganzzahl ist 32767.
                                                                             *  Der s16 Wertebereich wird durch die Multiplikation 555 * 1001 = 555555 mehrmals durchlaufen und die obere Grenze (32767) mehrmals überschritten.
                                                                             *  Wrap around: Aufgrund der Darstellung im Zweierkomplement fängt die Zählung beim Überschreiten der
                                                                             *  oberen Grenze an der unteren Grenze (-32768) wieder an, da z.B. 01111111 (127) + 1 (1) = 10000000 (-128).
                                                                             *  Somit ergibt sich der Wert für c_16 = ((555555 / 65536) - n) * 555555 = ((555555 / 65536) - 8) * 555555 = 31267 (n: Anzahl der Grenzüberschreitungen)
                                                                             */
                                                                            // Dort steht mit Klammern: c_32 = (c_16 = a_32 * b_32). Eine Zuweisung gibt den zugewiesenen und damit (c_16 = a_32 * b_32) gerade den falschen Wert wieder.
  printf("c_32 = c_16 = a_32 * b_32\n");                                    // Die Zeichenkette mit Darstellung der Multiplikation von a_32 und b_32 wird in den output stream geschrieben.
  printf("%d = %hd = %d * %d\n\n", c_32, c_16, a_32, b_32);                 // Die Zeichenkette mit Darstellung der Multiplikation von a_32 und b_32 wird mit Formatierung der Werte in den output stream geschrieben.

  return 0;                                                                 // Die Funktion main gibt den konstanten Wert 0 zurück.
}
