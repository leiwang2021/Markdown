# Linux与Shell

## 第一章　初识Linux Shell

### 1.1 什么是Linux

- Linux分为四个部分：

  - Linux内核
  - GNU工具
  - 图形化桌面环境
  - 应用软件

- 内核：

  - 系统内存管理，物理内存和虚拟内存，通过硬盘上的存储空间来实现虚拟内存，即交换空间swap space
    - 页面（Page) 内存存储单元按组划分成很多块，内核将每个内存页面放在物理内存或交换空间
  - 软件程序管理
    - 内核创建了第一个进程（init进程)来启动其他进程，当内核启动时，它会将init进程加载到虚拟内存中，内核在启动任何其他进程时，都会在虚拟内存中给新进程分配一块专有区域
    - 管理自动启动的进程表，位于 /etc/inittab中，Ubuntu中采用/etc/init.d目录下存放开机启动或停止某个应用的脚本，这些脚本通过/etc/rcX.d目录下的入口启动。X代表运行级别
    - 有５个启动运行级，运行级为１时，只启动基本的系统进程以及一个控制台终端程序，单用户模式
    - 标准的启动运行级是３，大多数应用软件
    - ５运行级，会启动图形化的X windows系统，允许通过图形化桌面登录系统
  - 硬件设备管理
    - 设备驱动代码：编译进内核的设备驱动代码
    - 可插入内核的设备驱动模块
    - Linux系统将硬件设备当成特殊的文件，称为设备文件：字符型设备文件（每次只能处理一个字符的设备，如调制解调器、终端）、块设备文件（每次处理大块数据，如硬盘）、网络设备文件（各种网卡和回环设备，回环设备允许使用常见的网络编程协议同自身通信）
    - Linux为每个设备都创建了节点　特殊文件，与设备的通信通过设备节点完成
  - 文件系统管理
    - Linux支持通过对不同类型的文件系统从硬盘中读写数据
    - Linux内核采用虚拟文件系统（VFS)作为和每个文件系统交互的接口，当每个文件系统都被挂载和使用时，VFS将信息都缓存在内存中

- GNU工具

  - 核心GNU工具
    - 供Linux系统使用的核心工具被称为GNU coreutils软件包：用以处理文件的工具、用以操作文本的工具、用以管理进程的工具
  - Shell
    - GNU/Linux shell是一种特殊的交互式工具，为用户提供了启动程序、管理文件系统中的文件以及运行在Linux系统上的进程的途径，Shell的核心是命令提示符，允许输入文本命令，然后解释命令，并在内核中执行
    - Shell脚本：将多个Shell命令放入文件中，所有Linux发行版默认的Shell都是bash shell，由GNU项目开发

- Linux桌面环境

  Linux有各种图形化界面供选择，弊端：占用系统资源

  - X Windows系统

    - X Windows软件是图形显示的核心部分，是直接和显卡及显示器打交道的底层程序
    - 能够实现X Windows的软件包不止一种，核心的X Windows软件可以产生图形化显示环境，但没有桌面环境供用户操作

  - KDE桌面

    生成一个类似于Microsoft Windows的图形化桌面环境

  - GNOME桌面

    另一个流行的Linux桌面，很多的默认的

  - Unity桌面

    Ubuntu所采用的

### 1.2 Linux发行版

- 完整的核心Linux发行版，特定用途的发行版，LiveCD测试发行版

- 核心用途的Linux发行版：

  - 含有内核、图形化桌面环境、Linux应用， 如Debian

- 特定用途的Linux发行版

  - 如Ubuntu，CentOS
  - 许多特定用途的Linux发行版都是基于Debian Linux,它们使用和Debian一样的安装软件，但仅打包了完整的Debian系统中的一小部分

- Linux LiveCD

  无需安装，从CD上运行，无需安装在硬盘，  Ubuntu有

## 第二章 走进Shell

### 2.1 进入命令行

- CLI： 文本命令行界面
- 控制台终端：Linux控制台，让Linux系统退出图形化桌面环境，进入文本模式
  - Linux系统启动时，会自动创建一些虚拟控制台，是运行在Linux系统内存中的终端会话
  - 除了虚拟化终端控制台，还可以使用Linux图形化桌面环境中的终端仿真包，模拟控制台终端的使用
  - 可以把图形化终端仿真器看作GUI中的CLI终端，将虚拟控制台终端看作GUI以外的CLI终端

### 2.2 通过Linux控制台终端访问CLI

- 在启动时会创建多个虚拟控制台，但很多在完成启动之后会切换到图形化界面，只能通过手动的方式访问虚拟控制台，Ubuntu使用Ctrl+Alt+F7进入。
- 登录进虚拟控制台之后，就进入了Linux CLI，在LInux虚拟控制台中是无法运行任何图形化程序的
- 可以在多个虚拟控制台之间切换，拥有多个活动会话
- 如果需要一边访问CLI，一边运行图形化程序，使用终端仿真软件包解决。

### 2.3 通过图形化终端访问CLI

- 常见三种图形化仿真器软件：GNONE Terminal 、Konsole Terminal 和xterm,一般会默认安装

### 2.4 使用GNONE Terminal 仿真器

- GNONE Terminal是GNONE桌面环境的默认终端仿真器，也是Ubuntu的默认终端仿真器
- 访问GNONE Terminal
- 菜单栏
  - New tab 打开一个新标签，每个标签中的会话被认为是独立的CLI会话
  - close tab  
  - Reset 发送终端会话重置控制码
  - Help菜单包括GNONE手册

### 2.5 使用Konsole Terminal 仿真器

- 访问Konsole Terminal
  - KDE环境默认的
  - 可在Unity桌面环境下安装
- 菜单栏

### 2.6 使用Xterm终端仿真器

- 最古老最基础的，在ubuntu中是默认安装的
- 可以通过向xterm命令加入参数来调用某些配置选项

- 命令 -help 确定使用的xterm实现支持哪些参数

## 第三章 基本的bash shell命令

- 大多数Linux发行版默认的Shell都是GNU bash shell

### 3.1 启动Shell

- /etc/passwd文件包含了所有系统用户账户列表以及每个用户的基本配置信息，每个条目有7个字段，字段之间用:隔开，最后一个字段指定了用户使用的Shell程序

### 3.2 Shell提示符

- leiwang@leiwang   用户名ID+系统名

### 3.3 bash手册

- man命令用来访问存储在Linux系统上的手册页面
  - 如man xterm查找xterm命令，手册页是由分页程序显示的
  - man man 查看与手册页相关的手册页
  - man -k 关键字，使用关键字搜索命令，如man -k terminal查找与终端相关的命令
- Linux手册也的内容区域
  - man工具通常提供的是命令所对应的最低编号的内容，如man xterm, 手册页的xterm后有一个1，表示所显示的手册页来自内容区域1
  - man 1 hostname 显示手册的第一部分    man 7 hostname显示手册的第7部分
  - 大多数命令可以接受-help或 --help选项

### 3.4 浏览文件系统

- Linux文件系统

  - Linux将文件存储在单个目录结构中，这个目录称为虚拟目录，虚拟目录只包含一个根目录的基础目录
  - 根驱动器包含了虚拟目录的核心，其他目录都是从那儿构建的
  - 挂载点是虚拟目录中用于分配额外存储设备的目录，实际上它们存储在另一个驱动器中
  - 通常系统文件会存储在根驱动器中，而用户文件存储在另一驱动器中
  - Linux顶层虚拟目录名

    - /bin 二进制目录，存放GNU工具

    - /boot 存放启动文件
    - /dev  设备节点
    - /etc  系统配置文件目录
    - /home 用户目录
    - /usr  用户二进制目录
    - /var  如日志文件
  - 在登录获得一个Shell提示符后，会话将从主目录开始，主目录是分配给用户账户的一个特有目录

- 遍历目录

  - cd命令没有参数时，将切换到主目录

    - 绝对文件路径

      以/作为起始，指明虚拟文件系统的根目录，波浪号表明Shell会话位于主目录中，pwd可以显示Shell会话的当前目录

    - 相对文件路径

      基于当前位置的目标文件路径

      单点符. 表示当前目录

      双点符.. 表示当前目录的父目录

### 3.5 文件和目录列表

- 查找文件和目录
  - find 

- 基本列表功能
  - ls -F可区分文件和目录，在可执行文件后加个星号
  - Linux经常使用隐藏文件来保存配置信息，隐藏文件通常是文件名以点号开始的文件，要显示它，需要 ls -a 命令
  - ls -R列出所有子目录下的所有文件
  - 命令可进行合并  如   ls  -FR
- 显示长列表
  - ls -l  输出的第一行显示了在目录中包含的总块数，每一行还包含了文件的各种信息
- 过滤输出列表
  - 决定显示哪些文件，如 ls -l  my_script只显示该文件信息
  - ?代表一个字符
  - *代表零个或多个字符，如  ls  -l  an\*
  - 文件扩展匹配  [ai]   [a-i]   [!a]

