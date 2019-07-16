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

  

