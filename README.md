# Serratura_che_si_sblocca_bussando
Arduino: creare serratura che si sblocca bussando

In questo progetto avrai la possibilità di creare una serratura segreta per tenere lontani gli ospiti indesiderati.

Il buzzer passivo può anche essere utilizzato come dispositivo di ingresso. Quando è collegato alla linea 5 V, il sensore può rilevare le vibrazioni misurabili dagli ingressi analogici di Arduino. Avrai bisogno di collegare una resistenza di alto valore (come 1 mega ohm) come riferimento a massa per far funzionare tutto correttamente.

Quando il piezo viene premuto contro una superficie solida in grado di vibrare, come un tavolo in legno, Arduino può percepire l’intensità del colpo. Utilizzando queste informazioni puoi contare quante volte è stato bussato in un intervallo prestabilito. Nel codice è possibile monitorare il numero di colpi e vedere se corrispondono alle tue impostazioni.

Un interruttore ti permetterà di bloccare il motore in posizione. Alcuni LED ti diranno lo stato: un LED rosso indica che la scatola è chiusa a chiave, un LED verde indica che è sbloccata e un LED giallo permette di sapere se è stato ricevuto un colpo valido.

Scriverai anche una funzione che ti consente di sapere se il colpo è troppo forte o troppo leggero. Scrivere funzioni consente di risparmiare tempo riutilizzando il codice invece di riscriverlo molte volte. Le funzioni possono avere dei parametri e restituire dei valori. In questo caso fornirai alla funzioni il volume del colpo. Se è nell’intervallo giusto incrementi una variabile.

Vi è data la possibilità ovviamente di costruire solo il circuito, ma è molto più divertente se lo si utilizza come strumento per chiudere a chiave qualcosa. Se hai una scatola di legno o di cartone puoi tagliarci dei fori e utilizzare il servomotore per aprire e chiudere un chiavistello, tendono le persone lontane dalle tue cose.

![alt text](https://i0.wp.com/www.moreware.org/wp/wp-content/uploads/2021/07/maxresdefault-1.jpg?resize=1024%2C576&ssl=1)

Componenti da utilizzare:

* 1x Board Arduino Uno
* 1x buzzer passivo
* 1x servomotore
* 1x condensatore da 10 microfarad
* 1x resistenza da 1 mega ohm
* 3x resistenza da 220 ohm
* 1x resistenza da 10 kilo ohm
* 3x led
* 1x led rosso
* 1x led giallo
* 1x led verde
* 1x pulsante
* vari jumper
* Eventualmente tre connettori maschio-maschio

![alt text](https://i0.wp.com/www.moreware.org/wp/wp-content/uploads/2021/07/Senza-titolo-3.png?w=772&ssl=1)

Diagramma di collegamento:

![alt text](https://i0.wp.com/www.moreware.org/wp/wp-content/uploads/2021/07/Untitled-Sketch-2_bb-4.png?resize=1024%2C849&ssl=1)

# [CODICE](https://github.com/SimoneMoreWare/Serratura_che_si_sblocca_bussando/blob/main/serratuura.ino)

Conclusione

Quando colleghi il circuito ad Arduino apri il monitor seriale.

Dovresti vedere accendersi il LED verde e il servo si sposta nella posizione di sblocco.

Il monitor seriale dovrebbe stampare “the box is unlocked!”. Probabilmente senti che il buzzer fa un piccolo clic quando viene alimentato.

Prova a bussare delicatamente e forte per vedere quale intensità del colpo attiva la funzione. Saprai che sta funzionando quando il LED giallo lampeggia e il monitor seriale ti dice che hai ricevuto un colpo valido e il suo valore. Ti permette anche di sapere il numero di colpi che mancano per sbloccare la scatola.

Una volta raggiunto il giusto numero di colpi, la luce rossa si spegne e la luce verde si accende. Il servo si sposta di 90 gradi e il monitor seriale ti informa che il blocco è disinnestato.

La tua serratura è pronta.
