#pragma once
#include <cstdlib>

#define NULL_TELEM 0
#define Minim -45000
typedef int TElem;

class IteratorColectie;

class Elem{
    TElem valoare;
    int nrAparitii;
public:
    Elem() = default;

    TElem get_valoare() const{
        return valoare;
    }

    int get_nrAparitii() const{
        return nrAparitii;
    }

    void set_valoare(TElem v){
        valoare = v;
    }

    void set_nrAparitii(int nr) {
        nrAparitii = nr;
    }
};

class Colectie
{
    friend class IteratorColectie;

private:
    /* aici e reprezentarea */
    int cap;
    Elem *elemente;
    int *urm;
    int primLiber;
    int size;

    void actPrimLiber();

    int dispersie(TElem elem) const;

    int hashCode(TElem elem) const;

public:
    int nr_elem_dist;
    //constructorul implicit
    Colectie();

    //adauga un element in colectie
    void adauga(TElem elem);

    //sterge o aparitie a unui element din colectie
    //returneaza adevarat daca s-a putut sterge
    bool sterge(TElem e);

    //verifica daca un element se afla in colectie
    bool cauta(TElem elem) const;

    //returneaza numar de aparitii ale unui element in colectie
    int nrAparitii(TElem elem) const;

    //intoarce numarul de elemente din colectie;
    int dim() const;

    //verifica daca colectia e vida;
    bool vida() const;

    //returneaza un iterator pe colectie
    IteratorColectie iterator() const;

    // destructorul colectiei
    ~Colectie();

    void realocare();

    TElem celMaiFrecvent() const;
};

