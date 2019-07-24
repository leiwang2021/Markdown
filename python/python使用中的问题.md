# python使用中的问题

- 当存在多个`numpy`版本时，可能会发生导入错误，这时需要卸载完全部版本重新安装

- jupyter notebook背景设置

  - pip install jupyterthemes

  - pip install *--upgrade jupyterthemes*

  - 输出的结果总是显示不全，差两个字符

    - 在.jupyter/custom路径下，打开custom.css文件，找到div.output_area语句块

    - leiwang@leiwang:~/.jupyter/custom$ 

    - 替换为

      ```
      div.output_area {
      
      
      
      display: -webkit-box;
      
      
      
      padding: 13px;
      
      
      
      }
      ```

- matplotlib 显示中文字体问题

  - 下载中文字体`simhei.ttf`  >

  - <https://www.fontpalace.com/font-download/SimHei/>

  - 找到`matplotlib`相关的`font`文件夹位置   matplotlib.matplotlib_fname()

  - 将字体放到该文件夹下，　~/.local/lib/python3.6/site-packages/matplotlib/mpl-data/fonts/ttf$

  - cp simhei.ttf /home/leiwang/.local/lib/python3.6/site-packages/matplotlib/mpl-data/fonts/ttf

  - 删除缓存字体：rm -rf ~/.matplotlib/*.cache

  - 最终的解决办法：若出现问题，先卸载库，再重新安装

    - https://www.fontpalace.com/font-download/SimHei/  下载后安装字体

    - 找到`matplotlib`相关的`font`文件夹位置   matplotlib.matplotlib_fname()

    - 将字体放到该文件夹下，　~/.local/lib/python3.6/site-packages/matplotlib/mpl-data/fonts/ttf$

    - cp simhei.ttf /home/leiwang/.local/lib/python3.6/site-packages/matplotlib/mpl-data/fonts/ttf

    - 修改配置文件matplotlibrc  同样在matplotlib/mpl-data/fonts目录下面，修改下面三项配置

      font.family         : sans-serif        

      font.sans-serif     : SimHei, Bitstream Vera Sans, Lucida Grande, Verdana, Geneva, Lucid, Arial, Helvetica, Avant Garde, sans-serif   

      axes.unicode_minus:False，#作用就是解决负号'-'显示为方块的问题

    - 改了配置之后并不会生效，需要重新加载字体，在Python中运行如下代码即可：

      from matplotlib.font_manager import _rebuild

      _rebuild() #reload一下

    - 

- 列表的索引问题

  ```python
  b=[1,2,3,4]
  b[:123]不会报错，索引全部的值
  ```

- gc.collect

  - 清理内存

- set_index

  - set_index( ) 将 DataFrame 中的列转化为行索引。  
  - 可以变成层级索引，即花括号结构

- stack和unstack是python进行层次化索引的重要操作。层次化索引就是对索引进行层次化分类，便于使用，这里的索引可以是行索引，也可以是列索引。常见的数据的层次化结构有两种，一种是表格，一种是“花括号”

  - stack: 将数据从”表格结构“变成”花括号结构“，即将其列索引变成行索引。

  - unstack: 数据从”花括号结构“变成”表格结构“，即要将其中一层的行索引变成列索引。如果是多层索引，则以上函数是针对内层索引（这里是store）。利用level可以选择具体哪层索引。

    ```python
    import numpy as np
    import pandas as pd
    from pandas import Series,DataFrame
    data=DataFrame(np.arange(12).reshape((3,4)),index=pd.Index(['street1','street2','street3']),
                   columns=pd.Index(['store1','store2','store3','store4']))
    print(data)
    print('-----------------------------------------\n')
    data2=data.stack()
    data3=data2.unstack()
    print(data2)
    print('-----------------------------------------\n')
    print(data3)
    ```

    

