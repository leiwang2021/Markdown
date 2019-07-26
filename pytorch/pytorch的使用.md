# pytorch的使用

## pytorch的基本使用

#### Tensors与numpy类似，不过可以在GPU上使用

```
#构建一个未初始化的矩阵
from __future__ import print_function
import torch
x = torch.empty(5, 3)
print(x)
#构建一个随机初始化的矩阵
torch.rand(5,3)
#构建一个全0的矩阵
torch.zeros(5,3,dtype=torch.long)
#直接从数据中构建张量
torch.tensor([5,4])
#产生与原来数据相同size的张量
x = torch.randn_like(x, dtype=torch.float)
#得到size
x.size()
```

``` 
#两个张量间的运算
y=torch.rand(5,3)
print(x+y)
print(torch.add(x,y))
result = torch.empty(5, 3)
torch.add(x, y, out=result)
print(result)
#in-place加法
y.add_(x)
x.t_()#将改变x本身
print(x[:,1])  #可以切片
#重新设置size和shape
x=torch.randn(4,4)
y=x.view(16)
z=x.view(-1,8)
print(x.size,y.size,z.size)
#一个元素的张量，用.item得到其作为Python的值
x=torch.randn(1)
print(x)
print(x.item())
```

```
#可将张量转换为numpy数组，共享相同的寄存位置，改变一个将改变另一个
a=torch.ones(5)
b=a.numpy()
print(a,b)
a.add_(1)
print(a,b)
#将数组转换为张量
a=np.ones(5)
b=torch.from_numpy(a)
np.add(a,1,out=a)
print(a,b)
```

```
#Tensors can be moved onto any device using the .to method
#可以将数据存放在CPU和GPU上，可在之间转移
# let us run this cell only if CUDA is available
# We will use ``torch.device`` objects to move tensors in and out of GPU
if torch.cuda.is_available():
    device = torch.device("cuda")          # a CUDA device object
    y = torch.ones_like(x, device=device)  # directly create a tensor on GPU
    x = x.to(device)                       # or just use strings ``.to("cuda")``
    z = x + y
    print(z)
    print(z.to("cpu", torch.double))       # ``.to`` can also change dtype together!
```

## AUTOGRAD: AUTOMATIC DIFFERENTIATION

- 张量的梯度：

  如果将.requires_grad设置为True，它将追踪在它上面的所有操作，当完成计算后调用.backward()方法，就自动计算了梯度，对于这个张量的梯度也将积累到.grad属性中。

  要阻止张量跟踪历史记录，可以调用.detach（）将其从计算历史记录中分离出来，并防止将来的计算被跟踪。

  要防止跟踪历史记录（和使用内存），您还可以使用with torch.no_grad（）：包装代码块， 在评估模型时，这可能特别有用，因为模型可能具有requires_grad = True的可训练参数，但我们不需要梯度。

  Each tensor has a `.grad_fn` attribute that references a `Function` that has created the `Tensor`

```import torch
import torch
x=torch.ones(2,2,requires_grad=True)
print(x)
y=x+2
print(y)
print(y.grad_fn)
z=y*y*3
out=z.mean()
print(z,out)
#requires_grad默认是false
a=torch.randn(2,2)
a=((a*3)/(a-1))
print(a.requires_grad)
a.requires_grad_(True)
print(a.requires_grad)
b=(a*a).sum()
print(b.grad_fn)

#梯度
out.backward()
print(x.grad)##得到的是out对x的导数
```

## torch.autograd

- `torch.autograd` is an engine for computing vector-Jacobian product

![](/home/leiwang/Downloads/FireShot/FireShot Capture 001 - Autograd_ Automatic Differentiation — PyTorch Tutorials 1.0.0.dev2019_ - pytorch.org.png)

```
x=torch.randn(3,requires_grad=True)
y=x*2
while y.data.norm()<1000:
	y=y*2
print(y)
v=torch.tensor([0.1,1.0,0.0001],dtype=torch.float)
y.backward(v)
print(x.grad)
```

- grad can be implicitly created only for scalar outputs

  `torch.autograd` could not compute the full Jacobian directly, but if we just want the vector-Jacobian product, simply pass the vector to `backward` as argument

##神经网络
- 神经网络可以通过torch.nn包构建，An `nn.Module` contains layers, and a method `forward(input)`that returns the `output`

- 定义一个神经网络

  Python中的**super()**方法设计目的是用来解决多重继承时父类的查找问题

  需要定义forward函数，backward函数自动地通过autograd计算
```
import torch
import torch.nn as nn
import torch.nn.functional as F

class Net(nn.Module):
	def __init__(self):
		super(Net,self).__init__()
		self.conv1=nn.Conv2d(1,6,5)
		self.conv2=nn.Conv2d(6,16,5)
		self.fc1=nn.Linear(16*5*5,120)
		self.fc2=nn.Linear(120,84)
		self.fc3=nn.Linear(84,10)
		
	def forward(self,x):
		x=F.max_pool2d(F.relu(self.conv1(x)),(2,2))
		x=F.max_pool2d(F.relu(self.conv2(x)),2)
		x=x.view(-1, self.num_flat_features(x))
  		x=F.relu(self.fc1(x))
  		x=F.relu(self.fc2(x))
  		x=self.fc3(x)
  		return x
  	def num_flat_features(self,x):
  		size=x.size()[1:]
  		num_features=1
  		for s in size:
  			num_features*=s
  		return num_features
net=Net()
print(net)
```

- 可学习的参数通过net.parameters返回

  ```
  params=list(net.parameters())
  print(len(params))
  print(params[0].size())
  input=torch.randn(1,1,32,32)
  out=net(input)
  print(out)
  ```

