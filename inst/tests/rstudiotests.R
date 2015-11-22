# rstudiotests
library(osrmrcpp)

startlat <- runif(1, max=-33.85,min=-33.90)
endlat <- runif(1, max=-33.85,min=-33.90)
startlng <- runif(1, min=151.150,max=151.250)
endlng <- runif(1, min=151.150,max=151.250)

osrmc_minexample(startlat, startlng, endlat, endlng)
