//
//  TestClassFille.hpp
//  ProjetCpp
//
//  Created by Océane Staron on 09/04/2019.
//  Copyright © 2019 Océane Staron. All rights reserved.
//

#ifndef TestClassFille_hpp
#define TestClassFille_hpp

#include <stdio.h>
#pragma once

//#include "Generic_station_parser.hpp"
//#include "Generic_connection_parser.hpp"
#include "Generic_mapper.hpp"

using namespace std;

class Mapper : public travel::Generic_mapper{
    private :
    virtual uint64_t min_distance(unordered_map<uint64_t, uint64_t> couts_chemins, unordered_map<uint64_t, bool> visited_station);
    
    protected :
    
    virtual void read_stations(const string& _filename) ;
    virtual void read_connections(const string& _filename) ;
    
    //generic mapper virtual functions
    
    virtual vector<pair<uint64_t,uint64_t> > compute_travel(uint64_t _start, uint64_t _end) ;
    virtual vector<pair<uint64_t,uint64_t> > compute_and_display_travel(uint64_t _start, uint64_t _end);
    
   virtual vector<pair<uint64_t,uint64_t> > compute_travel(const string&, const string&){
        throw("Nothing here");
    }
   virtual vector<pair<uint64_t,uint64_t> > compute_and_display_travel(const string&, const string&){
        throw("Nothing here");
    }
    
    void display_travel(vector<pair<uint64_t,uint64_t> > res_vector, uint64_t _start, uint64_t _end);
    
    unsigned int levenshtein_distance(const string& s1, const string& s2);
    
    unsigned int hamming_distance(const string& s1, const string& s2);
    
    string remplace_accents_string(string& s);
    char remplace_accents_char(char c);
    
    vector<string> split(string str, char delimiter);
    
    pair<uint64_t, uint64_t> station_id_from_name(const string& start_station_name,const string& end_station_name);

    
    public :
    
    void run_all(const string& stations_filename,const string& connections_filename,uint64_t _start, uint64_t _end);
    
    void run_all(const string& stations_filename,const string& connections_filename,string& _start_name, string& _end_name);
    

    
};

#endif /* TestClassFille_hpp */
