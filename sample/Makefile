PRE?=riscv64-linux-gnu-
CXX?=g++-13
CFLAGS?=-I../ -Wall -Wextra
CFLAGS+=-DXBYAK_RISCV_V
SRC=add.cpp cpuinfo.cpp fill.cpp vector_add_rvv.cpp vector_add_rvv_f32.cpp
OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)
TARGET=$(SRC:.cpp=.exe)
all: $(TARGET)

%.o: %.cpp
	$(PRE)$(CXX) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(@:.o=.d)

%.exe: %.o
	$(PRE)$(CXX) $< -o $@

clean:
	rm -rf *.o *.exe

-include $(DEP)

EXE?=add.exe
test: $(EXE)
	env QEMU_LD_PREFIX=/usr/riscv64-linux-gnu ./$(EXE)

.SECONDARY: $(OBJ)
