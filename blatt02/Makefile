#
# Variablen helfen in Makefiles copy&paste zu verringern und die "Rezepte"
# uebersichtlicher zu gestalten.
#

CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
BLATT02_1 = $(CC) $(CFLAGS) -o blatt02_1.exe blatt02_1.c
BLATT02_1_2 = $(CC) $(CFLAGS) -o blatt02_1_2.exe blatt02_1_2.c
BLATT02_1_3 = $(CC) $(CFLAGS) -o blatt02_1_3.exe blatt02_1_3.c
BLATT02_2_1 = $(CC) $(CFLAGS) -o blatt02_2_1.exe blatt02_2_1.c
BLATT02_2_2 = $(CC) $(CFLAGS) -o blatt02_2_2.exe blatt02_2_2.c
BLATT02_2_4 = $(CC) $(CFLAGS) -o blatt02_2_4.exe blatt02_2_4.c
BLATT02_2_5 = $(CC) $(CFLAGS) -o blatt02_2_5.exe blatt02_2_5.c
BLATT02_2_6 = $(CC) $(CFLAGS) -o blatt02_2_6.exe blatt02_2_6.c

# Rezept wird mit `make blatt02_1.exe` aufgerufen, Windows-Nutzer muessen vor
# `./blatt02_1.exe` ggf. das `./` entfernen.

all:
	$(BLATT02_1)
	$(BLATT02_1_2)
	$(BLATT02_1_3)
	$(BLATT02_2_1)
	$(BLATT02_2_2)
	$(BLATT02_2_4)
	$(BLATT02_2_5)
	$(BLATT02_2_6)
	blatt02_1.exe
	blatt02_1_2.exe
	blatt02_1_3.exe
	blatt02_2_1.exe
	blatt02_2_2.exe
	blatt02_2_4.exe
	blatt02_2_5.exe
	blatt02_2_6.exe
blatt02_1:
	$(BLATT02_1)
	blatt02_1.exe
blatt02_1_2:
	$(BLATT02_1_2)
	blatt02_1_2.exe
blatt02_1_3:
	$(BLATT02_1_3)
	blatt02_1_3.exe
blatt02_2_1:
	$(BLATT02_2_1)
	blatt02_2_1.exe
blatt02_2_2:
	$(BLATT02_2_2)
	blatt02_2_2.exe
blatt02_2_4:
	$(BLATT02_2_4)
	blatt02_2_4.exe
blatt02_2_5:
	$(BLATT02_2_5)
	blatt02_2_5.exe
blatt02_2_6:
	$(BLATT02_2_6)
	blatt02_2_6.exe