# -*- coding: utf-8 -*-
"""
Skript for automate feeding of the algorithms and analyzing their data
"""

import Points
import subprocess


def main():
    
    # Parameter (Später noch über schleifen)
    inputfile = "Data/Subsamples/bank/bankSample-0.csv"
    outputfolder = "Data/OutputData/Autoanalyzer/bank/Sample0/"
    outputfile = "bank0"
    maxCluster = 100
    
    # Shellcommand zusammensetzen
    command = f"cd .. && ./AlgFeeder.sh -i {inputfile} -o {outputfolder} -n {outputfile} -c {maxCluster}"
    
    #print(command)
    
    # Prozess erzeugen
    process = bash_command(command)
    # Prozess starten
    process.communicate()
    
    # Wenn man die Ausgabe als String haben will
    # outputString = process.communicate()[0]

    # TO-DO: Analyse der Radien
    
    return



# Kapselung des Bashcommands, der das mit der Shell regelt
def bash_command(cmd): 
    return subprocess.Popen(cmd, shell=True, executable='/bin/bash')





main()
