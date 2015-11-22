# osrmrcpp
Implementation of OSRM C++ API in R.

# Summary
This package is used for testing the OSRM C++ API in R for possible future inclusion in [stplanr](https://github.com/ropensci/stplanr).
The functions included in the package are minimal examples to test the concept and do not include any error checking.

# Building and running
Building this package requires the OSRM library to be installed as well as all its dependencies (boost, etc.).
The included Makevars file has been written for Linux and will (very likely) not run on Windows.

Running the functions require that you run osrm-datastore first to load the network and make it accessible by the API.

# Other details
The OSRM functions appear to crash RStudio in Ubuntu 15.10 (although not Ubuntu 14.04) but work properly when using R directly.
