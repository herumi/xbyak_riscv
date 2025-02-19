HEADER=../xbyak_riscv/xbyak_riscv_mnemonic.hpp

test: $(HEADER) jmp_test.exe
	./jmp_test.exe
	./test.sh
#	./test.sh svc

test_svc:
	./test.sh svc

%.exe: %.cpp $(HEADER)
	$(CXX) -o $@ $< -Wall -Wextra -I ../ -I ./

$(HEADER):
	$(MAKE) -C ../gen

clean:
	rm -rf generated.cpp a.out *.o *.txt *.s *.o *.exe
