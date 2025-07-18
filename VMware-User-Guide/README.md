# 虚拟机使用教程

有关虚拟机的安装包下载可以从网上找，也可以找我拷贝（系统只有Ubuntu），安装的教程网上多的很，耐心一点就行，文案中很多都是ai写的，随便看一看就可以，不过一定要实际操作，直到可以熟练的使用界面、命令以及解决碰到的问题。
该目录下还有一些eda工具的使用测试案例，可以直接拷贝，在虚拟机里安装工具并学习使用一下，下面的内容中也会提到。

## 前言：什么是虚拟机？

欢迎来到虚拟化的世界！**虚拟机 (Virtual Machine, VM)**，可以被看作是一台**“电脑中的电脑”**。是一个在当前操作系统（我们称之为“主机”）上通过软件模拟出来的、功能完备的计算机系统。您可以在这个虚拟电脑里安装一个全新的、与您主机完全隔离的操作系统（我们称之为“客户机”或“Guest OS”），例如绝大多数人都会使用的Ubuntu。

使用虚拟机，可以：

* **安全地学习和探索新系统**，完全不用担心会搞乱主电脑。
* **为不同的项目创建独立的开发环境**，避免软件版本和依赖冲突。
* **测试软件或运行有风险的程序**，将其与主系统完全隔离。

本指南介绍使用虚拟机的核心技巧。

---

## 第一部分：虚拟机核心管理

在深入学习虚拟机内部的操作系统之前，我们必须先学会如何管理和驾驭这个“数字沙盘”本身。这些是虚拟机最基础、也是最强大的功能。

### 1. 快照 (Snapshot)：你最重要的安全网

**快照是虚拟机最强大的功能，没有之一。**

您可以把它想象成一个游戏的**“存档点”**或者系统的**“时光机”**。它会完整地、瞬间地记录下虚拟机在某一时刻的所有状态——包括所有文件、设置、内存中正在运行的程序等一切信息。

**为什么它至关重要？**
在您进行任何可能有风险的操作之前，例如：尝试一个不熟悉的命令、安装一个大型复杂软件、修改系统核心配置文件等，您都应该先**拍摄一个快照**。如果后续操作失败或把系统搞乱了，您可以在几秒钟内，将虚拟机**完美地恢复**到拍摄快照时的那个健康状态。

这赋予了您**无限试错**的勇气。

**如何操作？**

* **创建快照**:
  1.  在 VMware 的顶部菜单栏选择 **“虚拟机 (VM)”** -> **“快照 (Snapshot)”** -> **“拍摄快照 (Take Snapshot)...”**。
  2.  在弹出的窗口中，为快照起一个有意义的名字，例如 **“一个干净的初始系统”** 或 **“安装VS Code之前”**，并可以添加一些描述。
  3.  点击 **“拍摄快照 (Take Snapshot)”** 按钮即可。

* **恢复到快照**:
  1.  选择 **“虚拟机 (VM)”** -> **“快照 (Snapshot)”** -> **“恢复到快照 (Revert to Snapshot)”**。
  2.  您也可以打开 **“快照管理器 (Snapshot Manager)”**，在快照树中选择您想恢复到的那个时间点，然后点击 **“转到 (Go To)”**。

> **注意：** 恢复到一个快照，将会**抛弃并删除**从该快照创建之后的所有更改。这是一个“回到过去”的操作，之后的所有工作都会消失，请在操作前确认。

### 2. 虚拟机的电源状态：不止是开关机

与物理电脑不同，虚拟机提供了更灵活的电源管理方式。

* **关机 (Shut Down Guest)**:
  这是最安全、最推荐的方式。它会通过正常的操作系统流程关闭所有程序和服务，然后关闭虚拟机。等同于您在 Ubuntu 系统内部点击“电源”->“关机”。

* **挂起 (Suspend)**:
  这是虚拟机的**“暂停”**功能。它会将虚拟机当前的所有运行状态（包括打开的程序、内存中的数据等）完整地保存到一个文件中，然后冻结虚拟机的运行。
  * **优点**: 恢复速度极快。下次启动时，您可以从中断的那个瞬间无缝继续工作，所有打开的窗口和程序都保持原样。非常适合需要临时中断工作又不想关闭所有程序的场景。

