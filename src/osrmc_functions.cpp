// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>
#include <osrm/libosrm_config.hpp>
#include <osrm/route_parameters.hpp>
#include "json_renderer.hpp"

// [[Rcpp::export]]
std::string viaroute_osrmc(double startlat, double startlng, double endlat, double endlng) {

    std::vector<char> jsonvector;
    std::string jsonstring;
    int result_code;

    try{

    libosrm_config lib_config;

    //
    /*
    const unsigned init_result = GenerateServerProgramOptions(
        argc, argv, lib_config.server_paths, ip_address, ip_port, requested_thread_num,
        lib_config.use_shared_memory, trial_run, lib_config.max_locations_distance_table,
        max_locations_map_matching);

    if (init_result == INIT_OK_DO_NOT_START_ENGINE)
    {
        return 0;
    }
    if (init_result == INIT_FAILED)
    {
        return 1;
    }
    */

    OSRM routing_machine(lib_config);

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
    route_parameters.coordinates.emplace_back(startlat * COORDINATE_PRECISION,
                                              startlng * COORDINATE_PRECISION);
    // target_coordinate
    route_parameters.coordinates.emplace_back(endlat * COORDINATE_PRECISION,
                                              endlng * COORDINATE_PRECISION);
    osrm::json::Object json_result;
    result_code = routing_machine.RunQuery(route_parameters, json_result);

    osrm::json::render(jsonvector, json_result);
    jsonstring = std::string(jsonvector.data());
    } catch(int x) {

    }

    return jsonstring;
}

// [[Rcpp::export]]
CharacterVector viaroute_osrmcv(NumericVector startlat, NumericVector startlng, NumericVector endlat, NumericVector endlng) {

    //std::string jsonvector;
    std::string jsonstring;
    int result_code;

        CharacterVector resultvec(startlat.size());

        libosrm_config lib_config;

        //
        /*
        const unsigned init_result = GenerateServerProgramOptions(
            argc, argv, lib_config.server_paths, ip_address, ip_port, requested_thread_num,
        lib_config.use_shared_memory, trial_run, lib_config.max_locations_distance_table,
        max_locations_map_matching);

        if (init_result == INIT_OK_DO_NOT_START_ENGINE)
        {
        return 0;
        }
        if (init_result == INIT_FAILED)
        {
        return 1;
        }
        */

        OSRM routing_machine(lib_config);

        for (int count = 0; count < startlat.size(); count++ ) {

            std::vector<char> jsonvector;
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

    return resultvec;
}

