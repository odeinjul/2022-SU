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