* **关闭电源 (Power Off)**:
  这等同于**直接拔掉真实电脑的电源线**。这是一种强制关机，不会给操作系统任何保存数据或正常关闭服务的机会，有可能会导致文件损坏或数据丢失。**请仅在虚拟机完全卡死、无法进行任何操作时，才使用此选项。**

### 3. 与主机交互：打破虚拟与现实的壁垒

让虚拟机用起来“不别扭”的关键，在于让它能与您的主机（真实电脑）流畅地交换信息。

* **共享剪贴板 (Shared Clipboard)**:
  当您正确安装了 VMware Tools (在 Ubuntu 中对应 `open-vm-tools-desktop`) 之后，共享剪贴板通常会自动启用。您可以像在单个系统上一样，在主机上复制（`Ctrl+C`）一段文本，然后直接在虚拟机窗口中粘贴（`Ctrl+V`），反之亦然。这个一般安装了就有，不用担心。

* **共享文件夹 (Shared Folders)**:
  这是在主机和虚拟机之间传输**文件**的最佳方式，尤其适合大文件。
  1.  将虚拟机**关机**。
  2.  进入虚拟机的**“设置 (Settings)”** -> **“选项 (Options)”** 标签页。
  3.  选择 **“共享文件夹 (Shared Folders)”**。
  4.  选择“**总是启用 (Always enabled)**”，然后点击下方的 **“添加 (Add...)”** 按钮。
  5.  跟随向导，选择一个您**主机**上的文件夹作为共享目录。
  6.  启动虚拟机后，您可以在 Ubuntu 系统的 `/mnt/hgfs/` 目录下找到您共享的那个文件夹。

* **拖拽 (Drag and Drop)**:
  在 VMware Tools 启用后，您也可以尝试直接从主机桌面拖拽一个文件到虚拟机桌面。这适合移动单个、小体积的文件。

### 4. 调整虚拟机资源：为你的“沙盘”增添动力

您可以随时根据需求，调整分配给虚拟机的硬件资源。

1.  确保虚拟机处于**彻底关机**状态。
2.  进入 **“编辑虚拟机设置 (Edit virtual machine settings)”**。
3.  在这里，您可以轻松地修改：
    * **内存 (Memory)**: 增加或减少分配给虚拟机的 RAM 大小。
    * **处理器 (Processors)**: 调整分配给虚拟机的 CPU 核心数。
    * **硬盘 (Hard Disk)**: **扩展**虚拟硬盘的总容量（通常只能增加，不能减少）。

掌握以上这些核心管理技巧，您就拥有了驾驭虚拟机这个强大工具的基础。您可以安全地进行任何实验，高效地在不同系统间传递信息，并根据任务需求灵活地配置您的“数字沙盘”。

---

## 第二部分：初识 Ubuntu 系统与终端 —— 与新世界对话

现在，您的虚拟机已经是一个安全、可随时恢复的实验环境了。接下来，我们将学习如何在这个新系统中导航、下达指令，并理解其权限体系。这就像学习一门新语言，我们将从最基本的“看”和“说”开始。

### 5. 桌面环境探索：图形化界面的导航

您登录 Ubuntu 后看到的整个图形化界面，被称为**桌面环境 (Desktop Environment)**。Ubuntu 默认使用的是**GNOME**，它以简洁、现代而著称。让我们来熟悉一下它的几个核心区域。

1.  **顶部状态栏 (Top Bar)**
    屏幕最上方的一条黑色的栏，分为三个区域：
    * **左侧，“活动 (Activities)”**: 点击它或按 `Win` 键，会进入“活动概览”视图。在这里，你可以看到所有打开的窗口、你的工作区，并能搜索应用程序。
    * **中间，时钟**: 显示当前时间和日期。点击它可以查看日历和通知。
    * **右侧，系统菜单 (System Menu)**: 点击这里会展开一个面板，包含了网络、音量、电源设置、以及关机/重启/注销的按钮。

2.  **Dock 栏 (The Dock)**
    这是屏幕左侧的快捷启动栏，类似于 Windows 的任务栏或 macOS 的 Dock。
    * **收藏夹**: 这里默认固定了一些常用应用。你可以从应用程序列表中将任何应用图标拖拽到 Dock 上来添加新的收藏。
    * **正在运行的应用**: 打开的应用图标下方会有一个小点作为标记。
    * **移除**: 在 Dock 上的图标点击右键，选择“从收藏夹移除 (Remove from Favorites)”。

