// <<< Green Ring >>>

// Primerament, declarem els .h necessaris.
#include <common.h>     // Funcions típiques
#include <game.h>       // Conté el relacionat amb el joc
#include <g3dhax.h>     // Models 3d i gràfics
#include <sfx.h>        // Efectes de so

// Ara declarem la classe dEn_c, que serà la del nostre sprite
class daGreenRing: public dEn_c { 
    // Funcions bàsiques:
    int onCreate();     // S'executa quan es crea (si es retorna fals, s'executa al frame següent)
    int onDelete();     // S'executa quan es borra un sprite de l'objecte
    int onExecute();    // Fa un loop, s'executa cada frame
    int onDraw();       // Dibuixa l'sprite, s'executa cada frame

    // Necessari per assignar memòria RAM a l'sprite
    mHeapAllocator_c allocator; 

    // Arxiu amb el model 3D i les animacions (.brres)
    nw4r::g3d::ResFile resFile;
    // 3D-bodyModel actual (.brres -> .mdl0-file)
    m3d::mdl_c bodyModel;
    // Animació actual si existeix (.brres -> .chr0-file)
    m3d::anmChr_c chrAnimation;
}