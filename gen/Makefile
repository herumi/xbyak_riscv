TARGET=../xbyak_riscv/xbyak_riscv.hpp ../xbyak_riscv/xbyak_riscv_mnemonic.hpp ../xbyak_riscv/xbyak_riscv_v.hpp
all: $(TARGET) ../CMakeLists.txt ../meson.build ../readme.md
../xbyak_riscv/xbyak_riscv_mnemonic.hpp: gen.py copyright.py ../xbyak_riscv/xbyak_riscv.hpp
	python3 gen.py > $@
	python3 bin2hex.py $@

../xbyak_riscv/xbyak_riscv.hpp: bit_pattern.py replace.py
	python3 replace.py
	python3 bin2hex.py $@

../xbyak_riscv/xbyak_riscv_v.hpp: gen_v.py copyright.py
	python3 gen_v.py > $@
	python3 bin2hex.py $@

VER=$(shell head -n 1 ../xbyak_riscv/xbyak_riscv_mnemonic.hpp|grep -o "[0-9.]*")
../CMakeLists.txt: $(TARGET)
	sed -i -e 's/CXX VERSION [0-9.]*/CXX VERSION $(VER)/' $@

../meson.build: $(TARGET)
	sed -i -e "s/version: '[0-9.]*',/version: '$(VER)',/" $@

../readme.md: $(TARGET)
	sed -l 2 -i -e "s/# Xbyak_riscv [0-9.]*/# Xbyak_riscv $(VER)/" $@
