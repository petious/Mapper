//
//  TestClassFille.cpp
//  ProjetCpp
//
//  Created by Océane Staron on 09/04/2019.
//  Copyright © 2019 Océane Staron. All rights reserved.
//

#include "Mapper.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <regex>
#include <sstream>
#include <vector>




using namespace std;

void Mapper::read_stations(const std::string& _filename){
    
    travel::Station station;
    string temp;
    int station_id_int;
    string station_id;
    
    
    ifstream infile(_filename.c_str());
    
    if(infile.is_open()==0){
        throw string("Stations file not found.");
    }
    
    //supprime les headers
    getline(infile, temp, '\n');
    
    while (getline(infile, temp, ',')){
        
        station.name = temp;
        
        getline(infile, temp, ',');
        
        station_id = temp;
        
        station_id_int = atoi (station_id.c_str());
        
        getline(infile, temp, ',');
        
        station.line_id = temp;
        
        getline(infile, temp, ',');
        
        station.address = temp;
        
        getline(infile, temp);
        
        station.line_name = temp;
        
        stations_hashmap.insert(make_pair(station_id_int,station));
    }
    
}

void Mapper::read_connections(const string& _filename){
    
    string headers, from, to, time,line;
    int from_int, to_int, time_int,pos;
    ifstream infile(_filename.c_str());
    
    if(infile.is_open()==0){
        throw string("Connections file not found.");
    }
    
    //get rid of the headers
    getline(infile, headers, '\n');
    
    while(getline(infile, line, '\n')){
        
        string delimiter = ",";
        
        pos = (int) line.find(delimiter);
        from = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        
        pos = (int)line.find(delimiter);
        to = line.substr(0,pos);
        line.erase(0, pos + delimiter.length());
        
        pos = (int)line.find(delimiter);
        time = line.substr(0,pos);
        
        from_int = atoi (from.c_str());
        to_int = atoi (to.c_str());
        time_int = atoi (time.c_str());
        
        connections_hashmap[from_int][to_int]=time_int;
        
    }
}

uint64_t Mapper::min_distance(unordered_map<uint64_t, uint64_t> couts_chemins, unordered_map<uint64_t, bool> visited_station) {
    // Initialize min value
    uint64_t min = INT_MAX;
    uint64_t min_index = -1;
    
    for (unordered_map<uint64_t, uint64_t> :: iterator i=couts_chemins.begin() ; i != couts_chemins.end() ; ++i){
        if (visited_station.at(i->first) == false && i->second <= min) {
            min = i->second;
            min_index = i->first;
        }
    }
    return min_index;
}

vector< pair<uint64_t,uint64_t> > Mapper::compute_travel(uint64_t _start, uint64_t _end){
    
    vector< pair<uint64_t,uint64_t> > res_vector;
    int nb_stations = (int)(stations_hashmap.size());
    uint64_t MAX_COUT = INT_MAX;
    unordered_map<uint64_t, uint64_t> couts_chemins;
    unordered_map<uint64_t, uint64_t> prev_station_shortest_path;
    unordered_map<uint64_t, bool> visited_stations;
    
    for (unordered_map<uint64_t, travel::Station > :: iterator i=stations_hashmap.begin() ; i != stations_hashmap.end() ; ++i){
        couts_chemins.insert(make_pair(i->first, MAX_COUT));
        visited_stations.insert(make_pair(i->first, false));
    }
    
    couts_chemins.at(_start) = 0;
    
    for (int i = 0; i < nb_stations; ++i){
        uint64_t current_station_id = min_distance(couts_chemins, visited_stations);
        unordered_map<uint64_t,uint64_t> current_station_connections = connections_hashmap.at(current_station_id);
        
        visited_stations.at(current_station_id) = true;
        
        for (unordered_map<uint64_t,uint64_t> :: iterator j=current_station_connections.begin() ; j != current_station_connections.end() ; ++j){
            
            uint64_t adjacent_station_id = j->first;
            uint64_t cout_adjacent_station = j->second;
            
            if (visited_stations.at(adjacent_station_id) == false &&
                couts_chemins.at(current_station_id) != MAX_COUT &&
                couts_chemins.at(current_station_id) + cout_adjacent_station < couts_chemins.at(adjacent_station_id)) {
                
                couts_chemins.at(adjacent_station_id) = couts_chemins.at(current_station_id) + cout_adjacent_station;
                prev_station_shortest_path[adjacent_station_id] = current_station_id;
            }
        }
    }
    // NOTE: ici on a les valeurs de tous les plus courts chemin de _start à tous les autres
    // + le predecesseur de chaque station dans le plus court chemin qui y mene
    uint64_t current_node_in_path = _end;
    uint64_t previous_station_in_path = prev_station_shortest_path.at(current_node_in_path);
    
    while (previous_station_in_path != _start) {
        res_vector.insert(res_vector.begin(), make_pair(current_node_in_path, couts_chemins.at(current_node_in_path)));
        current_node_in_path = previous_station_in_path;
        previous_station_in_path = prev_station_shortest_path.at(current_node_in_path);
    }
    
    res_vector.insert(res_vector.begin(), make_pair(current_node_in_path, couts_chemins.at(current_node_in_path)));
    res_vector.insert(res_vector.begin(), make_pair(_start, couts_chemins.at(_start)));
    
    return res_vector;
}

