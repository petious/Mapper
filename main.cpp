//
//  main.cpp
//  ProjetCpp
//
//  Created by Océane Staron on 09/04/2019.
//  Copyright © 2019 Océane Staron. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Mapper.hpp"
#include <regex>

using namespace std;

int main(int argc, const char * argv[]) {
    
    int start_station, end_station;
    string stations_filename, connections_filename;
    string param;
    
    string start_station_name, end_station_name;
    
    
    if ( argc != 6 ) {
        printf("usage: stations_filename connections_filename SearchParam(name or ID) start_station end_station.\n");
        exit(1);
    }else{
        stations_filename = argv[1];
        connections_filename = argv[2];
        
        param = argv[3];
        
        if(param.compare("ID") == 0 ){
            // conversion chaine de caractere -> nombre entier:
            sscanf( argv[4], "%d", &start_station );
            sscanf( argv[5], "%d", &end_station );
        }else{
            if(param.compare("name") ==0 ){
                start_station_name = argv[4];
                end_station_name = argv[5];
            }else{
                cerr<<"no valid param : ID or name"<<endl;
                exit(1);
            }
        }
    }
    
    Mapper new_mapper;
    
    try{
        if(param.compare("ID") == 0)
            new_mapper.run_all(stations_filename, connections_filename, start_station, end_station);
        if(param.compare("name") == 0 )
            new_mapper.run_all(stations_filename, connections_filename, start_station_name, end_station_name);
    }
    catch(string const& erreur) {
        cerr << "Error : "  <<erreur<< endl;
        exit(1);
    }
    catch(out_of_range) {
        cerr << "Error : key not found."  << endl ;
        exit(1);
    }
    
    
    return 0;
}
