# Week3 
## Advice for applying machine learning
### Evaluating your model
* training set $(x^{(1)},y^{(1)})$, test set$(x_{test}^{(1)},y_{test}^{(1)})$.
* Linear regression:
  * Cost function: $J_{train}+J_{test}+J_{regularzation}$
* Classify:
  * $J_{train}$ fraction of the train set that has been misclassified.
  * $J_{test}$ fraction of the test set that has been misclassified.

### Model Selection
Unrecommend (fitting d to test set, make the estimation overly optimal):
$$d=i, (w^{<i>},b^{<i>}), J_{test}(w^{<i>},b^{<i>})$$
Commend:
**Split into 3 sets**
* Training set $x_{train}$
* Cross-validation set / dev set $x_{cv}$
* test set $x_{test}$
  
**Then get 3 error**
* J_{train}
* J_{cv}
* J_{test}

**Choose the smallest $J_{cv}$**

**Estimate the generalization error using the test set $J_{test}$**

## Diagnose bias / variance
* High bias  / $J_{train}$ is high
* High variance / $J_{cv}>>J_{train}$
* Just right / $J_{train},J_{cv}$ is low
Also can figure out Regularization on bias / variance.

### A baseline level of performance
* Human level performance
* Competing algorithms performance
* Guess based on experience
Compare $J_{train}-J_{baseline}$, $J_{cv}-J_{train}$, to diagnose bias / variance.

### Learning curve
* High bias / more training data - no use
* High variance / more training data - useful

### Methods to decrease variance
* increase $\lambda$
* more training examples
* smaller set of features

### Methods to decrease bias
* decrease $\lambda$
* additional features
* add polynomial features

### Neural Network and bias / variance
> Large neural network are low bias machines.

* High bias -> bigger neural network (regularize appropriately)
* High variance -> larger dataset

$$\texttt{layer\_1 = Dense(units = 25, activation = 'sigmoid', kernel\_regularizer=L2(0.01))}
$$

## Machine learning development process
* Choose architecture
* Train model
* Diagnostics

### Error analysis
Catagorize errors based on common traits.

### Adding data
#### Data augmentation：
Modify the data by adding noise, rotation, etc.
#### Data synthesis：
Artificial data generation.

### Transfer learning
1. Train on a large dataset **(supervised pretraining)**
2. Transfer its parameters (except the output layer) on a smaller dataset **(fine tuning)**
> Same input size!
* only train output layer parameters
* train all parameters

## Skewed Daraset
### Precision / Recall
Precision matrix:
* True positive
* True negative
* False positive
* False negative

Precision:
$$\frac{\text{true pos}}{\text{true pos + false pos}}$$
Recall:
$$\frac{\text{true pos}}{\text{true pos + false neg}}$$

### Trading off
Raise threshold,
* Higher precision, lower recall.

Decrease threshold,
* Lower precision, higher recall.

#### F1 score
To balance precision and recall,
$$F_1= \frac{1}{\frac{1}{2}(\frac{1}{P}+\frac{1}{R})}=2\frac{PR}{P+R}$$
