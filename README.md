# [SISTEMI OPERATIVI](http://georgeosddev.github.com/markdown-edit)
### Bonadiman Gabriele, Ramponi Alan, Malesani Federico


Il progetto richiedeva l'implementazioni di utility di base di GNU/Linux che permettessero 'backup' e 'confronto di file' in ambiente UNIX.


## PREMESSE

E' stato reso obbligatorio l'utilizzo della system-call *getopt*, non e' stato ammesso l’utilizzo di comandi gia’ disponibili nel sistema GNU/Linux in forma di codice oggetto compilato ed inoltre tutti i processi generati non devono produrre processi zombie.




## LE UTLITY

### [• mkbkp]()

  Crea un file di archivio per il salvataggio di files e directories passati come argomenti flags:

      • -f <archivio> indica l'archivio da creare od estrarre.
      • -c indica la creazione dell'archivio
      • -x indica l'estrazione dell'archivio nella directory corrente
      • -t indica che deve essere visualizzato un elenco del contenuto dell'archivio

Nell’intera utility “mkbkp” sono gestiti i possibili errori di creazione, apertura, scrittura e lettura dei file passati come argomenti. I tre file code descritti qui sopra hanno al loro interno infatti, dove si necessita, una chiamata alla funzione dolog() contenuta nel file “log.c”.
Questa funzione prende in input un messaggio definito in base alle esigenze del programma.
Viene prima di tutto creata una directory all’interno della cartella “/var/log/utility/ <nome-Utility>” con permessi “0777” cosi’ da permettere la visualizzazione sia in lettura che in scrittura a tutti gli user che accedono al computer.
La funzione doLog() associa un file descriptor al file creato, ricava la data del sistema espressa come mese - giorno - ora e la trascrive nel .log assieme al messaggio che e’ stato passato.
Per poter utilizzare il programma bisogna essere amministratori di sistema cosi’ da permettere la creazione della cartella in “var/log”.
Nel creare questa utility abbiamo pensato ad una struttura di sei file, ognuno dei quali con una determinata funzione.
Il file principale “main.c” permette l’inserimento dei vari flag che seguono l’istruzione mkbkp la quale viene copiata dal
Makefile automaticamente nella cartella /bin/. Le combinazioni di flag possibili sono:

       * CREATE BACKUP: mkbkp -c -f<nomeArchivio> /pathBkp
       * EXTRACT BACKUP: mkbkp -x -f<nomeArchivio> /directoryCorrente
       * SHOW BACKUP: mkbkp -t -f<nomeArchivio>
       

 
#### CREATE BACKUP
Attraverso l’utilizzo della funzione getopt() il programma utilizza la lettura dei flag per sapere quale operazione l’utente desidera svolgere. In caso di flag non corretto il programma segnala a video un errore e ne contempo genera un file di log relativo a tale errore.
Per creare il file di backup abbiamo pensato all’utilizzo di due funzioni. La funzione “doBkp.c” prende come input gli argomenti passati da linea di comando considerando pero’ solo quelli superiori al quarto.
Come prima cosa viene considerato il file .bkp, che viene aperto da un fileDescriptor di tipo FILE* in scrittura. Successivamente il programma considera singolarmente i file seguenti. Ci possono essere due possibili scenari: il file che considero e’ una cartella oppure un semplice file.

###### SCENARIO 1: FOLDER.
Nel caso il file fosse una cartella viene associata ad un file descriptor e la si scandisce attraverso la scandir(), con l’utilizzo di una “struct dirent” e mediante un ordinamento alphasort() per ordinare i file al suo interno in ordine alfabetico. La struct in questo caso e’ utilizzata per conoscere il numero di file al suo interno,i loro nomi e le loro dimensioni.Durante questa operazione il fd scrive una carattere di riconoscimento per la funzione di estrazione. A questo punto viene chiamata, per ogni file all’interno della cartella la funzione readFile().

###### SCENARIO 2: FILE.
Tutti i file vengono scanditi secondo la medesima operazione attraverso la funzione di readFile(). L’idea e’ di trascrivere sul file .bkp la path completa del file il suo contenuto con altri piccoli parametri di divisione sempre per la funzione di estrazione.
Utilizziamo quindi una “struct stat” per determinare la grandezza del file. Con questa dimensione possiamo allocare in memoria una buffer che conterra’, attraverso la fread(), il contenuto del file che si sta considerando. Abbiamo dunque il fd del file .bkp che trascrive path completa, dimensione del buffer ed il buffer stesso. Viene quindi ritornato un valore 0 come successo dell’operazione. In tutta la funzione vengono gestiti errori e creati gli opportuni log.