void Mapper::display_travel(const vector<pair<uint64_t,uint64_t> > res_vector, uint64_t _start, uint64_t _end){
    
    travel::Station current_station;
    travel::Station prev_station;
    travel::Station end_station;
    travel::Station start_station;
    bool is_on_going_trip = false; //booléen indiquant si on est en cours de trajet sur une même ligne
    int time_change = 0; //temps de changement
    int time_trip = 0; //temps de voyage sur une ligne
    int cumulated_time = 0;//temps cumulé
    int time_start_trip = 0;//valeur du temps général au moment du début du voyage sur une ligne
    start_station = stations_hashmap.at(_start);
    end_station = stations_hashmap.at(_end);
    
    prev_station = start_station;
    
    cout<<"\nBest way from "<< start_station.name << " (line " << start_station.line_id<<")"<<" to "<<end_station.name<<
    " (line " << end_station.line_id<<") : \n"<<endl;
    
    for (vector<pair<uint64_t,uint64_t> > :: const_iterator i = res_vector.begin() ; i != res_vector.end() ; ++i){
        
        current_station = stations_hashmap.at(i->first);
        
        if(current_station.line_id != prev_station.line_id){
            time_change = (int)(i->second) - cumulated_time;
            if(is_on_going_trip){
                time_trip = (int)(i->second) - time_start_trip - time_change;
                cout<<" to "<< current_station.name;
                cout << " ("<<time_trip<<" s)"<<endl;
                is_on_going_trip = false;
            }
            cout<<"Walk to ";
            cout<<current_station.name<< ", line " << current_station.line_id;
            cout << " ("<< time_change <<" s)" <<endl;
        }
        
        //condition sur le temps permet de ne pas afficher les correpondances à 0, sur le nom de la station d'arrivée de ne pas afficher un dernier "faux" voyage
        if( !is_on_going_trip &&  (i->second - cumulated_time) != 0 && current_station.name.compare(end_station.name) !=0){
            cout<<"Take line "<< current_station.line_id<<" "<< current_station.line_name<<endl;
            cout<<"From "<<prev_station.name;
            is_on_going_trip=true;
            time_start_trip = cumulated_time + time_change;
        }
        
        cumulated_time = (int) i->second;
        prev_station = current_station;
    }
    
    if(is_on_going_trip){
        cout<<" to "<< current_station.name;
        time_trip = cumulated_time - time_start_trip;
        cout << " ("<<time_trip<<" s)"<<endl;
    }
    
    cout << "\nAfter " <<cumulated_time<<" seconds, you've reached your destination !" <<endl;
    
}

vector<pair<uint64_t,uint64_t> > Mapper::compute_and_display_travel(uint64_t _start, uint64_t _end){
    
    std::vector<std::pair<uint64_t,uint64_t> > res_vector;
    
    res_vector = compute_travel(_start,_end);
    
    display_travel(res_vector, _start, _end);
    
    return res_vector;
}

