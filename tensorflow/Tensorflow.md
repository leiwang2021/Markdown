# Tensorflow

- tf.contrib.training.HParams

  Class to hold a set of hyperparameters as name-value pairs.

- tf.gather_nd(params, indices, name=None)
  用indices从张量params得到新张量

- tf.squeeze

  该函数返回一个张量，这个张量是将原始input中所有维度为1的那些维都删掉的结果
  `axis`可以用来指定要删掉的为1的维度，**此处要注意指定的维度必须确保其是1，否则会报错**

- tf.assign(ref, value, validate_shape=None, use_locking=None, name=None)

  函数完成了将value赋值给ref的作用。其中：ref **必须是tf.Variable创建的tensor，如果ref=tf.constant()会报错！**

- saver = tf.train.Saver()

  保存和恢复都需要实例化一个 tf.train.Saver。然后，训练循环中，定期调用 saver.save() 方法，向文件夹中写入包含当前模型中所有可训练变量的 checkpoint 文件。

  之后，就可以使用 saver.restore() 方法，重载模型的参数，继续训练或用于测试数据：

  - saver.restore(sess, FLAGS.train_dir）

- tf.summary.FileWriter

  指定一个文件用来保存图。

- tf.nn.embedding_lookup( params, ids, …)

  主要使用params, ids两个参数，函数的功能是从params中挑出索引为ids的元素，并返回一个张量，假设params的shape是batch * hidden, ids的shape是  n*batch
  那么函数返回张量的shape是n\ *batch\* hidden

- embedding层就是以one hot为输入的全连接层

- ![preview](https://pic2.zhimg.com/v2-9de68e5c46e9ea1ea480e295b0cc0b87_r.jpg)

```
import tensorflow as tf
import numpy as np

a = [[0.1, 0.2, 0.3], [1.1, 1.2, 1.3], [2.1, 2.2, 2.3], [3.1, 3.2, 3.3], [4.1, 4.2, 4.3]]
a = np.asarray(a)
idx1 = tf.Variable([0, 2, 3, 1], tf.int32)
idx2 = tf.Variable([[0, 2, 3, 1], [4, 0, 2, 2]], tf.int32)
out1 = tf.nn.embedding_lookup(a, idx1)
out2 = tf.nn.embedding_lookup(a, idx2)
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    print sess.run(out1)
    print out1
    print '=================='
    print sess.run(out2)
    print out2

[[ 0.1  0.2  0.3]
 [ 2.1  2.2  2.3]
 [ 3.1  3.2  3.3]
 [ 1.1  1.2  1.3]]
Tensor("embedding_lookup:0", shape=(4, 3), dtype=float64)
==================
[[[ 0.1  0.2  0.3]
  [ 2.1  2.2  2.3]
  [ 3.1  3.2  3.3]
  [ 1.1  1.2  1.3]]

 [[ 4.1  4.2  4.3]
  [ 0.1  0.2  0.3]
  [ 2.1  2.2  2.3]
  [ 2.1  2.2  2.3]]]
Tensor("embedding_lookup_1:0", shape=(2, 4, 3), dtype=float64)
```

- tf.Variable(),tf.get_variable(),tf.Variable_scope(),tf.name_scope()

  - tf.Variable(<variable_name>)会自动检测命名冲突并自行处理，但tf.get_variable(<variable_name>)则遇到重名的变量创建且变量名没有设置为共享变量时，则会报错

  - tf.Variable(<variable_name>)和tf.get_variable(<variable_name>)都是用于在一个name_scope下面获取或创建一个变量的两种方式，区别在于：
    tf.Variable(<variable_name>)用于创建一个新变量，在同一个name_scope下面，可以创建相同名字的变量，底层实现会自动引入别名机制，两次调用产生了其实是两个不同的变量。
    tf.get_variable(<variable_name>)用于获取一个变量，并且不受name_scope的约束。当这个变量已经存在时，则自动获取；如果不存在，则自动创建一个变量。

  - Variable是定义变量，而get_variable是获取变量（只不过如果获取不到就重新定义一个变量）

    ```
    
    import tensorflow as tf
     
    v1 = tf.Variable(1,name="V1")                     # 第1句话
    v2 = tf.Variable(2,name="V1")                     # 第2句话
    v3 = tf.Variable(3,name="V1")                     # 第3句话
    v4 = tf.Variable(4,name="V1_1")                   # 第4句话
     
    print ("v1:",v1.name)
    print ("v2:",v2.name)
    print ("v3:",v3.name)
    print ("v4:",v4.name)
     
    v1 = tf.Variable(1,name="V1")                     # 第5句话
    print ("v1:",v1.name)
     
     
    ### 输出结果为 ###
    # v1: V1:0
    # v2: V1_1:0
    # v3: V1_2:0
    # v4: V1_1_1:0
    # v1: V1_3:0
    
    
    import tensorflow as tf
     
    v5 = tf.get_variable(name="V1",initializer=1)
    v6 = tf.get_variable(name="V1",initializer=1)
    print ("v5:",v5.name)
    print ("v6:",v6.name)
    #会报错，因为get_variable在没有定义变量作用域variable_scope的时候（后面会讲到）不会对＃#get_variable()创建的name相同的变量自动进行处理
    ```

  - ```
    import tensorflow as tf
     
    v1 = tf.Variable(1,name="V1")
    print ("v1:",v1.name)
     
    v5 = tf.get_variable(name="V1",initializer=1)
    v6 = tf.get_variable(name="V1_1",initializer=1)
    print ("v5:",v5.name)
    print ("v6:",v6.name)
     
     
     
    ### 输出结果如下 ###
    # v1: V1:0
    # v5: V1_1:0
    # v6: V1_1_1:0
    ```

  - ```
    import tensorflow as tf
     
    with tf.variable_scope("scope1"):
        v1 = tf.Variable(1, name="V1")
        v2 = tf.get_variable(name="V2", initializer=1.0)
     
    with tf.variable_scope("scope1", reuse=True):
        v3 = tf.Variable(1, name="V1")
        v4 = tf.get_variable(name="V2", initializer=1.0)
     
    print(v1.name)
    print(v2.name)
    print(v3.name)
    print(v4.name)
     
    print(v1 is v3, v2 is v4)
     
     
     
    ### 输出结果为 ###
    # scope1/V1:0
    # scope1/V2:0
    # scope1_1/V1:0
    # scope1/V2:0
    # False True
    ```

- 查看tensorflow中间过程的变量值

  - ```
    item_embeddings = self.item_embeddings.eval()
    ```

  - 即可查看

- tf.gather：用一个一维的索引数组，将张量中对应索引的向量提取出来

- 注意tensorflow的版本与cudn和cudnn的版本对应问题
  - cat /usr/local/cuda/version.txt查看cuda版本
  - cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2　查看cudnn版本

- Keras中构建 模型有两种方式，一种是通过Model类构建，一种是通过Sequential构建。前者类似对数据的pipline处理，后者侧重于模型的堆叠。

  - Model 类提供了数据特征处理和模型训练的一些操作。在keras中构建model有两种方式，直接构建和通过定义一个子类构建。

- eval

  - 可以使用sess.run()在同一步获取多个tensor中的值，使用Tensor.eval()时只能在同一步当中获取一个tensor值，并且每次使用 eval 和 run时，都会执行整个计算图

- tf.train.Saver()

  - 可用来保存模型

  - ```python
    saver.save(self.sess, '../model/Dnn.ckpt')
    ```

  - 加载模型

    ```python
    with tf.Session() as sess:
        #tf.train.import_meta_graph函数给出model.ckpt-n.meta的路径后会加载图结构，并返回saver对象
        saver = tf.train.import_meta_graph('../model/Dnn.ckpt.meta')
        saver.restore(sess,tf.train.latest_checkpoint("../model/"))
        graph = tf.get_default_graph()
        feat_user = graph.get_tensor_by_name("feat_user:0")
        feat_item = graph.get_tensor_by_name("feat_item:0")
        user_embeddings=graph.get_tensor_by_name("user_embeddings_2:0")
        item_embeddings = graph.get_tensor_by_name("item_embeddings_2:0")
        feed_dict={feat_user:user,feat_item:item}
        user_embeddings,item_embeddings=sess.run([user_embeddings,item_embeddings],feed_dict)
        score=tf.reduce_sum(tf.multiply(user_embeddings, item_embeddings),axis=1)
        score=sess.run(score)
    ```

    

 





