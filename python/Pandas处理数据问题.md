# Pandas处理数据问题

- 存取数据  read_csv, read_table

  to_csv()  ，指定index=False , 读取时默认即可，若为指定，会多出一列

  read_csv(), 若存的时候未指定index,则  index_col=0,将第一列当成索引

  parse_dates = ['col_name']   *# 指定某行读取为日期格式*

- 索引时 variable[column] 得到的是Series，variable[[column]]得到的是DataFrame

- 

- | `bool_`  | Boolean (True or False) stored as a byte                     |
  | -------- | ------------------------------------------------------------ |
  | `int_`   | Default integer type (same as C `long`; normally either `int64` or `int32`) |
  | intc     | Identical to C `int` (normally `int32` or `int64`)           |
  | intp     | Integer used for indexing (same as C `ssize_t`; normally either `int32` or `int64`) |
  | int8     | Byte (-128 to 127)                                           |
  | int16    | Integer (-32768 to 32767)                                    |
  | int32    | Integer (-2147483648 to 2147483647)                          |
  | int64    | Integer (-9223372036854775808 to 9223372036854775807)        |
  | uint8    | Unsigned integer (0 to 255)                                  |
  | uint16   | Unsigned integer (0 to 65535)                                |
  | uint32   | Unsigned integer (0 to 4294967295)                           |
  | uint64   | Unsigned integer (0 to 18446744073709551615)                 |
  | `float_` | Shorthand for `float64`.                                     |
  | float16  | Half precision float: sign bit, 5 bits exponent, 10 bits mantissa |
  | float32  | Single precision float: sign bit, 8 bits exponent, 23 bits mantissa |
  | float64  | Double precision float: sign bit, 11 bits exponent, 52 bits mantissa |



- totalExposure_exposureAid_id.apply(pd.value_counts)   统计次数

- totalExposureLog_aidRequest_time['aidRequest_time'].apply(process_time) 将自定义的函数应用到DataFrame上

- 修改列名

  df.rename(columns={'count':'other'},inplace=True)

- groupby的使用

  这里agg接受的不一定是`np.mean`这些函数, 你还可以进行自定义函数哦

  - 画图

    ```a
    data.groupby('race')['flee'].value_counts().unstack().plot(kind='bar', figsize=(20, 4))
    ```

  ```Python
  df.groupby(['Q','A','B','C'],as_index=False).count()
  ```

  - 对组内不同列采取不同的操作

    ```python
    data.groupby('race').agg({'age': np.median, 'signs_of_mental_illness': np.mean})
    ```

  - 同时求不同组内, 年龄的均值, 中位数, 方差

    ```
    data.groupby('flee')['age'].agg([np.mean, np.median, np.std])
    ```

  - 结合上面两个功能

    ```
    - - data.groupby('flee').agg({'age': [np.median, np.mean], 'signs_of_mental_illness': np.mean})
    ```

- pandas增加一行

  ```Python
  df.loc['5'] = [16, 17, 18, 19]    # 后面的序列是Iterable就行
  df.at['5'] = [16, 17, 18, 19]
  df.set_value('5', df.columns, [16, 17, 18, 19], takeable=False)    # warning，
  
  s = pd.Series([16, 17, 18, 19], index=df.columns, name='5')
  df = df.append(s)
  
  s = pd.Series([16, 17, 18, 19], index=df.columns)
  df = df.append(s, ignore_index=True)　　
  
  ```

- pandas增加一列

  ```python
  df.loc[:, 'E'] =s
  df['E']=s
  ```

  ```python
  s = pd.Series([16, 17, 18, 19], name='E', index=df.index)
  df = pd.concat([df, s], axis=1)
  ```

- pandas去重
  1. *#删除重复行，该函数返回的是删除重复行后的DataFrame对象*
  2. dframe.drop_duplicates()
  3. *#根据某个字段去重*
  4. dframe.drop_duplicates('color')

- 切片时pandas的索引问题

  reset_index(drop=True)重新索引

- loc和iloc

  ```
  loc是根据dataframe的具体标签选取列，而iloc是根据标签所在的位置，从0开始计数。
  ```

- 过滤数据时

  temp=ad_operation[(ad_operation['Aid_id'] == 593323) & (ad_operation['establishOrModify_time']==0)]     **没有小括号会报错**

- 链式操作

  先选取左右`A<0.3`的行，其次再从中选取B列，上述操作将其分为两部，那么这样就是链式操作。

  如果此时要进行：选取其中所有`A<0.3`的B列值并将其赋值为1，如果进行：

  df1[df1.A < 0.3].B = 1，此时就会报错SettingWithCopyWarning的Warning 
  如果此时再查看df1里面的值，会发现完全没有改变

  用loc函数如下：

  df1.loc[df1.A<0.3, 'B'] = 1

  凡事出现链式赋值的情况，pandas都是不能够确定到底返回的是一个引用还是一个拷贝。所以遇到这种情况就干脆报warning

- 更隐蔽的链式赋值

  f2 = df1.loc[df1.A<0.3]
  df2.loc[1,'B'] = 2

  虽然这两步每步都用了loc，但是凡是把取值（GET）操作分为两步的，仍然是链式赋值的状态，所以仍然会报warning。 

- 总结

  这里总结一下pandas的这个问题：

  - 避免任何形式的链式赋值，有可能会报warning也有可能不会报。而且即使报了，可能有问题，也可能没问题。
  - 如果需要用到多级选取，则用loc
  - 如果需要用到拷贝，则直接加copy()函数

