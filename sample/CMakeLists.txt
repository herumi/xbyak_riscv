add_executable(vector_add_rvv vector_add_rvv.cpp)
target_link_libraries(vector_add_rvv xbyak_riscv)

add_executable(vector_add_rvv_f32 vector_add_rvv_f32.cpp)
target_link_libraries(vector_add_rvv_f32 xbyak_riscv)

add_executable(add add.cpp)
target_link_libraries(add xbyak_riscv)

add_executable(cpuinfo cpuinfo.cpp)
target_link_libraries(cpuinfo xbyak_riscv)