### 3.6 处理文件

- 创建文件
  - touch命令创建空文件，若文件已存在，则修改文件的修改时间，不改变内容
  - touch -a 改变访问时间
  - 查看文件的访问时间，  ls -l  --time=atime
- 复制文件
  - cp 命令需要两个参数  cp  source destination   ,若再加上-i命令，询问是否需要覆盖已有文件
  - 在目标目录名尾部加上/,表明是目录而不是文件
  - 单点符适用于cp命令，表示将文件复制到当前工作目录
  - cp -R复制整个目录的内容到一个新的目录 ，如 cp  -R  Scripts/      Mod_Scripts
  - 通配符也可以用到cp命令中
- 制表键自动补全
- 链接文件
  - 采用保存一份物理文件副本和多个虚拟副本的方式，虚拟的副本称为链接，链接是指向文件真实位置的占位符
  - 符号链接是一个真实的文件，指向存放在虚拟目录结构中某个地方的另一个文件，通过符号链接在一起的文件，内容并不相同，如  ln  -s  data_file   sl_data_file
  - 文件或目录的inode编号是用于标识的唯一数字，ls -i  可查看
  - 硬链接会创建独立的虚拟文件，根本上而言是同一个文件，带有硬链接的文件共享inode编号
  - 同一个文件可拥有多个链接

- 重命名文件
  - 重命名文件称为移动，mv命令
  - 如  mv test_1   ./learn_test   将test_1文件移动到learn_test文件夹下，  mv也可修改文件名称，也可移动整个文件夹
- 删除文件
  - rm -i  文件名    一旦删除无法找回

### 3.7 处理目录

- 创建目录
  - mkdir  要同时创建多个目录时，加入-p命令
- 删除目录
  - rmdir,  默认情况下只能删除空目录
  - 可以使用  rm  -ri     目录名    递归删除目录下的所有文件和目录
  - rm  -rf没有警告信息，删除所有

### 3.8 查看文件内容

- 查看文件类型
  - file命令，不仅能确定包含的文本信息，还能确定其字符编码。还能确定目录
- 查看整个文件
  - cat命令    cat  -n给所有的行加上行号   cat  -b只给有文本的行加上行号
  - more命令会显示文本文件的内容，但会在显示每页数据之后停下来， q退出
  - less命令是more命令的升级，包含所有的more命令
- 查看部分文件
  - tail命令 默认显示文件的末尾10行    tail  -n  2  log_file   只显示最后两行
  - head显示文件前10行

## 第四章 更多的bash shell 命令

### 4.1 监测程序

- 探查进程

  - ps默认情况下，只会显示运行在当前控制台下的属于当前用户的进程

    - 进程ID（PID） 
    - 运行在哪个终端（TTY） 
    - 进程已用的CPU时间
    - Unix风格的参数，前面加单破折号
    - BSD风格的参数，前面不加破折号
    - GNU风格的长参数，前面加双破折号

  - Ｕnix风格的参数

    - 如ps -ef　　查看系统上运行的所有进程
    - UID: 启动这些进程的用户
    - PPID:父进程进程号
    - CMD:启动的程序名称
    - ps -l显示一个长格式输出

  - BSD（伯克利软件发行版）风格的输出

    - ps T
    - ps g
    - ps l采用长模式　　STAT列：双字符状态码

  - GNU长参数

    - ps --forest会显示进程的层级信息

- 实时监测进程
  - top命令实时显示进程信息
- 结束进程
  - 在Unix中，进程之间通过信号来通信，进程的信号就是预定义号的一个消息，进程能识别它并决定忽略还是做出反应
  - kill命令，kill命令可通过进程ＩD给进程发信号
    - -s命令支持指定其他信号
    - 如　kill -s   KILL  3570强行kill　3570进程，有的需要sudo权限
    - killall 支持通过进程名结束进程，也支持通配符

### 4.2 监测磁盘空间

- 挂载存储媒体
  - 在使用新的存储媒体之前，需要把它放在虚拟目录下，称为挂载，大部分发行版可自动挂载
  - mount命令，默认情况下会输出当前系统上挂载的设备列表
    - 提供四部分信息：媒体的设备文件名，媒体挂载到虚拟目录的挂载点。文件系统类型，已挂载媒体的访问状态
    - 手动挂载媒体设备的基本命令:  mount  -t type  device  directory
  - umonut命令　移除一个可移动设备时，不能直接从系统上移除，而应该先卸载
  - 使用df命令
    - df命令可以查看已挂载磁盘的使用情况,进程中使用的空间不会算为空闲
    - df -h   
  - du命令
    - 显示某个特定目录的磁盘使用情况（默认是当前），以磁盘块为单位
    - du -c 显示总大小　　du -h以易读的方式显示

### 4.3 处理数据文件

- 排序数据
  - sort参数，默认情况下会把数字当成字符排序，加-n参数会把数字识别成数字而不是字符，　-M参数，按月排序
  - sort -k 指定排序位置，　　sort -t指定区分键，　例如：sort -t ':'  -k 3 -n /etc/passwd
  - du -sh *| sort -nr   管道命令(|)将du命令的输出重定向到sort命令
- 搜索数据
  - grep在指定文件中查找匹配指定模式的字符的行，例如：　grep t filenam　找到包含t的行
  - grep -v t filename  找到不包含字符't'的行
  - 若要显示行号，加-n参数
  - 也可使用正则表达式
- 压缩数据
  - .bz   
  - .z
  - gzip工具　　.gz  GNU压缩工具
    - gzip  用来压缩文件
    - gunzip  用来解压缩文件
  - .zip  Windows上ＰＫＺＩＰ工具的Unix实现
- 归档数据
  - tar function [options]  object1 object2
  - tar -cvf  test.tar test/test2   将test/test2 归档为test.tar文件
  - tar -tf列出内容，但不提取
  - tar -xvf test.tar 提取文件
  - 很多开源软件以.tgz结尾，这些是gzip压缩过的tar文件。　可以以命令tar -zxvf filename.tgz来解压

## 第五章　理解shell

### 5.1 shell的类型

- 在/etc/passwd文件中，在用户ID记录的第七个字段中列出了默认的shell程序，　采用bash shell作为默认
- 默认的系统shell:　/bin/sh在ubuntu中软链接向dash shel
- 即有默认的交互shell和默认的系统shell
- 输入/bin/dash可启动dash　shell,  exit可退出

### 5.2 shell的父子关系

- 默认启动的是父shell, 在父shell中输入/bin/dash启动的是子shell
- 在生成子shell进程时，只有部分父进程的环境被复制到子shell环境中
- 子shell可以从父shell中创建，也可以从子shell中创建，ps --forest查看
- bash 的命令行参数
- exit可退出，可退出所有
- 进程列表
  - 命令列表，如 pwd;ls;cd /etc;pwd;ls
  - 进程列表，如(pwd;ls;cd /etc;pwd;ls), 加括号成为进程列表（是一种列表分组），生成了一个子shell来执行对应的命令
  - 另一种列表分组是{command ;}不会创建子shell
  - 借助环境变量查看生成了子shell,   echo $BASH_SUBSHELL$,若为０，则没有子shell
  -  (pwd;ls;cd /etc;pwd;ls; echo $BASH_SUBSHELL$)
  - 在shell脚本中，经常使用子shell进行多进程处理，但它并非真正的多进程处理，因为终端控制着子shell的I/O
- 在后台模式中运行命令可以在处理命令的同时让出ＣＬＩ，以供他用
  - sleep 10暂停１０秒
  - 将命令置入后台模式，在末尾加上&
  - jobs显示后台作业信息
  - 将进程列表置入后台模式，既可以在子shell中进行工作，同时不会让子shell的Ｉ/O受制于终端
- 协程
  -  在后台生成一个子shell,并在这个子shell中执行命令
  -  coproc 
  -  coproc sleep 10
  -  coproc My_Job { sleep 10; },　将协程命令
  -  coproc (sleep 10;sleep 10)　　将协程与进程列表结合产生嵌套子shell
  -  生成子shell的成本不低

### 5.3 理解shell的内建命令

- 外部命令

  - 也称为文件系统命令，是存在于bash　shell之外的程序，并不是shell程序的一部分，外部命令程序通常位于　/bin  /usr/bin  /sbin  /usr/sbin 中
  - ps是一个外部命令，可以通过which 和type找到它
  - 当外部命令执行时，会创建出一个子进程，即衍生，

