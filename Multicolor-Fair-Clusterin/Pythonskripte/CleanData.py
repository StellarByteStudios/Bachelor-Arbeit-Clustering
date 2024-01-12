# -*- coding: utf-8 -*-
"""
Skript to roughly analyse given Data by Chierichetti and divide it
into usable subsamples
"""

import pandas as pd
import os 
import shutil



def main():
    
    # # # Daten einlesen # # #
    # Pfade Hardcoden
    pathRawCensus = "../Data/Raw-Chierichetti/census/adult.data"
    pathRawBank = "../Data/Raw-Chierichetti/bank/bank-full.csv"
    pathRawDiabetes = "../Data/Raw-Chierichetti/diabetes/Gupta-Data/diabetic_data.csv"
    pathNormalizedData = "../Data/Raw-Chierichetti/normalized"
    pathCleanedData = "../Data/CleanedData"
    pathSubsamplesCensus = "../Data/Subsamples/census"
    pathSubsamplesBank = "../Data/Subsamples/bank"
    pathSubsamplesDiabetes = "../Data/Subsamples/diabetes"
    
    # Seed für Subsamples
    subSamSeed = 5
    
    # Dimensionierung der Subsamples
    numOfSamples = 20
    subsampleSizeCensus = 600
    subsampleSizeBank = 1000
    subsampleSizeDiabetes = 1000
    
    
    
    # # Ordner Spülen
    foldersToDelete = [pathNormalizedData, pathCleanedData, 
                       pathSubsamplesCensus, pathSubsamplesBank,
                       pathSubsamplesDiabetes]
    flushFiles(foldersToDelete)   
    
    
    # # Dateien normalisieren
    # Zensusdaten
    normalizeCensus(pathRawCensus, pathNormalizedData)

    # Bankdaten
    normalizeBank(pathRawBank, pathNormalizedData)

    # Diabetesdaten
    normalizeDiabetes(pathRawDiabetes, pathNormalizedData)
    
    # Daten in Pandas Tabelle
    pdFrameCensus = readPandaFromFile(pathNormalizedData + "/census-normalized.csv")
    pdFrameBank = readPandaFromFile(pathNormalizedData + "/bank-normalized.csv")
    pdFrameDiabetes = readPandaFromFile(pathNormalizedData + "/diabetes-normalized.csv")
    
    
    
    
    
    
    
    # # # Daten Angucken # # #
    # Einfach mal ein paar einträge
    print(pdFrameCensus.head(10))
    print(pdFrameBank.head(10))
    print(pdFrameDiabetes.head(10)) # TO-DO: Weitere Analyse
    
    # Verhältnisse des Kritischen Features testen
    # Zensus
    print("\n---- Census Ratio ----\n")
    pdCensusBySex = pdFrameCensus.groupby("sex").size()
    print(pdCensusBySex[:]) # Female 10771 / Male 21790
    ratioCensus = pdCensusBySex['Male']/pdCensusBySex['Female']
    print(f"Verhältniss Male/Female bei Zensus: {ratioCensus}")
    
    
    # Bank 
    print("\n---- Bank Ratios ----\n")
    pdBankByMartial = pdFrameBank.groupby("marital").size()
    print(pdBankByMartial[:])
    
    # Neue Spalte für binäres Feature married <--> not married
    pdFrameBank["bin-martial"] = "not-married" 
    
    
    pdFrameBank.loc[pdFrameBank["marital"] == "married", "bin-martial"] = "married"
    print(pdFrameBank[["age", "job", "marital", "bin-martial"]].head(10))    

    # Nochmal neu gruppieren
    print("\n---- Binary Bank Ratio ----\n")
    pdBankByMartial = pdFrameBank.groupby("bin-martial").size()
    print(pdBankByMartial[:])
    ratioBank = pdBankByMartial["married"]/pdBankByMartial["not-married"]
    print(f"Verhältniss married/not-married bei Zensus: {ratioBank}")







    
    # # # Spalten Aussortieren # # #
    # Zensus
    pdFrameCensus["kritFeature"] = 0 
    pdFrameCensus.loc[pdFrameCensus["sex"] == "Female", "kritFeature"] = 1
    pdFilteredCensus = pdFrameCensus[["kritFeature", "age", "fnlwgt", "education-num", "capital-gain", "hours-per-week"]]
    print(pdFilteredCensus.head(10))
    
    # Bank
    pdFrameBank["kritFeature"] = 0 
    pdFrameBank.loc[pdFrameBank["bin-martial"] == "married", "kritFeature"] = 1
    pdFilteredBank = pdFrameBank[["kritFeature", "age", "balance", "duration"]]
    print(pdFilteredBank.head(10))
    
    # # Cleaned-Data zwischendurch mal abspeichern
    saveToFile(pathCleanedData, "census-cleaned.csv", 
               pdFilteredCensus.to_csv(index=False, lineterminator="\n"))
    
    saveToFile(pathCleanedData, "bank-cleaned.csv", 
               pdFilteredBank.to_csv(index=False, lineterminator="\n"))
    
    
    
    
    
    
    # # # Subsamples erzeugen # # #
    print("\n\n---- Create Sub Samples ---- \n")
    # Zensus
    print("Create Subs of Census:")
    listOfCensusSamples = subsampleData(pdFilteredCensus, sampleSize = subsampleSizeCensus, 
                                        sampleCount = numOfSamples, seed = subSamSeed)
    
    print("\nCreate Subs of Bank:")
    # Bank
    listOfBankSamples = subsampleData(pdFilteredBank, sampleSize = subsampleSizeBank, 
                                        sampleCount = numOfSamples, seed = subSamSeed)
    
    # Ein paar Beispiele ausgeben
    shownum = 3
    if numOfSamples < shownum:
        shownum = numOfSamples
    
    print("\n# Samples of Census #") # neue Zeile
    [print(listOfCensusSamples[i].head(5)) for i in range(0, shownum)]
    
    print("\n# Samples of Bank #") # neue Zeile
    [print(listOfBankSamples[i].head(5)) for i in range(0, shownum)]
    
    
    
    
    
    # # # In einzelne Dateien speichern # # #
    # Zensus
    safeListOfSamples(pathSubsamplesCensus, "censusSample-", listOfCensusSamples)
    
    # Bank
    safeListOfSamples(pathSubsamplesBank, "bankSample-", listOfBankSamples)
    
    
    
    
    print("\n\n ------ Cleaning ans Sampling finished ------ \n\n")
    return















