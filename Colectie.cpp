#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
    nr_elem_dist = 0;
    size = 0;
    cap = 521;
    primLiber = 0;
    urm = new int[cap];
    elemente = new Elem[cap];
    for (int i = 0; i < cap; ++i) {
        elemente[i].set_valoare(Minim);
        elemente[i].set_nrAparitii(0);
        urm[i] = -1;
    }
}

void Colectie::actPrimLiber() {
    primLiber++;
    while(primLiber < cap and elemente[primLiber].get_valoare() != Minim)
        primLiber++;
}

int Colectie::hashCode(TElem elem) const {
    return abs(elem);
}

int Colectie::dispersie(TElem elem) const {
    return hashCode(elem)%cap;
}


void Colectie::adauga(TElem elem) {
    auto index = dispersie(elem);
    if(elemente[index].get_valoare() == Minim)
    {
        elemente[index].set_valoare(elem);
        elemente[index].set_nrAparitii(1);
        nr_elem_dist++;
        size++;
        if(index == primLiber)
            actPrimLiber();
    } else{
        int j;
        while (index!=-1 and elemente[index].get_valoare() != elem) {
            j = index;
            index = urm[index];
        }
        if(index != -1)
        {
            elemente[index].set_nrAparitii(elemente[index].get_nrAparitii()+1);
            size++;
        }
        else{
            if(nr_elem_dist < cap)
            {
                elemente[primLiber].set_valoare(elem);
                elemente[primLiber].set_nrAparitii(1);
                urm[j]=primLiber;
                nr_elem_dist++;
                size++;
                actPrimLiber();
            }
            else{
                realocare();
                adauga(elem);
            }
        }
    }
}


bool Colectie::sterge(TElem elem) {
    auto i = dispersie(elem);
    auto j = -1;

    auto k = 0;

    while(k < cap and j == -1) {
        if (urm[k] == i)
            j = k;
        else k++;
    }

    while (i != -1 and elemente[i].get_valoare() != elem)
    {
        j = i;
        i = urm[i];
    }

    if(i == -1) {return false;}

    if(elemente[i].get_nrAparitii() > 1)
    {
        elemente[i].set_nrAparitii(elemente[i].get_nrAparitii()-1);
        size--;
        return true;
    }

    auto ok = false;
    do{

        auto p = urm[i];
        auto pp = i;

        while (p != -1 and dispersie(elemente[p].get_valoare()) != i)
        {
            pp = p;
            p = urm[p];
        }

        if(p == -1)
            ok = true;
        else{
            elemente[i] = elemente[p];
            j = pp;
            i = p;
        }
    } while (!ok);

    if(j != -1)
        urm[j] = urm[i];

    elemente[i].set_valoare(Minim);
    elemente[i].set_nrAparitii(0);
    urm[i] = -1;

    if(primLiber > i)
        primLiber = i;

    size--;
    nr_elem_dist--;
    return true;
}


bool Colectie::cauta(TElem elem) const {
    auto index = dispersie(elem);
    while (index!=-1 and elemente[index].get_valoare() != elem)
        index = urm[index];

    if(index == -1)
        return false;
    return true;

}

int Colectie::nrAparitii(TElem elem) const {
    auto index = dispersie(elem);

    while (index!=-1 and elemente[index].get_valoare() != elem)
        index = urm[index];

    if(index == -1)
        return 0;
    return elemente[index].get_nrAparitii();
}

int Colectie::dim() const {
    return size;
}


bool Colectie::vida() const {
    return size == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

void Colectie::realocare() {
    cap *= 2;
    auto new_urm = new int[cap];
    auto new_elem = new Elem[cap];

    for (int i = 0; i < nr_elem_dist; ++i) {
        new_urm[i] = -1;
        new_elem[i] = elemente[i];
    }

    delete[] urm;
    delete[] elemente;

    urm = new int[cap];
    elemente = new Elem[cap];

    auto nr = nr_elem_dist;
    nr_elem_dist = 0;
    size = 0;

    for (int i = 0; i < cap; ++i) {
        elemente[i].set_valoare(Minim);
        elemente[i].set_nrAparitii(0);
        urm[i] = -1;
    }

    for (int i = 0; i < nr; ++i)
        while(new_elem[i].get_nrAparitii())
        {
            new_elem[i].set_nrAparitii(new_elem[i].get_nrAparitii()-1);
            adauga(new_elem[i].get_valoare());
        }

    primLiber = 0;
    actPrimLiber();
}

Colectie::~Colectie() {
    delete[] urm;
    delete[] elemente;
    size = 0;
    nr_elem_dist = 0;
    cap = 0;
    primLiber = -1;
}

TElem Colectie::celMaiFrecvent() const {
    if(size == 0)
        return NULL_TELEM;
    Elem elem{};
    auto it = iterator();
    it.prim();
    elem.set_nrAparitii(0);
    elem.set_valoare(-1);
    while(it.valid())
    {
        if(elemente[it.curent].get_nrAparitii() > elem.get_nrAparitii())
        {
            elem.set_nrAparitii(elemente[it.curent].get_nrAparitii());
            elem.set_valoare(elemente[it.curent].get_valoare());
        }
        it.urmator();
    }
    return elem.get_valoare();
}

