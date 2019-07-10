# DAN_Code

- nn.Conv2d
![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/nn_Conv2d.png)

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/example.png)

- nn.BatchNorm2d
  对于一个batch normalization层而言，求取的均值与方差是对于所有batch中的同一个channel进行求取，batch normalization中的batch体现在这个地方。 batch normalization层能够学习到的参数，对于一个特定的channel而言实际上是两个参数，gamma与beta，对于total的channel而言实际上是channel数目的两倍。

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/bn.png)

```
nn.BatchNorm2d(3)  # bn设置的参数实际上是channel的参数
BatchNorm就是在深度神经网络训练过程中使得每一层神经网络的输入保持相同分布的。
```

- *CLASS*`torch.nn.``MaxPool2d`(*kernel_size*, *stride=None*, *padding=0*, *dilation=1*, *return_indices=False*, *ceil_mode=False*)

  Applies a 2D max pooling over an input signal composed of several input planes.

- `torch.nn.``AvgPool2d`(*kernel_size*, *stride=None*, *padding=0*, *ceil_mode=False*, *count_include_pad=True*)
	Parameters:	
```kernel_size – the size of the window
stride – the stride of the window. Default value is kernel_size
padding – implicit zero padding to be added on both sides
ceil_mode – when True, will use ceil instead of floor to compute the output shape
count_include_pad – when True, will include the zero-padding in the averaging calculation
```

![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/nn_AvePool.png)

- *CLASS*`torch.nn.``Linear`(*in_features*, *out_features*, *bias=True*)

Applies a linear transformation to the incoming data:   y=xA^T+b



-  *CLASS*`torch.nn.``Module`

  Base class for all neural network modules.

  Your models should also subclass this class.

一般神经网络的类都继承自torch.nn.Module，__init__()和forward()两个函数是自定义类的主要函数。在__init__()中都要添加一句super(Net, self).__init__()，这是固定的标准写法，用于继承父类的初始化函数。__init__()中只是对神经网络的模块进行了声明，真正的搭建是在forwad()中实现。自定义类中的成员都通过self指针来进行访问，所以参数列表中都包含了self。



- super的作用是调用 当前类（子类）所继承的 基类（父类）的方法。

- `modules`()

  Returns an iterator over all modules in the network.

  ```
  l = nn.Linear(2, 2)
  net = nn.Sequential(l, l)
  for idx, m in enumerate(net.modules()):
          print(idx, '->', m)
  ```

- *CLASS*`torch.nn.``Sequential`(**args*)

  A sequential container. Modules will be added to it in the order they are passed in the constructor. Alternatively, an ordered dict of modules can also be passed in.

- Python中的 isinstance() 函数，是Python中的一个内置函数，用来判断一个函数是否是一个已知的类型，类似 type()
  isinstance(object,classinfo)
  object : 实例对象。classinfo : 可以是直接或者间接类名、基本类型或者由它们组成的元组。isinstance() 会认为子类是一种父类类型，考虑继承关系。

```python
layers = []
layers.append(nn.Linear(10,10))   
layers.append(nn.Linear(10,10))
net=nn.Sequential(*layers)       #   *layers可以得到列表里的内容，  模块必须是实例化后的
```

- Pyhton在类__init__时可以调用类的其他函数：

  ```
  class ResNet(nn.Module):
  
      def __init__(self, block, layers, num_classes=1000):
          self.inplanes = 64
          super(ResNet, self).__init__()
          self.conv1 = nn.Conv2d(3, 64, kernel_size=7, stride=2, padding=3,
                                 bias=False)
          self.bn1 = nn.BatchNorm2d(64)
          self.relu = nn.ReLU(inplace=True)
          self.maxpool = nn.MaxPool2d(kernel_size=3, stride=2, padding=1)
          self.layer1 = self._make_layer(block, 64, layers[0])
          self.layer2 = self._make_layer(block, 128, layers[1], stride=2)
          self.layer3 = self._make_layer(block, 256, layers[2], stride=2)
          self.layer4 = self._make_layer(block, 512, layers[3], stride=2)
          self.avgpool = nn.AvgPool2d(7, stride=1)
          self.baselayer = [self.conv1, self.bn1, self.layer1, self.layer2, self.layer3, self.layer4]
  
          for m in self.modules():
              if isinstance(m, nn.Conv2d):
                  n = m.kernel_size[0] * m.kernel_size[1] * m.out_channels
                  m.weight.data.normal_(0, math.sqrt(2. / n))
              elif isinstance(m, nn.BatchNorm2d):
                  m.weight.data.fill_(1)
                  m.bias.data.zero_()
  
      def _make_layer(self, block, planes, blocks, stride=1):
          downsample = None
          if stride != 1 or self.inplanes != planes * block.expansion:
              downsample = nn.Sequential(
                  nn.Conv2d(self.inplanes, planes * block.expansion,
                            kernel_size=1, stride=stride, bias=False),
                  nn.BatchNorm2d(planes * block.expansion),
              )
  
          layers = []
          layers.append(block(self.inplanes, planes, stride, downsample))
          self.inplanes = planes * block.expansion
          for i in range(1, blocks):
              layers.append(block(self.inplanes, planes))
  
          return nn.Sequential(*layers)
  ```