3.  **应用程序列表 (Application Grid)**
    点击 Dock 栏最下方的**九个点图标**，就会打开应用程序列表。这里展示了您虚拟机中所有已安装的图形化软件。您可以在顶部的搜索框中快速查找应用。

4.  **“设置”中心 (The "Settings" App)**
    这是您进行系统图形化配置的中枢，就像 Windows 的“控制面板”。您可以在这里更改壁纸、显示分辨率、网络、语言、用户账户等几乎所有设置。

花几分钟时间点击和探索这些区域，熟悉它们的位置和功能。

---

### 6. 初识终端 (Terminal)：为什么它是 Linux 的灵魂？

学习使用**终端 (Terminal)** 是必经之路。

**为什么终端如此重要？**

* **强大与高效**: 许多复杂的操作，在图形界面中需要点击数十次鼠标，而在终端里可能只需要一条简短的命令。
* **完全的控制权**: 不是所有的系统功能和设置都有图形界面。终端是您与系统底层进行直接、无限制沟通的唯一途径。
* **自动化**: 终端是所有脚本编程（我们之前学习过）的基础。您在终端里能做的事，就能写成脚本让电脑自动完成。
* **通用语言**: 无论您在网上查找任何关于 Linux 的教程或解决方案，99% 都会以命令行的方式提供。学会终端，您就学会了与全球 Linux 社区沟通的语言。

#### 如何打开终端

* **快捷键 (推荐)**: 按下 `Ctrl + Alt + T`。这是您需要记住的最重要的快捷键之一。
* **应用程序列表**: 在应用列表中搜索“终端”或“Terminal”。

#### 理解命令提示符

打开终端后，您会看到一行类似这样的文字：
`wayne@wayne-virtual-machine:~$`

这行被称为**命令提示符 (Prompt)**，它在等待您输入命令。它的构成为：

* `wayne`: 当前登录的用户名。
* `@`: 分隔符。
* `wayne-virtual-machine`: 这台电脑的主机名。
* `:`: 分隔符。
* `~`: 代表您当前所在的目录。`~` 是一个特殊符号，代表当前用户的**主目录**（即 `/home/wayne`）。
* `$`: 提示符符号。`$` 表示您当前是一个普通用户。如果是 `#`，则表示您是拥有最高权限的 `root` 用户。

---

### 7. 理解 `sudo`：获取临时的管理员权限

在您开始使用终端后，很快就会遇到“**权限不够 (Permission denied)**”的错误。这是因为 Linux 是一个非常注重安全的多用户系统，默认情况下，普通用户不允许进行安装软件、修改系统文件等敏感操作。

`sudo` (发音为 "soo-doo") 命令就是解决这个问题的钥匙。

#### `sudo` 是什么？

`sudo` 是 **S**uper**u**ser **Do** 的缩写，意为“以超级用户（即管理员）的身份去做某件事”。它允许一个被授权的普通用户，**临时地、一次性地**借用管理员的权限来执行一条特定的命令。

这就像您想进入一栋大楼的某个机房，您本身没有钥匙，但您可以向保安（系统）出示您的证件（输入密码），保安验证通过后，会帮您刷卡打开这一次门（执行这一次命令），但并不会把万能钥匙交给您。

#### 如何使用？

1.  在您需要管理员权限执行的命令**前面**，加上 `sudo` 和一个空格。
    * 错误示范: `apt install htop` -> (会提示权限不够)
    * **正确示范**: `sudo apt install htop`

2.  输入命令后按回车，系统会提示 `[sudo] password for wayne:`。
3.  此时，您需要输入**您自己的登录密码**，而不是某个单独的管理员密码。
4.  **注意**: 输入密码时，**屏幕上不会显示任何东西**（没有星号`*`也没有光标移动）。这是正常的安全措施。您只需盲打输入正确的密码，然后按回车即可。

一旦您成功验证了一次 `sudo`，在接下来的几分钟内再次使用 `sudo` 通常不再需要输入密码。

掌握了 `sudo`，您就掌握了在 Ubuntu 中执行管理任务的正确方式。

---

## 第三部分：文件系统与命令行基础 —— 学会“行走”与“创造”

现在您已经站在了新世界的门口（终端），并且拥有了管理员的临时钥匙 (`sudo`)。接下来，我们将学习如何在这个世界里“行走”（导航目录）、“观察”（列出文件）、“创造”（创建文件和目录）以及“管理”（复制、移动、删除）。

