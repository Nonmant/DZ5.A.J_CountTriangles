#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "3\n"
                "0 0\n"
                "2 2\n"
                "-2 2"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "1"
    );
}

TEST_CASE("test 2", ""){
    std::stringstream input(
            "4\n"
            "0 0\n"
            "1 1\n"
            "1 0\n"
            "0 1"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "4"
    );
}

TEST_CASE("2 symmetric", ""){
    std::stringstream input(
            "4\n"
            "0 0\n"
            "2 2\n"
            "2 -2\n"
            "5 -3\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
            "2"
    );
}
