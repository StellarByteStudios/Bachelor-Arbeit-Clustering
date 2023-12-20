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
    print("---- Census Ratio ----")
    pdCensusBySex = pdFrameCensus.groupby("sex").size()
    print(pdCensusBySex[:]) # Female 10771 / Male 21790
    ratioCensus = pdCensusBySex['Male']/pdCensusBySex['Female']
    print(f"Verhältniss Male/Female bei Zensus: {ratioCensus}")
    
    
    # Bank 
    print("---- Bank Ratios ----")
    pdBankByMartial = pdFrameCensus.groupby("marital-status").size()
    print(pdBankByMartial[:])
    
    # Neue Spalte für binäres Feature married <--> not married
    pdFrameCensus["bin-martial"] = 0 
    
    # Liste an Status, die ich als married interpretiere
    martialStatusList = ["Married-AF-spouse", "Married-civ-spouse", "Married-spouse-absent"]
    
    for status in martialStatusList:
        pdFrameCensus.loc[pdFrameCensus["marital-status"] == status, "bin-martial"] = 1
    print(pdFrameCensus[["age", "workclass", "marital-status", "bin-martial"]].head(10))    
    
    # Nochmal neu gruppieren
    print("---- Binary Bank Ratio ----")
    pdBankByMartial = pdFrameCensus.groupby("bin-martial").size()
    print(pdBankByMartial[:])
    # Married <--> not Married zusammensetzten
    #ratioBank = pdBankByMartial['Female']/pdBankByMartial['Male']
    #print(f"Verhältniss Female/Male bei Zensus: {ratioBank}")
    
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