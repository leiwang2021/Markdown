# Python的使用

- ```
  os.makedirs
  ```

​       用于递归创建目录

- argparse 用于解析命令行参数和选项的标准模块

  ```
  import argparse   #导入该模块
  parser = argparse.ArgumentParser() #创建一个解析对象，然后向该对象添加要关注的命令行参数
  parser.add_argument()   #对应一个要关注的参数或选项
  parser.parse_args()    #解析
  ```
- np.prod
  用于计算所有元素的乘积，对于有多个维度的数组可以指定轴

- sys

  sys.argv[]是用来获取命令行参数的,其第一个元素是程序本身，随后才依次是外部给予的参数。

  sys.argv[0]   sys.argv[0]表示代码本身文件路径

- os

  使用python获得系统的信息时，使用os.environ()

  environ是一个字符串所对应环境的映像对象;os.environ.keys()  主目录下所有的key,os.environ 显示key+内容。

  - windows：
    -   · os.environ['HOMEPATH']:当前用户主目录。
    -  os.environ['TEMP']:临时目录路径。
    -  os.environ[PATHEXT']:可执行文件。
    -  os.environ['SYSTEMROOT']:系统主目录。
    -  os.environ['LOGONSERVER']:机器名。
    -  os.environ['PROMPT']:设置提示符。
  - os.system(‘comand’) 会执行括号中的命令，如果命令成功执行，这条语句返回0，否则返回1
  - os.path模块主要用于文件的属性获取,exists是“存在”的意思，所以顾名思义，os.path.exists()就是判断括号里的文件是否存在的意思，括号内的可以是文件路径。

- 

