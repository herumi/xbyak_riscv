HEADER=../xbyak_riscv/xbyak_riscv_mnemonic.hpp

test: $(HEADER) jmp_test
	./jmp_test
	./test.sh
#	./test.sh svc

test_svc:
	./test.sh svc

jmp_test: jmp_test.cpp
	$(CXX) -o $@ $< -Wall -Wextra -I ../ -I ./

$(HEADER):
	$(MAKE) -C ../gen

clean:
	rm -rf generated.cpp a.out *.o *.txt *.s *.o jmp_test
