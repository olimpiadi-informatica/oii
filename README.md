# Problemi

Questo repository contiene i task di programmazione tratti dalle
selezioni territoriali e nazionali delle Olimpiadi Italiane di
Informatica.

## Struttura delle cartelle

La struttura delle cartelle è `<anno>/<evento>/<nome>` dove:

* `<anno>` è l'anno delle IOI per le quali si stava svolgendo la
  selezione (per esempio: 2005, se si tratta delle selezioni
  territoriali o nazionali che hanno portato a gareggiare nelle
  IOI 2005).
* `<evento>` è *territoriali* oppure *nazionali*.
* `<nome>` è il nome breve del task.

## Formato dei task

Il formato utilizzato, al momento, è il cosiddetto *Italian format*.

* `<nome>/`
    * `task.yaml`: il file che definisce nome breve (uguale al nome
      della cartella), il nome, il tempo limite, la memoria limite, e
      così via.
    * `gen/`
        * `GEN`: file usato per descrivere gli input. Le parti della
          riga dopo un `#` vengono ignorate. Le righe non banali (ovvero
          contenenti qualcosa oltre a whitespace prima del primo `#`)
          vengono passate al generatore e generano un input ciascuna.
          Se una riga inizia con `#ST:` viene usata per delimitare un
          subtask. `#ST:` va seguito con il punteggio assegnato a quel
          subtask. Se sono presenti i subtask, è necessario che la somma
          dei punti di ogni subtask sia 100. Se una riga inizia con
          `#COPY:` allora ciò che segue viene interpretato come un
          percorso relativo a `<nome>/` dal quale andare a copiare un
          input esistente.
        * `generatore.*`: programma che per una certa lista di argomenti
          produce (su *stdout*) un certo input valido.
    * `sol/`
        * `soluzione.*`: la soluzione ufficiale. Viene usata per
          generare gli output.
        * `<altro>`: eventuali altre soluzioni (ad esempio: `lenta.cpp`,
          `quadratica.pas`, etc) che vengono valutate automaticamente
          dal comando cmsMake.
    * `testo/`
        * `testo.tex`: il testo.
