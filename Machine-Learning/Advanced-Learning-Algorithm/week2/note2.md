# Neural Network Training
## Training Details
* Specify the model
* Loss and cost functions
* Gradient Descent 
  * Compute deriavtives using backpropagation (in $\texttt{model.fit()}$)

## Activation Functions
* Linear activation function
  * $\texttt{g(z) = z}$
* Sigmoid function
* ReLU function
  * $\texttt{g(z) = max(0, z)}$
* Softmax function

$z = \vec{w}\cdot\vec{x}+b$
### Choose Activation Function
#### For output layer
* Binary Classification Problem
  * Sigmod function
* Regression Problem
  * Linear activation function
* y non-negative, Regression Problem
  * ReLU function

#### For hidden layers
* Most common choice
  * ReLU function (faster)
  
> Don't use Linear activation function in hidden layers.

## Multiclass Classification
### Softmax Function
$$z_1 = \vec{w_1}\cdot\vec{x}+b_1$$
$$z_2 = \vec{w_2}\cdot\vec{x}+b_2$$
$$z_3 = \vec{w_3}\cdot\vec{x}+b_3$$
$$...$$
$$z_j= \vec{w_j}\cdot\vec{x}+b_j$$
$$a_1 = \frac{e^{z_1}}{e^{z_1}+e^{z_2}+e^{z_3}+...}=P(y=1|\vec{x})$$
$$...$$
$$a_j = \frac{e^{z_j}}{\sum\limits^N_{k=1}e^{z_j}}=P(y=j|\vec{x})$$
> $$a_1+a_2+...+a_N = 1$$

### Loss Function for Softmax Function
Sparse Categorical Crossentropy:
$$loss(a_1, a_2, ..., a_N, y) = \left\{ \begin{align}-log(a_1) \text{if y=1  }\\-log(a_2  ) \text{if y=2    }\\...\\-log(a_N) \text{if y=N  }\\\end{align}\right. $$

$$J(W,b) = \text{average loss}$$

### Neural Network with Softmax Output
Use a Softmax layer as the output layer. It has $N$ units, and will output a probability distribution over $N$ classes (a vector).

$$\vec{a}_{out} =(a_1,..., a_N) = g(z_1,...,z_N) $$
### Implement Softmax Function Better
In order to get more accurate answer in logistic regression, and softmax regression, you can use:
$$\text{output layer: }\texttt{Dense(units = 10, activation = "linear")}$$
$$\texttt{model.compile(loss=BinaryCrossEntropy(from\_logits = true))}$$
$$\texttt{logit = model(X)}$$
$$\texttt{f\_x = tf.nn.softmax(logit)}$$
or
$$\texttt{f\_x = tf.nn.sigmoid(logit)}$$

- Learned the preferred model construction in Tensorflow:
    - No activation on the final layer (same as linear activation)
    - SparseCategoricalCrossentropy loss function
    - use from_logits=True
> When it's possible to overflow, subtract the exponents by the max $z_J$.
> 
> Setting `from_logits=True` as an argument to the loss function specifies that the output activation was linear rather than a softmax.
**Multi-label Classification**
...

## Advanced Neural Network Concept
### Advanced Optimization
* Adam Algorithm, automatically adjust the learning rate.
  * Also different learning rate for every parameter.
  * $w_j,b$ keeps moving in same direction, increase $\alpha$.
  * $w_j,b$ keeps os  cillating, reduce $\alpha$.

$$\texttt{model.compile(optimizer=tf.keras.optimizers.Adam(learning\_rate=1e-3), loss=...)}$$
### Additional Layer Types
* Convolutional layer, each unit only looks at a limited window of the input
  * Faster
  * Need less training data (less prone to overfitting)