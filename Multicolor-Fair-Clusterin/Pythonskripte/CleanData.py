#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Skript to roughly analyse given Data by Chierichetti and divide it
into usable subsamples
"""

import numpy as np
import pandas as pd
#import matplotlib.pyplot as plt



def main():
    
    # # # Daten einlesen # # #
    # Pfade Hardcoden
    pathRawCensus = "../Data/Raw-Chierichetti/census/adult.data"
    pathRawBank = "../Data/Raw-Chierichetti/bank/bank-full.csv"
    pathNormalizedCensus = "../Data/Raw-Chierichetti/census/census-normalized.csv"
    pathNormalizedBank = "../Data/Raw-Chierichetti/bank/bank-normalized.csv"
    
    
    # # Dateien normalisieren
    
    
    # Zensusdaten
    normalizeCensus(pathRawCensus, pathNormalizedCensus)
    """
    # Daten als String holen
    f = open(pathRawCensus,'r')
    filedata = f.read()
    f.close()
    # Überschrifften hinzufügen
    captions = "age,workclass,fnlwgt,education,education-num,marital-status,"\
            "occupation,relationship,race,sex,capital-gain,capital-loss,"\
            "hours-per-week,native-country,income\n"
            
    newdata = captions + filedata
    
    
    # Neue Daten in Datei schreiben
    f = open(pathNormalizedCensus,'w')
    f.write(newdata)
    f.close()
    """
    
    # Bankdaten
    normalizeBank(pathRawBank, pathNormalizedBank)
    
    """
    # Daten als String holen
    f = open(pathRawBank,'r')
    filedata = f.read()
    f.close()
    
    # Anführungszeichen löschen
    newdata = filedata.replace('"','')
    # Semicola löschen
    newdata = newdata.replace(';',',')
            
    
    
    # Neue Daten in Datei schreiben
    f = open(pathNormalizedBank,'w')
    f.write(newdata)
    f.close()
    """
    
    # Daten in Pandas Tabelle
    pdFrameCensus = readPandaFromFile(pathNormalizedCensus)
    pdFrameBank = readPandaFromFile(pathNormalizedBank)
    
    
    
    
    
    # # # Daten Angucken # # #
    # Einfach mal ein paar einträge
    print(pdFrameCensus.head(10))
    print(pdFrameBank.head(10))
    
    #
    
    # # # Spalten Aussortieren # # #
    
    # # # Subsamples erzeugen # # #
    
    # # # In einzelne Dateien speichern # # #
    
    
    
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









main()