#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Skript to roughly analyse given Data by Chierichetti and divide it
into usable subsamples
"""

import numpy as np
import pandas as pd
import os 
#import matplotlib.pyplot as plt



def main():
    
    # # # Daten einlesen # # #
    # Pfade Hardcoden
    pathRawCensus = "../Data/Raw-Chierichetti/census/adult.data"
    pathRawBank = "../Data/Raw-Chierichetti/bank/bank-full.csv"
    pathNormalizedCensus = "../Data/Raw-Chierichetti/census/census-normalized.csv"
    pathNormalizedBank = "../Data/Raw-Chierichetti/bank/bank-normalized.csv"
    pathCleanedCensus = "../Data/CleanedData/census"
    pathCleanedBank = "../Data/CleanedData/bank"
    
    # Seed für Subsamples
    subSamSeed = 5
    
    # Dimensionierung der Subsamples
    numOfSamples = 3
    subsampleSize = 1000
    
    
    # # Dateien normalisieren
    # Zensusdaten
    normalizeCensus(pathRawCensus, pathNormalizedCensus)

    # Bankdaten
    normalizeBank(pathRawBank, pathNormalizedBank)

    
    # Daten in Pandas Tabelle
    pdFrameCensus = readPandaFromFile(pathNormalizedCensus)
    pdFrameBank = readPandaFromFile(pathNormalizedBank)
    
    
    
    
    
    
    
    # # # Daten Angucken # # #
    # Einfach mal ein paar einträge
    print(pdFrameCensus.head(10))
    print(pdFrameBank.head(10))
    
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
    pdFrameBank["bin-martial"] = 0 
    
    # Liste an Status, die ich als married interpretiere
    #martialStatusList = ["married", "Married-civ-spouse", "Married-spouse-absent"]
    
    #for status in martialStatusList:
    #    pdFrameBank.loc[pdFrameBank["marital-status"] == status, "bin-martial"] = 1
    
    pdFrameBank.loc[pdFrameBank["marital"] == "married", "bin-martial"] = 1
    print(pdFrameBank[["age", "job", "marital", "bin-martial"]].head(10))    

    # Nochmal neu gruppieren
    print("\n---- Binary Bank Ratio ----\n")
    pdBankByMartial = pdFrameBank.groupby("bin-martial").size()
    print(pdBankByMartial[:])
    ratioBank = pdCensusBySex[1]/pdCensusBySex[0]
    print(f"Verhältniss married/not-married bei Zensus: {ratioBank}")




    
    # # # Spalten Aussortieren # # #
    # Zensus
    pdFilteredCensus = pdFrameCensus[["age", "fnlwgt", "education-num", "capital-gain", "hours-per-week"]]
    print(pdFilteredCensus.head(10))
    
    # Bank
    pdFilteredBank = pdFrameBank[["age", "balance", "duration"]]
    print(pdFilteredBank.head(10))
    
    # # Cleaned-Data zwischendurch mal abspeichern
    os.makedirs(pathCleanedCensus, exist_ok=True) 
    saveToFile(pathCleanedCensus + "/census-cleaned.csv", 
               pdFilteredCensus.to_csv(index=False, lineterminator="\n"))
    
    os.makedirs(pathCleanedBank, exist_ok=True) 
    saveToFile(pathCleanedBank + "/bank-cleaned.csv", 
               pdFilteredBank.to_csv(index=False, lineterminator="\n"))
    
    
    
    # # # Subsamples erzeugen # # #
    print("\n\n---- Create Sub Samples ---- \n")
    # Zensus
    listOfCensusSamples = subsampleData(pdFilteredCensus, sampleSize = subsampleSize, 
                                        sampleCount = numOfSamples, seed = subSamSeed)
    
    print() # neue Zeile
    [print(listOfCensusSamples[i].head(5)) for i in range(0, numOfSamples)]
    
    
    # Bank
    listOfBankSamples = subsampleData(pdFilteredBank, sampleSize = subsampleSize, 
                                        sampleCount = numOfSamples, seed = subSamSeed)
    
    print() # neue Zeile
    [print(listOfBankSamples[i].head(5)) for i in range(0, numOfSamples)]
    
    # # # In einzelne Dateien speichern # # #
    
    
    print("\n\n ---- After all --- \n\n")
    return





def readPandaFromFile(path):
    pandaDataset = pd.read_csv(path) 
    return pandaDataset


def saveToFile(path, content):   
    f = open(path,'w')
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
    saveToFile(normalizedPath, newdata)
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
    saveToFile(normalizedPath, newdata)    
    return


def subsampleData(pdData, sampleSize = 1000, sampleCount = 10, seed = 0):

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









main()