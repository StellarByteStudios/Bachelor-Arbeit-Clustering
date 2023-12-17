# Standartwerte
INPUT=False
OUTPUT=Output/
CLUSTER=5
HELP=False
DATANAME=GenericData


# # Kommando-optionen holen # #
#TEMP=$(getopt -o i:o:c:n: --long input:,output:,maxCluster:,help,dataName:)
#TEMP=$(getopt -o i:o:c: --long input:,output:,maxCluster: -- "$@")

while true; do
  case "$1" in
    -i | --input ) INPUT=$2; shift 2;;
    -o | --output ) OUTPUT="$2"; shift 2;;
    -c | --maxCluster ) CLUSTER="$2"; shift 2 ;;
    -n | --dataName ) DATANAME="$2"; shift 2 ;;
    -h | --help ) HELP=True; shift ;;
#    -- ) shift; break ;;
    * ) break ;;
  esac
done



# # Hilfs-Text # # 
if [ $HELP = "True" ]; then
    # echo -e "Hilfe Text wird ausgegeben\nneue zeile mit Text"
    echo -e "    To use this Skript correctly you have to be in the same Folder as the
    Makefile and the Executable.
    Some Parameters have to be given: 
    \t- input-data
    
    Options:
    -i | --input [INPUT-FILE]\t\tFile, where the Data to be Clustered is coming from (required)\n
    -o | --output [OUTPUT-FOLDER]\tFolder, where the Outputdata is saved. If it isn't existing it will be created (Standard: $OUTPUT)\n
    -c | --maxCluster [MAXCLUSTER]\tWhat is the maximum of Clusters to be generated (Standard: $CLUSTER)\n
    -n | --dataName [NAME]\t\tThe Outputfiles are Named \"Clusterdata[NAME]Cluster[i].csv\" (Standard: $DATANAME)\n
    -h | --help \t\t\tgenerates this Help-Output
    "
    # Abbruch, dass programm nicht merh weiter geht
    exit 0
fi


# # Wurde ein Inputfile für die Daten gegeben? # # 
if [ $INPUT = "False" ]; then
    echo -e "Please give Inputfile as Data-Source\nexpl: ./AlgFeeder.sh -i input.csv"
    # Abbruch, dass programm nicht merh weiter geht
    exit 0
fi




# # Für Jede Clusteranzahl Algorithmus aufrufen # #
# sicherheitshalber erst nochmal kompilieren
make build
for (( i=1; i<=$CLUSTER; i++ ))
do  
    # Ausgabe, was gemacht wird
    echo "Berechne Daten mit $i Cluster"
    # Ordner erstellen, da bei Fehlendem Ordner das Clusterprogramm nicht mitmacht
    mkdir -p "$OUTPUT"
    ARGS="$INPUT ""$OUTPUT"Clusterdata"$DATANAME"Cluster"$i".csv" $i"
    #echo $ARGS
    # Programm aufrufen
    ./Fair-Clustering $ARGS
done



#echo "$INPUT"
#echo "$OUTPUT"
#echo "$CLUSTER"
