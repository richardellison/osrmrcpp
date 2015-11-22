// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppParallel)]]

#include <Rcpp.h>
#include <RcppParallel.h>
using namespace Rcpp;
using namespace RcppParallel;

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>
#include <osrm/libosrm_config.hpp>
#include <osrm/route_parameters.hpp>
#include "json_renderer.hpp"

struct QueryOsrm : public Worker {

    // source vectors
    const RVector<double> startlat;
    const RVector<double> startlng;
    const RVector<double> endlat;
    const RVector<double> endlng;

    std::vector<std::string> resultvec;

    libosrm_config lib_config;
    //OSRM routing_machine(lib_config);

    QueryOsrm(const NumericVector startlat, const NumericVector startlng, const NumericVector endlat, const NumericVector endlng)
        : startlat(startlat), startlng(startlng), endlat(endlat), endlng(endlng) {
        resultvec.resize(startlat.size());
    }


    void operator()(std::size_t begin, std::size_t end) {

        //libosrm_config lib_config;
        OSRM routing_machine(lib_config);
        std::string jsonstring;
        int result_code;

        for (std::size_t count = begin; count < end; count++ ) {

            std::vector<char> jsonvector;
            //std::vector<std::string> intervec;
            jsonstring = "";

            RouteParameters route_parameters;
            route_parameters.zoom_level = 18;           // no generalization
            route_parameters.print_instructions = false; // turn by turn instructions
            route_parameters.alternate_route = false;    // get an alternate route, too
            route_parameters.geometry = false;           // retrieve geometry of route
            route_parameters.compression = true;        // polyline encoding
            route_parameters.check_sum = -1;            // see wiki
            route_parameters.service = "viaroute";      // that's routing
            route_parameters.output_format = "json";
            route_parameters.jsonp_parameter = ""; // set for jsonp wrapping

            // start_coordinate
            route_parameters.coordinates.emplace_back(startlat[count] * COORDINATE_PRECISION,
                                                      startlng[count] * COORDINATE_PRECISION);
            // target_coordinate
            route_parameters.coordinates.emplace_back(endlat[count] * COORDINATE_PRECISION,
                                                      endlng[count] * COORDINATE_PRECISION);
            osrm::json::Object json_result;
            result_code = routing_machine.RunQuery(route_parameters, json_result);

            osrm::json::render(jsonvector, json_result);
            resultvec[count] = std::string(jsonvector.data());
        }

    }

};

// [[Rcpp::export]]
std::vector<std::string> viaroute_parallel(NumericVector startlat, NumericVector startlng, NumericVector endlat, NumericVector endlng) {

    QueryOsrm queryosrm(startlat, startlng, endlat, endlng);

    parallelFor(0, startlat.size(), queryosrm);

    return queryosrm.resultvec;

}
