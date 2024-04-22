# -*- coding: utf-8 -*-
"""
Splitting Test-Pipeline into pieces

In This file. The Algorithms are Executed and the Test-Data is written into files
"""
import subprocess
import time


def makeAlgorithms(outputFolder = "Data/OutputData/Final/AnalyzedSubsamples/", maxCluster = 15, 
                   numOfSamples = 5, algs = ["g", "r", "f"], 
                   processBar = False):
    
    # Parameter (Später noch über schleifen)
    
    
    # # # Binary Kompilieren
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
        safeTimestampData(timestamps);
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
        print(f"# = # = # = Cluster made for Sample: {inputfile} = # = # = #")
    
    return algoTimer

def safeTimestampData(timestamps):
    # TO-DO
    return
