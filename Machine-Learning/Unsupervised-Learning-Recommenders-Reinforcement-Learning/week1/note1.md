# Clustering and anomaly detection
Unsupervised learning: only input x, no labels y. 
## Clustering
### K-means intuition
Choose k centroids randomly, assign each point to the closest centroid, then move the centroids to the mean of the points assigned to it. Repeat until convergence.

* Initialize K cluster centroids: $\mu_1, ... \mu_K$
* Repeat:
  * \# assign points to closer cluster centroids
  * for(i = 1 to m)
    * $$c^{(i)} := j \text{ that minimizes } ||x^{(i)} - \mu_j||^2$$  
  * \# move cluseter centroids to the mean of the points assigned to it
  * for(j = 1 to K)
    * $$\mu_j := \frac{1}{\left|c^{(i)} = j\right|} \sum_{c^{(i)} = j} x^{(i)}$$

if any cluster is empty, then eliminate it and reassign the points to the remaining clusters.

### K-means optimization objective
Cost function (distortion function):
$$J(c^{(1)},...,c^{(m)},\mu_1,...,\mu\_k = \frac{1}{m}\sum_{i=1}^m{||x^{(i)}-\mu_{c^{(i)}}||^2}$$
Fix $\mu_1,...,\mu_K$, minimize $J$ over $c^{(1)},...,c^{(m)}$.
Then, fix $c^{(1)},...,c^{(m)}$, minimize $J$ over $\mu_1,...,\mu_K$.
The cost function should never increase, and choose to stop when it decrease very slowly.

### Initializing K-means
Choose K < m, then randomly **pick K training examples** as initial centroids.

Use multiple initials and choose the best one based on cost function.

### Choosing the number of clusters
**Elbow method**
Find the bend point of the J-K curve, where the decrease of J slows down.

Or evaluate K-mean based on how well it performs for that later purpose.

## Anomaly detection
**Density estimation**, get p(x), and test if p(x_test) smller than epsilon, then it is an anomaly.

### Gaussian（normal) distribution
x is a distributed Gaussian with mean $\mu$ and variance $\sigma^2$. p(x) stands for the probability of x.
$$p(x)=\frac{1}{\sqrt{2\pi}\sigma}e^{\frac{-(x-\mu)^2}{2\sigma^2}}$$

Estimate $\mu$, $\sigma$ using the dataset.

### Algorithm
$$p(x) = p(x_1;\mu_1,\sigma_1^2)*p(x_2;\mu_2,\sigma_2^2)*...*p(x_n;\mu_n,\sigma_n^2) = \Pi_{j=1}^{n}p(x_j;\mu_j,\sigma_j^2)$$

Steps:
* Choose features
* Compute $\mu_j, \sigma_j^2$
* Get p(x)
* Compare p(x) with epsilon

### Evaluating & Developing
Real-number evaluation: Assuming we have some labeled data.
* Training set, assume all are normal
  * Compute p(x) based on gaussian distribution.
* Cross validation set, with some anomalies
  * Tune the epsilon using the F1 score (Skewed data).
* (Test set), with some anomalies 
  * Score the model.

### Compare
* Anomaly detection: 
  * Very small number of anomalies (0..20)
  * Large number of normals
  * Future anomalies may be different from the past
* Supervised learning:
  * Large number of anomalies
  * Large number of normals
  * Future anomalies are likely to be similar to the past

### Choose features
* Non-Gaussian features
  * Use feature transformation
* Error analysis
  * Manually examine examples that are incorrectly classified
  * See if there are obvious trends
  * See if there are obvious features that could help