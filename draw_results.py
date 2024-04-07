#!/usr/bin/env python3


import pandas as pd
import matplotlib.pyplot as plt

gpu_data = pd.read_csv("data/results.csv")
tpool_data = pd.read_csv("data/results_tpool.csv")

plt.rcParams.update({'font.size': 18})
plt.figure(figsize=(10, 6))
categories = gpu_data.columns
bar_width = 0.35
index = range(len(categories))

plt.bar(index, gpu_data.mean(), bar_width, label='Vulkan')
plt.bar([i + bar_width for i in index], tpool_data.mean(), bar_width, label='Thread pool')

plt.xlabel('Run times')
plt.ylabel('Time (ms)')
plt.title('Comparison of Run Times Between The Vulkan Implementation and The Thread Pool Implementation')
plt.xticks([i + bar_width / 2 for i in index], categories)
plt.legend()
plt.tight_layout()
plt.show()
