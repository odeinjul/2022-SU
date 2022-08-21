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