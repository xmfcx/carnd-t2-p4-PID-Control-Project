# Reflection

> Describe the effect each of the `P`, `I`, `D` components had in your implementation.

`cte` = Cross Track Error
`c_P` = P coefficient
`c_I` = I coefficient
`c_D` = D coefficient
`e_P` = P error
`e_I` = I error
`e_D` = D error

### `P`roportional Error

This error is calculated like `e_P = cte * c_P`.
And it directly affects the error by a proportion. 
It's effect is instantenous relative to the size of our error.

* Making `c_P` too big will cause hard oscillations.
* Making `c_P` too small will cause slow error correction.

Therefore we should set it in such a way that it gracefully steers the wheel while not being too slow.

### `I`ntegral Error

This error is calculated like `e_I += cte * c_I`.
Therefore it grows or shrinks over time relative to our 'cte * c_I'.
This error helps the system get back in track when it is too far off from the
desired target and once things go better, its effect becomes small because system is back on track.

* Makin `c_I` too big will cumultatively increase the error so much and it will overshoot even after fixing
the error. And even when error is fixed, it will overshoot to the other direction. And its cumultative effect
can go so out of hand if car stays out of track for a while.
* Makin `c_I` too small will make its effect too small. And it won't be able to correct the accumulated error
when car is too far off the center. And it will fail to help to his `e_P` brother.

Therefore we should set it in a way that it doesn't do hardcore changes when car is on track and it
fixes the error just enough when we are having a hard turn.

### `D`erivative Error

This error is calculated like `e_D = ( cte - e_P ) * c_P`.
Which is the (change in the error between current and previous states) multiplied by c_P.
This error tells us how fast the `cte` is changing.
And it allows us to 


> Describe how the final hyperparameters were chosen.