---

### 8. Linux 文件系统结构概览

在开始“行走”之前，我们需要一张地图。与 Windows 有 C:、D: 等多个“盘符”不同，Linux 拥有一个**单一的、统一的树状目录结构**。所有的一切都始于**根目录 (root directory)**，它用一个单独的斜杠 `/` 来表示。

作为新手，您只需要了解几个最重要的“地标”：

* `/`: **根目录**。所有其他目录都是它的分支，是整棵树的树根。
* `/home`: **用户之家**。系统上所有普通用户的个人目录都存放在这里。
* `/home/wayne` (或用 `~` 代替): **您的个人主目录**。这是您的“私人地盘”，您拥有这里的完全权限。您日常的所有工作，如创建文件、编写代码、下载资料，都应该在这里进行。
* `/etc`: **系统配置目录**。包含了系统和大部分软件的配置文件，非常重要。
* `/usr/bin`: **程序存放目录**。您执行的大部分命令，如 `ls`, `cp` 等程序本身，都存放在这里。
* `/tmp`: **临时文件目录**。用于存放临时文件，通常系统重启后会被清空。

---

### 主题9：核心导航命令：`pwd`, `ls`, `cd` (终端的“GPS”)

这三个命令是您在终端中定位和探索的基础。

`pwd` (Print Working Directory) 命令会告诉你当前所处的目录路径。

**实际操作**:

1. 打开终端 (`Ctrl + Alt + T`)。

2. 输入命令并回车：

   ```bash
   pwd
   ```

3. **输出**: ` /home/wayne `（显示当前位置）

`ls` (List) 命令用于列出当前目录下的文件和文件夹。

**实际操作**:

1. 在终端中输入：

   ```bash
   ls
   ```

   **输出**: 您会看到 `Desktop`, `Documents`, `Downloads` 等文件夹的名称。

2. 使用 `-l` 选项查看详细列表 (long format):

   ```bash
   ls -l
   ```

   **输出**:

   ```
   drwxr-xr-x 2 wayne wayne 4096 Jul 15 22:30 Desktop
   drwxr-xr-x 2 wayne wayne 4096 Jul 15 22:30 Documents
   ...
   ```

   第一列的 `drwxr-xr-x` 代表文件类型和权限，我们以后会学到。

3. 使用 `-a` 选项查看所有文件，包括隐藏文件 (all):

   ```bash
   ls -a
   ```

   您会看到一些以 `.` 开头的文件，如 `.bashrc`，这些是通常被隐藏的配置文件。

4. **组合使用 (最常用)**:

   ```bash
   ls -la
   ```

   这会以详细列表的形式，显示当前目录下的所有文件（包括隐藏文件）。

`cd` (Change Directory) 命令用于切换您所在的目录。

**实际操作**:

1. **切换到“下载”目录**:（一定要在当前工作目录里有该目录才会进入，否则会报错，建议cd前先ls一下）

   ```bash
   cd Downloads
   ```

   现在您的提示符可能会变成 `wayne@...:~/Downloads$`。用 `pwd` 命令验证一下，您会看到路径已经改变。

2. **返回上一级目录**: `..` 代表上一级目录。

   ```bash
   cd ..
   ```

   执行后，您就从 `Downloads` 目录回到了主目录 `~`。

3. **快速返回主目录**: 无论您身在何处，只需输入 `cd` 或 `cd ~` 即可瞬间返回。

   ```bash
   cd /etc  # 先去一个系统目录
   pwd      # 验证一下，现在在 /etc
   cd       # 直接回家
   pwd      # 验证一下，回到了 /home/wayne
   ```

---

### 10. 文件和目录操作：创造、复制、移动与删除

现在我们来学习如何管理文件。

**实际操作 (一个连贯的练习)**:

1. **`mkdir` (Make Directory): 创建一个新目录**
   确保您在主目录 (`~`)下，我们来创建一个项目文件夹。

   ```bash
   mkdir my_first_project
   ls 
   ```

   您会看到 `my_first_project` 出现在列表中。

2. **`cd` 进入新目录**:

   ```bash
   cd my_first_project
   ```

3. **`touch`: 创建一个空白文件**

   ```bash
   touch readme.txt
   ls
   ```

   您会看到一个名为 `readme.txt` 的新文件。

