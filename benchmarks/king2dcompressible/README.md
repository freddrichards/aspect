# The King compressible convection benchmark

This folder contains input files for the benchmark from {cite:t}`king:etal:2010`

King, Scott D., et al. (2010): "A community benchmark for 2-D
Cartesian compressible convection in the Earth's mantle."
Geophysical Journal International 180(1), 73-87.

This includes versions for the ALA and TALA approximations for
different values of the Dissipation number `Di` and the Rayleigh
number `Ra`. The complete input file can be found in
[ala.prm](https://github.com/geodynamics/aspect/blob/main/benchmarks/king2dcompressible/ala.prm).
All other input files are generated by the `run_all_models.sh` script.
All models can be started by running

```{code-block} bash
  bash run_all_models.sh
```

To run a model with a specific set of setting you can modify the loops
inside of this script to only generate models you are interested in.

The python script 'get_statistics.py' can extract the relevant statistics
(Nusselt number, root mean square velocity, average temperature,
total shear heating and total adiabatic heating in the last time step)
of several model runs and copy the results to the screen and a
separate file [statistics.txt](statistics.txt). It also prints a figure of the
Nusselt number (heat flux) and convergence rate of the heat flux
postprocessors. You can modify which models are plotted inside
the script.

```{figure-md} fig:king
<img src="king.*" alt="Screenshot"  width="100%"/>

Example convergence of the King benchmark cases with Ra=1e5 and the ALA approximation.
Left panel: Nusselt number over
cell size h. Right panel: Relative error over cell size. Gray lines
indicate the reference values from {cite:t}`king:etal:2010` (left panel) and
theoretical convergence predicted for different convergence orders
(right panel). Dashed lines show a simple
heat flux computed as the gradient of temperature, solid lines show the
heat flux computed using a consistent boundary flux method.
```