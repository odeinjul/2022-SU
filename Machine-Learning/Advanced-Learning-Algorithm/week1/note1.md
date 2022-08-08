# Neurons and the brain
## Nerual networks intuition
### Biological neuron
input(dendrites) -> nucleus -> output(axon) / activations - activation numbers
### Demand prediction 
**Layer**: Serval neurons, takes same or similar inputs and output some numbers.

**Output Layer**: the final layer

**Hidden Layer**: middle layer

**Input Layer $\vec{x}$**: the first layer, consists serval numbers

**Output $\vec{a}  / a$**: also called activation

$$\vec{x} \text{(input layer)} \rightarrow \text{hidden layers}\rightarrow \vec{a} \rightarrow \text{output layer}\rightarrow a$$
Use superscript to represent the layer.
$$\text{layer 0}^{[0]}\rightarrow\text{layer 1}^{[1]}\rightarrow...$$
Activations are higher level features. 

Each neuron($\vec{w}_j^{[i]},b_j^{[i]}$) just perform logic operation on the input, output:
$$a_j^{[l]}=g(\vec{w}_j^{[l]}\cdot \vec{a}^{[l-1]}+b_j^{[l]})\space(\vec{x} = \vec{a}^{[0]})\space(f(\vec{x}) = \vec{a}^{[n]})$$

Activation of the layer: $\vec{a}^{[i]} = \{a_1^{[i]},a_2^{[i]} ...a_n^{[i]} \}$

sigmoid => activation function

**Predicts / Inference (Forward Propagation)**

## Tensorflow Implementation    
Use *Dense* layer, like this.

$$\texttt{layer\_1 = Dense(units = 25, activation = 'sigmoid')}\\\texttt{a1 = layer\_1(x)}$$

Note the differences between numpy and tensorflow.
* numpy [1-D vector]
* tensorflow [[2-D Matrix]]

Another way to implement:
$$\texttt{layer\_1 = Dense(units = 25, activation = 'sigmoid')}\\
\texttt{layer\_2 = Dense(units = 10, activation = 'sigmoid')}\\
\texttt{model = Sequential([layer\_1, layer\_2])}\\
\texttt{model.compile(...)}\\
\texttt{model.fit(x, y)}\\
\texttt{model.predict(x\_new)}$$

## Neural Network Implementation in Python
* Forward prop in a single layer for each neuron
* General implementation
$$\texttt{def Dense(a\_in, W, b, g)}\\
\texttt{def sequential(x)}
$$

## Vectorization
* Save weights for a single neuron in the same column.
* Use 2D array for anything and $\texttt{np.matmul}$ or $\texttt{@}$ .