- 列数相同，行数不同的Series赋值会报错

- pandas merge 函数

  基本的结构为：pd.merge（df1，df2，合并方式，df1合并用的键，df2合并用的键）。

- map, apply applymap

  总的来说就是apply()是一种让函数作用于列或者行操作，applymap()是一种让函数作用于DataFrame每一个元素的操作，而map是一种让函数作用于Series每一个元素的操作

- 赋值问题

  当将含一个元素的Series赋值给DataFrame时，对Series取item（）得到它的值，再进行赋值

- 使用逻辑运算符时，注意加括号

  ```
  (temp2.iloc[i]>=temp_time[m])&(temp2_max_time.iloc[i]<temp_time[m+1])
  ```

  若未加括号，结果可能不正确

- 删除nan所在行或列

  `DataFrame.``dropna`(*axis=0*, *how='any'*, *thresh=None*, *subset=None*, *inplace=False*)[[source\]](http://github.com/pandas-dev/pandas/blob/v0.24.2/pandas/core/frame.py#L4456-L4603)

- pd.to_datetime('2018/04/16')

  Timestamp('2018-04-16 00:00:00')

- pd.sort_values

  Sort by the values along either axis

- reset_index(drop=True)

  去除掉原来的行名

- pandas.merge使用

  left 参与合并的左侧DataFrame 
  right 参与合并的右侧DataFrame 
  how 连接方式：‘inner’（默认）；还有，‘outer’、‘left’、‘right’ 
  on 用于连接的列名，必须同时存在于左右两个DataFrame对象中，如果位指定，则以left和right列名的交集作为连接键 
  left_on 左侧DataFarme中用作连接键的列 

  right_on 右侧DataFarme中用作连接键的列 

  - 参数ｈow的使用

    默认：inner 内连接，取交集”,   键值的交集

    outer 外连接，取并集，并用nan填充

    left 左连接， 左侧取全部，右侧取部分

    right 有连接，左侧取部分，右侧取全部

- pandas.get_dummies

  Convert categorical variable into dummy/indicator variables

  ```python
  pd.get_dummies(pd.Series(list('abcaa')))
     a  b  c
  0  1  0  0
  1  0  1  0
  2  0  0  1
  3  1  0  0
  4  1  0  0
  ```

- pd.concat

  Concatenate pandas objects along a particular axis with optional set logic along the other axes.

- 1、./是[当前目录](https://www.baidu.com/s?wd=%E5%BD%93%E5%89%8D%E7%9B%AE%E5%BD%95&tn=SE_PcZhidaonwhc_ngpagmjz&rsv_dl=gh_pc_zhidao)

  2、../是父级目录

  3、/是根目录

## time模块的使用

- 将字符串的时间转换为时间戳

  ```Python
  #a="2013-10-10 23:40:00"
  import time
  timeArray=time.strptime(a,%Y-%m-%d %H:%M:%S") #将其转换为时间数组
  timeStamp=int(time.mktime(timeArray))  #转换为时间戳
  ```

- 字符串格式更改

  ```Python
  #如a = "2013-10-10 23:40:00",想改为 a = "2013/10/10 23:40:00"
  #方法:先转换为时间数组,然后转换为其他格式
  timeArray = time.strptime(a, "%Y-%m-%d %H:%M:%S")
  otherStyleTime = time.strftime("%Y/%m/%d %H:%M:%S", timeArray) 
  ```

- 时间戳转换为指定格式日期

  ```Python
  #利用localtime()转换为时间数组,然后格式化为需要的格式,
  timeStamp = 1381419600
  timeArray = time.localtime(timeStamp)
  otherStyleTime = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)
  otherStyletime == "2013-10-10 23:40:00"
  ```

- 获取当前时间并转换为指定格式

  ```python
  import time
  now=int(time.time())  #这是时间戳
  timeArray = time.localtime(timeStamp)
  otherStyleTime = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)
  ```

  ```python
  import datetime
  #获得当前时间
  now = datetime.datetime.now()  #->这是时间数组格式
  #转换为指定的格式:
  otherStyleTime = now.strftime("%Y-%m-%d %H:%M:%S")
  ```

- 获取三天前的时间

  ```Python
  import time
  import datetime
  #先获得时间数组格式的日期
  threeDayAgo = (datetime.datetime.now() - datetime.timedelta(days = 3))
  #转换为时间戳:
  timeStamp = int(time.mktime(threeDayAgo.timetuple()))
  #转换为其他字符串格式:
  otherStyleTime = threeDayAgo.strftime("%Y-%m-%d %H:%M:%S")
  #注:timedelta()的参数有:days,hours,seconds,microseconds
  ```

- 时间戳ｘ 

  x.date()  获得的是日期

- 利用pandas绘图

  - `DataFrame.plot.bar`(*x=None*, *y=None*, ***kwds*)
  - ‘line’ : line plot (default)#折线图
  - ‘bar’ : vertical bar plot#条形图
  - ‘barh’ : horizontal bar plot#横向条形图
  - ‘hist’ : histogram#柱状图
  - ‘box’ : boxplot#箱线图
  - 例如：item_attr.item_price.value_counts().head(50).plot.bar(figsize=(15,9))  画出前５０个元素的dataframe的柱状图，figsize指明大小

- pd.to_datetime

  - Convert argument to datetime.