4. **`cp` (Copy): 复制文件**

   ```bash
   cp readme.txt readme_backup.txt
   ls
   ```

   现在目录下有了两个文件。（cp是可以添加文件具体路径的，在当前文件夹里也可以操作其他文件夹的文件进行copy到另一个文件夹，其他指令基本也可以这样，例如cp ./Desktop/readme.md ./../Download/readme.md）

5. **`mv` (Move): 移动或重命名文件**

   * **重命名**:

     ```bash
     mv readme_backup.txt notes.txt
     ls
     ```

     `readme_backup.txt` 消失了，取而代之的是 `notes.txt`。

   * **移动**:

     ```bash
     mkdir text_files
     mv notes.txt text_files/
     ls
     ls text_files/
     ```

     `notes.txt` 现在被移动到了 `text_files` 目录中。

6. **`rm` (Remove): 删除文件**

   ```bash
   rm readme.txt
   ls
   ```

   `readme.txt` 被删除了。现在来尝试删除目录：

   ```bash
   rm text_files 
   ```

   您会收到一个错误，因为 `rm` 默认不能删除目录。要删除目录及其中的所有内容，需要 `-r` (recursive) 选项。

   ```bash
   rm -r text_files
   ls
   ```

   现在 `text_files` 目录也被删除了。

> **警告：** Linux 的 `rm` 命令是**永久性的**！它不会将文件移入回收站，一旦执行，数据就很难恢复。在使用 `rm -r` 时，请务必再三确认您所在的目录和要删除的目标，因为一个错误的命令可能会瞬间删除掉重要的数据。

---

### 11. 查看文件内容：`cat` 和 `less`

#### `cat`: 一次性显示全部内容

`cat` (Concatenate) 命令会将文件的全部内容一次性打印到终端上。它适合查看简短的文本文件。

**实际操作**:

1. 我们先创建一个有内容的文件。`echo` 命令可以打印文本，`>` 可以将输出写入文件。（>和>>自行查询，有关定向输出）

   ```bash
   echo "This is the first line." > report.txt
   echo "This is the second line." >> report.txt # '>>' 是追加内容
   ```

2. 现在用 `cat` 查看它：

   ```bash
   cat report.txt
   ```

#### `less`: 分页查看器

当文件很长时，`cat` 会瞬间刷屏。`less` 命令则提供了一个可以上下滚动的分页查看器。

**实际操作**:

1. 我们创建一个长文件来做实验：

   ```bash
   # 这个 for 循环会生成一个包含100行内容的文件
   for i in {1..100}; do echo "This is line number $i." >> long_file.txt; done
   ```

2. 用 `less` 打开它：

   ```bash
   less long_file.txt
   ```

3. 现在您进入了 `less` 的界面：

   * 使用**方向键 `↑` `↓`** 或 **`PageUp` `PageDown`** 键来滚动。
   * 输入 `/` 然后跟上关键词，可以进行搜索。
   * 按 **`q`** 键退出查看器，返回到终端。

掌握了以上这些命令，您就已经具备了在 Linux 终端中进行基本文件管理和导航的能力，为后续所有更高级的操作打下了坚实的基础。

#### `clear`: 清空当前终端，但是记录不会删除

#### `history`: 查看当前终端命令的历史记录，会显示序列号，使用！+序列号可以执行该条指令

---

## 第四部分：软件管理与环境配置 —— 打造你的专属工具箱

本篇我们将聚焦于使用命令行来管理软件和配置系统环境。这是 Linux 系统最强大、最高效的部分。我们将学习 Ubuntu 的核心软件包管理器 `apt`，并通过实战来安装、配置和切换我们日常所需的工具。

---

### 12. 包管理器 `apt` 的核心用法

在 Linux 世界中，软件通常以“包 (Package)”的形式存在，而这些包被存放在互联网上的“软件仓库 (Repository)”中。`apt` (Advanced Package Tool) 就是 Ubuntu 系统上用于与这些仓库交互、全自动处理软件安装、更新和卸载的强大管家。

#### 核心 `apt` 命令

您需要掌握以下几个核心命令。由于它们会修改系统，所以通常需要 `sudo` 权限。