- 使用随机梯度将所有参数和反向的梯度缓冲区归零

  ```
  net.zero_grad()
  out.backward(torch.randn(1, 10))
  ```

- torch.nn 仅支持mini-batchers，如nn.Conv2d仅支持`nSamples x nChannels x Height xWidth`.

  如果只有单个样本，可以使用input.unsqueeze(0)增加一个假的batch

  - `torch.Tensor` - A *multi-dimensional array* with support for autograd operations like `backward()`. Also *holds the gradient* w.r.t. the tensor.

  - `nn.Module` - Neural network module. *Convenient way of encapsulating parameters*, with helpers for moving them to GPU, exporting, loading, etc.

  - `nn.Parameter` - A kind of Tensor, that is *automatically registered as a parameter when assigned as an attribute to a* `Module`.

  - `autograd.Function` - Implements *forward and backward definitions of an autograd operation*. Every `Tensor` operation creates at least a single `Function` node that connects to functions that created a `Tensor` and *encodes its history*

### 损失函数

```
#MSE损失
output=net(input)
target=torch.randn(10)
target=target.view(1,-1)
criterion=nn.MSELoss()
loss=criterion(output,target)
print(loss)
```

- 若跟随loss的backward方向，使用.grad_fn属性，可看到计算图：

  ```
  input -> conv2d -> relu -> maxpool2d -> conv2d -> relu -> maxpool2d
        -> view -> linear -> relu -> linear -> relu -> linear
        -> MSELoss
        -> loss
  ```

- So, when we call `loss.backward()`, the whole graph is differentiated w.r.t. the loss, and all Tensors in the graph that has `requires_grad=True` will have their `.grad` Tensor accumulated with the gradient.

  ```
  print(loss.grad_fn)
  print(loss.grad_fn.next_functions[0][0])
  print(loss.grad_fn.next_functions[0][0].next_functions[0][0]) 
  ```

### Backprop

- 需要先清除已有的梯度

  ```
  net.zero_grad() #将所有参数的梯度缓存清零
  print('conv1.bias.grad before backward')
  print(net.conv1.bias.grad)
  
  loss.backward()
  print('conv1.bias.grad after backward')
  print(net.conv1.bias.grad)
  ```

### 更新权重

```
learning_rate=0.01
for f in net.parameters():
	f.data.sub_(f.grad.data*learning_rate)
```

```
import torch.optim as optim
optimizer=optim.SGD(net.parameters(),lr=0.01)

#in training loop
optimizer.zero_grad()  #需要手动将梯度清零
output=net(input)
loss=criterion(output,target)
loss.backward()
optimizer.step()
```

## 训练一个分类器

- 将数据转化为tensors

  - For images, packages such as Pillow, OpenCV are useful
  - For audio, packages such as scipy and librosa
  - For text, either raw Python or Cython based loading, or NLTK and SpaCy are useful

- 一个通用的包torchvision,   that has data loaders for common datasets such as Imagenet, CIFAR10, MNIST, etc. and data transformers for images, viz.,`torchvision.datasets` and `torch.utils.data.DataLoader`.

- CIFAR10例子

  It has the classes: ‘airplane’, ‘automobile’, ‘bird’, ‘cat’, ‘deer’, ‘dog’, ‘frog’, ‘horse’, ‘ship’, ‘truck’. The images in CIFAR-10 are of size 3x32x32

  ```
  import torch
  import torchvision
  import torchvision.transforms as transforms
  ```

  ```
  transform = transforms.Compose(
      [transforms.ToTensor(),
       transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])
  
  trainset = torchvision.datasets.CIFAR10(root='./data', train=True,
                                          download=True, transform=transform)
  trainloader = torch.utils.data.DataLoader(trainset, batch_size=4,
                                            shuffle=True, num_workers=2)
  
  testset = torchvision.datasets.CIFAR10(root='./data', train=False,
                                         download=True, transform=transform)
  testloader = torch.utils.data.DataLoader(testset, batch_size=4,
                                           shuffle=False, num_workers=2)
  
  classes = ('plane', 'car', 'bird', 'cat',
             'deer', 'dog', 'frog', 'horse', 'ship', 'truck')
  ```

  ```
  import matplotlib.pyplot as plt
  import numpy as np
  def imshow(img):
  	img=img/2+0.5
  	npimg=img.numpy()
  	plt.imshow(np.transpose(npimg,(1,2,0)))
  	plt.show()
  dataiter=iter(trainloader)
  images,labels=dataiter.next()
  imshow(torchvision.utils.make_grid(images))
  print(' '.join('%5s' % classes[labels[j]] for j in range(4)))
  ```

- 定义一个卷积神经网络，具有三通道

  ```
  import torch.nn as nn
  import torch.nn.functional as F
  
  
  class Net(nn.Module):
      def __init__(self):
          super(Net, self).__init__()
          self.conv1 = nn.Conv2d(3, 6, 5)
          self.pool = nn.MaxPool2d(2, 2)
          self.conv2 = nn.Conv2d(6, 16, 5)
          self.fc1 = nn.Linear(16 * 5 * 5, 120)
          self.fc2 = nn.Linear(120, 84)
          self.fc3 = nn.Linear(84, 10)
  
      def forward(self, x):
          x = self.pool(F.relu(self.conv1(x)))
          x = self.pool(F.relu(self.conv2(x)))
          x = x.view(-1, 16 * 5 * 5)
          x = F.relu(self.fc1(x))
          x = F.relu(self.fc2(x))
          x = self.fc3(x)
          return x
  
  
  net = Net()
  ```
