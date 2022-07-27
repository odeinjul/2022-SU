# Note - Week3
## Classification with Logistic Regression
### Binary classification
It is a type of classification where the data is divided into two groups: **positive** and **negative** (1 or 0, yes or no ...etc).

One way: apply linear regression to the data, add a threshold to get the decision boundary.(Often don't work well)

## Logistic regression
### Sigmoid function
Want outputs between 0 and 1. Sigmoid function is also called logistic function.

$$g(z) = \frac{1}{1+e^{-z}}, 0 < g(z) < y $$

### Model
$$ z = \vec{w} \cdot \vec{x} + b $$
let
$$f_{\vec{w},b}(z) = g(z) = \frac{1}{1+e^{-(\vec{w}\cdot\vec{x}+b)}} = P(y=1|\vec{x};\vec{w},b)$$
It means the probability of $y$ being 1, given the input $\vec x$ and parameters $\vec w, b$.
$$P(y=1)+P(y=0) = 1 $$

### Decision boundary
A common choice is 0.5, so if $f(z)\geq 0.5$, also means $z = \vec{w}\cdot\vec{x}+b \geq 0$, then the prediction $\hat y =1$.

Otherwise, if$z = \vec{w}\cdot\vec{x} +b<0$, then the prediction is $\hat y = 0$.

**z = $\vec{w}\cdot\vec{x}+b$ = 0** is the decision boundary.

Combinated with polynomial regression, we can get other types(non-linear) decision boundaries(with $x^n$ or $x^{\frac{1}{n}}$).

### Cost function for logistic regression
>**Definition Note:**   In this course, these definitions are used:  
**Loss** is a measure of the difference of a single example to its target value while the  
**Cost** is a measure of the losses over the training set

The square error function used in cost functio nis non-convex in logistic regression, so other forms should be choosed.

Let the loss function be:
$$L(f_{\vec{w},b}(\vec{x}^{(i)}),y^{(i)}) = -log(f_{\vec{w},b}(\vec{x}^{(i)})), if\space y^{(i)}=1$$
$$L(f_{\vec{w},b}(\vec{x}^{(i)}),y^{(i)}) = -log(1 - f_{\vec{w},b}(\vec{x}^{(i)})), if\space y^{(i)}=0$$

The loss function above can be rewritten to be easier to implement.
$$L(f_{\mathbf{w},b}(\mathbf{x}^{(i)}), y^{(i)}) = (-y^{(i)} \log\left(f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right) - \left( 1 - y^{(i)}\right) \log \left( 1 - f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right)$$

and then the cost function is:
$$J(\vec{w},b) = \frac{1}{m} \sum_{i=1}^{m} L(f_{\vec{w},b}(\vec{x}^{(i)}),y^{(i)})$$

this cost function will be convex so that gradient descent can be used to find the minimum(It does not have plateaus, local minima, or discontinuities. ).

Use the simplified version of the loss function, we can get the cost function:

$$J(\vec{w},b) = -\frac{1}{m}{\sum^{m-1}_0}\left[ y^{(i)} \log\left(f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right) + \left( 1 - y^{(i)}\right) \log \left( 1 - f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right)\right]$$