1.  **`sudo apt update` (更新软件列表)**
    * **作用**: 这条命令**不会升级**你的任何软件。它的作用是访问所有已配置的软件源服务器，下载一份最新的可用软件包“目录”。
    * **何时使用**: **在进行任何安装或升级操作之前，都应该先执行一次 `apt update`**，以确保您的系统知道有哪些最新的软件可用。

2.  **`sudo apt upgrade` (升级已安装的软件)**
    * **作用**: 这条命令会对比您本地已安装的软件版本和刚刚 `update` 下载的最新“目录”。如果发现有可升级的版本，它就会下载并安装它们。
    * **习惯**: `sudo apt update && sudo apt upgrade -y` 是一条非常好的组合命令，可以一次性完成列表刷新和软件升级。`-y` 表示在升级过程中自动回答“是”。

3.  **`apt search <关键词>` (搜索软件)**
    * **作用**: 当您不确定一个软件的准确包名时，可以用它来搜索。

4.  **`sudo apt install <软件包名>` (安装软件)**
    * **作用**: 安装一个新的软件包。`apt` 的强大之处在于，它会自动分析这个包需要哪些其他“依赖包”，并一次性将它们全部安装好。

5.  **`sudo apt remove <软件包名>` (卸载软件)**
    * **作用**: 卸载一个软件包。通常会保留它的配置文件。

6.  **`sudo apt purge <软件包名>` (彻底卸载软件)**
    * **作用**: 在卸载软件包的同时，也一并删除它的全局配置文件，清理得更干净。

---

### 13. 安装与配置中文输入法 (Fcitx5)

我们将安装目前最推荐的中文输入法框架 Fcitx5。

#### 步骤1：安装 Fcitx5 框架和中文引擎

```bash
# 首先刷新软件列表
sudo apt update

# 同时安装 Fcitx5 核心、中文插件包和配置工具
sudo apt install fcitx5 fcitx5-chinese-addons fcitx5-config-gtk
```

#### 步骤2：将系统输入法框架切换为 Fcitx5

我们需要告诉 Ubuntu，默认使用我们刚安装的 Fcitx5，而不是系统自带的其他输入法框架。

执行`im-config`，在弹窗下先点击OK，下一窗口选择YES，再在列表中选择fcitx5，点击Ok，最后需要重启虚拟机才能够完全生效。

---

### 14. 安装 VS Code 及另一种包管理器 `snap`

Visual Studio Code 是一个极其强大的代码编辑器。在 Ubuntu 上，安装它的最佳方式是使用 `snap`。

#### `apt` vs. `snap`

- `apt` 是 Ubuntu 传统的、与系统深度集成的包管理器。
- `snap` 是一种更现代的包管理器。Snap 包像一个“集装箱”，它将应用程序和其所有依赖都打包在一起，与系统其他部分隔离。这使得应用更新更快，也更安全。

#### 步骤1：使用 `snap` 安装 VS Code

```bash
# 'code' 是 VS Code 的包名
# '--classic' 选项给予 VS Code 必要的系统访问权限，以便它能正常工作
sudo snap install code --classic
```

#### 步骤2：如何启动 VS Code

在终端输入code即可，或者在应用程序列表里点击也可以。

---

### 15. 系统语言与输入法切换

#### 切换系统语言（一般不建议，用英文的bug少一些）

这是一个图形化操作，但了解它很重要。

1. 打开 **“设置 (Settings)”** -> **“区域与语言 (Region & Language)”**。
2. 在“**语言 (Language)**”一栏，您可以点击它来选择已安装的语言作为主语言。
3. 点击 **“管理已安装的语言 (Manage Installed Languages)”** 按钮，可以添加或删除系统中的语言支持。
4. **重要**: 任何对主语言的更改，都需要**注销并重新登录**后才能完全生效。登录时，系统会询问您是否要将标准文件夹（如“桌面”、“文档”）的名称更新为新语言，您可以根据需要选择。

#### 切换输入法

当您已经按照前面的步骤安装并配置好了多种输入法后（例如系统默认的英语键盘和我们安装的中文拼音），您可以通过以下方式在它们之间切换：

- **快捷键 (最常用)**:
  - **`Ctrl` + `Space` (空格键)**
  - 这是 Fcitx5 默认的切换快捷键。每按一次，就会在您的输入法列表中切换到下一个。
- **通过系统托盘图标**:
  - 在屏幕**右上角**的系统菜单区域，您会看到一个键盘图标（例如 `EN` 代表英语，`拼` 代表拼音）。
  - **直接点击这个图标**，就会弹出一个列表，显示出您所有可用的输入法，您可以点击选择要使用的那一个。这个图标也直观地告诉您当前正在使用哪种输入法。