- 定义损失和optimizer
```
import torch.optim as optim
criterion=nn.CrossEntropyLoss()
optimizer=optim.SGD(net.parameters(),lr=0.001,momentum=0.9)
```

- 训练网络

  ```
  for epoch in range(2):
  	running_loss=0.0
  	for i,data in enumerate(trainloader,0):
  		inputs,labels=data
  		optimizer.zero_grad()
  		outputs=net(inputs)
  		loss=criterion(outputs,labels)
  		loss.backward()
  		optimizer.step()
  		
  		running_loss+=loss.item()
  		if i%2000 ==1999:
  			print('[%d, %5d] loss: %.3f' %
                    (epoch + 1, i + 1, running_loss / 2000))
              running_loss = 0.0
  print('Finished Training')
  ```

- 测试数据

  ```
  dataiter = iter(testloader)
  images, labels = dataiter.next()
  
  # print images
  imshow(torchvision.utils.make_grid(images))
  print('GroundTruth: ', ' '.join('%5s' % classes[labels[j]] for j in range(4)))
  outputs = net(images)
  _, predicted = torch.max(outputs, 1)
  print('Predicted: ', ' '.join('%5s' % classes[predicted[j]]
                                for j in range(4)))
  ```

  ```
  correct = 0
  total = 0
  with torch.no_grad():
      for data in testloader:
          images, labels = data
          outputs = net(images)
          _, predicted = torch.max(outputs.data, 1)
          total += labels.size(0)
          correct += (predicted == labels).sum().item()
  
  print('Accuracy of the network on the 10000 test images: %d %%' % (
      100 * correct / total))
  ```

  ```
  class_correct = list(0. for i in range(10))
  class_total = list(0. for i in range(10))
  with torch.no_grad():
      for data in testloader:
          images, labels = data
          outputs = net(images)
          _, predicted = torch.max(outputs, 1)
          c = (predicted == labels).squeeze()
          for i in range(4):
              label = labels[i]
              class_correct[label] += c[i].item()
              class_total[label] += 1
  
  
  for i in range(10):
      print('Accuracy of %5s : %2d %%' % (
          classes[i], 100 * class_correct[i] / class_total[i]))
  
  ```

- 在GPU上训练

  device=torch.device("cuda:0" if torch.cuda.is_available() else  "cpu")

  print(device)

  - 这些方法将递归遍历所有模块并将其参数和缓冲区转换为CUDA张量

    ```
    net.to(device)
    inputs, labels = inputs.to(device), labels.to(device)
    ```

### 定义新的autograd functions

- In PyTorch we can easily define our own autograd operator by defining a subclass of `torch.autograd.Function` and implementing the `forward` and `backward` functions. We can then use our new autograd operator by constructing an instance and calling it like a function, passing Tensors containing input data

  ```
  import torch
  
  
  class MyReLU(torch.autograd.Function):
      """
      We can implement our own custom autograd Functions by subclassing
      torch.autograd.Function and implementing the forward and backward passes
      which operate on Tensors.
      """
  
      @staticmethod
      def forward(ctx, input):
          """
          In the forward pass we receive a Tensor containing the input and return
          a Tensor containing the output. ctx is a context object that can be used
          to stash information for backward computation. You can cache arbitrary
          objects for use in the backward pass using the ctx.save_for_backward method.
          """
          ctx.save_for_backward(input)
          return input.clamp(min=0)
  
      @staticmethod
      def backward(ctx, grad_output):
          """
          In the backward pass we receive a Tensor containing the gradient of the loss
          with respect to the output, and we need to compute the gradient of the loss
          with respect to the input.
          """
          input, = ctx.saved_tensors
          grad_input = grad_output.clone()
          grad_input[input < 0] = 0
          return grad_input
  
  
  dtype = torch.float
  device = torch.device("cpu")
  # device = torch.device("cuda:0") # Uncomment this to run on GPU
  
  # N is batch size; D_in is input dimension;
  # H is hidden dimension; D_out is output dimension.
  N, D_in, H, D_out = 64, 1000, 100, 10
  
  # Create random Tensors to hold input and outputs.
  x = torch.randn(N, D_in, device=device, dtype=dtype)
  y = torch.randn(N, D_out, device=device, dtype=dtype)
  
  # Create random Tensors for weights.
  w1 = torch.randn(D_in, H, device=device, dtype=dtype, requires_grad=True)
  w2 = torch.randn(H, D_out, device=device, dtype=dtype, requires_grad=True)
  
  learning_rate = 1e-6
  for t in range(500):
      # To apply our Function, we use Function.apply method. We alias this as 'relu'.
      relu = MyReLU.apply
  
      # Forward pass: compute predicted y using operations; we compute
      # ReLU using our custom autograd operation.
      y_pred = relu(x.mm(w1)).mm(w2)
  
      # Compute and print loss
      loss = (y_pred - y).pow(2).sum()
      print(t, loss.item())
  
      # Use autograd to compute the backward pass.
      loss.backward()
  
      # Update weights using gradient descent
      with torch.no_grad():
          w1 -= learning_rate * w1.grad
          w2 -= learning_rate * w2.grad
  
          # Manually zero the gradients after updating weights
          w1.grad.zero_()
          w2.grad.zero_()
  ```

  

## 与Tensorflow的区别

