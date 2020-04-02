# Mapper
Route planning program (Paris subway network)

The s.csv is the offcial list of every subway stations, and c.csv the official list of connections.

Run the MakeFile, then type into command line the type of search (if you wish to identify the stations by name or id from which station to which you would like to travel, as followed :

./my_prog "s.csv" "c.csv" name START_STATION_NAME END_STATION_NAME

for example : ./my_prog "s.csv" "c.csv" voltaire bastille


result :

voltaire not found. Best match : Voltaire (Léon Blum)

bastille not found. Best match : Bastille

Best way from Voltaire (Léon Blum) (line 9) to Bastille (line 8) : 

Take line 9 (PONT DE SEVRES <-> MAIRIE DE MONTREUIL) - Retour

From Voltaire (Léon Blum) to Oberkampf (208 s)

Walk to Oberkampf, line 5 (98 s)

Take line 5 (BOBIGNY - PABLO PICASSO <-> PLACE D'ITALIE) - Aller

From Oberkampf to Bastille (320 s)

Walk to Bastille, line 8 (180 s)