- torch.cat(tensors, dim=0, out=None) → Tensor
Concatenates the given sequence of seq tensors in the given dimension. All tensors must either have the same shape (except in the concatenating dimension) or be empty.
```
x = torch.randn(2, 3)
tensor([[ 0.6580, -1.0969, -0.4614],
        [-0.1034, -0.5790,  0.1497]])
torch.cat((x, x, x), 0)
tensor([[ 0.6580, -1.0969, -0.4614],
        [-0.1034, -0.5790,  0.1497],
        [ 0.6580, -1.0969, -0.4614],
        [-0.1034, -0.5790,  0.1497],
        [ 0.6580, -1.0969, -0.4614],
        [-0.1034, -0.5790,  0.1497]])
```

- torch.unsqueeze

  Returns a new tensor with a dimension of size one inserted at the specified position.

  The returned tensor shares the same underlying data with this tensor.

  ```
  x = torch.tensor([1, 2, 3, 4])
  torch.unsqueeze(x, 0)
  tensor([[ 1,  2,  3,  4]])
  torch.unsqueeze(x, 1)
  tensor([[ 1],
          [ 2],
          [ 3],
          [ 4]])
  ```

- torch.expand

  Returns a new view of the `self` tensor with singleton dimensions expanded to a larger size.

  Passing -1 as the size for a dimension means not changing the size of that dimension.

  ```
  x = torch.tensor([[1], [2], [3]])
  x.expand(3, 4)
  tensor([[ 1,  1,  1,  1],
          [ 2,  2,  2,  2],
          [ 3,  3,  3,  3]])
  x.expand(-1, 4)
  tensor([[ 1,  1,  1,  1],
          [ 2,  2,  2,  2],
          [ 3,  3,  3,  3]])
  ```

- torch.utils.model_zoo.load_url(url, model_dir=None, map_location=None, progress=True)
  Loads the Torch serialized object at the given URL.

- `state_dict`(*destination=None*, *prefix=''*, *keep_vars=False*)

  Returns a dictionary containing a whole state of the module.

  ```
  module.state_dict().keys()
  ['bias', 'weight']
  ```

