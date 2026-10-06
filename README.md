# root-intro-tasks
Introductory root tasks to learn about using histograms and fitting.

Write a root macro that does the following:

1) Create a one dimensional histogram that hold float variables
2) Generate N=1000 random values that are sampled from a gaussian distribution with mean -1 and standard deviation 5 and fill the histogram you created at step 1
3) Fit the histogram with a Gaussian distribution and obtain the mean and sigma, as well as the uncertainties from the fit

Extra
Create a second loop (this is a hint that the above should have a loop) to study the statistical uncertainty of the extracted mean as a function of event number. For this, you need to do the following at each iteration:
- clear the histogram 
- generate N events (where N is different from each iteration - lets say iteration 0 N=1, iteration 1 N=10, iteration 2  N=100, iteration 3 is N=1000, iteration 4 is 10000… up to 6 iterations
- Fit the histogram with a Gaussian distribution and obtain the mean and sigma, as well as their uncertainties from the fit.
- Create a TGraphErrors object that holds the values of the mean and the uncertainties as a function of N.

A quick ROOT guide can be found here: 
[https://root.cern.ch/root/htmldoc/guides/primer/ROOTPrimer.html](https://root.cern.ch/root/htmldoc/guides/primer/ROOTPrimer.html)

The Classes you would need to use are TH1F, TF1, and TRandom3. (for the extra you would also need TGraphErrors class) A lot of info and examples can be found online so dont be shy looking at other examples.
