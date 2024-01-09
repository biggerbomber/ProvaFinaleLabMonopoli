//@Casucci Leonardo 2073980

#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H
/*
Enum che descrive gli eventi della partita, si attribuiscono
delle etichette ai possibili avvenimenti nel gioco.
*/
enum EventType {
    PASSAGGIO_VIA, TIRO_DADI, ARRIVO, ACQUISTO_TERRENO,
    COSTRUZIONE_CASA, COSTRUZIONE_ALBERGO,
    PAGAMENTO_PERNOTTAMENTO, SHOW_COMMAND, FINE_TURNO,
    ELIMINAZIONE, VITTORIA
};

#endif