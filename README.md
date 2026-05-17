# 图书管理系统（Library Management System）
基于 **C语言** 开发的课程设计项目，提供两种数据持久化方案：**文件存储版** 与 **MySQL 数据库版**。

---

## 项目简介
本项目是一个功能完整的图书管理系统，实现了图书、读者、借阅信息的全流程管理，满足课程设计的核心需求。

### 核心功能
- 图书管理：增删改查、库存管理、多条件查询
- 读者管理：增删改查、借阅上限控制
- 借阅管理：借书登记、还书处理、借阅记录查询
- 双版本支持：无需数据库的文件存储版 / 高性能的MySQL版

---

## 项目目录结构

LibraryManagementSystem/
├── src/ # 核心源码目录
│ ├── Library-File.c # 文件存储版本主程序（无数据库依赖）
│ └── Library-MySQL.c # MySQL 数据库版本主程序
├── test/ # 学习与测试代码目录
│ ├── mysql_test.c # MySQL 连接基础测试
│ ├── mysql_base_test.c # MySQL 基础 SQL 操作测试
│ └── book_crud_test.c # 图书表 CRUD 功能演示
└── README.md # 项目说明文档

---

## 编译与运行指南

### 1. 文件存储版本（无需数据库）
该版本通过本地文本文件读写实现数据持久化，开箱即用，无额外依赖。
```bash
# 编译
gcc src/Library-File.c -o Library-File

# 运行
./Library-File

2. MySQL 数据库版本
该版本基于 MySQL 实现数据存储，支持复杂查询与事务操作，性能更强。
前置条件
已安装 MySQL 服务
已创建项目所需的数据库与表（可根据代码中的 SQL 语句创建）
编译与运行

# 编译（需链接MySQL客户端库）
gcc src/Library-MySQL.c -o Library-MySQL -lmysqlclient

# 运行

## 项目亮点
模块化设计，代码结构清晰，易于扩展
完整的用户交互界面，操作友好
包含学习过程中的测试代码，便于理解 C 语言与数据库交互
双版本对比，适合学习不同数据持久化方案的实现