def flushFiles(listOfFolders):
    
    print("\n---- Deleting Folders with files ----")
    
    for path in listOfFolders:
        print(f"Delete Folder {path}") 
        if os.path.isdir(path):
            shutil.rmtree(path, ignore_errors=False)  
    
    return



def readPandaFromFile(path):
    pandaDataset = pd.read_csv(path) 
    return pandaDataset


def saveToFile(path, filename, content): 
    os.makedirs(path, exist_ok=True) 
    f = open(path + "/" + filename,'w')
    f.write(content)
    f.close()
    return

def normalizeCensus(rawPath, normalizedPath):
    # Daten als String holen
    f = open(rawPath,'r')
    filedata = f.read()
    f.close()
    
    # Überschrifften hinzufügen
    captions = "age,workclass,fnlwgt,education,education-num,marital-status,"\
            "occupation,relationship,race,sex,capital-gain,capital-loss,"\
            "hours-per-week,native-country,income\n"        
    newdata = captions + filedata
    
    # Leerzeichen löschen
    newdata = newdata.replace(' ','')
    
    # Neue Daten in Datei schreiben
    saveToFile(normalizedPath, "census-normalized.csv", newdata)
    return

def normalizeBank(rawPath, normalizedPath):
    # Daten als String holen
    f = open(rawPath,'r')
    filedata = f.read()
    f.close()
    
    # Anführungszeichen löschen
    newdata = filedata.replace('"','')
    # Semicola löschen
    newdata = newdata.replace(';',',')
    
    # Neue Daten in Datei schreiben
    saveToFile(normalizedPath, "bank-normalized.csv", newdata)    
    return


def normalizeDiabetes(rawPath, normalizedPath):
    # Daten als String holen
    f = open(rawPath,'r')
    filedata = f.read()
    f.close()
    
    # Hier passiert nichts, da die Daten hier schon in einem 
    # brauchbaren Format sind
    
    # Neue Daten in Datei schreiben
    saveToFile(normalizedPath, "diabetes-normalized.csv", filedata)    
    return



def subsampleData(pdData, sampleSize = 1000, sampleCount = 10, seed = 0):
    # Sicherung falls Zahlen nicht passen
    instances = len(pdData.index)
    
    if instances < sampleSize * sampleCount:
        print(f"!- - Not enough instances ({instances}) for sampling Dataset to {sampleSize} by {sampleCount} Sets ({sampleSize*sampleCount} Instances needed)- -!")
    
        while instances < sampleSize * sampleCount:
            sampleCount -= 1
        print(f"reduced to {sampleCount} samples\nnow using {sampleSize*sampleCount} of {instances} Instances\n")

    # Leere Liste in welche die Daten reinkommen
    dataList = []

    for i in range(0, sampleCount):
        # Sample holen
        pdSubsample = pdData.sample(n=sampleSize, random_state=seed)
        # Aus original Set löschen
        pdData = pdData.drop(pdSubsample.index)
        # In die Liste der Subsamples hinzufügen
        dataList.append(pdSubsample)
        
        #länge als Sanatiy-Check ausgeben
        print(f"Länge des Ursprungssatzes nach {i+1} Iteration/en: {len(pdData)}")
             
    return dataList


def safeListOfSamples(folder, naming, listOfSamples):
    
    counter = 0
    for sample in listOfSamples:
        saveToFile(folder, f"{naming}{counter}.csv", 
                   sample.to_csv(index=False, lineterminator="\n"))
        counter += 1
        
    return





main()