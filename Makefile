PREFIX?=/usr/local
INSTALL_DIR=$(PREFIX)/include/xbyak_riscv

all:
#	$(MAKE) -C sample

clean:
	$(MAKE) -C sample clean
	$(MAKE) -C test clean

install:
	mkdir -p $(INSTALL_DIR)
	cp -pR xbyak_riscv/*.h $(INSTALL_DIR)

uninstall:
	rm -i $(INSTALL_DIR)/*.h
	rmdir $(INSTALL_DIR)

update:
	$(MAKE) -C gen

test:
	$(MAKE) clean
	$(MAKE) -C gen
	$(MAKE) -C test test

bin2hex:
	python3 gen/bin2hex.py xbyak_riscv/xbyak_riscv.hpp
	python3 gen/bin2hex.py xbyak_riscv/xbyak_riscv_csr.hpp
	python3 gen/bin2hex.py xbyak_riscv/xbyak_riscv_mnemonic.hpp

test_svc:
	$(MAKE) -C test test_svc

disas:
	riscv64-linux-gnu-as -c -o a.o a.s && riscv64-unknown-elf-objdump -d a.o
disas_c:
	riscv64-linux-gnu-as -c -o a.o a.s -march=rv64gc && riscv64-unknown-elf-objdump -d a.o

.PHONY: test update
