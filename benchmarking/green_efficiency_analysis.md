# Green Efficiency Analysis

## Measurement Methodology

In this project, I tested three C programs to understand how much time they need to run. I used `clock()` to measure CPU time in seconds.
For the first program, `baseline_loop.c`, I ran a loop with 100 million iterations. I executed the program three times and saved the results.
For the second program, `comparison_algorithms.c`, I compared two algorithms. The first algorithm uses two loops, while the second uses only one loop. I ran the program three times to compare their execution times.
For the third program, `instrumentation_lab.c`, I measured three parts of the program: building the data, processing the data, and calculating a checksum. I also measured the total execution time.

## Observed Performance Differences

The first program gave three results: 0.082199, 0.081131, and 0.086966 seconds. The average time was 0.083432 seconds.
The results were not exactly the same, even though the program did the same work each time.
For the second program, the naive algorithm took an average of 0.496473 seconds. The single-pass algorithm took only 0.000016 seconds.
Based on these measurements, the single-pass algorithm was much faster. However, the two algorithms did not give the same result, so this is not a perfect comparison.
For the third program, the total time was 0.000255 seconds.
Building the data took 0.000118 seconds. Processing the data took 0.000091 seconds, and calculating the checksum took 0.000043 seconds.
Building the data was the slowest part of this program.

## Relation Between Runtime and Energy Consumption

A computer uses electricity when it runs programs.
When a program finishes faster, it may use less energy because the processor works for less time.
In my tests, the single-pass algorithm needed much less CPU time than the naive algorithm.
However, I only measured execution time, not electricity consumption. Because of this, I cannot say exactly how much energy was saved.

## Limitations of the Experiment

My experiment has some limits.
First, I only ran the first two programs three times. More tests would help make the results more reliable.
Second, other programs running on the computer can affect execution times.
Third, I did not measure real electricity consumption
Also, the two algorithms in the second test produced different results, which makes the comparison less accurate.
Finally, the third program was measured only once.

## Practical Engineering Takeaway

This project helped me understand why measuring program performance is important.
I learned that using fewer loops can reduce execution time, although the program must still produce the correct result.
I also learned that measuring different parts of a program helps find where time is spent.
In the third program, building the data took the most time.
In the future, I will test my code, compare results, and look for ways to improve performance.
Faster programs may help reduce energy use, but real energy measurements are needed to prove this.
