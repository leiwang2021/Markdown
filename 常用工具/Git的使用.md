# Git的使用

## Git简介

- Git是分布式版本控制系统

### Git的诞生

- Linus在1991年创建了开源的Linux 
- Linus花了两周时间自己用C写了一个分布式版本控制系统 

### 集中式vs分布式

- 集中式版本控制系统，版本库是集中存放在中央服务器的，而干活的时候，用的都是自己的电脑，所以要先从中央服务器取得最新的版本，然后开始干活，干完活了，再把自己的活推送给中央服务器 

- 在实际使用分布式版本控制系统的时候，其实很少在两人之间的电脑上推送版本库的修改，因为可能你们俩不在一个局域网内，两台电脑互相访问不了。因此，分布式版本控制系统通常也有一台充当“中央服务器”的电脑，但这个服务器的作用仅仅是用来方便“交换”大家的修改，没有它大家也一样干活，只是交换修改不方便而已。

### 安装Git

- Linux系统：sudo apt-get install git 
- 安装完成后设置：
  -  $ git config --global user.name "Your Name"
  - $ git config --global user.email "email@example.com"

### 创建版本库

- 创建一个目录：
- 通过git init目录将它变成Git可以管理的仓库
- 当前目录下多了一个`.git`的目录，这个目录是Git来跟踪管理版本库的 
- 也不一定必须在空目录下创建Git仓库，选择一个已经有东西的目录也是可以的 
- 所有的版本控制系统，其实只能跟踪文本文件的改动，比如TXT文件，网页，所有的程序代码等等，Git也不例外。版本控制系统可以告诉你每次的改动，比如在第5行加了一个单词“Linux”，在第8行删了一个单词“Windows”。而图片、视频这些二进制文件，虽然也能由版本控制系统管理，但没法跟踪文件的变化，只能把二进制文件每次改动串起来，也就是只知道图片从100KB改成了120KB，但到底改了啥，版本控制系统不知道，也没法知道 
- Microsoft的Word格式是二进制格式，因此，版本控制系统是没法跟踪Word文件的改动的 
- Microsoft开发记事本的团队使用了一个非常弱智的行为来保存UTF-8编码的文件，他们自作聪明地在每个文件开头添加了0xefbbbf（十六进制）的字符，你会遇到很多不可思议的问题，比如，网页第一行可能会显示一个“? 
- 把一个文件放到Git仓库
  - 用命令`git add`告诉Git，把文件添加到仓库： 如git add readme.txt
  - 用命令`git commit`告诉Git，把文件提交到仓库，如git commit -m "wrote a readme file"
  -  `commit`可以一次提交很多文件，所以你可以多次`add`不同的文件 

## 时光机穿梭

- `git status`命令可以让我们时刻掌握仓库当前的状态 
- `git diff`这个命令看看 修改了什么内容， git diff readme.txt
- 提交修改和提交新文件是一样的两步 

### 版本回退

