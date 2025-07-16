// sim_main.cpp

#include <iostream>
#include "Vfull_adder.h"      // 包含由 Verilator 生成的模块头文件
#include "verilated.h"        // 包含 Verilator 的核心头文件
#include "verilated_vcd_c.h"  // 包含波形生成相关的头文件

int main(int argc, char** argv) {
    // 初始化 Verilator
    Verilated::commandArgs(argc, argv);

    // 实例化我们的 full_adder 模块
    Vfull_adder* top = new Vfull_adder;

    // --- 波形生成设置 ---
    Verilated::traceEverOn(true); // 开启波形追踪
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99); // 将波形追踪绑定到我们的模块实例
    tfp->open("waveform.vcd"); // 指定输出的波形文件名

    // --- 仿真主循环 ---
    vluint64_t main_time = 0; // vluint64_t 是 Verilator 使用的64位无符号整数

    while (!Verilated::gotFinish()) {
        // 施加激励信号
        if (main_time < 10) {
            top->a = 0; top->b = 0; top->cin = 0;
        } else if (main_time < 20) {
            top->a = 0; top->b = 0; top->cin = 1;
        } else if (main_time < 30) {
            top->a = 0; top->b = 1; top->cin = 0;
        } else if (main_time < 40) {
            top->a = 0; top->b = 1; top->cin = 1;
        } else if (main_time < 50) {
            top->a = 1; top->b = 0; top->cin = 0;
        } else if (main_time < 60) {
            top->a = 1; top->b = 0; top->cin = 1;
        } else if (main_time < 70) {
            top->a = 1; top->b = 1; top->cin = 0;
        } else if (main_time < 80) {
            top->a = 1; top->b = 1; top->cin = 1;
        } else {
            break; // 结束仿真
        }

        // 评估电路状态（关键步骤）
        top->eval();

        // 将当前状态写入波形文件
        tfp->dump(main_time);

        // 打印到终端，方便观察
        std::cout << "Time=" << main_time
                  << " a=" << (int)top->a
                  << " b=" << (int)top->b
                  << " cin=" << (int)top->cin
                  << " -> sum=" << (int)top->sum
                  << " cout=" << (int)top->cout << std::endl;

        // 推进仿真时间
        main_time++;
    }

    // --- 清理工作 ---
    tfp->close(); // 关闭波形文件
    delete top;
    exit(0);
}
