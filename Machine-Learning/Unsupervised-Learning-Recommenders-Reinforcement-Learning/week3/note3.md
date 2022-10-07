# Reinforcement Learning
State s -> action a.
Reward function, terminal state.

(R, a, R(S), S')
### The return in reinforcement learning
$Return = R1 + \gamma R2 + \gamma^2 R3...$

$\gamma = 0.9$ Discount factor.
* state
* action
* reward
* discount factor
* return 
* policy

Markov Decision Process

### State action value function
Q(s,a) = the **return** if you:
* start in state s
* take action a (once)
* then behave optimally after that

The best possible action a in state s is the action that gives $\max Q(s,a)$

### Bellman Equation
To compute Q(s,a) we need to know the value of the next state, $Q(s',a')$.

R(s): reward for being in state s.

$$Q(s,a) = R(s) + \gamma \cdot \max Q(s',a')$$

### Random (stochastic) environment (Markov Decision Process)
Expected return = $E[R1+\gamma R_2+\gamma^2 R_3+...]$

$$Q(s,a) = R(s) + \gamma \cdot E[\max Q(s',a')]=R(s)+\gamma\cdot E[Q(s')]$$

### Continuous state spaces
e.g: $s = (x,y,\theta,\dot x, \dot y, \dot \theta)$

### Lunar lander
$s = (x,y,\dot x, \dot y, \theta, \dot \theta, l,r)$

Reward function: Landing, crashing, flying...

To learn a policy $\pi$, to pick an action $a=\pi(s)$ to maximize the expected return. Using $\gamma = 0.985$

### Learning the state-value function
Initialize $Q(s,a)$ randomly as a guess.

Repeat:
* Take action and get (s, a, R(s), s').
* Store 10,000 most recent (s, a, R(s), s') tuples (replay buffer).

* Train neural network:
  * Create training set of 10,000 examples using x = (s, a) and y = R(s) + $\gamma \cdot \max Q(s',a')$.
  * Train $Q_{new}$ such that $Q_{new}(s,a)$ is close to y.
* Set Q = Q_new.

### $\epsilon$-greedy policy
* 0.95 - pick a that maximizes Q(s,a)
* 0.05 - pick a randomly

### Minibatch, soft update
* Minibatch, each iteration only looks at a small part of the large dataset.
* Soft update, each iteration only updates a small part of the neural network.
  * $Q = 0.01\cdot Q_{new} + 0.99\cdot Q_{old}$