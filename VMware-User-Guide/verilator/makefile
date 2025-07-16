# Makefile for Verilator Project

# --- Variables ---
# 最终生成的可执行文件名
TARGET = sim_verilator

# 你的 C++ 测试平台文件
CPP_SOURCES = sim_main.cpp

# 你的 Verilog 设计文件
V_SOURCES = full_adder.v
# Verilog 顶层模块名
TOP_MODULE = Vfull_adder

# --- Verilator & C++ Compiler Flags ---
# Verilator 的参数
VERILATOR_FLAGS = --cc --trace
# C++ 编译器的参数
CPP_FLAGS = -I/usr/share/verilator/include -Iobj_dir
# C++ 链接器需要链接的 Verilator 库
LD_LIBS = /usr/share/verilator/include/verilated.cpp /usr/share/verilator/include/verilated_vcd_c.cpp

# --- Rules ---
.PHONY: all run wave clean

# 默认目标：编译
all: $(TARGET)

# 编译最终的可执行文件
$(TARGET): obj_dir/$(TOP_MODULE)__ALL.a $(CPP_SOURCES)
	@echo "--- Linking executable: $(TARGET) ---"
	g++ $(CPP_FLAGS) -o $(TARGET) $(CPP_SOURCES) obj_dir/$(TOP_MODULE)__ALL.a $(LD_LIBS)

# 生成 Verilator 的静态库文件 (这是更稳健的做法)
obj_dir/$(TOP_MODULE)__ALL.a: $(V_SOURCES)
	@echo "--- Verilating $(V_SOURCES) ---"
	verilator $(VERILATOR_FLAGS) $(V_SOURCES)
	@echo "--- Compiling Verilated C++ sources ---"
	cd obj_dir && make -f $(TOP_MODULE).mk

# 运行仿真
run: $(TARGET)
	@echo "--- Running simulation ---"
	./$(TARGET)

# 查看波形
wave:
	gtkwave waveform.vcd &

# 清理所有生成的文件
clean:
	@echo "--- Cleaning up ---"
	rm -rf $(TARGET) obj_dir waveform.vcd
