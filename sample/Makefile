CXX=riscv64-linux-gnu-g++-12
CFLAGS?=-I../ -Wall -Wextra
TARGET=add.exe
all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

%.exe: %.o
	$(CXX) $< -o $@

clean:
	rm -rf *.o *.exe

test: $(TARGET)
	env QEMU_LD_PREFIX=/usr/riscv64-linux-gnu ./add.exe