---

## 第五部分：搭建数字IC设计环境 —— 核心开源EDA工具链

**前言**

恭喜您完成了前面所有基础部分的学习！现在，您的 Ubuntu 虚拟机不仅是一个稳定的操作系统，更是一个强大的工作平台。本部分我们将为其安装“灵魂”——一套专业的、开源的 **EDA (电子设计自动化)** 工具。

安装完这些工具后，您的虚拟机将具备从 Verilog 代码编写、功能仿真验证到逻辑综合的完整数字IC设计前端能力，成为一个功能完备的“数字逻辑实验室”。

---

### 16. Icarus Verilog (`iverilog`): 标准的 Verilog 仿真器

* **它是什么？**
  `Icarus Verilog` 是一个在学术界和开源社区中广泛使用的 Verilog 编译器和仿真器。您可以把它想象成 Verilog 语言的 `gcc` 编译器。它的任务是读取您的 `.v` 设计文件和测试平台文件，检查语法，并生成一个可执行的仿真模型。

* **核心作用**:
  **功能验证 (Functional Verification)**。通过仿真，您可以在将设计付诸物理实现之前，验证您编写的电路逻辑是否符合预期功能，从而在早期发现并修复绝大部分的设计错误。

* **安装命令**:

  ```bash
  sudo apt update
  sudo apt install iverilog
  ```

---

### 17. GTKWave: 图形化波形查看器

* **它是什么？**
  `GTKWave` 是一款功能强大且轻量化的波形查看工具。它本身不进行任何仿真，而是读取并显示由仿真器（如 Icarus Verilog）生成的波形数据文件（通常是 `.vcd` 格式）。

* **核心作用**:
  **仿真结果分析 (Simulation Result Analysis)**。您可以把它看作是您在数字世界的“虚拟示波器”。通过 GTKWave，您可以直观地看到设计中每一个信号在仿真过程中的高低电平变化，从而进行调试和分析。它是仿真验证过程中不可或缺的可视化工具。

* **安装命令**:

  ```bash
  sudo apt install gtkwave
  ```

---

### 18. Yosys: 强大的逻辑综合引擎

* **它是什么？**
  `Yosys` 是一个开源的 Verilog HDL 综合框架。它的角色是一位“硬件翻译官”。

* **核心作用**:
  **逻辑综合 (Logic Synthesis)**。Yosys 读取您的 RTL (寄存器传输级) Verilog 代码，并将其“翻译”成一个由基础逻辑门（如与门、或门、触发器等）和它们之间的连接关系构成的**门级网表 (Gate-Level Netlist)**。它是连接抽象的逻辑设计与具体的物理实现的桥梁。

* **安装命令**:

  ```bash
  sudo apt install yosys
  ```

---

### 19. Verilator: 高性能的 Verilog 转 C++ 编译器

* **它是什么？**
  `Verilator` 是另一款开源的 Verilog 仿真器，但它以**极致的速度**而闻名。与 `iverilog` 不同，它不是一个解释器，而是一个编译器。它会将您的 Verilog 代码转换成高度优化的 C++ 模型。

* **核心作用**:
  **高速仿真 (High-Speed Simulation)**。当您的设计变得非常庞大和复杂，`iverilog` 的仿真速度变得无法接受时，`Verilator` 就派上用场了。通过将硬件模型编译成原生的 C++ 代码，它的仿真速度可以达到甚至超过商业仿真器，非常适合进行大规模的系统级验证。

* **安装命令**:

  ```bash
  sudo apt install verilator
  ```

---

## 第六部分：构建工作习惯

掌握了 `git`, `make`, `iverilog`, `yosys` 等命令，就像是学会了乐器的指法。而将这些指法串联起来，演奏出优美的乐章，则需要我们养成良好的“练习习惯”和“乐理知识”。本篇将分享一些能让您在科研和工程道路上事半功倍的核心工作习惯。

---

### 20. 版本控制是一切的基石：Git 的日常化

我们已经学习了 `git init`, `add`, `commit`。现在，要将它从一个“偶尔使用的工具”变成一个像呼吸一样自然的**工作习惯**。

