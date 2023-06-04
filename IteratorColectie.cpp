#include <exception>
#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    curent = 0;
    deplasare();
    nrApar = col.elemente[curent].get_nrAparitii();
}

void IteratorColectie::prim() {
	curent=0;
    deplasare();
    nrApar = col.elemente[curent].get_nrAparitii();
}


void IteratorColectie::urmator() {
    if(!valid())
        throw std::exception();

    if(nrApar > 1)
    {
        nrApar--;
        return;
    }
	curent++;
    deplasare();
    nrApar = col.elemente[curent].get_nrAparitii();
}


bool IteratorColectie::valid() const {
    return curent < col.cap;
}


TElem IteratorColectie::element() const {
    if(!valid())
        throw std::exception();
    return col.elemente[curent].get_valoare();
}

void IteratorColectie::deplasare() {
    while (curent < col.cap and col.elemente[curent].get_valoare() == Minim)
        curent++;
}
