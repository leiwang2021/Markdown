# deep network

##  ResNet

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/resnet2.jpg)

- resNet主要解决一个问题，就是更深的神经网络如何收敛的问题，为了解决这个问题，论文提出了一个残差学习的框架

- 对于传统的方法是直接去学习输入到输出的映射，而深度卷积残差网络是去学习输入到（输出－输入）的映射。这样就有了一个先验信息：输出一定是可以由输入的一部分组成的。事实上证明，这个先验信息是很有用的，这对应于相等映射（也就是要学习的参数都为０的情况），而传统网络在学习参数都为０的情况是输出０映射。对于传统网络而言，要想学习一个相等映射，再深的网络由于其本身的非线性性，很难学出来。

- 事实上，改变网络结构的方式有很多，一种是改变每一层的内容，比如将卷积改为全连接，改变卷积核的大小，而ResNet改变的是神经网络的连接方式，将前一层（输入）直接连接到后一层（输出）,这样实现残差的学习，而参数相比传统的VGG一点都没有多，但是结构改了。

- Resnet提供了两种选择方式，也就是identity mapping和residual mapping，如果网络已经到达最优，继续加深网络，residual mapping将被push为0，只剩下identity mapping，这样理论上网络一直处于最优状态了，网络的性能也就不会随着深度增加而降低了。
其中ResNet提出了两种mapping：一种是identity mapping，指的就是图1中”弯弯的曲线”，另一种residual mapping，指的就是除了”弯弯的曲线“那部分，所以最后的输出是 y=F(x)+xy=F(x)+x 
identity mapping顾名思义，就是指本身，也就是公式中的xx，而residual mapping指的是“差”，也就是y−xy−x，所以残差指的就是F(x)F(x)部分。 

  ![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/ResNet1.png)
- 这两种结构分别针对ResNet34（左图）和ResNet50/101/152（右图），一般称整个结构为一个”building block“。其中右图又称为”bottleneck design”，目的一目了然，就是为了降低参数的数目，第一个1x1的卷积把256维channel降到64维，然后在最后通过1x1卷积恢复，整体上用的参数数目：1x1x256x64 + 3x3x64x64 + 1x1x64x256 = 69632，而不使用bottleneck的话就是两个3x3x256的卷积，参数数目: 3x3x256x256x2 = 1179648，差了16.94倍。 
对于常规ResNet，可以用于34层或者更少的网络中，对于Bottleneck Design的ResNet通常用于更深的如101这样的网络中，目的是减少计算和参数量（实用目的

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/two.png)

两种Shortcut Connection方式实例（左图channel一致，右图channel不一样）

所以采用计算方式： 
y=F(x)+x 

y=F(x)+Wx ,其中W是卷积操作，用来调整x的channel维度的； 

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/ResNet3.png)

**101层网络仅仅指卷积或者全连接层，而激活层或者Pooling层并没有计算在内；** 



## *基于ResNet101的Faster RCNN* 

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/Fater_RCNN.png)

## GAN

- ![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-31-40.png)
         crossEntroy
- ![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-29-21.png)

![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-46-18.png)

![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-46-03.png)

![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-47-21.png)

- JS散度

  ![](/home/leiwang/screenshot/Screenshot from 2019-04-10 14-49-43.png)

- C  = − log(4) is the global minimum of C(G) and that the only solution is p_g = p_data 

- ![](/home/leiwang/screenshot/Screenshot from 2019-04-10 15-00-48.png)

  

## ADDA

- combine adversarial learning with discriminative feature learning
- modeling the distributions is not strictly necessary to achieve domain adaptation, as long as the latent feature space is domain invariant

- 首先，作者使用判别模型。因为作者认为用于生成样本的大量参数与要执行的判别任务无关。

- 其次，作者使用独立的源域和目标域映射网络，两部分不共享参数。这是一个更灵活的设计，可以让映射网络学习到更多的特定领域特征。作者用预训练的源域映射网络权重初始化目标域映射网路。

- 最后，作者使用GAN loss作为映射网络的对抗损失。

- 首先，使用源域数据对源域映射网络M_s和分类器C进行监督训练，优化损失函数L_{cls}

  ![](/home/leiwang/Pictures/9375256-8a695852880029ea.png)

- 其次，固定源域映射网络M_s，使用目标域数据和源域数据对目标域映射网络M_t和判别器D进行对抗训练，优化损失函数L_{advD}和L_{advM}。

​       ![](/home/leiwang/Pictures/9375256-36dcac25c57e3b5e.png)

- 不需要模拟输入图像的分布，最终的任务是学习一个判别表示
- All adversarial losses train the adversarial discriminator using a standard classification loss, L_advD. However, they differ in the loss used to train the mapping L_advM
- 注意采用CrossEntroy损失和BCELosss时两种计算方式的区别和联系