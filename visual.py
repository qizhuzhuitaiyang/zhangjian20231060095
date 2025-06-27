import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("result.csv")

plt.figure(figsize=(12, 8))

for algo in df['algorithm'].unique():
    sub = df[df['algorithm'] == algo]
    plt.plot(sub['n'], sub['time_ms'], marker='o', label=algo)

plt.xscale("log")
plt.yscale("log")
plt.xlabel("物品数量 n (log)")
plt.ylabel("执行时间 (ms, log)")
plt.title("四种算法运行时间对比")
plt.legend()
plt.grid(True, which="both", linestyle="--", alpha=0.5)
plt.show()