- Pytorch是动态的计算图，Tensorflow是静态的计算图

  在Tensorflow中，只定义计算图一次，而在Pytorch中，每一个forward操作都定义一个新的计算图

  静态图可以节约优化资源，

  ```
  import tensorflow as tf
  import numpy as np
  
  # First we set up the computational graph:
  
  # N is batch size; D_in is input dimension;
  # H is hidden dimension; D_out is output dimension.
  N, D_in, H, D_out = 64, 1000, 100, 10
  
  # Create placeholders for the input and target data; these will be filled
  # with real data when we execute the graph.
  x = tf.placeholder(tf.float32, shape=(None, D_in))
  y = tf.placeholder(tf.float32, shape=(None, D_out))
  
  # Create Variables for the weights and initialize them with random data.
  # A TensorFlow Variable persists its value across executions of the graph.
  w1 = tf.Variable(tf.random_normal((D_in, H)))
  w2 = tf.Variable(tf.random_normal((H, D_out)))
  
  # Forward pass: Compute the predicted y using operations on TensorFlow Tensors.
  # Note that this code does not actually perform any numeric operations; it
  # merely sets up the computational graph that we will later execute.
  h = tf.matmul(x, w1)
  h_relu = tf.maximum(h, tf.zeros(1))
  y_pred = tf.matmul(h_relu, w2)
  
  # Compute loss using operations on TensorFlow Tensors
  loss = tf.reduce_sum((y - y_pred) ** 2.0)
  
  # Compute gradient of the loss with respect to w1 and w2.
  grad_w1, grad_w2 = tf.gradients(loss, [w1, w2])
  
  # Update the weights using gradient descent. To actually update the weights
  # we need to evaluate new_w1 and new_w2 when executing the graph. Note that
  # in TensorFlow the the act of updating the value of the weights is part of
  # the computational graph; in PyTorch this happens outside the computational
  # graph.
  learning_rate = 1e-6
  new_w1 = w1.assign(w1 - learning_rate * grad_w1)
  new_w2 = w2.assign(w2 - learning_rate * grad_w2)
  
  # Now we have built our computational graph, so we enter a TensorFlow session to
  # actually execute the graph.
  with tf.Session() as sess:
      # Run the graph once to initialize the Variables w1 and w2.
      sess.run(tf.global_variables_initializer())
  
      # Create numpy arrays holding the actual data for the inputs x and targets
      # y
      x_value = np.random.randn(N, D_in)
      y_value = np.random.randn(N, D_out)
      for _ in range(500):
          # Execute the graph many times. Each time it executes we want to bind
          # x_value to x and y_value to y, specified with the feed_dict argument.
          # Each time we execute the graph we want to compute the values for loss,
          # new_w1, and new_w2; the values of these Tensors are returned as numpy
          # arrays.
          loss_value, _, _ = sess.run([loss, new_w1, new_w2],
                                      feed_dict={x: x_value, y: y_value})
          print(loss_value)
  ```

## nn模块

  - The `nn` package defines a set of **Modules**, which are roughly equivalent to neural network layers. A Module receives input Tensors and computes output Tensors, but may also hold internal state such as Tensors containing learnable parameters. The `nn` package also defines a set of useful loss functions that are commonly used when training neural networks.

    ```
    import torch
    
    # N is batch size; D_in is input dimension;
    # H is hidden dimension; D_out is output dimension.
    N, D_in, H, D_out = 64, 1000, 100, 10
    
    # Create random Tensors to hold inputs and outputs
    x = torch.randn(N, D_in)
    y = torch.randn(N, D_out)
    
    # Use the nn package to define our model as a sequence of layers. nn.Sequential
    # is a Module which contains other Modules, and applies them in sequence to
    # produce its output. Each Linear Module computes output from input using a
    # linear function, and holds internal Tensors for its weight and bias.
    model = torch.nn.Sequential(
        torch.nn.Linear(D_in, H),
        torch.nn.ReLU(),
        torch.nn.Linear(H, D_out),
    )
    
    # The nn package also contains definitions of popular loss functions; in this
    # case we will use Mean Squared Error (MSE) as our loss function.
    loss_fn = torch.nn.MSELoss(reduction='sum')
    
    learning_rate = 1e-4
    for t in range(500):
        # Forward pass: compute predicted y by passing x to the model. Module objects
        # override the __call__ operator so you can call them like functions. When
        # doing so you pass a Tensor of input data to the Module and it produces
        # a Tensor of output data.
        y_pred = model(x)
    
        # Compute and print loss. We pass Tensors containing the predicted and true
        # values of y, and the loss function returns a Tensor containing the
        # loss.
        loss = loss_fn(y_pred, y)
        print(t, loss.item())
    
        # Zero the gradients before running the backward pass.
        model.zero_grad()
    
        # Backward pass: compute gradient of the loss with respect to all the learnable
        # parameters of the model. Internally, the parameters of each Module are stored
        # in Tensors with requires_grad=True, so this call will compute gradients for
        # all learnable parameters in the model.
        loss.backward()
    
        # Update the weights using gradient descent. Each parameter is a Tensor, so
        # we can access its gradients like we did before.
        with torch.no_grad():
            for param in model.parameters():
                param -= learning_rate * param.grad
    ```

## optim模块

