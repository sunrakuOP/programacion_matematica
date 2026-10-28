# Tres programas independientes, uno por materia (cada uno es su propio .tns):
#   metodos_numericos.tns   termodinamica.tns   fluidos.tns
#
#   make            compila los tres para la TI-Nspire (requiere el SDK de Ndless en el PATH)
#   make fluidos.tns   compila solo uno
#   make test       pruebas en la Mac
#   make host-numericos | host-termo | host-fluidos     correr un menu en la Mac
COMUN = src/comun/expr.cpp src/comun/io.cpp
NUM   = src/numerico/numerico.cpp src/numerico/menu_numerico.cpp
TERMO = src/termo/termo.cpp src/termo/menu_termo.cpp
FLU   = src/fluidos/fluidos.cpp src/fluidos/menu_fluidos.cpp

PROGRAMAS = metodos_numericos termodinamica fluidos
HDRS      = $(wildcard src/*/*.hpp)
INC       = -Isrc/comun -Isrc/numerico -Isrc/termo -Isrc/fluidos

GXX       = nspire-g++
LD        = nspire-ld
GENZEHN   = genzehn
GCCFLAGS  = -Wall -W -marm -Os $(INC)
LDFLAGS   = -Wl,--nspireio

all: $(addsuffix .tns,$(PROGRAMAS))

build/%.o: src/%.cpp $(HDRS)
	mkdir -p $(@D)
	$(GXX) $(GCCFLAGS) -c $< -o $@

obj = $(patsubst src/%.cpp,build/%.o,$(1))

metodos_numericos.elf: $(call obj,$(COMUN) $(NUM) src/numerico/main_numerico.cpp)
termodinamica.elf:     $(call obj,$(COMUN) $(TERMO) src/termo/main_termo.cpp)
fluidos.elf:           $(call obj,$(COMUN) $(FLU) src/fluidos/main_fluidos.cpp)

%.elf:
	$(LD) $^ -o $@ $(LDFLAGS)

%.tns: %.elf
	$(GENZEHN) --input $< --output $@.zehn --name "$*"
	make-prg $@.zehn $@
	rm $@.zehn

test:
	mkdir -p build
	g++ -std=c++17 -Wall -Wextra $(INC) -o build/test_host test/test_main.cpp $(COMUN) $(NUM) $(TERMO) $(FLU)
	./build/test_host

host-numericos:
	mkdir -p build
	g++ -std=c++17 -Wall -Wextra $(INC) -o build/host_numericos $(COMUN) $(NUM) src/numerico/main_numerico.cpp
	./build/host_numericos
host-termo:
	mkdir -p build
	g++ -std=c++17 -Wall -Wextra $(INC) -o build/host_termo $(COMUN) $(TERMO) src/termo/main_termo.cpp
	./build/host_termo
host-fluidos:
	mkdir -p build
	g++ -std=c++17 -Wall -Wextra $(INC) -o build/host_fluidos $(COMUN) $(FLU) src/fluidos/main_fluidos.cpp
	./build/host_fluidos

clean:
	rm -rf build *.elf *.tns

.PHONY: all test host-numericos host-termo host-fluidos clean
.SECONDARY:
