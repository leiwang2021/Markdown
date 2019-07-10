# Linux使用常见问题

## gcc的版本切换

Ubuntu18.04自带了两个版本的GCC，分别为6.4.0 和 7.3.0， gcc 在 /usr/bin  目录下

- 通过两条命令查看

  ```
  ls /usr/bin/gcc*
  ls /usr/bin/g++*
  ```

- 将某个版本加入gcc候选中，最后的数字是优先级，我自己是直接设为100（测试没有问题），指令如下：

  ```
  sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 100
  sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 100
  ```

- 修改g++的优先级

  ```
  sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-6 100 
  sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 100
  ```

- 可以通过下面的指令来选择不同的gcc和g++的版本了

  ```
  sudo update-alternatives --config gcc  //选择对应的gcc编号
  sudo update-alternatives --config g++  //配置g++
  //当切换使用了其他版本的gcc时，请务必保持g++的版本和gcc版本的一致性，否则用cmake配置出来的项目遇到c++代码还是会用之前版本的gcc。
  ```
## 截图工具的使用
- windows键+screenshot即可
- 

## cuda

- nvcc --V 显示cuda的版本   ， 9.0.176    路径位置：/usr/local/cuda-9.0
- 直接使用桌面图标而不是Shell启动Pycharm。这样会导致Pycharm无法导入环境变量配置文件~/.bashrc。因此出现了可以在Shell中的Python环境导入但不能在Pycharm环境中导入的情况。
  1. 使用Shell命令: pycharm进行启动

     2.如果仍想使用图标启动，则需要在Pycharm的Run->Edit Configurations界面的Environment variables列表中加入Cuda的环境变量项，具体为：LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64(Cuda安装路径)。在File->Setting->Build, Execution, Deployment->Console->Python Console中加入Cuda的环境变量。

### 忽略‘google-chrome.list.1’(于目录‘/etc/apt/sources.list.d/’)，鉴于它的文件扩展名无效 问题的解决方法

sudo gedit /etc/apt/sources.list.d/google-chrome.list.1（复制其内容到清空后的google-chrome.list）

sudo gedit /etc/apt/sources.list.d/google-chrome.list（保存）

sudo rm -f /etc/apt/sources.list.d/google-chrome.list.1

### Ubuntu16.04下ppa方式安装chrome后sudo apt-get update的错误

**源的选择**

当update时连接dl.google.com超时，原因是当前ip无法ping到google（墙）。 
需要更改ip：

1. 网页上搜站长工具，在里面查找能ping到dl.google.com的IP。

2. 将连接dl.google.com时的ip修改为搜索到的ip： 
   Linux用户打开/etc/hosts文件。 `sudo gedit /etc/hosts` 
   打开文件后添加以下内容：

   #Download 下载
   203.208.46.146 dl.google.com
   203.208.46.146 dl-ssl.google.com

    #Groups
   203.208.46.146 groups.google.com

    #Google URL Shortener
   203.208.46.146 goo.gl

    #Google App Engine
   203.208.46.146 appengine.google.com

    #Android Developer
   74.125.113.121 developer.android.com

   

## indicator-sysmonitor的安装

 可以通过添加PPA安装：

- sudo add-apt-repository ppa:fossfreedom/indicator-sysmonitor

- sudo apt-get update

- sudo apt-get install indicator-sysmonitor

  启动： indicator-sysmonitor &

## 增加虚拟内存

- free -m  查看内存使用情况

- top可查看使用情况

- 创建虚拟内存配置文件

  - mkdir swap  *//穿件文件夹*
    cd swap

    sudo dd if=/dev/zero of=swapfile bs=2048 count=100000  *//其中bs是创建*
    *//的打小,单位为百kb,这个是创建204M,当然如果太大了可能会出问题*

    *//把生成的文件转换成 Swap 文件*
    sudo mkswap swapfile

    sudo swapon swapfile
    *//之后会显示是否成功,如果一定要注意可能第二行的信息是Failed,*

    如果要卸载,执行下面命令
    sudo swapoff swapfile

  - 此时开的虚拟内存会在开机后消失,如果永久保持下去,在/etc/fstab文件尾添加一下信息:
    swapfilepath swap swap defaults 0 0
    例如:我的我是在/root/进行的配置,因此添加了下面内容
    /root/swap/swapfile swap swap defaults 0 0

- anjuta的安装

  - sudo apt-get install anjuta
  - 编译出现错误:   You must have `libtool’ installed 时安装　　　apt-get install libtool-bin
  - 安装C++开发文档：　　sudo apt-get　install manpages-dev　　之后可以用man fopen查看函数用法

## 安装软件过程中遇到的问题

- locate filename  查找文件在哪里

- pycharm.sh 的路径为:/snap/pycharm-community/132/bin/pycharm.sh

- PATH环境变量为命令搜索的路径，可添加目录到PATH环境变量中，如果要变量持久化，将其放入到$HOME/.bashrc中

- 安装常用的软件:

  - 使用https://github.com/RokasUrbelis/docker-wine-linux的方式进行安装

- 清理垃圾：

  sudo apt-get autoclean 清理旧版本的软件缓存
  sudo apt-get clean 清理所有软件缓存
  sudo apt-get autoremove 删除系统不再使用的孤立软件

- Your container id is 13a

- [source start.sh -i  13a TIM] to run TIM or another APP

- bash start.sh --help'

- 追求稳定的话建议每个wine应用使用单独容器运行(即每次运行应用前先运行run.sh)，而不是集中在一个容器上，这样方便管理并且降低崩溃概率。

- 每执行一次`run.sh`会生成一个容器，每次重启系统这些容器就会处于退出状态，并且你不会再使用它，久而久之容器数量就会占据硬盘大量空间，直接执行`bash clear.sh`即可释放资源

- 建议至少每个月执行一次(每天执行一次更好)，具体多久执行一次取决于你系统资源是否够用以及开的容器数目是否够多，可配合crontab使用

- 执行`clear.sh`的时候所有与`docker-wine-linux`镜像有关的容器都将被删除，在此之前请备份好`APP_PATH`目录里面你通过应用传输的重要文件

### 安装sysstat

- 地址;<http://sebastien.godard.pagesperso-orange.fr/download.html

- 解压： tar -zxvf sysstat-12.1.5.tar.gz

- 进入到目录中

- ./configure检查系统

     Sysstat version:		12.1.5
     Installation prefix:		/usr/local
     rc directory:		/etc
     Init directory:		/etc/init.d
     Systemd unit dir:		/lib/systemd/system
     Configuration directory:	/etc/sysconfig
     Man pages directory:		${datarootdir}/man
     Compiler:			gcc
     Compiler flags:		-g -O2

- make

- sudo make install安装到系统上常用的位置上

- 有以下命令：**sar**　是Linux下系统运行状态统计工具，　**iostat命令**被用于监视系统输入输出设备和CPU的使用情况


​    

​    

​    

​    