* **勤于提交 (Commit Early, Commit Often)**
  不要等到一天工作结束才进行一次巨大的提交。每当您完成一个**小的、逻辑上完整的功能**（例如，修复一个 bug、完成一个模块的编写、修改了一个测试用例），就应该进行一次提交。这样做的好处是：
  1.  您的修改历史会非常清晰。
  2.  如果发现后面的修改有问题，可以轻松地回退到前一个正确的状态。

* **撰写有意义的提交信息 (Write Meaningful Commit Messages)**
  `git commit -m "update"` 这样的信息是毫无价值的。一个好的提交信息应该遵循规范，例如：
  * **格式**: `类型: 简短描述`，如 `feat: Add ALU subtraction module` 或 `fix: Correct carry-out logic in full_adder`。
  * **内容**: 清晰地说明**这次提交做了什么**以及**为什么这么做**。

* **拥抱分支 (Embrace Branching)**
  **永远不要在 `main` 或 `master` 主分支上直接进行开发！** 这是专业开发的第一条铁律。
  * **工作流**: 当您要开始一个新功能或进行一项实验时，请创建一个新的分支：`git checkout -b new-feature-branch`。
  * 在这个新分支上随心所欲地工作、提交、甚至搞砸。
  * 当功能完成后，再将这个分支**合并 (merge)** 回主分支。
  * 这样做可以保证您的 `main` 分支永远是稳定、可用的。

* **善用远程仓库 (GitHub/GitLab)**
  在 GitHub 或类似的平台上为您的每一个项目创建一个私有仓库。在每天工作结束时，养成 `git push` 的习惯。这不仅是与他人协作的基础，也是您**最重要的数据异地备份策略**。

---

### 21. 文档驱动设计：为你的“遗产”负责

您写的代码、做的设计，不仅是给机器运行的，更是给未来的您和您的合作者看的。良好的文档是项目的生命线。

* **注释你的代码**: 注释不应该解释代码**在做什么**（例如 `a = a + 1; // a自增1`），而应该解释代码**为什么这么做**。

  ```verilog
  // 使用进位选择加法器结构，以优化关键路径延迟
  assign cout = ...; 
  ```

* **每个项目都应有 `README.md`**: 在您每个项目的根目录下，都应该有一个 `README.md` 文件。它应该至少包含：

  1.  项目的目标和简介。
  2.  项目的目录结构说明。
  3.  **如何构建和运行这个项目**（例如，需要哪些工具，`make` 的常用目标有哪些）。

* **记录设计决策**: 对于重要的设计选择（例如，“为什么我选择了多周期架构而不是单周期？”），建议您在一个单独的文档（如 `doc/design_notes.md`）中记录下来龙去脉。几个月后，您会感谢自己当初这么做了。

---

### 22. 自动化思维：让机器做重复的事

**如果发现自己正在手动重复某个操作超过两次，就应该考虑如何将它自动化。**

* **`Makefile` **: 持续迭代 `Makefile`。是否经常需要单独测试某个模块？那就为它添加一个 `make test_alu` 的目标。您是否需要生成最终的报告？那就添加一个 `make report` 的目标，让它自动运行所有脚本并整理结果。（给工具名，让ai帮你写makefile脚本，例如vcs，vnc服务器上有）

* **Shell 脚本**: 对于那些跨项目的、通用的重复性任务，请将它们写成一个可重用的 Shell 脚本。例如：
  * 一个可以一键创建标准项目目录结构（`rtl`, `tb`, `sim`...）的脚本。
  * 一个可以自动分析多个仿真结果文件并提取关键数据（如误码率）的脚本。

* **`alias` 是你的快捷键**: 对于您在终端中每天都要敲很多遍的长命令，请在您的 `~/.bashrc` 或 `~/.zshrc` 文件中为它创建一个简短的**别名 (alias)**。

---

### 23. 保持学习与探索：拥抱开源社区

您所学的这一整套工具链都源于开源社区，这是取之不尽的知识宝库。

* **阅读文档**: 养成遇到问题先查阅官方文档的习惯。
* **关注项目**: 在 GitHub 上关注 `Yosys`, `Cocotb`, `Verilator` 等项目，看看它们的发展动态，学习别人的代码和提交记录。
* **保持好奇**: 当您看到一个不理解的命令、脚本或配置时，不要满足于“复制粘贴能跑就行”，花几分钟时间去搜索和理解它背后的原理。
