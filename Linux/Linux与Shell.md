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