```
import torch

# N is batch size; D_in is input dimension;
# H is hidden dimension; D_out is output dimension.
N, D_in, H, D_out = 64, 1000, 100, 10

# Create random Tensors to hold inputs and outputs
x = torch.randn(N, D_in)
y = torch.randn(N, D_out)

# Use the nn package to define our model and loss function.
model = torch.nn.Sequential(
    torch.nn.Linear(D_in, H),
    torch.nn.ReLU(),
    torch.nn.Linear(H, D_out),
)
loss_fn = torch.nn.MSELoss(reduction='sum')

# Use the optim package to define an Optimizer that will update the weights of
# the model for us. Here we will use Adam; the optim package contains many other
# optimization algoriths. The first argument to the Adam constructor tells the
# optimizer which Tensors it should update.
learning_rate = 1e-4
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
for t in range(500):
    # Forward pass: compute predicted y by passing x to the model.
    y_pred = model(x)

    # Compute and print loss.
    loss = loss_fn(y_pred, y)
    print(t, loss.item())

    # Before the backward pass, use the optimizer object to zero all of the
    # gradients for the variables it will update (which are the learnable
    # weights of the model). This is because by default, gradients are
    # accumulated in buffers( i.e, not overwritten) whenever .backward()
    # is called. Checkout docs of torch.autograd.backward for more details.
    optimizer.zero_grad()

    # Backward pass: compute gradient of the loss with respect to model
    # parameters
    loss.backward()

    # Calling the step function on an Optimizer makes an update to its
    # parameters
    optimizer.step()
```

## 一般的nn模块

- Sometimes you will want to specify models that are more complex than a sequence of existing Modules; for these cases you can define your own Modules by subclassing `nn.Module` and defining a `forward` which receives input Tensors and produces output Tensors using other modules or other autograd operations on Tensors.

  ```
  import torch
  
  
  class TwoLayerNet(torch.nn.Module):
      def __init__(self, D_in, H, D_out):
          """
          In the constructor we instantiate two nn.Linear modules and assign them as
          member variables.
          """
          super(TwoLayerNet, self).__init__()
          self.linear1 = torch.nn.Linear(D_in, H)
          self.linear2 = torch.nn.Linear(H, D_out)
  
      def forward(self, x):
          """
          In the forward function we accept a Tensor of input data and we must return
          a Tensor of output data. We can use Modules defined in the constructor as
          well as arbitrary operators on Tensors.
          """
          h_relu = self.linear1(x).clamp(min=0)
          y_pred = self.linear2(h_relu)
          return y_pred
  
  
  # N is batch size; D_in is input dimension;
  # H is hidden dimension; D_out is output dimension.
  N, D_in, H, D_out = 64, 1000, 100, 10
  
  # Create random Tensors to hold inputs and outputs
  x = torch.randn(N, D_in)
  y = torch.randn(N, D_out)
  
  # Construct our model by instantiating the class defined above
  model = TwoLayerNet(D_in, H, D_out)
  
  # Construct our loss function and an Optimizer. The call to model.parameters()
  # in the SGD constructor will contain the learnable parameters of the two
  # nn.Linear modules which are members of the model.
  criterion = torch.nn.MSELoss(reduction='sum')
  optimizer = torch.optim.SGD(model.parameters(), lr=1e-4)
  for t in range(500):
      # Forward pass: Compute predicted y by passing x to the model
      y_pred = model(x)
  
      # Compute and print loss
      loss = criterion(y_pred, y)
      print(t, loss.item())
  
      # Zero gradients, perform a backward pass, and update the weights.
      optimizer.zero_grad()
      loss.backward()
      optimizer.step()
  ```

## 动态图的例子

```
import random
import torch


class DynamicNet(torch.nn.Module):
    def __init__(self, D_in, H, D_out):
        """
        In the constructor we construct three nn.Linear instances that we will use
        in the forward pass.
        """
        super(DynamicNet, self).__init__()
        self.input_linear = torch.nn.Linear(D_in, H)
        self.middle_linear = torch.nn.Linear(H, H)
        self.output_linear = torch.nn.Linear(H, D_out)

    def forward(self, x):
        """
        For the forward pass of the model, we randomly choose either 0, 1, 2, or 3
        and reuse the middle_linear Module that many times to compute hidden layer
        representations.

        Since each forward pass builds a dynamic computation graph, we can use normal
        Python control-flow operators like loops or conditional statements when
        defining the forward pass of the model.

        Here we also see that it is perfectly safe to reuse the same Module many
        times when defining a computational graph. This is a big improvement from Lua
        Torch, where each Module could be used only once.
        """
        h_relu = self.input_linear(x).clamp(min=0)
        for _ in range(random.randint(0, 3)):
            h_relu = self.middle_linear(h_relu).clamp(min=0)
        y_pred = self.output_linear(h_relu)
        return y_pred


# N is batch size; D_in is input dimension;
# H is hidden dimension; D_out is output dimension.
N, D_in, H, D_out = 64, 1000, 100, 10

# Create random Tensors to hold inputs and outputs
x = torch.randn(N, D_in)
y = torch.randn(N, D_out)

# Construct our model by instantiating the class defined above
model = DynamicNet(D_in, H, D_out)

# Construct our loss function and an Optimizer. Training this strange model with
# vanilla stochastic gradient descent is tough, so we use momentum
criterion = torch.nn.MSELoss(reduction='sum')
optimizer = torch.optim.SGD(model.parameters(), lr=1e-4, momentum=0.9)
for t in range(500):
    # Forward pass: Compute predicted y by passing x to the model
    y_pred = model(x)

    # Compute and print loss
    loss = criterion(y_pred, y)
    print(t, loss.item())

    # Zero gradients, perform a backward pass, and update the weights.
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
```
## 迁移学习

- **Finetuning the convnet**: Instead of random initializaion, we initialize the network with a pretrained network, like the one that is trained on imagenet 1000 dataset. Rest of the training looks as usual.

