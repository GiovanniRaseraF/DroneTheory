# Questo file contiene le idee principali per il projetto

## Pricipale
- Creare un Drone 
  - Software
  - PID
  - Comunicazine con radio
  - Lettura dei sensori (giroscopio, GPS, accelerometro)
  - Hardware
  - Funzioni di trasferimento
  - Documentazione
  - Test

## Documentazione
- Documentare il processo di creazione
  - Creazione diagramma di classi
  - Tecnologie coinvolte
  - Duscussione sui calcoli matematici coinvolti
  - Analisi dell'andamento del projetto

## Requisiti
- Documentazione
  - Più chiara possibile
  - Ogni cosa deve essere documentata
  - Ogni problema deve essere documentato
    - Deve essere aperta una issue su git che espone il problema
    - La soluzione al problema deve essere collegata alla issue su git con una breve discussione 
  - Ogni nuova scoperta deve essere documentata nella wiki del projetto
  - Importante dare credito ai lavori a cui si fa riferimento 

- Codice 
  - Deve essere scelto e rispettato un coding style (Utilizzare quello di INAV: [Coding Style](../Styles/codingstyle.md))
  - Deve essere creato lo schema che spiega l'interazione tra le classi e le funzioni implementate
  - Il codice deve essere più semplice possibile, se non è possibile deve essere spiegato tramite commenti
  - Ogni funzione deve essere documentata nella wiki del progetto
  - Il codice deve essere scritto utilizzando il software STM32CubeIDE 
  - Il codece deve comprendere i test necessari al corretto funzionamento 
  - Deve essere presente un sistema di CI per compilare ogni commit relativo al codice 
   
- Hardware
  - Deve essere realizzata una versione di test che non comprende un PCB
  - Deve essere realizzata una versione in un PCB tramite il programma KiCad 
  - Deve essere incluso ogni pdf o link al pdf che descrive ogni componente che viene utilizzato 

- Software Utilizzati
    - Devono essere open-source o almeno non avere licenze di nessun tipo
    - KiCad per il design PCB
    - VSCode per la scrittura del codice 
    - ToolChain arm 
    - Dia per il design di diagrammi
    - Project Libre per gestione progetto
    - Git per il versioning
    - STM32CubeIDE per l'aiuto sulle librerie e il debugging  