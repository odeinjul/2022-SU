# Recommmender systems
## Collaborative filtering
### Making recommendations
* $n_u$ = no. of users, $n_m$ no. of items, $n$ no. of item features, $m^{(j)}$ the no. of items j-th user rated.
* $r(i,j)$ if user i rated item j, $y^{(i,j)}$ the rating, $x^{(i)}$ the i-th item's features.

### Using per-term features
* Predict user j's rating for item i as $w^{(j)}\cdot x^{(i)}+b^{(j)}$ (Linear regression)

To learn w, b, use 
**Cost Function**:
$$\min J(w^{(j)},b^{(j )}) = \frac{1}{2}\sum_{i:r(i,j)=1}(w^{(j)}\cdot x^{(i)}+b^{(j)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{k=1}^n(w_k^{(j)})^2$$

To learn w, b for all users, use:
$$\min J(w,b) = \frac{1}{2}\sum_{j=1}^{n_u}\sum_{i:r(i,j)=1}(w^{(i)}\cdot x^{(i)}+b^{(j)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{j=1}^{n_u}\sum_{k=1}^n(w_k^{(j)})^2$$

### Collaborative filtering learning algorithm
No features, just use the rating of other users to predict the rating of a user.

Given parameters and ratings, try to guess the features best fit the ratings.

To learn x(i), use **Cost Function**
$$\min J(x^{(i)}) = \frac{1}{2}\sum_{j:r(i,j)=1}(w^{(j)}\cdot x^{(i)}+b^{(j)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{k=1}^n(x_k^{(i)})^2$$

To leran x for all features, use:
$$\min J(x^{(i)}) = \frac{1}{2}\sum_{i=1}^{n_m}\sum_{j:r(i,j)=1}(w^{(j)}\cdot x^{(i)}+b^{(j)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{i=1}^{n_m}\sum_{k=1}^n(x_k^{(i)})^2$$

**Collaborative filtering learning algorithm**
Putting together:
$$\min J(w,b,x) = \frac{1}{2}\sum_{(i,j):r(i,j)=1}(w^{(i)}\cdot x^{(i)}+b^{(j)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{j=1}^{n_u}\sum_{k=1}^n(w_k^{(j)})^2+\frac{\lambda}{2}\sum_{i=1}^{n_m}\sum_{k=1}^n(x_k^{(i)})^2$$

Use gradient descent to minimize the cost function.

### Binary labels: favs, likes and clicks.
Predict the probility of $y^{(i,j)} = 1$:
Use: $g(w^{(j)}\cdot x^{(i)}+b^{(j)})$, $g = \frac{1}{1+e^{-z}}$

Loss function (Binary cross-entropy loss function):
$$L(f(x),y)=-y^{(i,j)}\log(f(x))-(1-y^{(i,j)})\log(1-f(x))$$

Cost function:
$$J(w,b,x) = \sum_{(i,j):r(i,j)=1} L(f(x),y)$$

## Implemention details
### Mean normalization
Compute the mean of each feature $\mu$, and subtract it from the feature. And when predicting, add it back.

### Tensor flow
Auto Diff
```
w = tf.Varible(3.0)
...
with tf.GradientTape() as tape:
    fwb = w*x
    costJ = (fwb - y) ** 2
[dJdw] tape.gradient(costJ, [w])
w.assign_add(-alpha * dJdw)
```
Adam optimizer
```
optimizer = keras.optimizers.Adam(learning_rate=0.01)
...
with tf.GradientTape() as tape:
    cost_value = cofiCostFuncV(X, W, b, Ynorm, R, num_users, num_movies, lambda)

grads = tape.gradient(cost_value, [X, W, b])

optimizer.apply_gradients(zip(grads, [X, W, b]))
```
### Finding related items
Find the most similar item k with item i, whose feature $x^{(k)} makes the minimum of the distance between $x^{(k)}$ and $x^{(i)}$.

## Content based filtering
$v_u^{(j)}, v_m^{(i)}$ are vectors computed from $x_u^{(j)}, x_m^{(i)}$, should be the same size.

### Deep learning
User network, movie network, their output layers should be the same size.

$g(v_u^{(i)} \cdot v_m^{(j)})$ to predict the probility of $y^{(i,j)} = 1$.

Cost function: $J = \sum_{(i,j):r(i,j)=1}(v_u^{(i)}\cdot v_m^{(j)} - y^{(i,j)})^2 + NR$

Find the similar movies with movie i, whose feature $v_m^{(k)}$ makes the minimum of the distance between $v_m^{(k)}$ and $v_m^{(i)}$.

### Recommender system from a large catalog
* Retrieve and ranking
  - Retrieve: find the most relevant items
  - Ranking: train models only on the retrieved items