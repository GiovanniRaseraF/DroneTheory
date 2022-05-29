# Test dei singoli componenti Harware e Software

## STM32CubeIDETest
- Vengono eseguiti i test di compilazione tramite una generica toolchain allinterno di sistemi operativi windows e mac
### Scoperte
- Su macOS la compilazione tramite la toolchain arm funziona usando il file make che genera STM32CubeIDE
    - Da sistemare il fatto che il file make deve prendere un path generico perché in questo momento prendere un path assoluto ai file da compilare
- Su windows non è possibile compilare direttamente utilizzando il file make siccome la toolchain non ha i riferimenti giusti alla cartella
- Da testare la compilazione su linux

## CITest
- Test relativi a CI 
  
## CodeStyleTest
- Test relativi al code style
- Utilizzo del comando astyle

## ToolChainDownloadTest
- Bisogna sistemare il download della giusta toolchain per linux
    - Impossibile utilizzare la toolchain siccome non è compatibile con x86 
    - Sistemare l'URL di download
    - Togliere la funzione di salvataggio del file tar nella cartella utente/.env
    - Aggiungere la possibilità di sceglire il path dove estrarre la toolchain
    
    