- load_state_dict(*state_dict*, *strict=True*)

  Copies parameters and buffers from [`state_dict`](https://pytorch.org/docs/master/nn.html?highlight=load_state_dict#torch.nn.Module.state_dict) into this module and its descendants. If `strict` is `True`, then the keys of [`state_dict`](https://pytorch.org/docs/master/nn.html?highlight=load_state_dict#torch.nn.Module.state_dict) must exactly match the keys returned by this module’s [`state_dict()`](https://pytorch.org/docs/master/nn.html?highlight=load_state_dict#torch.nn.Module.state_dict) function.

- `train`(*mode=True*)

  Sets the module in training mode.

- `torch.nn.functional.``log_softmax`(*input*, *dim=None*, *_stacklevel=3*, *dtype=None*)

  Applies a softmax followed by a logarithm.

  While mathematically equivalent to log(softmax(x)), doing these two operations separately is slower, and numerically unstable. This function uses an alternative formulation to compute the output and gradient correctly.

- torch.nn.functional.nll_loss(input, target, weight=None, size_average=None, ignore_index=-100, reduce=None, reduction='mean')

  The negative log likelihood loss.

- .cuda()
  Moves all model parameters and buffers to the GPU.
  This also makes associated parameters and buffers different objects. So it should be called before constructing optimizer if the module will live on GPU while being optimized.

- 新构造的模块的参数默认requires_grad为True

- torch.utils.data.Dataset

  an abstract class representing a dataset. Your custom dataset should inherit `Dataset` and override the following methods:

  - `__len__` so that `len(dataset)` returns the size of the dataset.

  - `__getitem__` to support the indexing such that `dataset[i]` can be used to get iith sample

    an optional argument `transform` so that any required processing can be applied on the sample

- class torchvision.transforms.RandomHorizontalFlip
  随机水平翻转给定的PIL.Image,概率为0.5。即：一半的概率翻转，一半的概率不翻转

- class torchvision.transforms.ToTensor
  把一个取值范围是[0,255]的PIL.Image或者shape为(H,W,C)的numpy.ndarray，转换成形状为[C,H,W]，取值范围是[0,1.0]的torch.FloadTensor

- class torchvision.transforms.Compose(transforms)
  将多个transform组合起来使用

- class torchvision.transforms.RandomCrop(size, padding=0)
  切割中心点的位置随机选取。size可以是tuple也可以是Integer。

- Resize
  对PIL Image实现resize操作
  如果输入为单个int值，则将输入图像的短边resize到这个int数，长边根据对应比例调整，图像长宽比保持不变。
  如果输入为(h,w)，且h、w为int，则直接将输入图像resize到(h,w)尺寸，图像的长宽比可能会发生变化

- transforms的22个方法

  <https://blog.csdn.net/u011995719/article/details/85107009#1transformsRandomCrop_38>

- datasets.ImageFolder
  ImageFolder假设所有的文件按文件夹保存好，每个文件夹下面存贮同一类别的图片，文件夹的名字为分类的名字。
  ImageFolder(root,transform=None,target_transform=None,loader=
  default_loader)
  root : 在指定的root路径下面寻找图片 
  transform: 对PIL Image进行转换操作,transform 输入是loader读取图片返回的对象 
  target_transform :对label进行变换 
  loader: 指定加载图片的函数，默认操作是读取PIL image对象

- ```
  torch.utils.data.DataLoader
  ```

  该接口主要用来将自定义的数据读取接口的输出或者PyTorch已有的数据读取接口的输入按照batch size封装成Tensor，后续只需要再包装成Variable即可作为模型的输入，因此该接口有点承上启下的作用

- torchvision dataset
  All datasets are subclasses of torch.utils.data.Dataset i.e, they have __getitem__ and __len__ methods implemented. Hence, they can all be passed to a torch.utils.data.DataLoader which can load multiple samples parallelly using torch.multiprocessing workers. For example:

  ```
  imagenet_data = torchvision.datasets.ImageFolder('path/to/imagenet_root/')
  data_loader = torch.utils.data.DataLoader(imagenet_data,
                                            batch_size=4,
                                            shuffle=True,
                                            num_workers=args.nThreads)
  ```

- iter next 

  list、tuple等都是可迭代对象，我们可以通过******iter()******函数获取这些可迭代对象的迭代器。然后我们可以对获取到的迭代器不断使******⽤******next()******函数来获取下******⼀条数据***

- eval

   Calling `eval()` sets the training variable in all modules in the network to false

- requires_grad

  Variable变量的requires_grad的属性默认为*False*,若一个节点requires_grad被设置为True，那么所有依赖它的节点的requires_grad都为True

- volatile
  volatile=True是Variable的另一个重要的标识，它能够将所有依赖它的节点全部设为volatile=True，其优先级比requires_grad=True高。因而volatile=True的节点不会求导，即使requires_grad=True，也不会进行反向传播，对于不需要反向传播的情景(inference，测试推断)，该参数可以实现一定速度的提升，并节省一半的显存，因为其不需要保存梯度

- Module

  **Module** 是 `pytorch` 提供的一个基类，每次我们要 搭建 自己的神经网络的时候都要继承这个类，继承这个类会使得我们 搭建网络的过程变得异常简单

  ```
  def __init__(self):
      self._backend = thnn_backend
      self._parameters = OrderedDict()
      self._buffers = OrderedDict()
      self._backward_hooks = OrderedDict()
      self._forward_hooks = OrderedDict()
      self._forward_pre_hooks = OrderedDict()
      self._modules = OrderedDict()
      self.training = True
  ```

  在`forward` 过程中，直接获取，父类的`training`的值。

  我们 通常通过 `module.train()` 和 `module.eval()` 来切换模型的 训练测试阶段。

- ##### nn.CrossEntropyLoss()

  ##### nn.CrossEntropyLoss()是nn.logSoftmax()和nn.NLLLoss()的整合,可以直接使用它来替换网络中的这两个操作

  ##### 输入是size是(minibatch,C)。这里的C是类别数:

  ![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/loss.png)

- nn.LogSoftmax()

  nn.Nll_Loss():

  ![](/home/leiwang/transfer_learning/transferlearning-master/code/deep/DAN/loss_.png)

x_{n,y_n}表示目标类所对应输入x中值

