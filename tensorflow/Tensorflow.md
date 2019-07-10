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

  主要使用params, ids两个参数，函数的功能是从params中挑出索引为ids的元素，并返回一个张量，假设params的shape是batch * hidden, ids的shape是batch * n
  那么函数返回张量的shape是batch *n * hidden
- embedding层就是以one hot为输入的全连接层

  

  

  
