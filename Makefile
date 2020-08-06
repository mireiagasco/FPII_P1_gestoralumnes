#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------

OBJETOS	:= build/main.o build/gestoralumnes.o build/linkedlist.o build/altres.o build/cerques.o

#-------------------------------------------------------------------------------
# make commands
#-------------------------------------------------------------------------------
all: gestoralumne

gestoralumne: $(OBJETOS)
	gcc -o gestoralumne $(OBJETOS)

build/main.o: main.c gestoralumnes.h
	gcc -c main.c -o build/main.o

build/gestoralumnes.o: gestoralumnes.c gestoralumnes.h
	gcc -c gestoralumnes.c -o build/gestoralumnes.o

build/linkedlist.o: linkedlist.c gestoralumnes.h
	gcc -c linkedlist.c -o build/linkedlist.o

build/cerques.o: cerques.c gestoralumnes.h
	gcc -c cerques.c -o build/cerques.o

build/altres.o: altres.c gestoralumnes.h
	gcc -c altres.c -o build/altres.o

clean:
	rm -f gestoralumne.exe $(OBJETOS)