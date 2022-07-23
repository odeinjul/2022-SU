# Note - Week 1
## Classification
* Supervised Machine Learning: 
  
    Input have "right answers"
    -   Classification model: predicts categories / small numbers of outputs
    -   Regression model: predicts numbers / infinite numbers of outputs
* Unsupervised Machine Learning:
  
    Input don't have labels.
    -   Clustering model
    -   Dimensionality reduction model
    -   Dimensionality expansion model

## Linear Regression Model Terminology
* Training set
* x = input varible / input feature
* y = output varible / output target
* m = number of training examples
* (x, y) = single training example
* $(x^{(i)}, y^{(i)})$ = $i^{th}$ training example / specific row in the table
* $\hat y$: the prediction of y
* f: hypothesis function: the model

## Linear Regression Model with One Varible
or *univariate linear regression model*

$f_{w,b}(x) = wx + b$  or  $f(x)$

## Cost function
Error: $\hat y - y$

Cost funtcion:$J(w,b) = \frac{\sum\limits^{m-1}_0 (\hat y^{(i)} - y^{(i)})^2 }{2m}=\frac{\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})^2 }{2m}$  

Goal: $\mathop{minimize}\limits_{w,b} \space J(w,b)$

## Gradient Descent
* Start with some $w,b$
* Keep changing $w,b$ to reduce J(w,b)
* (Look around to find the deepest gradient, and repeat the process)

## Gradient Descent Algorithm
* Initialize $w,b$
* $w = w - \alpha \frac{\partial J(w,b)}{\partial w}$
* $b = b - \alpha \frac{\partial J(w,b)}{\partial b}$
  * $\alpha$ is the learning rate between 0 and 1
* **Simultaneously update $w,b$**
* Repeat until convergence

If $\alpha$ is too small, the algorithm will converge slowly.

If $\alpha$ is too large, the algorithm may never converge, even diverge.

Can reach local minimum with fixed learning rate.

Near a local minimum, derivative becomes smaller, update steps become smaller.

## Gradient Descent for Linear Algorithm
Linear -> cost function is convex -> can use gradient descent to reach the only global minimum.


$repeate\space until\space converge:${
$$
w = w - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})x^{(i)}
\newline
b = b - \alpha \frac{1}{m}\sum\limits^{m-1}_0 (f_{(w,b)}(x^{(i)}) - y^{(i)})$$
}

"**Batch**" Gradient Descent, **Batch**: each step of gradient descent is using all training examples. 