- 内建命令

  - 不需要子进程来执行，已经和shell编译成了一体，作为shell工具的组成部分存在，更快

  - 可通过type查看命令是否是内建的

  - 有些命令有多种实现，既有内建命令又有外部命令　　　使用 type -a 查看

  - 要使用其外部命令实现，直接指明对应的文件

  - 内建命令: history  跟踪用过的命令，可以修改HISTSIZE环境变量设置保存在bash历史记录中的命令数　　！！执行上一条命令　　命令历史记录保存在.bash_history隐藏文件中，位于用户的主目录

    history -a在打开的会话中向.bash_history文件中添加记录　　!20编号为２０的命令历史记录中被取出

  - 命令别名，为常用的命令创建另一个名称　　alias -p 可查看　　alias li='ls -li'  创建自己的别名，命令别名属于内部命令，仅在被定义的shell进程中才有效

  - 当用户登录终端时，通常会启动一个默认的交互式shell，一般是/bin/bash  默认的系统shell(/bin/sh)用于系统shell脚本，如那些需要在系统启动时运行的脚本

## 第六章　使用Linux环境变量

### 6.1 什么是环境变量

- 环境变量分为：　全局变量　　局部变量
- 全局环境变量：对于shell和子shell都可见，系统环境变量一般使用大写字母，
  - 使用　env 或 printenv命令查看　　env显示全部的　　printenv HOME
  - ​        echo  $HOME也可显示    在变量名前加上$能够让变量作为命令行参数
- 局部环境变量：只能在定义它的shell可见
  - set命令会显示为某个特定进程设置的所有环境变量，包括局部变量、全局变量、用户定义变量

### 6.2 设置用户定义变量

- 设置局部用户定义变量
  - 可以通过等号给环境变量赋值　　 echo $my_variable　　　　 echo $my_variable
  - 自己创建的局部变量或shell脚本，使用小写字母
- 设置全局环境变量
  - 先创建一个局部环境变量，再把它导出到全局环境中，通过export完成
  - 修改子shell中全局环境变量并不会影响到父shell中该变量的值

### 6.3 删除环境变量

- unset my_variable  
- 要用到变量，使用$, 要操作变量，不使用　$,  删除子进程中环境变量，该变量在父进程中仍然可用

### 6.4 默认的shell环境变量



### 6.5 设置PATH环境变量

- 在shell命令行界面输入一个外部命令时，shell必须搜索系统来找到对应的程序。PATH环境变量定义了用于进行命令和程序查找的目录

- echo $PATH　　　

  /usr/local/cuda-9.0/bin:/home/leiwang/.local/bin:/opt/jvm/jdk1.8.0_181/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin　　　使用冒号分割

- 若命令或程序的位置没有包括在PATH变量中，若不使用绝对路径的话，shell是没法找到的，若shell找不到，会产生一个错误信息: command not found

- 将新的搜索目录添加到现有PATH环境变量中

  ```shell
  echo $PATH
  PATH=$PATH:/home/christine/Scripts    添加了搜索目录
  如果要子shell也能找到程序的位置，把修改后的PATH环境变量导出　export
  ```

- 将单点符加入到PATH环境变量，单点符代表当前目录 .

- 对PATH变量的修改只能持续到退出或重启系统

### 6.6 定位系统环境变量

- 默认情况下bash会在几个文件中查找命令，这些文件叫做启动文件或环境文件
- 登录shell
  - 登录Linux系统时，bash shell作为登录shell启动，登录shell会从５个不同的启动文件里读取命令
    - /etc/profile    是系统上默认的bash shell的主启动文件，系统上每个用户登录时都会执行这个启动文
    - $HOME目录下的启动文件，提供一个用户专属的启动文件来定义该用户所用到的环境变量
    - $HOME/.bash_profile    都是隐藏文件,不一定都有
    - $HOME/.bashrc
    - $HOME/.bash_login
    - $HOME/.profile
- 交互式shell进程
  - 不是在登录系统时启动的
  - 不会访问/etc/profile文件，只会检查用户HOME目录中的.bashrc文件
  - .bashrc文件有两个作用: 一是查看/etc目录下通用的bashrc文件，而是为用户提供一个定制自己的命令别名和私有脚本函数
- 非交互式shell
  - 系统执行shell脚本时，没有命令提示符
  - 当shell启动一个非交互式进程时，会检查BASH_ENV这个环境变量来查看要执行的启动文件
  - 由父shell设置但并未导出的变量都是局部变量，子shell无法继承局部变量
- 环境变量持久化
  - 最好是在/ect/profile.d目录中创建一个以.sh结尾的文件，把所有新的或修改过的全局环境变量设置放在这个文件中

### 6.7 数组变量

- 环境变量可以作为数组使用

  ```shell
  mytest=(one two three)
  echo $mytest
  echo ${mytest[2]}
  echo ${mytest[*]}
  ```

## 第７章　理解Linux文件权限

### 7.1 Linux的安全性

- /etc/passwd文件
  - 将用户的登录名匹配到对应的UID值
  - root用户账户是Linux系统的管理员，固定分配给它的UID是０
  - Linux系统会为各种各样的功能创建不同的用户账户
  - 所有的密码字段都被设置成了x,将用户密码保存在了/etc/shadow中
  - 若文件出现损坏，系统就无法读取内容，导致用户无法正常登录
- /etc/shadow文件
  - 只有root用户能访问
- 添加新用户
  - useradd命令，使用系统的默认值以及命令行参数来设置用户账户，可使用useradd -D查看默认值
  - 默认时系统会将/etc/skel目录下的内容复制到用户HOME目录下
  - useradd  -m  test　　创建新用户
  - 查看新用户的HOME目录: ls -al /home/test
  - 可以在-D 选项后跟上一个指定的值来修改系统默认的新用户设置
  - useradd -D -s /bin/tsch
- 删除用户
  - 默认情况下，userdel只删除/etc/passwd文件中的用户信息，而不会删除属于该账户的任何文件
  - 若加上-r参数，会删除用户的HOME目录以及邮件目录，但系统上仍可能存在已删除用户的其他文件，需慎用
- 修改用户
  - usermod命令
  - passwd更改密码
  - finger 命令可查看系统上的用户信息

### 7.2 使用Linux组

- 组权限允许多个用户对系统中的对象共享一组共用的权限，唯一的GID
- /etc/group组的信息
- 当一个用户在/etc/passwd文件中指定某个组作为默认组时，用户账户不会作为该组成员再出现在/etc/group中
- 创建新组  groupadd
- 修改组   groupmod

### 7.3理解文件权限

- 使用文件权限符
  - 第一个字段描述文件和目录权限的编码
  - 之后有三组三字符的编码，每一组定义了３种访问权限，若没有某种权限，则为单破折号，这三组权限分别对应对象的三个安全级别
- 默认文件权限
  - umask用来设置所创建文件和目录的默认权限，第一位代表粘着位，后三位表示umask八进制值
  - umask值是一个掩码
  - umask 026设置一个指定新值

### 7.4 改变安全性设置

- 改变权限
  - chmod  760 newfile    使用八进制赋予newfile新的权限
  - chmod有八进制模式和符号模式两种
- 改变所属关系
  - chown改变文件的属主
  - chgrp改变文件的默认属组

### 7.5 共享文件



## 第８章　管理文件系统

### 8.1 探索Linux文件系统

- 基本的Linux文件系统
  - ext文件系统(扩展文件系统)：　使用虚拟目录来操作硬件设备，通过索引结点号来标识文件，按定长的块来存储数据
  - ext2文件系统，扩展了索引节点表的格式，通过按组分配磁盘块来减轻碎片化，文件系统每次存储或更新文件，都要用新信息来更新索引节点表，可能会对系统造成问题
- 日志文件系统
  - 先将文件的更改写入到临时文件，在数据成功写到存储设备和索引节点表后，再删除对应的日志条目。若系统在数据被写入存储设备之前断点了，日志文件系统下次会读取日志文件并处理上次留下的未写入数据
    - 数据模式
    - 有序模式
    - 回写模式
  - ext3文件系统（一般默认的) 
    - 给每个存储设备增加了一个日志文件，默认为有序模式
  - ext4文件系统(Ｕbuntu的默认)
    - 支持数据压缩和加密
    - 区段在存储设备上按块分配空间，但在索引节点表中只保存起始块的位置
    - 块预分配技术
  - Reiser文件系统
  - JFS文件系统
  - XFS文件系统
- 写时复制文件系统(COW)
  - ZFS文件系统
  - Btrf文件系统

### 8.2 操作文件系统

- 创建分区

  - fdisk工具用来帮助管理安装在系统上的任何存储设备上的分区

  - Linxu使用/dev/sdx为硬盘分配设备名称，其中x可能是a,b...

    - sudo fdisk  /dev/sdb  指定要分区的存储设备的设备名　
    - 可用p命令将一个存储设备的详细信息显示出来，　此处sda为固态硬盘，sdb为磁盘，其中有488.5G为Linux文件系统
    - n创建分区，分区可以按主分区或扩展分区
    - fdisk允许创建多种分区类型，用w命令将更改保存到存储设备上

