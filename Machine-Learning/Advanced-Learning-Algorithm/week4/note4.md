# Week4
## Decision tree
* Root node
* Decision node
* Leaf node - prediction

### Learning Process
- Choose featue to split on each node
  - Maximun purity / minmun impurity (entropy to estimize)
- When to stop split
    - Node is 100% one class 
    - When splitting a node will result in the tree exceeding a maximum depth
    - When improvements in purity score are below a threshold    
    - When number of examples in a node is below a threshold

To keep the tree smaller, and avoid over fitting.

### Entropy criteria
Measure impurity using entropy functi on
$p_1$ the fraction of examples that is target.
$$p_0=1-p_1$$
$$H(p_1)=-p_1\log_2(p_1)-p_0\log_2(p_0)$$
$$H(p_1)=-p_1\log_2(p_1)-(1-p_1)\log_2(1-p_1)$$
$$0\log(0) = 0$$

### Choosing a split: Information gain
We can get $H_{left}, H_{right}$, perform a weighted average, and compute the reduction on entropy from unsplitted entropy.
$$H-\frac{n_{left}}{N}H_{left}+\frac{n_{right}}{N}H_{right}$$
Information gain:
$$H(p_1^{root})-w^{left}H(p_1^{left})+w^{right}H(p_1^{right})$$

### Decision tree learning algorithm
root node -> compute information gain (for each feature) -> split -> repeat

#### One hot encoding
Multiple categories -> multiple binary features

#### Continuous valued features
Test threshold at the midpoint of test examples.

#### Continuous prediction
Given a decision tree: 
* predict using the average of the training examples in the leaf node

Generate a decision tree:
* minimize the total weighted variance in each leaf node
* (compute the decrease in variance - information gain)

### Multiple decision trees
Ensemble trees using sampling with replacement. To construct multiple random training sets and train decision trees on it.

#### Random forest
At each node choose a random subset of features to split on.
$$k=\sqrt{n}$$

#### XGBoost
Boosted trees intuition:
More likely to pick examples that the previous trained trees misclassified.

## Choose
Decision tree and tree emsembles are good for:
Faster,
structured data

Neural network is good for:
Slower,
unstructured data