pair<uint64_t, uint64_t> Mapper::station_id_from_name(const string& start_station_name,const string& end_station_name){
    
    pair<uint64_t, uint64_t> id_stations;
    travel::Station current_station;
    uint64_t max_distance_start = INT_MAX;
    uint64_t max_distance_end = INT_MAX;
    uint64_t id_station_start = -1, id_station_end = -1;
    uint64_t distance;
    string start_station_name_copy = start_station_name;
    string end_station_name_copy = end_station_name;
    
    //passe toutes les lettres en minuscule
    transform(start_station_name_copy.begin(), start_station_name_copy.end(), start_station_name_copy.begin(), ::tolower);
    transform(end_station_name_copy.begin(), end_station_name_copy.end(), end_station_name_copy.begin(), ::tolower);
    
    for (unordered_map<uint64_t, travel::Station > :: iterator i=stations_hashmap.begin() ; i != stations_hashmap.end() ; ++i){
        current_station = i->second;
        
        string current_station_name_copy = current_station.name;
        transform(current_station_name_copy.begin(), current_station_name_copy.end(), current_station_name_copy.begin(), ::tolower);
        
        //les parties entre parenthèses des noms de stations ne sont pas utilisés couramment, donc pas pertinents. Une autre facon de faire aurait été de splitter le nom de la station puis de comparer mot par mot, mais quelques stations, comme Pont Marie (Cité des Arts) et Cité auraient posé problème.
        int pos = (int)current_station_name_copy.find('(');
        string current_station_name = current_station_name_copy.substr(0,pos);
        
        distance = levenshtein_distance(current_station_name, start_station_name_copy);
        
        if(distance<max_distance_start){
            id_station_start = i->first;
            max_distance_start=distance;
        }
        
        distance = levenshtein_distance(current_station_name, end_station_name_copy);
        
        if(distance<max_distance_end){
            id_station_end = i->first;
            max_distance_end=distance;
        }
    }
    
    //le présent algorithme trouvera la station dont le nom s'approche le plus, donc les exceptions ci-dessous n'arriveront jamais
    if((int)id_station_start == -1){
        throw string("Start station not found at all.");
    }
    if((int)id_station_end == -1){
        throw string("End station not found at all.");
    }
    
    if(start_station_name.compare( stations_hashmap.at(id_station_start).name ) !=0){
        cout<<start_station_name<<" not found. Best match : "<<stations_hashmap.at(id_station_start).name<<endl;
    }
    if(end_station_name.compare( stations_hashmap.at(id_station_end).name ) !=0){
        cout<<end_station_name<<" not found. Best match : "<<stations_hashmap.at(id_station_end).name<<endl;
    }
    
    id_stations.first = id_station_start;
    id_stations.second = id_station_end;
    
    return id_stations;
}

unsigned int Mapper::levenshtein_distance(const string& s1, const string& s2){
    //distance de Levenshtein
    const size_t len1 = s1.size(), len2 = s2.size();
    
    vector<vector<int> > d(len1 + 1, vector<int>(len2 + 1));
    
    d[0][0] = 0;
    for(int i = 1; i <= (int)len1; ++i) d[i][0] = i;
    for(int i = 1; i <= (int)len2; ++i) d[0][i] = i;
    
    for(int i = 1; i <= (int)len1; ++i)
        for(int j = 1; j <= (int)len2; ++j)
            d[i][j] =  min( min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)) ;
    
    return d[len1][len2];
}

unsigned int Mapper::hamming_distance(const string& s1, const string& s2){
    //distance de hamming (non utilisée ici)
    int size_loop, i, distance=0;
    
    if(s1.length() < s2.length()){
        size_loop =(int)s1.length();
    }else{
        size_loop = (int)s2.length();
    }
    
    for(i=0; i < (int)size_loop; i++){
        if( s1[i] != s2[i] ) {
            distance = distance+1;
        }
    }
    return distance;
}

string Mapper::remplace_accents_string(string& s){
    //non utilisée ici
    string res =s;
    int i, j=0;
    char c;
    
    for (i=0; i<(int)s.length(); i++){
        c = s[i];
        cout<<c<<endl;
        if((int)c >= 32 && (int)c < 127 ){
            res.at(j)=c;
            j++;
        }
    }
    return res;
}

vector<string> Mapper::split(string str, char delimiter) {
    //non utilisée ici
    vector<string> internal;
    stringstream ss(str);
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

void Mapper::run_all(const string& stations_filename,const string& connections_filename,string& _start_name, string& _end_name){
    
    vector<pair<uint64_t,uint64_t> > res_vector;
    pair<uint64_t, std::uint64_t> id_stations;
    
    read_stations(stations_filename);
    
    read_connections(connections_filename);
    
    id_stations = station_id_from_name(_start_name, _end_name);
    
    res_vector = compute_and_display_travel(id_stations.first, id_stations.second);
    
}

void Mapper::run_all(const string& stations_filename, const string& connections_filename, uint64_t _start, uint64_t _end){
    
    vector<pair<uint64_t,uint64_t> > res_vector;
    
    read_stations(stations_filename);
    
    if(stations_hashmap.find(_start) == stations_hashmap.end() ){
        throw string("Start station not found in stations file.");
    }
    if(stations_hashmap.find(_end) == stations_hashmap.end() ){
        throw string("End station not found in stations file.");
    }
    
    read_connections(connections_filename);
    
    if(connections_hashmap.find(_start) == connections_hashmap.end() ){
        throw string("Start station not found in connections file.");
    }
    if(connections_hashmap.find(_end) == connections_hashmap.end() ){
        throw string("End station not found in connections file.");
    }
    
    res_vector = compute_and_display_travel(_start, _end);
}