- 创建文件系统

  - 在将数据存储到分区之前，必须使用某种文件系统对其进行格式化
  - mkfs.ext4  创建一个ext4文件系统　　　sudo  mkfs.ext4  /dev/sdb1
  - 为分区创建了文件系统之后，下一步将它挂载到虚拟目录下的某个挂载点，这样就可以将数据存储到新文件系统中了
  - mkdir在虚拟目录创建挂载点，mount将新的硬盘分区添加到挂载点
  - /mnt下挂载是临时的，　　/etc/fstab下挂载在Ｌinux启动时自动挂载

- 文件系统的检查与修复

  - fsck能够检查和修复大部分类型的Ｌinux文件系统
  - fsck options filename
  - 只能在未挂载的文件系统上运行fsck命令

### 8.3 逻辑卷的管理

可以将另外一个硬盘上的分区加入已有文件系统，动态地添加存储空间，Linux逻辑卷管理器(LVM)

- 逻辑卷管理布局
  - 硬盘分区称为物理卷 PV，逻辑卷管理系统将卷组视为一个物理硬盘
  - Linux系统将逻辑卷视为物理分区，每个逻辑卷可以被格式化成ext4文件系统，然后挂载到虚拟目录中某个特定位置
- Linux中的LVM
  - LVM2的功能
    - 快照：允许在逻辑卷在线的状态下将其复制到另一个设备
    - 条带化：可跨多个物理硬盘创建逻辑卷
    - 镜像：一个实时更新的逻辑卷的完整副本，写操作时，一次写入到逻辑卷，一次写入到镜像副本
- 使用LVM
  - 定义物理卷：将硬盘上的物理分区转换成LVM使用的物理卷区段
    - fdisk创建，t改变分区类型
    - 分区类型8e表示被用作LVM系统的一部分
    - 用分区创建实际的物理卷: sudo pvcreate /dev/sdb1
    - 可以使用pvdispaly查看已创建的物理卷列表
  - 创建卷组
    - sudo vgcreate Voll /dev/sdb1
  - 创建逻辑卷
    - Linux系统使用逻辑卷来模拟物理分区，并在其中保存文件系统，并允许将文件系统挂载到虚拟目录上
    - lvcreate创建逻辑卷选项
  - 创建文件系统
    - sudo mkfs.ext4  /dev/Voll/lvtest
  - 挂载到虚拟目录上
    - sudo mount /dev/Voll/lvtest  /mnt/my_partition
  - 修改LVM
    - 能够动态修改文件系统

## 第九章　安装软件程序

### 9.1 包管理基础

- PMS包管理系统使用一个数据库来记录各种相关内容
- PMS基础工具是dpkg和rpm
- 基于Debian(如Ubuntu)使用的是dpkg命令
- 基于Red Hat(如Fedora)使用的是rpm命令

### 9.2 基于Debian的系统

- 包含在PMS的其他工具还有:

  - apt-get
  - apt-cache
  - aptitude. 本质上是apt工具和dpkg的前端

- 用aptitude管理软件包

  - aptitude进入全屏模式，管理
  - 在命令行下以单个命令显示:  aptitude show packge_name
  - dpkg -L pack_name  输出软件包所安装的全部文件
  - 查找某个特定文件属于哪个软件包：　dpkg   --search  filename(绝对路径)

- 用aptitude安装软件包

  - aptitude 　search package_name  找到相关的软件包
    - p或v表示可用还未安装，i表示已安装
    - c表示软件已删除，但配置文件未清除
  - aptitude install package_name  从软件仓库中安装软件包

- 用aptitude更新软件

  - 解决有依赖关系的多个包时，可用aptitude  safe-upgrade可安全更新所有软件包

- 用aptitude卸载软件

  - aptitude remove   packge_name 只删除软件包而不删除数据和配置文件
  - aptitude purge     packge_name  删除软件包和相关的数据和配置文件

- aptitude仓库

  - aptitude默认的软件仓库位置是在安装Linux发行版时设置的，在/etc/apt/sources.list中
  - 如果需要添加额外的软件仓库，在上面这个文件中设置
  - 通常通过库来升级或安装软件包最安全，不会相互冲突
  - deb( or deb-src) address distribution_name package_type_list   deb说明是一个已编译程序源，deb-src说明是一个源代码源
  - 通常软件仓库网站或各种包开发人员网站上都会有一行文本，可以直接复制粘贴到source.list中

- apt命令

  - apt install

  - apt remove

  - apt purge

  - apt update   刷新存储库索引

  - apt upgrade 升级所有可升级的软件包

  - apt list  列出包含条件的包（已安装，可升级等

  - apt edit-sources 编辑源列表

  - ```
    、dpkg是用来安装.deb文件,但不会解决模块的依赖关系,且不会关心ubuntu的软件仓库内的软件,可以用于安装本地的deb文件。
    2、apt会解决和安装模块的依赖问题,并会咨询软件仓库, 但不会安装本地的deb文件, apt是建立在dpkg之上的软件管理工具。
    ```

  - 软件安装后相关文件位置

    1.下载的软件包存放位置

    /var/cache/apt/archives

    2.安装后软件默认位置

    /usr/share

    3.可执行文件位置

    /usr/bin

    4.配置文件位置

    /etc

    5.lib文件位置

    /usr/lib

  - sources.list  存放有你要访问的软件源的地址。

### 9.3 基于Red Hat的系统

- yum   都是基于rmp命令行工具的
- urpm
- zypper
- 列出已安装的包
  - yum list installed
  - 查找特定文件属于的安装包 yum provide file_name

### 9.4 从源码安装

- 软件包sysstat提供了各种系统监测工具

- 地址;<http://sebastien.godard.pagesperso-orange.fr/download.html>

- 解压： tar -zxvf sysstat-12.1.5.tar.gz

- ./configure检查系统，确保有合适的编译器能编译源代码，还需要正确的库依赖关系

- 1、configure，这一步一般用来生成 Makefile，为下一步的编译做准备，你可以通过在 configure 后加上参数来对安装进行控制，比如代码:./configure –prefix=/usr 意思是将该软件安装在 /usr 下面，执行文件就会安装在 /usr/bin （而不是默认的 /usr/local/bin),资源文件就会安装在 /usr/share（而不是默认的/usr/local/share）。同时一些软件的配置文件你可以通过指定 –sys-config= 参数进行设定。有一些软件还可以加上 –with、–enable、–without、–disable 等等参数对编译加以控制，你可以通过允许 ./configure –help 察看详细的说明帮助。

  2、make，构建各种二进制文件，会编译源码，链接器会为这个包创建最终的可执行文件,从这个目录下运行不便，需要安装到Linux系统中常用的位置上

  这一步就是编译，大多数的源代码包都经过这一步进行编译（当然有些perl或python编写的软件需要调用perl或python来进行编译）。如果 在 make 过程中出现 error ，你就要记下错误代码（注意不仅仅是最后一行），然后你可以向开发者提交 bugreport（一般在 INSTALL 里有提交地址），或者你的系统少了一些依赖库等，这些需要自己仔细研究错误代码。

  3、make insatll，安装到系统上常用的位置上，这条命令来进行安装（当然有些软件需要先运行 make check 或 make test 来进行一些测试），这一步一般需要你有 root 权限（因为要向系统写入文件）。




## 第10章　使用编辑器

### 10.1 vim 编辑器

- 检查vim软件包
  - 如果vim设置了链接，可能被链接到一个功能较弱的编辑器
  - Ubuntu中输入vi命令时，执行的是链接后的 vim.tiny  只提供少量的vim功能
  - readlink -f /usr/bin/vi查看指向的链接文件
  - /usr/bin/vim.basic基础版的vim
- vim基础
  - 在内存缓冲区处理数据
  - 普通模式下：gg移到第一行　　G移到最后一行　　　num G移到第num行
  - 命令行模式下：q   q!   w  wq
- 编辑数据
  - x
  - dd
  - dw
  - d$
  - J
  - u
  - A
- 复制和粘贴
  - p粘贴
  - 复制命令：　y
  - 在可视模式下复制：　　v进入可视模式，覆盖了需要复制的后，y键复制
- 查找和替换
  - /word  查找该单词

### 10.2 nano编辑器

### 10.3 emacs编辑器

- 有控制台模式和图形模式两种
- which命令未找到已安装命令时，直接返回的是bash shell提示符
- 在Ubuntu上安装emacs编辑器　sudo apt-get install emacs
- 在控制台使用emacs
  - 在图形化界面中使用emacs:    emacs -nw  filename
  - 只有一个模式
- 在GUI环境中使用emacs

### 10.5 GNOME编辑器

- gedit
- F9启用左显示框

## 第11章　构建基本脚本

### 11.1 使用多个命令

- 多个命令放在同一行执行时，用分号隔开，如 date; who

### 11.2创建shell脚本文件

- 创建shell脚本，要在文件的第一行指定要使用的shell
  - #!/bin/bash    #为注释，这一行例外
  - ./test1   在当前目录下运行脚本test1
  - 需要赋予权限　　chmod u+x test1

### 11.3 显示消息

- echo   "字符串"　　　
- echo -n可以把文本字符串和命令行输出显示在同一行中

