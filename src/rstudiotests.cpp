// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <osrm/osrm.hpp>
#include <osrm/libosrm_config.hpp>

// [[Rcpp::export]]
std::string osrmc_minexample(double startlat, double startlng, double endlat, double endlng) {

        std::string jsonstring;
        libosrm_config lib_config;

        OSRM routing_machine(lib_config);

        jsonstring = "Finished!";

        return jsonstring;
}
