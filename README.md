# Mapper
Route planning program (Paris subway network): computes the best travel itinerary between two stations. 

The `s.csv` is the offcial list of every subway stations, and `c.csv` the official list of connections.

Run the MakeFile, then type into command line the type of search (if you wish to identify the stations by name or id), then the name/id of the start station and the name/id of the end station, as followed :

`./my_prog "s.csv" "c.csv" name START_STATION_NAME END_STATION_NAME` 

for example : `./mon_prog "s.csv" "c.csv" name voltaire bastile`


result :

```
voltaire not found. Best match : Voltaire (Léon Blum)
bastile not found. Best match : Bastille

Best way from Voltaire (Léon Blum) (line 9) to Bastille (line 8) : 

Take line 9 (PONT DE SEVRES <-> MAIRIE DE MONTREUIL) - Retour
From Voltaire (Léon Blum) to Oberkampf (208 s)
Walk to Oberkampf, line 5 (98 s)
Take line 5 (BOBIGNY - PABLO PICASSO <-> PLACE D'ITALIE) - Aller
From Oberkampf to Bastille (320 s)
Walk to Bastille, line 8 (180 s)

After 806 seconds, you've reached your destination !
```

