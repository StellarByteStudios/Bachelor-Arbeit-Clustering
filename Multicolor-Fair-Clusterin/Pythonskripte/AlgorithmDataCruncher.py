# -*- coding: utf-8 -*-
"""
Splitting Test-Pipeline into pieces

In This file. The Algorithms are Executed and the Test-Data is written into files
"""
import subprocess
import time
import os


# # # Hauptmethode um Algorithmen auszuführen # # #
# # # Triggert das Autofeeder-Skript mit allen 3 Datensätzen # # #
def makeAlgorithms(outputFolder = "Data/OutputData/Final/AnalyzedSubsamples/", maxCluster = 15, 
                   numOfSamples = 5, algs = ["g", "r", "f"], makeCompiling = False,
                   processBar = False):
    
    # # # Binary Kompilieren
    if makeAlgorithms:
        compileBinary(withProcessBar=processBar)
    
    for i in range(0, len(algs)):          
        
        # # # Algorithmus ausführen
        timeBank = do_algorithm("bank", folderPath=outputFolder, numOfSamples=numOfSamples, 
                                maxCluster=maxCluster, algorithm=algs[i])
        timeCensus = do_algorithm("census", folderPath=outputFolder, numOfSamples=numOfSamples, 
                                  maxCluster=maxCluster, algorithm=algs[i])
        timeDiabetes = do_algorithm("diabetes", folderPath=outputFolder, numOfSamples=numOfSamples, 
                                    maxCluster=maxCluster, algorithm=algs[i])
         
        # Muss noch abgespeichert werden
        timestamps = [timeBank, timeCensus, timeDiabetes]
        safeTimestampData(timestamps, outputFolder="../" + outputFolder, algorithm=algs[i]);
    return


# # # Kompiliert die Binary über das Makefile # # #
def compileBinary(withProcessBar=False):
    print("Compiling Binary")
    
    command = "make -C .. build"
    if(withProcessBar):
        command = command + "ProcessBar"
        
    print("Command:", command)
    # Subprozess bauen
    process = bash_command(command, ignoreStdout=False)
    # Prozess starten
    process.communicate()
    
    print("Finished compiling")
    
    return


# Kapselung des Bashcommands, der das mit der Shell regelt
def bash_command(cmd, ignoreStdout = True):
    # stdout wird weggeworfen
    if ignoreStdout:    
        return subprocess.Popen(cmd, shell=True, executable='/bin/bash', stdout=subprocess.DEVNULL)
    # Stdout vom Skript in Pythonkonsole
    return subprocess.Popen(cmd, shell=True, executable='/bin/bash')



# # # Algorithmus sukzessive auf den einzelnen Sampels ausführen und abspeichern # # #
def do_algorithm(samplename, folderPath, numOfSamples = 20, maxCluster = 20, algorithm = "g"):
    # Liste um die Ausführzeiten zu speichern
    algoTimer = []
    
    for i in range(0, numOfSamples):
        # # Bankdaten
        # Pfade algorithmisch zusammensetzen
        # Welcher Algorithmus?
        algPathAdd = "GonzalezClustering"
        if(algorithm == "r"):
            algPathAdd = "RedClustering"
        if(algorithm == "f"):
            algPathAdd = "FastClustering"
        
        inputfile = f"Data/Subsamples/{samplename}/{samplename}Sample-{i}.csv"
        outputfolder = f"{folderPath}{algPathAdd}/{samplename}/Sample{i}/"
        outputfile = f"{samplename}{i}"
        # Shellcommand zusammensetzen
        directoryChange = "cd .."
        feederCommand = f"./AlgFeeder.sh -i {inputfile} -o {outputfolder} -n {outputfile} -c {maxCluster} -a {algorithm}"
        command = directoryChange + " && " + feederCommand
        
        #print(f"Der Bashbefehl wurde zusammengesetzt: {command}")
        
        # Prozess erzeugen
        process = bash_command(command, ignoreStdout=False)
        # Zeitmessung Starten
        startTime = time.process_time_ns();
        # Prozess starten
        process.communicate()
        # Zeitmessung stoppen
        algoTimer.append(time.process_time_ns() - startTime)
        print(f"# = # = # = Cluster made for Sample: {inputfile} with {algPathAdd} = # = # = #")
    
    return algoTimer


# # # Methode um die Zeitstempel als CSV abzuspeichern # # #
def safeTimestampData(timestamps, outputFolder, algorithm="g"):
    # Kopf
    csvToSave = "Sample,BankTime,CensusTime,diabetesTime"  + str('\n');
    
    # einzelne Zeitmessungen übertragen
    for i in range(0, len(timestamps[0])):
        csvToSave = csvToSave + f"{i},{timestamps[0][i]},{timestamps[1][i]},{timestamps[2][i]}" + str('\n')
    
    # Daten abspeichern
    # Welcher Algorithmus?
    algPathAdd = "GonzalezClustering"
    if(algorithm == "r"):
        algPathAdd = "RedClustering"
    if(algorithm == "f"):
        algPathAdd = "FastClustering"
    # Abspeichern
    saveToFile(path=outputFolder, filename=f"{algPathAdd}-TimeStamps.csv", content=csvToSave)
    return



# # # Methode speichert gegebenen String in Datei # # #
def saveToFile(path, filename, content): 
    os.makedirs(path, exist_ok=True) 
    f = open(path + "/" + filename,'w')
    f.write(content)
    f.close()
    return
