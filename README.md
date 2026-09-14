# Minesweeper / 扫雷（C 语言）

一个用基础 C 语言写的命令行扫雷小游戏，只有一个源码文件 `minesweeper.c`，不需要第三方库。

## 游戏规则

- 棋盘：9 × 9
- 地雷：10 个
- 输入“行 列”打开格子，例如：`3 5`
- `#` 表示未打开
- `.` 表示周围没有雷
- 数字表示周围 8 个格子中的地雷数量
- `*` 表示地雷（游戏结束后显示）
- 第一次选择的格子保证不会是雷

## 最简单的打开方式

C 程序需要先编译一次。如果电脑已经安装 GCC，在仓库目录运行下面一行即可。

### Windows

```bash
gcc minesweeper.c -o minesweeper.exe && minesweeper.exe
```

### macOS / Linux

```bash
gcc minesweeper.c -o minesweeper && ./minesweeper
```

运行后会看到棋盘，然后直接输入两个数字，例如：

```text
Open cell (row column): 3 5
```

表示打开第 3 行、第 5 列。

## 分开编译和运行

如果想分两步执行：

```bash
gcc minesweeper.c -o minesweeper
```

然后：

```bash
./minesweeper
```

Windows 下运行：

```bash
minesweeper.exe
```

## 文件

```text
Minesweeper/
├── minesweeper.c   # 游戏全部代码
└── README.md       # 使用说明
```

代码只使用 C 标准库中的 `stdio.h`、`stdlib.h` 和 `time.h`，适合作为基础 C 语言练习项目。
