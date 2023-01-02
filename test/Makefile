HEADER=../xbyak_riscv/xbyak_riscv_mnemonic.hpp

test: $(HEADER)
	./test.sh

$(HEADER):
	$(MAKE) -C ../gen

clean:
	rm -rf generated.cpp a.out *.o *.txt *.s *.o
