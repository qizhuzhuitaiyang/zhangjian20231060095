import os

algorithms = ['brute', 'dp', 'greedy', 'backtrack']
sizes = [10, 20, 30, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 40000, 80000, 160000, 320000]
capacities = [10000, 100000, 1000000]

output_file = 'result.csv'
with open(output_file, 'w') as f:
    f.write("algorithm,n,C,value,time_ms\n")

for algo in algorithms:
    for n in sizes:
        filename = f"data_{n}.txt"
        for C in capacities:
            # 限制蛮力和回溯在小数据集
            if (algo in ['brute', 'backtrack']) and n > 30:
                continue
            cmd = f".\main {algo} {filename} {C} {output_file}"
            print(f"执行: {cmd}")
            os.system(cmd)
