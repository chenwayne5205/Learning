// tb_full_adder.v (Corrected Version)

// `timescale 是编译器指令，它的位置是正确的，在所有 module 之外
`timescale 1ns/1ps

module tb_full_adder;
  // 1. Inputs are declared as 'reg' (register) type
  reg  a, b, cin;
  // 2. Outputs are declared as 'wire' type
  wire sum, cout;

  // 3. Instantiate the Unit Under Test (UUT)
  // 将我们设计的 full_adder 模块在此处实例化，并连接信号
  full_adder uut (
    .a(a), 
    .b(b), 
    .cin(cin), 
    .sum(sum), 
    .cout(cout)
  );

  // 4. initial 块包含了仿真的主要行为
  initial begin
    // --- 修正点 1: 将波形记录相关的系统任务移入 initial 块 ---
    // --- 修正点 2: 使用正确的 $ 符号，而不是 ` 符号 ---
    
    // 指定生成的波形文件的名称
    $dumpfile("waveform.vcd");
    // 指定要记录波形的信号范围。0 表示记录 uut 模块下所有层次的信号
    $dumpvars(0, uut);

    // 5. 提供激励信号 (Stimulus)
    // 在每个 #10 之后，仿真会暂停 10 个时间单位 (10ns)
    a=0; b=0; cin=0; #10;
    a=0; b=0; cin=1; #10;
    a=0; b=1; cin=0; #10;
    a=0; b=1; cin=1; #10;
    a=1; b=0; cin=0; #10;
    a=1; b=0; cin=1; #10;
    a=1; b=1; cin=0; #10;
    a=1; b=1; cin=1; #10;

    // 6. 结束仿真
    $finish;
  end

endmodule
