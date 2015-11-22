library(osrmrcpp)
library(microbenchmark)
library(RCurl)

startlat <- runif(1000, max=-33.85,min=-33.90)
endlat <- runif(1000, max=-33.85,min=-33.90)
startlng <- runif(1000, min=151.150,max=151.250)
endlng <- runif(1000, min=151.150,max=151.250)

runcpp <- function(startlat, startlng, endlat, endlng) {
    i <- 1
    j <- length(startlat)
    while (i <= j) {
        testdata <- viaroute_osrmc(startlat[i],startlng[i],endlat[i],endlng[i])
        i <- i + 1
    }
    rm(testdata)
    gc()
}
runcppv <- function(startlat, startlng, endlat, endlng) {
        testdata <- viaroute_osrmcv(startlat,startlng,endlat,endlng)
        rm(testdata)
        gc()
}
runcppvp <- function(startlat, startlng, endlat, endlng) {
    testdata <- viaroute_parallel(startlat, startlng, endlat, endlng)
    rm(testdata)
    gc()
}

runhttp <- function(startlat, startlng, endlat, endlng) {
    i <- 1
    j <- length(startlat)
    while (i <= j) {
        testdata <- getURL(paste0("http://127.0.0.1:5000/viaroute?loc=",
                      startlat[i],
                      ",",
                      startlng[i],"&loc=",
                      endlat[i],",",
                      endlng[i],"&instructions=false&alt=false&geometry=false"))
        i <- i + 1
    }
    rm(testdata)
    gc()
}

benchoutput <- microbenchmark(
    runhttp(startlat, startlng, endlat, endlng),
    runcpp(startlat, startlng, endlat, endlng),
    runcppv(startlat, startlng, endlat, endlng),
    runcppvp(startlat, startlng, endlat, endlng),
    times=10
)
