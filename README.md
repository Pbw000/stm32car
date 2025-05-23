# stm32car 项目文档

## 功能概述
- [x] 巡线巡逻：利用传感器识别地面引导线，实现自动路线跟随
- [ ] 地形探测：集成超声波/红外传感器，动态感知地形起伏与障碍物

## 硬件设计
- [x] 传感器模块
  - [x] 巡线传感器：黑色线识别模块（车底前置）
  - [x] 超声波阵列：1组测距传感器（车头/侧方）
  - [x] 红外探测器：地面障碍物预判模块
- [x] 控制单元：STM32F103C8T6主控芯片
- [x] 驱动系统
  - [ ] 舵机模块：SG90舵机（转向控制）

## 软件架构
- [x] 巡线算法
  - [ ] PID闭环控制
  - [ ] 线迹偏离补偿
- [ ] 自适应导航系统
  - [ ] A*路径规划算法
  - [ ] 障碍物绕行策略

## 系统流程
- [x] 启动初始化
  - [x] 硬件自检
  - [x] 传感器标定
- [x] 巡逻模式
  - [x] 引导线跟踪
- [x] 避障处理
  - [x] 超声波融合检测
  - [x] 红外预报警机制
- [ ] 安全协议
  - [ ] 紧急制动
  - [ ] 电量预警