- **ConvNet as fixed feature extractor**: Here, we will freeze the weights for all of the network except that of the final fully connected layer. This last fully connected layer is replaced with a new one with random weights and only this layer is trained.

  ```
  # License: BSD
  # Author: Sasank Chilamkurthy
  
  from __future__ import print_function, division
  
  import torch
  import torch.nn as nn
  import torch.optim as optim
  from torch.optim import lr_scheduler
  import numpy as np
  import torchvision
  from torchvision import datasets, models, transforms
  import matplotlib.pyplot as plt
  import time
  import os
  import copy
  
  plt.ion()   # interactive mode
  
  # Data augmentation and normalization for training
  # Just normalization for validation
  data_transforms = {
      'train': transforms.Compose([
          transforms.RandomResizedCrop(224),
          transforms.RandomHorizontalFlip(),
          transforms.ToTensor(),
          transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
      ]),
      'val': transforms.Compose([
          transforms.Resize(256),
          transforms.CenterCrop(224),
          transforms.ToTensor(),
          transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
      ]),
  }
  
  data_dir = 'data/hymenoptera_data'
  image_datasets = {x: datasets.ImageFolder(os.path.join(data_dir, x),
                                            data_transforms[x])
                    for x in ['train', 'val']}
  dataloaders = {x: torch.utils.data.DataLoader(image_datasets[x], batch_size=4,
                                               shuffle=True, num_workers=4)
                for x in ['train', 'val']}
  dataset_sizes = {x: len(image_datasets[x]) for x in ['train', 'val']}
  class_names = image_datasets['train'].classes
  
  device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
  
  def imshow(inp, title=None):
      """Imshow for Tensor."""
      inp = inp.numpy().transpose((1, 2, 0))
      mean = np.array([0.485, 0.456, 0.406])
      std = np.array([0.229, 0.224, 0.225])
      inp = std * inp + mean
      inp = np.clip(inp, 0, 1)
      plt.imshow(inp)
      if title is not None:
          plt.title(title)
      plt.pause(0.001)  # pause a bit so that plots are updated
  
  
  # Get a batch of training data
  inputs, classes = next(iter(dataloaders['train']))
  
  # Make a grid from batch
  out = torchvision.utils.make_grid(inputs)
  
  imshow(out, title=[class_names[x] for x in classes])
  
  ```

  - 训练一个model

    ```
    def train_model(model, criterion, optimizer, scheduler, num_epochs=25):
        since = time.time()
    
        best_model_wts = copy.deepcopy(model.state_dict())
        best_acc = 0.0
    
        for epoch in range(num_epochs):
            print('Epoch {}/{}'.format(epoch, num_epochs - 1))
            print('-' * 10)
    
            # Each epoch has a training and validation phase
            for phase in ['train', 'val']:
                if phase == 'train':
                    scheduler.step()
                    model.train()  # Set model to training mode
                else:
                    model.eval()   # Set model to evaluate mode
    
                running_loss = 0.0
                running_corrects = 0
    
                # Iterate over data.
                for inputs, labels in dataloaders[phase]:
                    inputs = inputs.to(device)
                    labels = labels.to(device)
    
                    # zero the parameter gradients
                    optimizer.zero_grad()
    
                    # forward
                    # track history if only in train
                    with torch.set_grad_enabled(phase == 'train'):
                        outputs = model(inputs)
                        _, preds = torch.max(outputs, 1)
                        loss = criterion(outputs, labels)
    
                        # backward + optimize only if in training phase
                        if phase == 'train':
                            loss.backward()
                            optimizer.step()
    
                    # statistics
                    running_loss += loss.item() * inputs.size(0)
                    running_corrects += torch.sum(preds == labels.data)
    
                epoch_loss = running_loss / dataset_sizes[phase]
                epoch_acc = running_corrects.double() / dataset_sizes[phase]
    
                print('{} Loss: {:.4f} Acc: {:.4f}'.format(
                    phase, epoch_loss, epoch_acc))
    
                # deep copy the model
                if phase == 'val' and epoch_acc > best_acc:
                    best_acc = epoch_acc
                    best_model_wts = copy.deepcopy(model.state_dict())
    
            print()
    
        time_elapsed = time.time() - since
        print('Training complete in {:.0f}m {:.0f}s'.format(
            time_elapsed // 60, time_elapsed % 60))
        print('Best val Acc: {:4f}'.format(best_acc))
    
        # load best model weights
        model.load_state_dict(best_model_wts)
        return model
    ```

    ```
    def visualize_model(model, num_images=6):
        was_training = model.training
        model.eval()
        images_so_far = 0
        fig = plt.figure()
    
        with torch.no_grad():
            for i, (inputs, labels) in enumerate(dataloaders['val']):
                inputs = inputs.to(device)
                labels = labels.to(device)
    
                outputs = model(inputs)
                _, preds = torch.max(outputs, 1)
    
                for j in range(inputs.size()[0]):
                    images_so_far += 1
                    ax = plt.subplot(num_images//2, 2, images_so_far)
                    ax.axis('off')
                    ax.set_title('predicted: {}'.format(class_names[preds[j]]))
                    imshow(inputs.cpu().data[j])
    
                    if images_so_far == num_images:
                        model.train(mode=was_training)
                        return
            model.train(mode=was_training)
    ```

- Finetuning the convnet, Load a pretrained model and reset final fully connected layer.

  ```
  model_ft = models.resnet18(pretrained=True)
  num_ftrs = model_ft.fc.in_features
  model_ft.fc = nn.Linear(num_ftrs, 2)
  
  model_ft = model_ft.to(device)
  
  criterion = nn.CrossEntropyLoss()
  
  # Observe that all parameters are being optimized
  optimizer_ft = optim.SGD(model_ft.parameters(), lr=0.001, momentum=0.9)
  
  # Decay LR by a factor of 0.1 every 7 epochs
  exp_lr_scheduler = lr_scheduler.StepLR(optimizer_ft, step_size=7, gamma=0.1)
  ```

  - 训练和评估

    ```
    model_ft = train_model(model_ft, criterion, optimizer_ft, exp_lr_scheduler,
                           num_epochs=25)
    ```

    ```
    visualize_model(model_ft)
    ```

