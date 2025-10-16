# 集群概况

目前集群硬件资源如下：

- M6 集群 共 5 个节点
    - CPU (M600,M601)：2 x Intel Silver 4314 16Core @ 2.4GHz (32 核心 64 线程)
    - CPU (M602,M603,M604)：2 x Intel Gold 5320 26Core @ 2.2GHz (52 核心 104 线程)
    - 内存：DDR4 256 GB 以上
    - Ethernet：10 Gbps
    - Infiniband：HDR 200 Gbps

- M7 集群 共 2 个节点
    - CPU：2 x Intel Gold 5418Y 24Core @ 2.0GHz (48 核心 96 线程)
    - 内存 DDR5-4800
    - Ethernet：1 Gbps

- RISC-V 集群 ([**进迭时空**](https://www.spacemit.com/)提供) 共 8 个节点
    - CPU：Spacemit X60 @ 1.6Ghz
    - 内存：8GB
    - Ethernet：100Mbps


- V100 集群 共 32 个节点，每个节点有 2 个 GPU
    - GPU：NVIDIA V100 32GB * 2
    - Ethernet：10Gbps
    - Infiniband：HDR 200Gbps

- 鲲鹏 920 集群 共 1 个节点
    - CPU：Kunpeng 920 128Core @ 2.6GHz
    - 内存：DDR4 512 GB
    - Ethernet：10Gbps

## 存储

集群中有两个位置用于存储文件：

- `~`：6.4T SSD 阵列，你的家目录，权限仅个人，每人限额50G
- `/river`：和家目录同一个阵列，用于共享文件

这些位置均跨节点挂载，你可以在任意节点访问这些存储池。