#### EXTRACT BACKUP
Per le operazioni di estrazione abbiamo implementato il file “exBkp.c”. Questo file e’ stato scritto quasi in contemporanea al file di creazione del backup per poter scegliere le migliori soluzioni. I problemi di lettura del file .bkp infatti sono stati tutti risolti quando abbiamo considerato di inserire la dimensione del file all’interno del bkp.
La funzione di extract() prende come parametro di ingresso il file bkp. Viene eseguita una stat() sul file per determinarne la dimensione e associato un fd in lettura. Comincia cosi’ la lettura del buffer scandendo i seguenti parametri. Se viene letta una ‘f’ viene creata una cartella con gli n caratteri che seguono. Succssivamente fino al prossimo carattere ‘.’ e’ letto e salvato il nome della cartella e il nome del file. Viene letto un numero che corrisponde alla lunghezza del contenuto effettivo del file e salvato tutto in un in un array di char*. Una volta che il nostrso index arriva al valore di dimensione del contenuto del file, utilizzo i nomi letti in precedenza e creo la path per il file. Con una creat() creo il file, gli associo un fd FILE* in scrittura, e scrivo il contenuto effettivo del file. Dealloco lo spazio in memoria e mi preparo la prossima locazione di memoria dei miei array.

#### SHOW BACKUP
Infine l’utility di “show” mostra i file contenuti all’interno del mio .bkp. La funzione prende in input il file .bkp e attraverso una lettura a buffer, analoga a quella utilizzata per le operazioni di estrazione, visualizza a video il nome dei file al suo interno.
Viene utilizzato un unico fd di tipo FILE* che legge e memorizza dal buffer, il nome dei file, i quali sono stati scritti utilizzando dei terminatori ben definiti.


### [• equal]()
  Prevede due argomenti, che possono essere nomi di files o directories:

      • Ritorna 0 se gli argomenti hanno contenuto identico
      • Ritorna 1, se gli argomenti differiscono, elencando a video quali elementi differiscono

Più in dettaglio:<br>
• L’utility prende in input il nome di due files o cartelle da confrontare, distingue se sono due file, e in questo caso li confronta, due cartelle, e anche in questo caso le confronta, o se sono un file e una cartella, il che comporta che siano ovviamente diversi. <br>
• Sia il primo controllo, sia la verifica dell’uguaglianza sono state implementati in file diversi e vengono chiamati come funzioni all’occorrenza.<br>
• Il controllo della tipologia di file viene fatto mediante la funzione S_ISDIR.<br>
• La verifica dell’uguaglianza di due file in primo luogo filtra i file che hanno uguale dimensione (se hanno dimensione diversa non potranno essere uguali) e, qualora il primo controllo sia positivo, proceed con una verifica bit a bit dei file.<br>
• Il controllo dell’uguaglianza tra due cartelle controlla in primis se i nomi dei file contenuti nelle due cartelle sono uguali (se ci sono file con nomi differenti li inserisce direttamente tra i file diversi). Se ci sono file con nomi uguali allora l’utility proceed con la verifica utilizzando la funzione di controllo tra due file già vista in precedenza. Qualora all’interno della cartella ci siano ulteriori cartelle la funzione viene chiamata ricorsivamente.
Ogni utility registra le operazioni effettuate in un file di log all’interno della cartella “/var/log/utility/<nome-Utility>”.<br>
• Durante l’implementazione dell’utility abbiamo deciso di suddividere il tutto in diversi file: “main.c”, “doubleFile.c”, “doubleFolder.c”, “control.c”, “log.c”, “lib.h”.<br>

Le combinazioni di flag possibili sono:

       * FILES COMPARISON: equal <nomeFile1> <nomeFile2>
       * FOLDERS COMPARISON: equal <nomeCartella1> <nomeCartella2> equal <nomeFile> <nomeCartella>
       * FILE-FOLDER COMPARISON: equal <nomeCartella> <nomeFile>
       
       
       
       
## CONCLUSIONI
Il progetto descritto è stato sviluppato per un esame nell' anno 2012/1013. Entrambe le utility funzionano correttamente anche se sono presenti alcuni errori nella stesura del codice. Qualsiasi request per un miglioramento del codice è ben accetta. 