- ConvNet as fixed feature extractor

  we need to freeze all the network except the final layer. We need to set `requires_grad == False`to freeze the parameters so that the gradients are not computed in `backward()`

  ```
  model_conv = torchvision.models.resnet18(pretrained=True)
  for param in model_conv.parameters():
      param.requires_grad = False
  
  # Parameters of newly constructed modules have requires_grad=True by default
  num_ftrs = model_conv.fc.in_features
  model_conv.fc = nn.Linear(num_ftrs, 2)
  
  model_conv = model_conv.to(device)
  
  criterion = nn.CrossEntropyLoss()
  
  # Observe that only parameters of final layer are being optimized as
  # opposed to before.
  optimizer_conv = optim.SGD(model_conv.fc.parameters(), lr=0.001, momentum=0.9)
  
  # Decay LR by a factor of 0.1 every 7 epochs
  exp_lr_scheduler = lr_scheduler.StepLR(optimizer_conv, step_size=7, gamma=0.1)
  ```

  - ### Train and evaluate

    ```
    model_conv = train_model(model_conv, criterion, optimizer_conv,
                             exp_lr_scheduler, num_epochs=25)
    ```

    ```
    visualize_model(model_conv)
    
    plt.ioff()
    plt.show()
    ```

## Saving and Loading Model

