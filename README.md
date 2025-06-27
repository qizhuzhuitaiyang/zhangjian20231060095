
# 0-1 背包算法实验（20231060095 张坚）

本项目用于评估四种典型的 0-1 背包问题算法在不同数据规模与背包容量下的运行效率与求解质量。实验基于 C 与 Python 实现，并支持全自动化测试与可视化分析。

---

##  算法实现

项目实现了以下四种经典算法：

- **Brute Force**：穷举所有物品组合，计算最大价值（适用于 n ≤ 30）；
- **Backtracking**：使用深度优先搜索并剪枝优化的回溯法；
- **Greedy**：按单位价值从大到小排序的贪心法（近似解）；
- **Dynamic Programming (DP)**：使用一维数组优化的动态规划法，保证最优解。

---

## 📂 项目结构

```
.
├── data.c # 数据生成器（C语言）
├── main.c # 四种算法实现
├── auto.py # 批量自动测试脚本
├── visual.py # 可视化脚本（生成图表）
├── result.csv # 实验结果记录（算法/规模/容量/值/时间）
├── figures/ # 输出图表目录
├── data_*.txt # 生成的数据文件（物品权重与价值）
└── algorithm_comparison.png / *.png # 可视化图表
```

---

## 🚀 快速开始

### 1. 编译程序

```bash
gcc data.c -o data_gen
gcc main.c -o main -lm
```

### 2. 生成实验数据

```bash
./data_gen
```

会生成如下文件：

```
data_10.txt, data_20.txt, ..., data_320000.txt
```

每个文件内为一组物品的 `[weight, value]` 数据。

### 3. 运行自动化测试

```bash
python3 auto.py
```

将自动调用四种算法运行不同数据规模与容量组合，并将结果写入 `result.csv`。

### 4. 可视化实验结果

```bash
python3 visual.py
```

将输出图表至 `figures/` 文件夹，包含运行时间对比图、解的质量比较图等。

📊 **图表示例**

部分自动生成图表如下：

- `01_time_logscale.png`：四种算法运行时间对比图（对数尺度）
- `03_solution_value.png`：各算法求解价值对比图
- `04_greedy_error_vs_dp.png`：Greedy 相对 DP 的解误差比例图

---

## 🖥 实验环境（推荐）

建议在如下环境中运行以保证性能：

项目 | 配置说明
---|---
系统 | Ubuntu 22.04.5 LTS
CPU | Intel Core i9-14900K (24核32线程, 6.0GHz)
内存 | 128GB
GPU | NVIDIA GeForce RTX 3090 24GB（CUDA 12.4）
编译器 | GCC 12.2.0
Python | 3.10+，依赖 pandas、matplotlib

📌 **注意事项**

- `brute` 和 `backtrack` 算法仅适用于小样本（n ≤ 30）；
- `dp` 算法运行时间和内存消耗与容量 C 成正比；
- `greedy` 算法速度快但不能保证最优解，适用于近似求解。
 