- git log 查看历史记录
- 在Git中，用`HEAD`表示当前版本，也就是最新的提交 ，上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，往上100个写成`HEAD~100` 
- 还原： git reset --hard HEAD^
- 还原后，若要还原回去，找不到时：git reset --hard 1094a    1094a为版本号的前几位
- 关闭后，找不到版本号，则使用`git reflog可查看记录你的每一次命令 
- `HEAD`指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令`git reset --hard commit_id`。
- 穿梭前，用`git log`可以查看提交历史，以便确定要回退到哪个版本。
- 要重返未来，用`git reflog`查看命令历史，以便确定要回到未来的哪个版本

### 工作区和暂存区

- 所以，`git add`命令实际上就是把要提交的所有修改放到暂存区（Stage），然后，执行`git commit`就可以一次性把暂存区的所有修改提交到分支 

### 管理修改

- Git跟踪并管理的是修改，而非文件 
- 每次修改，如果不用`git add`到暂存区，那就不会加入到`commit`中 

### 撤销修改

- `git checkout -- file`可以丢弃工作区的修改 ，命令`git checkout -- readme.txt`意思就是，把`readme.txt`文件在工作区的修改全部撤销 

- 用命令`git reset HEAD <file>`可以把暂存区的修改撤销掉（unstage），重新放回工作区：

- 场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令`git checkout -- file`。

  场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令`git reset HEAD <file>`，就回到了场景1，第二步按场景1操作。

  场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，参考[版本回退](https://www.liaoxuefeng.com/wiki/896043488029600/897013573512192)一节，不过前提是没有推送到远程库。

### 删除文件

- 若手动删除了文件导致工作区和版本库不一致了，则需要git rm删除，并要git commit
- 如果误删了，从版本库里恢复：git checkout -- test.txt
- git checkout其实是用版本库里的版本替换工作区的版本，无论工作区是修改还是删除，都可以“一键还原”。



## 远程仓库

- 创建SSH Key。在用户主目录下，看看有没有.ssh目录，如果有，再看看这个目录下有没有`id_rsa`和`id_rsa.pub`这两个文件，如果已经有了，可直接跳到下一步。如果没有，打开Shell（Windows下打开Git Bash），创建SSH Key 

- ```
  ssh-keygen -t rsa -C "youremail@example.com"
  ```

- 登陆GitHub，打开“Account settings”，“SSH Keys”页面： 

- 然后，点“Add SSH Key”，填上任意Title，在Key文本框里粘贴`id_rsa.pub`文件的内容 

- 为什么GitHub需要SSH Key呢？因为GitHub需要识别出你推送的提交确实是你推送的，而不是别人冒充的，而Git支持SSH协议，所以，GitHub只要知道了你的公钥，就可以确认只有你自己才能推送。

- 当然，GitHub允许你添加多个Key。假定你有若干电脑，你一会儿在公司提交，一会儿在家里提交，只要把每台电脑的Key都添加到GitHub，就可以在每台电脑上往GitHub推送了

- 在GitHub上免费托管的Git仓库，任何人都可以看到喔（但只有你自己才能改）。所以，不要把敏感信息放进去。 

- 如果你不想让别人看到Git库，有两个办法，一个是交点保护费，让GitHub把公开的仓库变成私有的，这样别人就看不见了（不可读更不可写）。另一个办法是自己动手，搭一个Git服务器，因为是你自己的Git服务器，所以别人也是看不见的。这个方法我们后面会讲到的

### 添加远程库

- 在github创建一个新仓库，与本地仓库相关联
- git add . 添加所有的文件
- 在本地的`learngit`仓库下运行命令 ：

```
git remote add origin git@github.com:leiwang2021/learn.git
```

- 添加后，远程库的名字就是`origin`，这是Git默认的叫法，也可以改成别的， 

- 下一步，就可以把本地库的所有内容推送到远程库上 :

  - 把本地库的内容推送到远程，用`git push`命令，实际上是把当前分支`master`推送到远程 

  - 第一次推送`master`分支时，加上了`-u`参数，Git不但会把本地的`master`分支内容推送的远程新的`master`分支，还会把本地的`master`分支和远程的`master`分支关联起来，在以后的推送或者拉取时就可以简化命令 

  - ```
    git push -u origin master
    ```

- 如果远程仓库初始化了，可能出现冲突错误，git pull origin master --allow-unrelated-histories 解决
- 从现在起，只要本地作了提交，就可以通过命令  git push origin master
- 移除:git remote rm origin 

### 从远程库克隆

- 先创建远程库

- 用clone命令克隆一个本地库

  - ```
    $ git clone git@github.com:leiwang2021/gitskill.git
    ```

- Git支持多种协议，默认的`git://`使用ssh，但也可以使用`https`等其他协议。 

- 从远程克隆得到的仓库也可以从本地推送到远程仓库

  - git push origin master

## 分支管理

### 创建与合并分支

- 创建分支：$ git checkout -b dev      相当于$ git branch dev$ git checkout dev

- 用`git branch`命令查看当前分支 

- Git鼓励你使用分支完成某个任务，合并后再删掉分支，这和直接在`master`分支上工作效果是一样的，但过程更安全

- 查看分支：`git branch`

  创建分支：`git branch <name>`

  切换分支：`git checkout <name>`

  创建+切换分支：`git checkout -b <name>`

  合并某分支到当前分支：`git merge <name>`

  删除分支：`git branch -d <name>`

- 未合并前，在其他分支修改的内容不影响此分支

   

### 解决冲突

当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。

解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。

用`git log --graph`命令可以看到分支合并图

### 分支管理策略

在实际开发中，我们应该按照几个基本原则进行分支管理：

首先，`master`分支应该是非常稳定的，也就是仅用来发布新版本，平时不能在上面干活；

那在哪干活呢？干活都在`dev`分支上，也就是说，`dev`分支是不稳定的，到某个时候，比如1.0版本发布时，再把`dev`分支合并到`master`上，在`master`分支发布1.0版本；

你和你的小伙伴们每个人都在`dev`分支上干活，每个人都有自己的分支，时不时地往`dev`分支上合并就可以了。

所以，团队合作的分支看起来就像这样：

- 合并分支时，加上`--no-ff`参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而`fast forward`合并就看不出来曾经做过合并 

### BUG分支

- 每个bug都可以通过一个新的临时分支来修复，修复后，合并分支，然后将临时分支删除。
-  $ git stash  ，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作
- 首先确定要在哪个分支上修复bug，假定需要在`master`分支上修复，就从`master`创建临时分支 
-  回到工作分支，用git stash pop恢复
- 可以用git stash list查看

### Feature分支

- 如果要丢弃一个没有被合并过的分支，可以通过`git branch -D <name>`强行删除 

### 多人协作

