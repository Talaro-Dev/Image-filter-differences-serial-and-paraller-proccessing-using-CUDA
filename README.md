# Image-filter-differences-serial-and-paraller-proccessing-using-CUDA

In this repository i created two mini projects to remove from jpeg images the red and green color channels using serial and paraller proccessing in order to calculate the differences between those two proccessing methods in order of speed.

Some of the results are:
          Execution time in serial |    Execution time in            |  Image resolution(pixels
          proccessing (sec)        |    parallel proccesing (sec)    |
------------------------------------------------------------------------------------------------
Example 1|        0.353               |         1.409                   |    5088 x 3253
------------------------------------------------------------------------------------------------
Example 2|        0.356               |         0.931                   |    6720 x 4480
------------------------------------------------------------------------------------------------
Example 3|        0.349               |         1.431                   |    4160 x 6240
------------------------------------------------------------------------------------------------
Example 4|        1.218               |         3.360                   |    10929 x 5553
------------------------------------------------------------------------------------------------
Example 5|        2.557               |         7.732                   |    10000 x 10000
------------------------------------------------------------------------------------------------

The delay in parallel proccessing is created because i used WSl and docker in order to detect my GPU.