### 11.4　使用变量

- 环境变量

  - set可显示环境变量列表
  - 在shell中，可以在环境变量前加上&使用环境变量
  - USER  UID  HOME
  - 只要脚本中出现$,认为在引用一个变量，可加上\显示$
- 用户变量

  - shell脚本自动识别变量值的类型，在脚本的整个生存期间存在，用户变量可通过$引用
  - 在将一个变量赋值给另一个变量时，仍然需要$,没有$，变量会被解释为普通的文本字符串
- 命令替换：允许将shell命令的输出赋给变量
  - 反引号`　　　testing= $(date)
  - $()格式
  - date+%y%m%d
  - 命令替换换创建一个子shell来运行对应的命令，由该子shell所执行命令是无法使用脚本中所创建的变量的
  - ./运行命令会创建子shell，不加入路径就不会创建子shell

### 11.5 重定向输入和输出

- 输出重定向
  - command>outputfiles
  - date >test2  将输出重定向到文件
  - date >>test2 追加数据到文件后
- 输入重定向
  - 将文件的内容重定向到命令
  - command < inputfile
  - wc可以对数据文本进行计数
  - wc <test6
  - 内联输入重定向  <<
  - wc  EOF   date  EOF      EOF为开始和结束标识

### 11.6 管道

- 将一个命令的输出作为另一个命令的输入
- command1 | command2
- rpm -qa | sort |more

- 可以搭配使用重定向和管道将输出保存到文件中

### 11.7 执行数学运算

- expr命令
  - expr 1+5
- 使用方括号
  - var1=$[1+5]
  - echo $var1
  - bash shell只支持整数运算
- 浮点解决方案
  - bc计算器，允许在命令行中输入浮点表达式
  - scale内建变量控制小数位数
  - 在脚本中使用bc
    - 可以用命令替换运行bc命令
    - var1=$(echo "scale=4; $var1/$var2" | bc)
    - 内联输入重定向结合bc命令

### 11.8 退出脚本

- $?保存上个已执行命令的退出状态码
- 一个成功结束的命令退出状态码是０，错误时为一个正数值
- exit命令
  - 默认时，shell脚本会以脚本中的最后一个命令的退出状态码退出
  - exit命令允许脚本结束时指定一个退出状态码
  - 命令状态码的范围是0-255

## 第12章　使用结构化命令

### 12.1 if-then语句

- ```shell
  if command
  then 
  	command
  fi
  ```

  如果if后的命令执行成功，则执行then后的命令，否则不执行

- then部分可以使用不止一条命令

### 12.2   if-then-else语句

- 当if语句的命令返回非０退出状态码时，执行else部分中的命令

### 12.3 嵌套if

- elif

  ```shell
  if command1
  then
  	command2
  elif command3
  then
  	command4
  fi
  ```

### 12.4 test 命令

- test condition  　条件成立时，退出返回状态码０，不成立返回非零状态码，可以和if语句合用

- 另一种条件测试方法：加方括号

  ```
  if test codition
  then
  	comand
  else
  	comand
  fi
  
  if [ condition ]
  then
  	command
  else
  	command
  fi
  ```

- teset 命令可以判断三类条件

  - 数值比较
  - 字符串比较
  - 文件比较

- 数值比较

  - eq  ge gt le lt ne
  - bash shell只能处理整数

- 字符串比较

  -  =  !=  <  >   -n  -z
  - \> 需要转义符号\ 
  - sort命令处理大写字母的方法跟test命令相反
  - test命令和测试表达式使用标准的数学比较符号来表示字符串比较，而用文本代码来表示数值比较
  - \- n \-z  检查一个变量是否含有数据
  - 空的和未初始化的变量会对shell脚本测试造成灾难性的影响

- 文件比较

  - -d  -e  -f -r  -s -w  -x -O -G   file1 -nt file2  file1  -ot file2
  - -d 检查目录
  - -e 检查文件是否存在
  - -f 是否为文件
  - -r 是否可读
  - -s 文件是否为空
  - -w是否可写
  - -x 是否有执行权限
  - -O是否为文件属主
  - -G 检查默认组
  - -nt 一个文件是否比另一个文件新
  - -ot 一个文件是否比另一个文件旧

- 复合条件测试

  - [ condition1 ] && [ condition2 ]
  - [ condition1 ] || [ condition2 ]

### 12.6 if-then的高级特性

- 使用双括号　　(())
  - 双括号中可以是高级数学表达式
  - (( val2=$val1**2))   
  - 双括号中的大于符号不需要转义
- 使用双方括号
  - [[]]
  - 提供了针对字符串比较的高级特性
  - 提供了test命令未提供的一个特性:模式匹配
  - 模式匹配中，可以定义一个正则表达式来匹配字符串值



### 12.7 case命令

```shell
case variable in
pattern1 | pattern2) commands1;
pattern3) commands2;;
*) default commands;;
esac
```



## 第13章　更多的结构化命令

### 13.1 for命令

- for命令

  ```shell
  for var in list
  do
  	commands
  done
  ```

- 读取列表中的值

- 读取列表中的复杂值

  - 有单引号时，采用转义字符或者双引号解决
  - for循环假设每个值都是用空格分割的，有空格的数据
  - 如果在单独的数据中有空格，用双引号圈出来

- 从变量读取列表

- 从命令读取值

  - 使用命令的输出
  - for 命令可以以每次一行的方式读取cat命令的输出

- 更改字段分隔符

  - 内部字段分隔符环境变量IFS定义了bash shell用作字段分隔符的一系列字符
  - 默认情况下为：
    - 空格
    - 制表符
    - 换行符
  - 可以在shell脚本中临时更改IFS环境变量的值来限制被bash shell当做分隔符的字符　　IFS=$'\n'
  - 遍历文件时
  - 指定多个IFS值　　IFS=$'\n':;""

- 用通配符读取目录

  - bash shell会将额外的单词当作参数，进而造成错误

### 13.2 C语言风格的for 命令

- C语言的for命令
  - 变量赋值可以有空格
  - 条件中的变量不以美元符开头
  - 迭代过程中的算式未用expr命令格式
- 使用多个变量

### 13.3 while命令

- 在test命令返回非零退出状态码时，while命令会停止执行那组命令

  ```
  while test command
  do
  	other command
  done
  ```

- 使用多个测试命令，只有最后一个测试命令的退出状态码被用来决定什么时候结束循环

### 13.4 until命令

- 只有测试命令的退出状态码不为0，bash shell才会执行循环中列出的命令

  ```
  until test commands
  do
  	other commands
  done
  ```

- 和while命令类似，只有最后一个命令的退出状态码决定

### 13.5 嵌套循环

### 13.6 循环处理文件数据

```shell
 #!/bin/bash
 
 IFS.OLD=$IFS
 IFS=$'\n'
 for entry in $(cat /etc/passwd)
 do
     echo "Values in $entry -"
     IFS=:
     for value in $entry
     do
         echo "   $value"
     done
 done

