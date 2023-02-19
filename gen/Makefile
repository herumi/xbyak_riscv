all: ../xbyak_riscv/xbyak_riscv.hpp ../xbyak_riscv/xbyak_riscv_mnemonic.hpp ../xbyak_riscv/xbyak_riscv_v.hpp

../xbyak_riscv/xbyak_riscv_mnemonic.hpp: gen.py
	python3 gen.py > $@
	python3 bin2hex.py $@

../xbyak_riscv/xbyak_riscv.hpp: bit_pattern.py replace.py
	python3 replace.py
	python3 bin2hex.py $@

../xbyak_riscv/xbyak_riscv_v.hpp: gen_v.py
	python3 gen_v.py > $@
	python3 bin2hex.py $@
