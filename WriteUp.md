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

* Making `c_I` too big will cumultatively increase the error so much and it will overshoot even after fixing
the error. And even when error is fixed, it will overshoot to the other direction. And its cumultative effect
can go so out of hand if car stays out of track for a while.
* Making `c_I` too small will make its effect too small. And it won't be able to correct the accumulated error
when car is too far off the center. And it will fail to help to his `e_P` brother.

Therefore we should set it in a way that it doesn't do hardcore changes when car is on track and it
fixes the error just enough when we are having a hard turn.

### `D`erivative Error

This error is calculated like `e_D = ( cte - e_P ) * c_P` [`e_P` is from the previous step!!].

Which is the (change in the error between current and previous states) multiplied by c_P.

This error tells us how fast the `cte` is changing.
And it allows us to change the adaptive speed of the PID controller.
It helps us to stabilize the PID controller.

* Making `c_P` too big will make the PID controller too slow to react to changes made although it adds 
smoothness through time.

* Making `c_P` too small will make the PID controller jittery, overreactive like it was as if this was 0.

Therefore we should set it in a way that it just adds enough smoothness and stabilization to our error
and not make it too loose.

> Describe how the final hyperparameters were chosen.

I followed the wiki article on manual tuning: https://en.wikipedia.org/wiki/PID_controller#Manual_tuning

Basically considering all the things I have explained in previous question, I tweaked P, I and D one after the other.
Also, I have made another PID controller to control the speed. I can set speed whatever I want and car goes
at that cruise speed by controlling the throttle.

I have realized that different speeds require different PID coefficients. 
Because at higher speeds;

* turns require faster and harder steer actions, requiring `P` and `I` to be higher then average.

* straight roads require lower steering actions and higher `D` coefficient values with smaller `P` and `I`.

So, I tuned my PID controller to be able to go well in 30 to 50 mph. You can play around with the speed_target value in

https://github.com/xmfcx/carnd-t2-p4-PID-Control-Project/blob/master/src/main.cpp#L57

to test it in different speeds. In 50mph it might be a little bit jittery but in 40mph it will be just fine.

I have managed to make it go at 60mph without ever crashing too but it was driving like a madman so I did not include that
here because you would think I didn't set things correctly because of unusual driving behaviour.