```

### 13.7 控制循环

- break和continue命令
- break  n     n可指定要跳出的循环层级，默认为1
- continue n   n定义了要继续的循环层级

### 13.8 处理循环的输出

- 对循环的输出使用管道或进行重定向，在done命令后添加一个处理命令实现

### 13.9 实例

- 查找可执行文件
  - 对PATH中的目录进行迭代
- 创建多个用户账户
  - read命令会自动读取文本文件的下一行内容，当read命令返回false时，即读取完整个文件

## 第14章　处理用户输入

### 14.1 命令行参数

- 位置参数　　$0是程序名称　　$1是第一个参数，直到第9个　　每个参数都必须用空格分开，要在参数值中包含空格，必须要用引号
- 第10个及以后的参数，用　${10}  ${11} 形式
- 可以用$0参数获取shell在命令行启动的脚本名
- basename命令会返回不包含路径的脚本名
- 可编写基于脚本名称执行不同功能的脚本，可使用-n参数测试来检查命令行参数$1中是否有数据

### 14.2 特殊参数变量

- 参数统计
  - 特殊变量$#含有脚本运行时携带的命令行参数的个数，在使用参数前测试参数的总数，　${!#}获得输入的最后一个参数
- 抓取所有的数据
  - $*会将命令行上提供的所有参数当作一个单词保存，即将所有参数当成单个参数
  - $@变量会将命令行上提供的所有参数当作同一字符串中的多个独立的单词，单独处理每个参数

### 14.3 移动变量

- shift命令会根据它们的相对位置来移动命令行参数，如$2的值会移到$1

### 14.4 处理选项

- 查找选项
  - 处理简单选项
    - 用case语句判断某个参数是否为选项
  - 分离参数和选项
    - shell会用双破折线来表明选项列表结束，在双破折号之后，可将剩余的命令行参数当作参数
  - 处理带值的选项
- 使用getopt命令
  - 命令的格式
    - getopt optstring parameters
  - 在脚本中使用getopt
    - set -- $(getopt -q ab:cd "$@")
  - getopt命令不擅长处理带空格和引号的参数值
- 使用getopts
  - 它一次只处理命令行上检测到的一个参数，处理完所有参数后，他会返回一个大于0的退出状态码
  - 会用到两个环境变量　OPTARG  OPTINF

### 14.5 将选项标准化

### 14.6 获得用户输入

- 基本的读取
  - read命令，从标准输入或另一个文件描述符中接受输入
  - 若在read命令行中不指定变量，read命令会将它收到的任何数据都放进特殊环境变量REPLY中
- 超时
  - -t选项指定了read命令等待输入的秒数
  - -n1选项告诉read接受单个字符后退出
- 隐藏方式读取
  - -s选项可以避免read命令中输入的数据出现在显示器上
- 从文件中读取
  - 每次调用，都会从文件中读取一行文本

## 第15章　呈现数据

### 15.1 理解输入和输出

- 标准文件描述符
  - Linux系统将每个对象当作文件处理，包括输入和输出进程，Linux用文件描述符来标识每个文件对象
  - 三个保留的特殊文件符0 1 2
    - STDIN,代表shell的标准输入，即键盘，可以使用输入重定向改变<
    - STDOUT,shell的标准输出，显示器，可以使用输出重定向改变>     z追加到文件>>
    - STDERR,处理错误信息，代表shell的标准错误输出
- 重定向错误
  - 只重定向错误，将文件描述符放在重定向符号前
  - 重定向错误和数据，同时重定向错误和正常输出时，必须使用两个重定向符号
  - 特殊的重定向符号&>，可以将STDERR和STDOUT的输出重定向到同一个输出文件

### 15.2 在脚本中重定向输出

- 临时重定向

  - ./test8 2>test9 通过STDOUT显示的文本显示在了屏幕上，而发送给STDERR的echo语句则被重定向到了输出文件

- 永久重定向

  - 可以用exex命令告诉shell在脚本执行期间重定向某个文件描述符

  - ```shell
     #!/bin/bash
     
     exec 2>testerror
     
     echo "This is the start of the script"
     echo "now redirecting output "
     
     exec 1>testout
     
     echo "This output should go to the testout file"
     echo "This output should go to the testerror file" >&2
      
    ```

### 15.3 在脚本中重定向输入

- exec命令允许将STDIN重定向到Linux系统上的文件中

- exec 0<testfile

- ```shell
   #!/bin/bash
   
   exec 0<testfile
   count=1
   
   while read line
   do
       echo "Line #$count: $line"
       count=$[ $count+1 ]
   done
  ```

### 15.4 创建自己的重定向

- 在shell中最多有9个打开的文件描述符，其他6个从3-8的文件描述符均可用作输入或输出重定向

- 创建输出文件描述符　　

  - exec 3>test13out
  - echo "This should be stored in the file " >&3     将被重定向到文件test13out中

- 重定向文件描述符

  ```shell
   #!/bin/bash
   
   exec 3>&1
   exec 1>testout
   
   echo "This should store in the output file"
   
   exec 1>&3
   echo "This should dispaly in the screen"
  
  ```

- 创建输入文件描述符

  - 与重定向输出文件描述符类似的方法

- 创建读写文件描述符

  - exec 3<> testfile
  - 由于是对同一个文件进行读写，shell会维护一个内部指针，指明在文件中的当前位置，任何读写都会从文件指针上次的位置开始

- 关闭文件描述符

  - 关闭文件描述符　exec 3>&-
  - 若关闭后，在脚本中打开同一个文件，会用一个新的文件替换已有的文件

### 15.5 列出打开的文件描述符

- lsof列出整个Linux系统打开的所有文件描述符　　　/usr/sbin/lsof
- lsof -p     指定进程　　　　　lsof -d 指定要显示的文件描述符
- lsof -a -p $$ -d 0,1,2　　　　　　　　　-a的选项执行布尔AND运算　　　特殊环境变量$$当前PID

```shell
 #!/bin/bash
 
 exec 3>test18file1
 exec 6>test18file2
 exec 7<testfile
 
 lsof -a -p $$ -d 0,1,2,3,6,7

```

### 15.6 阻止命令输出

- 可将STDERR重定向到一个叫做null文件的特殊文件,null文件什么都没有，shell输出到null文件的任何数据都不会保存，位置在/dev/null,这是避免出现错误信息，也无需保存它们的一个常用方法
- cat  /dev/null   >testfile     清除testfile内容的常见方法，清除日志文件的常用方法

### 15.7 创建临时文件

- /tmp目录存放不需要永久保留的文件，大多数Linux系统在启动时自动删除/tmp目录的所有文件，不用担心清理
- mktemp 命令会在/tmp目录下创建一个唯一的临时文件
- 创建本地临时文件　　mktemp testing.XXXXXX     要加6个XXXXXX,  mktemp命令会用6个字符码替换这6个X
- 在/tmp目录创建临时文件
  - -t选项会强制mktemp命令在系统的临时目录来创建该文件　　　mktemp -t ss.XXXXXX　　　会返回全路径名称
- 创建临时目录
  - -d选项创建临时目录

### 15.8 记录消息

- tee命令将STDIN过来的数据同时发往STDOUT和指定的文件名　　　 date | tee testfile　

### 15.9 实例

```shell
 #!/bin/bash
 
 outfile='members.sql'
 
 IFS=','
 while read lname fname address city state zip
 do  
     cat >> $outfile << EOF
     INSERT INTO members (lname,fname,address,city,state,zip) VALUES
     ('$lname','$fname','$address','$city','$state','$zip');
 EOF
 done < ${1}   #指明了待读取的文件
