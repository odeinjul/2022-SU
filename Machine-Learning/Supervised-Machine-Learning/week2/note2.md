# Note - Week 2
## Multiple Linear Regression
Vectorization: 
$$f_{\vec{w},b}(x) = \vec{w}\cdot\vec{x}+b$$
or in python:
```py
f = np.dot(w, x) + b
```

## Vectorization
* It allows your code to run more easily on parallel compute hardware
* It makes your code run faster
* It can make your code shorter 

### Gradient Descent

$repeate\space until\space converge${
$$
w_j = w_j-\alpha\frac{\partial}{\partial w_j}J(\vec{w},b)
$$
$$
b = b-\alpha\frac{\partial}{\partial b}J(\vec{w},b)
$$
}

or

$repeate\space until\space converge${
$$
w_j = w_j - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(\vec{w},b)}(\vec{x}^{(i)}) - y^{(i)})x_j^{(i)}
\newline
b = b - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(\vec{w},b)}(\vec{x}^{(i)}) - y^{(i)})
$$
}

### An alternative way to gradient descent - normal equation
* Only for linear regression
* Solve for w, b without iterations
* Doesn't generalize to other learning algorithms
* Slow when the number of features is large(>100000)
* may appear in *backend* of some libraries

## Feature Scaling
* Performing transformings on your training data and let them take comparable ranges of values to each other.

### Simply divide the data by the maximum of the data
* $x_j = x_j/x_{j,max}$

### Mean Normalization
* Calculate the mean of each feature
* $x_j = \frac{x_j - \mu_j}{x_{j,max} - x_{j,min}}$
* -1 < x_j < 1

### Z-Score Normalization
* Calculate the mean of each feature
* Calculate the standard deviation of each feature
* $x_j = \frac{x_j - \sigma_j}{\mu_j}$
* x_j between (around) [-1...1]
  
It's always okay to perform rescaling to booster the gradient descent algorithm. Whether the data is too large, too small, or ranging from a wide range of values, it's always okay to rescale the data.

## Checking gradient descent for convergence
### Look at the learning curve
**Learning curve:** J(w,b) vs. iteration number

When the curve levels off, it means the algorithm has converged.

If the curve increases, there may be a bug in the program or the learning rate is too big. So set the learning rate to a relatively small value can test out whether there's bug in the algorithm.

### Automatic convergence test
Let $\epsilon$ be a relatively small value, when J(w,b) decreaces by less than $\epsilon$ in one iteration, the algorithm has converged.

### Advantage
The counter is more likely as a circle, so the result is that updates to parameters during gradient descent can make equal progress for each parameter. In this way, the gradient descent algorithm is faster.

## Choosing the learning rate
Try 0.001 -> 0.003 -> 0.01 -> 0.03 -> 0.1 ...
And find the largest possible learning rate that the algorithm can converge.

If normalized, try 0.1 as a start.

## Feature engineering
Use intuition to design new features by combining or transforming existing features.

## Polynomial Regression
Multiple linear regression + feature engineering. Create new features like $x^n$ or $x^{\sqrt{n}}$ using $x$，and apply multiple linear regression to them.

**Gradient descent is picking the 'correct' features for us by emphasizing its associated parameter, and the best features will be *linear* to  the target.**