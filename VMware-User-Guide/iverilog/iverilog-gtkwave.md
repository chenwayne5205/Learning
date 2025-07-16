# 使用 Icarus Verilog 与 GTKWave 进行数字电路仿真的详尽指南

## 前言：什么是仿真，以及我们为什么需要它？

在集成电路 (IC) 设计中，**仿真是验证设计功能是否正确的核心步骤**。在我们将设计“变硬”（即制造成芯片或下载到 FPGA）之前，必须通过软件来模拟电路在各种输入下的行为，以确保其逻辑符合预期。这个过程就像在飞机的设计图纸完成之后，先用计算机进行成千上万次的飞行模拟，而不是直接造一架真飞机去试飞。

在这个领域，`Icarus Verilog` 和 `GTKWave` 构成了一套经典、强大且完全免费的开源工具链：

* **Icarus Verilog (`iverilog`)**: 扮演**“编译器”**和**“仿真引擎”**的角色。它读取你的 Verilog 设计代码和测试代码，将其编译成一个可执行的仿真程序。
* **GTKWave**: 扮演**“虚拟示波器”**的角色。它读取仿真过程中产生的波形数据文件，并以图形化的方式展示出来，让你可以直观地分析每个信号随时间的变化。

本指南将带您完整地走一遍从编写代码到分析波形的全过程。

---

### 第一章：工具安装与准备

在开始之前，我们需要确保这两个核心工具已经安装在您的 Ubuntu 系统中。

* **安装命令**: 打开终端，运行以下命令。
    ```bash
    sudo apt update
    sudo apt install iverilog gtkwave
    ```
* **验证安装**:
    ```bash
    iverilog -V
    gtkwave --version
    ```
    如果这两条命令都能成功显示版本号，说明工具已准备就绪。

---

### 第二章：Verilog 设计文件剖析

一个完整的仿真项目通常至少包含两个 `.v` 文件：一个是**设计文件 (DUT)**，另一个是**测试平台文件 (Testbench)**。

#### 2.1 设计文件 (DUT - Design Under Test)

这是您要实现的核心电路逻辑，也叫“被测设计”。我们以之前用过的**全加器**为例。

* **文件名**: `full_adder.v`
* **代码**:
    ```verilog
    // `module` 定义了一个电路模块的开始
    module full_adder(
      // `input` 和 `output` 定义了模块的端口
      input  a, b, cin,
      output sum, cout
    );
      // `assign` 描述了组合逻辑的行为
      // 这里用拼接符 {} 和加法运算简洁地描述了全加器的逻辑
      assign {cout, sum} = a + b + cin;
      
    // `endmodule` 标志着模块定义的结束
    endmodule
    ```

#### 2.2 测试平台文件 (Testbench)

Testbench 的目的就是为我们的 DUT 创建一个“虚拟测试环境”。它不包含任何可综合的电路逻辑，其唯一的作用就是在仿真中：
1.  实例化（调用）我们的 DUT。
2.  为 DUT 的输入端口提供一系列激励信号。
3.  （可选）检查 DUT 的输出是否符合预期。
4.  控制仿真过程，如生成波形文件、结束仿真等。

* **文件名**: `tb_full_adder.v`
* **代码**:
    ```verilog
    // `timescale 定义了仿真的时间单位和精度 (1ns / 1ps)
    `timescale 1ns/1ps

    // Testbench 模块通常没有输入输出端口
    module tb_full_adder;
      // 1. 信号声明
      // 要给 DUT 输入的信号，必须声明为 reg (寄存器) 类型
      reg  a, b, cin;
      // 从 DUT 输出的信号，用 wire (导线) 类型来连接
      wire sum, cout;

      // 2. 实例化 DUT
      // 就像在电路板上放一个芯片，我们把 full_adder 模块实例化，并命名为 uut
      // .port_name(signal_name) 是推荐的端口连接方式
      full_adder uut (
        .a(a), 
        .b(b), 
        .cin(cin), 
        .sum(sum), 
        .cout(cout)
      );

      // 3. 仿真控制与激励生成
      // `initial` 块内的代码会在仿真开始时 (时间为0) 执行一次
      initial begin
        // --- 仿真控制任务 ---
        // $dumpfile 指定了输出波形文件的名字
        $dumpfile("full_adder_waveform.vcd");
        // $dumpvars 指定了要记录波形的信号范围。0, uut 表示记录 uut 实例下的所有信号
        $dumpvars(0, uut);

        // --- 激励信号 ---
        // 给予所有输入组合，每个组合持续 10ns (#10)
        a=0; b=0; cin=0; #10;
        a=0; b=0; cin=1; #10;
        a=0; b=1; cin=0; #10;
        a=0; b=1; cin=1; #10;
        a=1; b=0; cin=0; #10;
        a=1; b=0; cin=1; #10;
        a=1; b=1; cin=0; #10;
        a=1; b=1; cin=1; #10;

        // --- 结束仿真 ---
        // $finish 是一个系统任务，用于正常结束仿真
        $finish;
      end

    endmodule
    ```

---

### 第三章：核心仿真流程：从代码到波形

现在，我们把以上两个文件放在同一个目录下，开始执行仿真。

#### **步骤 1：编译 Verilog 代码**

此步骤使用 `iverilog` 将我们的 `.v` 文本文件编译成一个二进制的仿真模型。
```bash
# -o 选项指定输出文件的名称，我们将其命名为 my_simulation
iverilog -o my_simulation full_adder.v tb_full_adder.v
vvp my_simulation
gtkwave full_adder_waveform.vcd

### 第四章：GTKWave 基础操作指南
初次打开 GTKWave 可能会觉得有些不知所措，请遵循以下步骤：

选择信号

在左上角的 SST (Signals, Search, Tree) 面板中，你会看到你的 testbench 模块层次结构，点击 tb_full_adder -> uut。

在中间的 Signal List 面板中，会显示出 uut 模块下的所有信号 (a, b, cin, cout, sum)。

添加信号到波形窗口

在 Signal List 面板中，按住 Ctrl 键，用鼠标左键点选所有你关心的信号。

点击下方的 “Append” 按钮。

查看波形

此时，所有被选中的信号会出现在主窗口（右侧的 Waves 窗口）中，并显示出它们随时间变化的波形图。

缩放与适配

点击工具栏上的 “Zoom Fit” 图标（一个带四个外向箭头的放大镜），波形会自动缩放到最适合窗口的尺寸。这是最常用的缩放按钮。

您也可以使用其他放大镜图标或鼠标滚轮进行自由缩放。

使用标尺 (Marker)

在波形显示区的时间轴上（顶部的时间刻度）任意位置单击鼠标左键，会出现一条黄色的垂直标尺。

在 Signals 面板中，会实时显示标尺所在时刻，每个信号的具体值（0 或 1），方便您精确地检查逻辑功能是否正确。
