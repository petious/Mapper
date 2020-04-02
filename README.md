# Mapper
Route planning program (Paris subway network): computes the best travel itinerary between two stations. 

The `s.csv` is the offcial list of every subway stations, and `c.csv` the official list of connections.

Run the MakeFile, then type into command line the type of search (if you wish to identify the stations by name or id), then the name/id of the start station and the name/id of the end station, as followed :

`./my_prog "s.csv" "c.csv" name START_STATION_NAME END_STATION_NAME` 

for example : `./mon_prog "s.csv" "c.csv" name voltaire poisoniere`


result :

```
voltaire not found. Best match : Voltaire (Léon Blum)
poisoniere not found. Best match : Poissonnière

Best way from Voltaire (Léon Blum) (line 9) to Poissonnière (line 7) : 

Take line 9 (PONT DE SEVRES <-> MAIRIE DE MONTREUIL) - Retour
From Voltaire (Léon Blum) to République (316 s)
Walk to République, line 5 (105 s)
Take line 5 (BOBIGNY - PABLO PICASSO <-> PLACE D'ITALIE) - Aller
From République to Gare de l'Est (Verdun) (271 s)
Walk to Gare de l'Est (Verdun), line 7 (15 s)
Take line 7 (LA COURNEUVE - 8 MAI 1945 <-> VILLEJUIF-L. ARAGON / MAIRIE D'IVRY) - Retour
From Gare de l'Est (Verdun) to Poissonnière (141 s)

After 848 seconds, you've reached your destination !
```