```



## 第16 章　控制脚本

### 16.1 处理信号

- Linux系统利用信号与运行在系统中的进程进行通信

- 重温Linux信号

  - 默认情况下，bash shell会忽略收到的任何SIGQUIT(3)和SIGTERM(15)

- 生成信号

  - bash shell允许用键盘上的组合键生成两种基本的Linux信号
  - 中断进程　CTRL+Ｃ会生成SIGINT,并将其发送给当前在shell中运行的所有进程
  - 暂停进程　CTRL+Z会生成一个SIGTSTP,停止shell中运行的任何进程
    - 可以用kill命令来发送一个SIGKILL命令来终止它，kill -9 PID

- 捕获信号

  - trap命令允许指定shell脚本要监看并从shell中拦截的Linux信号，该信号不再由shell处理，而是交由本地处理

  - trap commands signals    捕获到signals时执行commands

  - ```shell
     #!/bin/bash
     
     trap "echo ' Sorry! I have trapped Ctrl-C'" SIGINT
     
     echo This is a test script
     
     count=1
     while [ $count -le 10 ]
     do
         echo "Loop #$count"
         sleep 1
         count=$[ $count+1 ]
     done
     echo "This is the end of the test"
    ```

- 捕获脚本退出

  - 捕获shell脚本的退出，只要在trap命令后加上EXIT信号就可以了　　trap "echo GoodBye..." EXIT

- 修改或移除捕获

  - 重新使用带有新选项的trap命令，修改捕获
  - 删除已设置好的捕获:  加上两个破折号　　trap -- SIGINT

### 16.2 以后台模式运行脚本

- 在后台模式中，进程运行时不会和终端会话上的STDIN  STDOUT以及STDERR关联
- 后台运行脚本
  - 在命令后加一个&就可以了　　　Typora &
  - 当后台进程结束时，会在终端上显示出一条信息　　[1]  done
  - 当后台进程运行时，仍然会使用终端显示器来显示STDOUT和STDERR消息，最好将其重定向
- 运行多个后台作业
- 如果终端会话退出，那么后台进程也会随之退出

### 16.3 在非控制台下运行脚本

- 即使退出终端会话，仍然运行，可以使用nohuo命令实现
- nohup ./test1.sh &
- 由于nohup命令会解除终端与进程的关联，进程不再同STDOUT和STDERR联系在一起，nohup命令会自动将STDOUT和STDERR的消息重定向到nohup.out文件中

### 16.4 作业控制

- 查看作业
  - 可以用$$变量来显示Linux系统分配给该脚本的PID
  - jobs命令允许查看shell当前正在处理的作业
  - jobs -l　可查看作业的PID
  - 带加号的作业被当作默认的作业
  - 带减号的作业成为下一个默认的作业
- 重启停止的作业
  - bg   作业号　　以后台模式重启一个作业
  - fg   作业号　　以前台模式重启作业

### 16.5 调整谦让度

- 调度优先级是内核分配给进程的CPU时间，由shell启动的所有进程的调度优先级默认都是相同的，默认情况下以优先级0来启动所有进程
- 调度优先级从-20 到19(最低)
- nice命令
  - nice -n  优先级　脚本　　　指定调度优先级
  - nice -n 10 sleep 1000 &
  - ps -p 8324 -o pid,ppid,ni,cmd　　查看优先级
  - 普通用户被阻止提高优先级
- renice命令
  - 改变系统上已运行命令的优先级，允许你指定运行进程的PID来改变它的优先级
  - renice -n 10 -p 8614
  - ps -p 8614 -o ni

### 16.6 定时运行作业

- at命令
  - at的守护进程atd以后台模式运行，检查作业队列来运行，大多数在启动时运行此守护进程
  - atd守护进程会检查目录　/var/spool/at  来获取at命令提交的作业，每60秒
  - at命令的格式
    - at [-f filenaem] time
    - 在使用at命令时，该作业会被提交到作业队列，26种不同优先级的作业
    - -q 参数指定不同的队列字母优先级
  - 获取作业的输出
    - at命令将用户的电子邮件作为STDOUT和STDERR,最好重定向
  - 列出等待的作业
    - atq命令可以查看系统中有哪些作业在等待
  - 删除作业
    - atrm

- 安排需要定期执行的脚本

  - cron程序会在后台运行并检查一个特殊的表，以获知已安排执行的作业

  - cron时间表

  - 命令列表必须指定运行的命令或脚本的全路径名

  - 构建cron时间表

    - crontab -l  列出
    - crontab -e创建

  - 浏览cron目录

    - 可以用预配置的cron脚本目录会更方便

    - ls /etc/cron.*ly

    - ```shell
      /etc/cron.daily:
      0anacron    aptitude          dpkg           man-db   popularity-contest
      apport      bsdmainutils      google-chrome  mlocate  ubuntu-advantage-tools
      apt-compat  cracklib-runtime  logrotate      passwd   update-notifier-common
      
      /etc/cron.hourly:
      
      /etc/cron.monthly:
      0anacron
      
      /etc/cron.weekly:
      0anacron  man-db  update-notifier-common
      
      ```

    - 将脚本复制到相应的目录

  - anacron程序

    - 如果某个程序错过了执行时间，它会尽快执行
    - 只会处理位于cron目录的程序
    - 时间戳文件:  /var/spool/anacron
    - 自己的时间表　　/etc/anacrontab

- 使用新shell启动脚本

  - 每次启动一个新shell时，bash shell都会运行.bashrc文件，　可将命令放在该脚本文件中



## 第17章　创建函数

### 17.1 基本的脚本函数

- 创建函数

  - ```shell
    function  name{
        commands
    }
    ```

  - ```shell
    name(){
        commands
    }
    ```

- 使用函数

### 17.2 返回值

- bash shell会把函数当作一个小型脚本，运行结束时返回一个退出状态码
- 默认退出状态码
  - 函数的默认退出状态码是函数中最后一条命令返回的退出状态码，函数执行结束后，用$?来查看
- 使用return 命令
  - return 命令返回一个退出状态码，必须是0-255,函数以结束就取返回值
  - $?变量会返回执行的最后一条命令的退出状态码
- 使用函数输出
  - result=$(dbl)    dbl为函数

### 17.3 在函数中使用变量

- 向函数传递参数
  - 函数可以使用标准的参数环境变量来表示命令行上传给函数的参数
  - 指定参数时，必须将参数和函数放在同一行　　　func1  $value  10
  - 函数无法直接获取脚本在命令行中的参数值
- 在函数中处理变量
  - 全局变量:  在shell脚本中任何地方都有效的变量，默认情况下，在脚本中定义的任何变量都是全局变量
  - 局部变量　在变量声明前加上local

### 17.4 数组变量和函数

- 向函数传数组参数
  - 必须将数组变量的值分解为单个值，然后将这些值作为函数参数使用
- 从函数返回数组
  - 从函数向脚本传回数组变量也是类似的办法

### 17.5 函数递归



### 17.6 创建库

- bash shell允许创建函数库文件，然后在脚本中引用该文件

- shell函数仅在定义它的shell会话内有效，如果在shell命令行界面运行脚本，会创建一个新的shell并在其中运行这个脚本

- source命令会在当前shell上下文中执行命令，而不是创建一个新的shell     source命令有个快捷的别名，点操作符  . ./myfuncs

- ```shell
                                                                   
   #!/bin/bash
   
   . ./myfuncs   #库文件
   
   result=$(addem 10 15)
   echo "The result is $result"
   ~                                
  ```



### 17.7 在命令行上使用函数

- 一旦在shell中定义了函数，就可以在整个系统中使用它了，无需担心脚本是不是在PATH环境变量中

- 在命令行上创建函数

  ```shell
  function divem { echo $[ $1 / $2];}
  divem 100 10
  ```

- **在./bashrc文件中定义函数**

  - 直接定义函数
    - bash shell在每次启动时都会检查这个文件
  - 读取函数文件
    - 在shell脚本中，都可以用source命令(别名点操作符  .  /etc/myfuncs)将库文件的函数添加到.bashrc脚本中

### 17.8 实例

- GNU shtool shell脚本函数库提供了一些常用的函数
- 下载安装

  - <ftp://ftp.gnu.org/gnu/shtool/>
- 构建库

  - 使用标准的configure和make命令对环境进行配置
  - ./configure   会检查构建shtool库文件所必须的软件，一旦发现了所需的工具，会使用工具路径修改配置文件
  - make　　负责构建shtool库文件　　最终的结果是一个完整的库软件包
  - make test 测试这个库文件，测试模式会测试库所有的函数　　测试通过后安装
  - make install 安装在公用位置
- shtool库函数
- 使用库

## 第18章　图形化桌面环境汇总的脚本编程

### 18.1 创建文本菜单

- 创建菜单布局

  - clear 命令清空
  - echo  -e 　　echo -e "1.\tDisplay the space"
  - echo -en "1.\tDisplay the space"　　-en去掉末尾的换行符
  - read -n 选项  -n限制只读取一个字符　read -n 1 option　　　　　　　　

- 创建菜单函数

- 添加菜单逻辑

- 整合shell脚本菜单

- 使用select命令

  - ```shell
    select variable in list
    do
    	commands
    done
    ```

  - list 参数是由空格分割的文本选项列表

  - 存储在变量中的结果值是整个文本字符串而不是跟菜单选项相关联的数字

### 18.2 制作窗口

- dialog包能够用ANSI转义字符在文本环境中创建标准的窗口对话框
- dialog包
  - dialog   --widget  parameters     widget是部件名　　parameters定义了窗口的大小以及部件需要的文本
  - dialog命令会将数据发送到STDERR
- msgbox部件
  - dialog --title Testing --msgbox "Thi is a test" 10 20
- yesno部件
  - dialog --title "Please answer"  --yesno "Is this thing on?"  10  20
  - dialog命令的退出状态码会根据用户选择的按钮来设置
- inputbox部件
  - dialog命令会将文本字符串的值发送给STDERR
  - dialog --inputbox "Enter your age:" 10 20 2>age.txt
- textbox部件
  - dialog --textbox /etc/passwd 15 45
- menu部件
  - dialog --menu "Sys Admin Menu"  20  30 10  1  "Display disk space "   2  "Display users"  3  "Dispaly memory usage"  2>test.txt
- fselect部件
  - dialog --title "Select a file"  --fselect  $HOME/  10 50 2>file.txt
- 在脚本中使用dialog命令
  - 如果有Cancel或NO按钮，检查dialog命令的退出状态码
  - 重定向STDERR来获得输出值



### 18.4 使用图形

- KDE环境
- GNOME环境
  - gdialog
  - zenity
    - zenity命令会将值返回到STDOUT中
    - zenity --file-selection  显示目录窗口，选中后返回路径

## 第19 章　初识sed和gawk

### 19.1 文本处理

- sed编辑器(流编辑器)

  - 在编辑器处理数据之前基于预先提供的一组规则来编辑数据流
  - 在流编辑器将所有命令与一行数据匹配完毕后，它会读取下一行数据并重复这个过程
  - sed options script file
    - -e script
    - -f  file
    - -n
  - 在命令行定义编辑器命令
    - 默认情况下，将指定的命令应用到STDIN输入流上
    - s命令，第二个文本字符串替换第一个文本字符串　　echo "This is a test" | sed 's/test/big test/'
    - sed编辑器并不会修改文本文件的数据，它只会将修改后的数据发送到STDOUT
  - 在命令行使用多个编辑器命令
    - 采用-e选项
    - sed -e 's/brown/green/; s/dog/cat/'  data1.txt
    - 命令之间用分号分开
    - bash shell的次提示符，只要输入第一个单引号标示起始，会提示输入更多命令，直到结束的单引号
  - 从文件中读取编辑器命令
    - sed -f script1.sed data1.txt      script1.sed 的每行是一条命令

- gawk程序

  - 提供一个类编程环境来修改和重新组织文件中的数据

  - gawk程序是Unix中的原始awk程序的GNU版本

  - 它提供了一种编程语言而不只是编辑器命令

  - gawk命令格式

    - gawk options program file

  - 从命令行读取程序脚本

    - gawk程序脚本用一对花括来定义，还必须将脚本放到单引号中
    - gawk '{print "hello world"}'
    - gawk程序会从STDIN接收数据
    - CTRL+D会在bash中产生一个EOF字符

  - 使用数据字段变量

    - gawk会将如下变量分配给它在文本行中发现的数据字段　　$0代表整行　　$n代表第n个数据字段
    - 每个数据字段通过字段分隔符
    - gawk '{print $1}' data2.txt
    - -F可以指定分隔符
    - gawk -F:  '{print $1}'   /etc/passwd

  - 在程序脚本中使用多个命令

    - 在命令行中多条命令用分号分开
    - echo "My name is Rich"   |  gawk '{$4="Christine" ;  print $0}'

  - 从文件中读取程序

    -  {print $1 "'s hoem directory is " $6}

    - gawk -F: -f script2.gawk /etc/passwd

    - ```shell
       {
           text="'s home directory is "
           print $1 text $6
       }
      ```

  - 在处理数据前运行脚本

    - BEGIN会强制在读取数据前执行BEGIN关键字后指定的程序脚本
    - gawk 'BEGIN {print  "Hello World"}'

  - 在处理数据后运行脚本

    - END关键字允许指定在读取数据后执行它

    - ```shell
       BEGIN{
       print "The latest list of users and shells"
       print "UserID \t Shell"
       print"--------\t----------"
       FS=":"
       }
       
       {
           print $1 "      \t"    $7
       }
       
       END{
       print "This concludes the listing"
       }
      ```

  

### 19.2 sed编辑器基础

  - 更多的替换选项

    - 替换标记
      - 默认情况下它只替换每行中出现的第一处
      - 替换标记会在替换命令字符串之后设置
      - s/pattern/replacement/flags
      - 4种可用的替换标记
        - 数字
        - g
        - p　　会打印与替换命令中指定的模式匹配的行
        - w file  只有包含匹配模式的行才会保存在指定的输出文件中
    - 替换字符
      - 可以用!作为字符串分隔符　　
      - sed 's!/bin/bash!/bin/csh!'  /etc/passwd

- 使用地址

  - 只想将命令作用于特定行，则必须使用行寻址
  - 以数字形式表示行区间　　[address] command
    - sed '2s/dog/cat/'  data1.txt
    - sed '2,3s/dog/cat/'  data1.txt
    - sed '2,$s/dog/cat/'  data1.txt       $表示到所有行
    - sed '2s/dog/cat/'  data1.txt
  - 用文本模式来过滤出行
    - /pattern/command
    - sed  '/leiwang/s/bash/csh/'  /etc/passwd      只作用到匹配文本模式上的行
  - 命令组合
    - 如果需要在单行上执行多条命令，可以用花括号将多条命令组合到一起
    - sed '2{s/fox/elephant/; s/dog/cat/}' data1.txt

- 删除行

  - 'd'
  - sed '3d' data1.txt         寻址模式

- 插入和附加文本

  - i
  - a
  - sed '3i This is a inserted line.' data1.txt 

- 修改行

  - c

- 转换命令

  - y 
  - sed  'y/123/789'  data2.txt  将字符值进行一对一的映射

- 回顾打印

  - 打印行
    - p    
    - sed -n '2,3p'  data6.txt
  - 打印行号
    - 等号命令会打印在数据流中的当前行号
    - sed '='  data1.txt
  - 列出行
    - l
    - sed  -n  'l'  data9.txt

- 使用sed 处理文件

  - 写入文件

    - sed  '1,2w  test.txt'  data6.txt

  - 从文件读取数据

    - r

    - 将一个独立文件中的数据插入到数据流中

    - sed '3r data12.txt'  data6.txt

## 第20章　正则表达式

### 20.1 什么是正则表达式

- 定义
  - 正则表达式是定义的模式模板
  - 正则表达式模式利用通配符来描述数据流的一个或多个字符
- 正则表达式的类型
  - Linux中的不同应用程序可能会用不同类型的正则表达式
  - 正则表达式是通过正则表达式引擎实现的，正则表达式引擎是一套底层软件，负责解释正则表达式模式并使用这些模式进行文本匹配
  - POSIX基础正则表达式　BRE引擎
  - POSIX扩展正则表达式　ERE引擎

### 20.3 　定义BRE模式

- 纯文本

  - 正则表达式模式都区分大小写
  - 不用写出整个单词，只要定义的文本出现在数据流中，正则表达式就能匹配　echo "This is a test" | sed -n '/tes/p'
  - 正则表达式中空格和其他字符没有区别
- 特殊字符

  - 正则表达式识别的特殊字符包括 :   .*[]^{}$\+?|()
  - 需要用到特殊字符时，需要转义操作\             sed -n '/\\$/p'  data2
  - 要使用正斜线，也必须使用转义
- 锚字符

  - 锁定在行首
    - 脱字符^定义从数据流中文本行的行首开始的模式　　　sed -n '/^Book/p'
    - 脱字符放到模式开头之外的其他位置，那么它就根普通字符一样
  - 锁定在行尾
    - 特殊字符美元符$ 定义了行尾锚点
  - 组合锚点
    - ^$的组合
- 点号字符

  - 点号字符用来匹配除换行符之外的任意单个字符
- 字符组

  - 限定待匹配的特殊字符
  - 使用[]来定义一个字符组　　sed -n '/[ch]at/p'  data6
  - 可以在单个表达式中使用多个字符组
- 排除型字符组

  - 反转字符组的作用，寻找组中没有的字符，在字符组的开头加个脱字符^     \[^ch]
- 区间

  - sed -n '/^\[0-9]\[0-9][0-9]\[0-9]$/p' data8
  - sed  -n '/\[c-h]at/p'  data6
  - 多个不连续的区间　　\[a-ch-m]
- 特殊的字符组
  - \[\[:alpha:]]  匹配任意字母字符
- 星号
  - 在字符后面放置星号表明必须在匹配模式的文本中出现0次或多次
  - echo "ieek" | sed -n '/ie*k/p'
  - 将点号特殊字符和星号特殊字符组合起来，这个组合能够匹配任意数量的任意字符
  - echo "this is a regular pattern expression" | sed -n "/regular.*expression/p"
  - 星号还可以用在字符组上

### 20.3 扩展正则表达式

- 可用在gawk程序脚本中的较常见的ERE模式符号
- 问号
  - 问号表示前面的字符可以出现0次或1次
  - 可以将问号和字符组一起使用
  - echo "bet" | gawk '/b[ae]?t/{print $0}'
- 加号
  - 加号表明前面的字符可以出现1次或多次，但必须至少出现1次
  - echo "beeeeet" | gawk '/b[ae]+t/{print $0}'
- 使用花括号
  - 允许为可重复的正则表达式指定一个上限，称为间隔
  - m　 正则表达式准确出现m次
  - m,n　   正则表达式至少出现m次，至多n次
  - echo "beet" | gawk --re-interval '/be{1,2}t/{print $0}'
  - 间隔模式匹配同样适用于字符组
- 管道符号
  - expr1|expr2    用逻辑或方式
- 表达式分组
  - 正则表达式可以用圆括号进行分组，该组会被认为是一个标准字符
  - echo "Sat" | gawk '/Sat(urday)?/{print $0}'

### 20.4 正则表达式实战

- 目录文件计数

  - echo $PATH | sed 's/:/ /g'

  - ```shell
     #!/bin/bash
     
     mypath=$(echo $PATH | sed 's/:/ /g')
     count=0
     for directory in $mypath
     do
         check=$(ls $directory)
         for item in $check
         do
             count=$[ $count+1 ]
         done
         echo "$directory - $count"
         count=0
     done 
    ```

- 验证电话号码

- 解析邮件地址

  - ^([a-zA-z0-9_\\-\\.\\+]+)@
  - ([a-zA-Z0-9_\\-\\.]+)
  - ^([a-zA-z0-9_\\-\\.\\+]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$



## 第21章　sed进阶



## 第22章　gawk进阶



## 第23章　使用其他shell

- bash shell是Linux发行版中最广泛使用的shell

### 23.1 什么是dash shell

- Ubuntu发行版将bash shell用作默认的交互shell,但将dash shell用作默认的/bin/sh  shell,  将/bin/sh文件链接到了shell程序/bin/dash
- 在Unix世界中，默认shell一直是/bin/sh



### 23.2 dash shell的特性

- dash 命令行参数
- dash环境变量
  - 默认环境变量
  - 位置参数
  - 用户自定义的环境变量
  - dash shell不支持数组
- dash 内建命令

### 23.3 dash 脚本编程

### 23.4 zsh shell

- 每一种shell都包含一组内建命令，内建命令已经在内存中了，随时可用，zsh shell提供了一组核心内建命令，提供了添加额外命令模块的能力

### 23.5 zsh shell的组成



## 第24章　编写简单的脚本实用工具

### 24.1 归档

#### 归档数据文件

-   需要的功能
    - 

​    

​    

​    

​       
















