- 当你从远程仓库克隆时，实际上Git自动把本地的`master`分支和远程的`master`分支对应起来了，并且，远程仓库的默认名称是`origin`。 
- 要查看远程库的信息，用`git remote`： 
- 推送分支：把该分支上的所有本地提交推送到远程库。推送时，要指定本地分支，这样，Git就会把该分支推送到远程库对应的远程分支上   git push origin master
- `master`分支是主分支，因此要时刻与远程同步；
- `dev`分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步；
- bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug；
- feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发。
- 首先，可以试图用`git push origin <branch-name>`推送自己的修改；
- 如果推送失败，则因为远程分支比你的本地更新，需要先用`git pull`试图合并；
- 如果合并有冲突，则解决冲突，并在本地提交；
- 没有冲突或者解决掉冲突后，再用`git push origin <branch-name>`推送就能成功！
- 如果`git pull`提示`no tracking information`，则说明本地分支和远程分支的链接关系没有创建，用命令`git branch --set-upstream-to <branch-name> origin/<branch-name>`。
- 查看远程库信息，使用`git remote -v`；
- 本地新建的分支如果不推送到远程，对其他人就是不可见的；
- 从本地推送分支，使用`git push origin branch-name`，如果推送失败，先用`git pull`抓取远程的新提交；
- 在本地创建和远程分支对应的分支，使用`git checkout -b branch-name origin/branch-name`，本地和远程分支的名称最好一致；
- 建立本地分支和远程分支的关联，使用`git branch --set-upstream branch-name origin/branch-name`；
- 从远程抓取分支，使用`git pull`，如果有冲突，要先处理冲突。

### Rebase

- rebase操作可以把本地未push的分叉提交历史整理成直线；
- rebase的目的是使得我们在查看历史提交的变化时更容易，因为分叉的提交需要三方对比。

## 标签管理

### 创建标签

- 切换到需要打标签的分支上： 敲命令`git tag <name>`就可以打一个新标签
- 可以用命令`git tag`查看所有标签 
-  git tag v0.9 f52c633    对历史提交打标签
- `git show <tagname>`查看标签信息：
-  创建带有说明的标签，用`-a`指定标签名，`-m`指定说明文字： 
- git tag -a v0.1 -m "version 0.1 released" 1094adb
- 如果标签打错了，也可以删除 。git tag -d v0.1
- 要推送某个标签到远程，使用命令`git push origin <tagname>`： 
- $ git push origin --tags，一次性推送全部尚未推送到远程的本地标签： 
- 如果标签已经推送到远程，要删除远程标签就麻烦一点，先从本地删除 ，然后，从远程删除。删除命令也是push ，git push origin :refs/tags/v0.9

## 使用github

- Fork”就在自己的账号下克隆了一个bootstrap仓库，然后，从自己的账号下clone： 

## 自定义Git

### 忽略特殊文件

- 在Git工作区的根目录下创建一个特殊的`.gitignore`文件，然后把要忽略的文件名填进去，Git就会自动忽略这些文件 
- 忽略某些文件时，需要编写`.gitignore`；
- `.gitignore`文件本身要放到版本库里，并且可以对`.gitignore`做版本管理！

### 配置别名

- ```
  $ git config --global alias.co checkout
  $ git config --global alias.ci commit
  $ git config --global alias.br branch
  ```

- `--global`参数是全局参数，也就是这些命令在这台电脑的所有Git仓库下都有用。

- 每个仓库的Git配置文件都放在`.git/config`文件中 

-  当前用户的Git配置文件放在用户主目录下的一个隐藏文件`.gitconfig`中 

### 搭建Git服务器

- sudo apt-get install git  安装git
- 创建一个`git`用户，用来运行`git`服务      sudo adduser git
- 创建证书登录：收集所有需要登录的用户的公钥，就是他们自己的`id_rsa.pub`文件，把所有公钥导入到`/home/git/.ssh/authorized_keys`文件里，一行一个。 
- 初始化Git仓库，先选定一个目录作为Git仓库，假定是`/srv/sample.git`，在`/srv`目录下输入命令 ， sudo git init --bare sample.git
- Git就会创建一个裸仓库，裸仓库没有工作区，因为服务器上的Git仓库纯粹是为了共享，所以不让用户直接登录到服务器上去改工作区，并且服务器上的Git仓库通常都以`.git`结尾。然后，把owner改为`git`     sudo chown -R git:git sample.git
- 禁用shell登录 
- 因为Git支持钩子（hook），所以，可以在服务器端编写一系列脚本来控制提交等操作，达到权限控制的目的。[Gitolite](https://github.com/sitaramc/gitolite)就是这个工具。 

### 常见问题

- ```
  # 有时候需要突然修改 .gitignore 文件，随后要立即生效
  git rm -r --cached .  #清除缓存  
  git add . #重新trace file  
  git commit -m "update .gitignore" #提交和注释  
  git push origin master #可选，如果需要同步到remote上的话  
  ```

- rm -rf .git/  取消git初始化
- 如果不慎commit 不恰当的文件，可以git reset --hard 版本号回退　　或者从远程仓库中git pull origin master