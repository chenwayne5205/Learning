# 使用 Yosys 进行逻辑综合的详尽指南

## 前言：从“功能验证”到“电路实现”

在上一份指南中，我们通过仿真 (Simulation) 回答了“我的设计**功能**对不对？”这个问题。现在，我们将进入数字 IC 设计流程中至关重要的一步：**逻辑综合 (Logic Synthesis)**。

这个阶段要回答的问题是：“我的设计应该由**哪些具体的电路元件**构成？”

如果说仿真是对设计蓝图的“功能审查”，那么综合就是将这份蓝图转换成一份详细的“施工材料清单和接线图”。这份“接线图”在数字电路领域被称为**门级网表 (Gate-Level Netlist)**。

**Yosys** 就是一个开源的、功能强大的综合引擎。它扮演着**“硬件编译器”**的角色，读取您的 Verilog 代码（行为描述），并将其“编译”成一个由基础逻辑门构成的电路结构（结构描述）。

本指南将教您如何使用 Yosys 来完成这一关键的转换过程。

---

### 第一章：核心概念：什么是逻辑综合？

在开始操作前，理解几个核心概念至关重要，这将帮助您明白每一步操作的意义。

* **RTL (Register-Transfer Level, 寄存器传输级)**
    您编写的 Verilog 代码通常属于 RTL 级别。它描述的是数据如何在寄存器之间流动和处理（例如 `assign c = a + b;`），这是一种**行为描述**。它更关注“做什么”，而不是“用什么做”。

* **门级网表 (Gate-Level Netlist)**
    这是综合的**产物**。它不再描述行为，而是用最基础的逻辑门（如 AND, OR, XOR, NOT, DFF 等）和它们之间的连线（`wire`）来描述电路的**物理结构**。它是连接逻辑设计（前端）和物理设计（后端）的桥梁。

* **技术库 (Technology Library)**
    在真实的芯片制造中，综合器会将通用的逻辑门映射到特定工艺（例如台积电 7nm）提供的、具有实际物理尺寸和电气特性的**标准单元 (Standard Cell)**上。在我们的学习中，Yosys 会先将其综合到它内部的通用逻辑门。

---

### 第二章：工具安装与准备

我们需要确保 `yosys` 以及一个用于图形化显示电路的辅助工具 `xdot` 都已安装。

* **安装命令**: 打开终端，运行以下命令。
    ```bash
    sudo apt update
    sudo apt install yosys xdot
    ```
* **验证安装**:
    ```bash
    yosys -V
    ```
    如果能成功显示 Yosys 的版本号，说明工具已准备就绪。

---

### 第三章：Yosys 的两种使用模式

与许多工程软件一样，Yosys 支持两种主要的使用模式：

* **交互模式 (Interactive Mode)**
    直接在终端输入 `yosys` 启动。您可以在 `yosys>` 提示符后逐条输入命令，并立即看到结果。这种模式非常适合学习、调试和快速实验。

* **脚本模式 (Script Mode)**
    将所有要执行的命令预先写在一个 `.ys` 脚本文件中，然后通过 `yosys your_script.ys` 命令一次性执行。这是专业、可复现、可自动化的工作方式，也是实际项目中的标准做法。

---

### 第四章：实战演练：综合一个全加器

我们将继续使用之前验证过的 `full_adder.v` 文件。请确保这个文件在您当前的工作目录下。

#### 4.1 准备设计文件

**`full_adder.v` 代码回顾**:
```verilog
module full_adder(
  input  a, b, cin,
  output sum, cout
);
  assign {cout, sum} = a + b + cin;
endmodule


### 4.2 使用交互模式进行探索
yosys
read_verilog full_adder.v
show
exit

### 4.3 使用脚本模式实现自动化
nano synth_script.ys

# Yosys Synthesis Script for full_adder

# 将所有输出信息记录到 synth.log 文件中
log synth.log

# 1. 读取设计文件
read_verilog full_adder.v

# 2. 执行一个标准的综合流程，并指定顶层模块
synth -top full_adder

# 3. 清理电路，移除未使用的连线，方便查看
clean -purge

# 4. 将综合后的网表保存为 Verilog 文件
#    -noattr 选项可以去除一些不必要的属性，让网表更干净
write_verilog -noattr synth_adder_script.v

# 5. 生成电路图并直接保存为 PNG 图片
#    -format 指定格式, -prefix 指定文件名前缀
show -format png -prefix ./full_adder_schematic

log --- Synthesis complete. ---



yosys synth_script.ys

### 第五章：分析与理解综合结果
cat synth_adder_script.v
full_adder_schematic.png
synth.log
