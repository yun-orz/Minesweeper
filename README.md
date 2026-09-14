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

## Windows 最省事：下载 EXE 直接运行

仓库已经配置 GitHub Actions，会自动生成 Windows 版 `minesweeper.exe`，不需要你自己安装 GCC。

1. 打开仓库顶部的 **Actions**。
2. 点击最新一次 **Build Windows EXE**。
3. 在页面底部的 **Artifacts** 下载 `Minesweeper-Windows`。
4. 解压 ZIP，双击里面的 `minesweeper.exe` 即可开始游戏。

Actions 页面：

https://github.com/yun-orz/Minesweeper/actions

> GitHub 的 Artifact 会以 ZIP 形式下载，解压一次后即可直接双击 EXE。

## 自己编译

如果电脑已经安装 GCC，也可以在仓库目录直接编译运行。

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

## 文件

```text
Minesweeper/
├── .github/workflows/build-windows.yml  # 自动生成 Windows EXE
├── minesweeper.c                        # 游戏全部代码
└── README.md                            # 使用说明
```

代码只使用 C 标准库中的 `stdio.h`、`stdlib.h` 和 `time.h`，适合作为基础 C 语言练习项目。
