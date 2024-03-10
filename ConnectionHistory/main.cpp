//  Created by Charles Kerr on 3/9/24.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <filesystem>
#include <string>

#include "ConnectionStatus.hpp"
using namespace std::string_literals ;

int main(int argc, const char * argv[]) {
    auto exitcode = EXIT_SUCCESS ;
    
    try {
        auto connectionLog = std::filesystem::path() ;
        auto clientName = std::string() ;
        
        if (argc <= 1) {
            throw std::runtime_error("No connection log was provided.") ;
        }
        connectionLog = std::filesystem::path(argv[1]);
        auto connectionStatus = ConnectionStatus(connectionLog);
        if (argc <= 2) {
            // we where given a connection log, but no client hname, give back all the client names available
            std::cout << "No client name was provided, options are: " << std::endl;
            auto keys = connectionStatus.keys() ;
            for (const auto &entry: keys) {
                std::cout << "\t" << entry << std::endl;
            }
            
        }
        else {
            clientName = argv[2] ;
            if (!connectionStatus.contains(clientName)) {
                std::cout << "No history found for: " << clientName << std::endl;
            }
            else {
                auto history = connectionStatus[clientName] ;
                auto count = history.size() ;
                std::cout << "There are " << count << " entries for: " << clientName << std::endl;
                for (auto i = count -1; i >= 0; i -= 1 ) {
                    std::cout << "\t" <<  history[i].describe() << std::endl;
                }
            }
        }
        
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exitcode = EXIT_FAILURE ;
    }
    catch (...) {
        std::cerr << "Unknown Error" << std::endl;
        exitcode = EXIT_FAILURE ;
    }
    return exitcode;
}