1. [torch.save](https://pytorch.org/docs/stable/torch.html?highlight=save#torch.save): Saves a serialized object to disk. This function uses Python’s [pickle](https://docs.python.org/3/library/pickle.html) utility for serialization. Models, tensors, and dictionaries of all kinds of objects can be saved using this function.
2. [torch.load](https://pytorch.org/docs/stable/torch.html?highlight=torch%20load#torch.load): Uses [pickle](https://docs.python.org/3/library/pickle.html)’s unpickling facilities to deserialize pickled object files to memory. This function also facilitates the device to load the data into (see [Saving & Loading Model Across Devices](https://pytorch.org/tutorials/beginner/saving_loading_models.html#saving-loading-model-across-devices)).
3. [torch.nn.Module.load_state_dict](https://pytorch.org/docs/stable/nn.html?highlight=load_state_dict#torch.nn.Module.load_state_dict): Loads a model’s parameter dictionary using a deserialized *state_dict*. For more information on *state_dict*, see [What is a state_dict?](https://pytorch.org/tutorials/beginner/saving_loading_models.html#what-is-a-state-dict).
   - A *state_dict* is simply a Python dictionary object that maps each layer to its parameter tensor

```
# Define model
class TheModelClass(nn.Module):
    def __init__(self):
        super(TheModelClass, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = self.pool(F.relu(self.conv1(x)))
        x = self.pool(F.relu(self.conv2(x)))
        x = x.view(-1, 16 * 5 * 5)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return x

# Initialize model
model = TheModelClass()

# Initialize optimizer
optimizer = optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

# Print model's state_dict
print("Model's state_dict:")
for param_tensor in model.state_dict():
    print(param_tensor, "\t", model.state_dict()[param_tensor].size())

# Print optimizer's state_dict
print("Optimizer's state_dict:")
for var_name in optimizer.state_dict():
    print(var_name, "\t", optimizer.state_dict()[var_name])
```

- Save/Load state_dict

  ```
  torch.save(model.state_dict(), './model/test_model.pt')
  ```

  ```
  model = TheModelClass(*args, **kwargs)
  model.load_state_dict(torch.load('./model/test_model'))
  model.eval()
  ```

  - Remember that you must call `model.eval()` to set dropout and batch normalization layers to evaluation mode before running inference. Failing to do this will yield inconsistent inference results.

- Save/Load整个模型

  ```
  torch.save(model, './model/model_2.pt')
  ```

  ```
  model = torch.load('./model/model_2.pt')
  model.eval()
  ```

  

- 计算两个tensor矩阵之间的矩阵距离

  ```
  def guassian_kernel(source, target, kernel_mul=2.0, kernel_num=5, fix_sigma=None):
      n_samples = int(source.size()[0])+int(target.size()[0])
      total = torch.cat([source, target], dim=0)
      total0 = total.unsqueeze(0).expand(int(total.size(0)), int(total.size(0)), int(total.size(1)))
      total1 = total.unsqueeze(1).expand(int(total.size(0)), int(total.size(0)), int(total.size(1)))
      L2_distance = ((total0-total1)**2).sum(2)   #sum at the 2 dimension
  	return L2_distance
  ```

- 采用numpy计算两个矩阵之间的距离矩阵

  ```
  def distance(source,target):
      num_test=source.shape[0]
      num_train=target.shape[0]
      dists=np.zeros((num_test,num_train))
      dists+=np.sum(target**2,axis=1).reshape(1,num_train)
      dists+=np.sum(source**2,axis=1).reshape(num_test,1)
      dists-=2*np.dot(source,target.T)
      return dists
  ```

- 网络模块参数定制

  为不同的子网络参数设置不同的学习率，finetune常用

  ```
  # # 直接对不同的网络模块制定不同学习率
  optimizer = optim.SGD([{'params': net.features.parameters()}, # 默认lr是1e-5
                         {'params': net.classifiter.parameters(), 'lr': 1e-2}], lr=1e-5)
  ```

  

- LeakyReLU()

- nn.BCELoss()

  适用于多目标分类, input: X --> (N, *), Y --> (N, *),  Y元素的值只能是０或１的float值

  ![](/home/leiwang/Pictures/013.png)

- torchvision.utils.save_image(tensor, filename, nrow=8, padding=2, normalize=False, range=None, scale_each=False)
  将给定的Tensor保存成image文件。如果给定的是mini-batch tensor，那就用make-grid做成雪碧图，再保存

- torch.manual_seed(args.seed)  
  为CPU设置种子用于生成随机数，以使得结果是确定的

- torch.cuda.manual_seed(args.seed)
  为当前GPU设置随机数种子

- nn.Softmax()

  ![](/home/leiwang/Pictures/2018092810574029.png)

- nn.logSoftmax()

  ![](/home/leiwang/Pictures/2018092811014249.png)

- 如果某一个variable的`volatile`属性被设为True，那么所有依赖它的节点`volatile`属性都为True。volatile属性为True的节点不会求导，volatile的优先级比`requires_grad`高。

- nn.CrossEntropyLoss()

  This criterion combines `nn.LogSoftmax()` and `nn.NLLLoss()` in one single class.

​        loss(*x*,*c**l**a**s**s*)=−log(∑*j*exp(*x*[*j*])exp(*x*[*c**l**a**s**s*]))=−*x*[*c**l**a**s**s*]+log(*j*∑exp(*x*[*j*]))

- torch.save()

- torch.load()  可加载存储的模型

- 注意Tensor与非Tensor之间的运算，应先使用item()获得数据后再与非Tensor运算

- cudnn.benchmark

  - 设置这个 flag 可以让内置的 cuDNN 的 auto-tuner 自动寻找最适合当前配置的高效算法，来达到优化运行效率的问题。

- ```
  self.source_encoder_conv = nn.Sequential()
  self.source_encoder_conv.add_module('conv_pse1', nn.Conv2d(in_channels=3, out_channels=32, kernel_size=5,padding=2))
  self.source_encoder_conv.add_module('ac_pse1', nn.ReLU(True))
  self.source_encoder_conv.add_module('pool_pse1', nn.MaxPool2d(kernel_size=2, stride=2))
  ```

- nn.Sequential

  - A sequential container. Modules will be added to it in the order they are passed in the constructor. Alternatively, an ordered dict of modules can also be passed in

- from torch.autograd import Function

  - 虽然pytorch可以自动求导，但是有时候一些操作是不可导的，这时候你需要自定义求导方式。也就是所谓的 “Extending torch.autograd”. 

  - 扩展torch.autograd.Function

  - ```python
    import torch.autograd.Function as Function
    class LinearFunction(Function):
    　  # 创建torch.autograd.Function类的一个子类
        # 必须是staticmethod
        @staticmethod
        # 第一个是ctx，第二个是input，其他是可选参数。
        # ctx在这里类似self，ctx的属性可以在backward中调用。
        # 自己定义的Function中的forward()方法，所有的Variable参数将会转成tensor！因此这里的input也是tensor．在传入forward前，autograd engine会自动将Variable unpack成Tensor。
        def forward(ctx, input, weight, bias=None):
            print(type(input))
            ctx.save_for_backward(input, weight, bias) # 将Tensor转变为Variable保存到ctx中
            output = input.mm(weight.t())  # torch.t()方法，对2D tensor进行转置
            if bias is not None:
                output += bias.unsqueeze(0).expand_as(output)　＃unsqueeze(0) 扩展处第0维
                # expand_as(tensor)等价于expand(tensor.size()), 将原tensor按照新的size进行扩展
            return output
    
        @staticmethod
        def backward(ctx, grad_output): 
            # grad_output为反向传播上一级计算得到的梯度值
            input, weight, bias = ctx.saved_variables
            grad_input = grad_weight = grad_bias = None
            # 分别代表输入,权值,偏置三者的梯度
            # 判断三者对应的Variable是否需要进行反向求导计算梯度
            if ctx.needs_input_grad[0]:
                grad_input = grad_output.mm(weight) # 复合函数求导，链式法则
            if ctx.needs_input_grad[1]:
                grad_weight = grad_output.t().mm(input)　# 复合函数求导，链式法则
            if bias is not None and ctx.needs_input_grad[2]:
                grad_bias = grad_output.sum(0).squeeze(0)
    
            return grad_input, grad_weight, grad_bias
    
    #建议把新操作封装在一个函数中
    def linear(input, weight, bias=None):
        # First braces create a Function object. Any arguments given here
        # will be passed to __init__. Second braces will invoke the __call__
        # operator, that will then use forward() to compute the result and
        # return it.
        return LinearFunction()(input, weight, bias)#调用forward()
    
    # 或者使用apply方法对自己定义的方法取个别名
    linear = LinearFunction.apply
    
    #检查实现的backward()是否正确
    from torch.autograd import gradcheck
    # gradchek takes a tuple of tensor as input, check if your gradient
    # evaluated with these tensors are close enough to numerical
    # approximations and returns True if they all verify this condition.
    input = (Variable(torch.randn(20,20).double(), requires_grad=True),)
    test = gradcheck(LinearFunction(), input, eps=1e-6, atol=1e-4)
    print(test)  #　没问题的话输出True
    ```

  - apply

    - **apply** *(function, args[, kwargs])*
    - Required. The function argument must be a callable object (a user-defined or built-in function or method, or a class object).

    