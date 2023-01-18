HEADER=../xbyak_riscv/xbyak_riscv_mnemonic.hpp

$(HEADER): gen.py bit_pattern.py replace.py
	python3 gen.py > $(HEADER)
	python3 replace.py


