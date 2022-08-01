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

$$J(\vec{w},b) = -\frac{1}{m}{\sum^{m-1}_{i=0}}\left[ y^{(i)} \log\left(f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right) + \left( 1 - y^{(i)}\right) \log \left( 1 - f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right)\right]$$

## Gradient Descent in Logistic Regression

$repeate\space until\space converge${
$$
w_j = w_j - \alpha \frac{1}{m}\sum\limits^{m-1}_{i=0} (f_{(\vec{w},b)}(\vec{x}^{(i)}) - y^{(i)})x_j^{(i)}
\newline
b = b - \alpha \frac{1}{m}\sum\limits^{m-1}_{i=0} (f_{(\vec{w},b)}(\vec{x}^{(i)}) - y^{(i)})
$$
}

Seems same as linear regression, but $f_{(\vec{w},b)}$ isdifferent from linear regression.
$$f_{\vec{w},b}(z) = \frac{1}{1+e^{-(\vec{w}\cdot\vec{x}+b)}} = P(y=1|\vec{x};\vec{w},b)$$

**Same concepts**:
* Monitor gradient descent (learning curve)
* Vectorized implementation
* Feature Scaling

## Overfitting / Underfitting
**Generalization**: good prediction on new examples

Overfitting(High variance) - Just Right(gerneralization) - Underrfitting(High bias)
Too many features - Just right - Too few features

### Addressing overfitting
* Collect more training data
* Select features to include/exclude
* Regularization - reduce size of parameters 

## Regularzation 
**Intuition**: reduce the size of the parameters, by adding a penalty to the cost function.


* $\lambda = 0$ overfit
* $\lambda >> 1$ underfit
### Regularized Linear Regression
Linear regression cost function (modified):
$$J(w,b) = \frac{1}{2m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})^2 + \frac{\lambda}{2m}\sum\limits^{n-1}_{j=0}w_j^2$$
The second term is called the regularization term (No need to penalize $b$).


$repeate\space until\space converge${
$$
w = w - \alpha [\frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})x^{(i)} + \frac{\lambda}{m}w_j] = w(1-\frac{\lambda}{m}) - \alpha x\frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})x^{(i)}
\newline
b = b - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})\text{ (don't have to regularize b)}$$ 
}

### Regularized Logistic Regression
Logistic regression cost function (modified):
$$J(\vec{w},b) = -\frac{1}{m}{\sum^{m-1}_0}\left[ y^{(i)} \log\left(f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right) + \left( 1 - y^{(i)}\right) \log \left( 1 - f_{\mathbf{w},b}\left( \mathbf{x}^{(i)} \right) \right)\right] + \frac{\lambda}{2m}\sum\limits^{n-1}_{j=0}w_j^2$$

Gradient Descent:

$repeate\space until\space converge${
$$
w = w - \alpha [\frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})x^{(i)} + \frac{\lambda}{m}w_j] = w(1-\frac{\lambda}{m}) - \alpha x\frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})x^{(i)}
\newline
b = b - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})\text{ (don't have to regularize b)}$$ 
}
