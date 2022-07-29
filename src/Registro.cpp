#include "../include/Registro.h"

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Registro::Registro(int c, int s)
{
    chave = c;
    dado_satelite = s;
}

Registro::~Registro()
{
    //destrutor
}

/// GET

int Registro::getChave()
{
    return this->chave;
}

int Registro::getDadoSatelite()
{
    return this->dado_satelite;
}

/// IMPRESSAO

std::ostream& operator<<(std::ostream& os, const Registro& reg)
{
    os << '(' << reg.chave << ';' << reg.dado_satelite << ')';
    return os;
}

/// COMPARACOES ENTRE REGISTROS DADAS PELA CHAVE PRINCIPAL

bool Registro::operator < (const Registro& x) const
{
        return (chave < x.chave);
}

bool Registro::operator <= (const Registro& x) const
{
        return (chave <= x.chave);
}

bool Registro::operator > (const Registro& x) const
{
        return (chave > x.chave);
}

bool Registro::operator >= (const Registro& x) const
{
        return (chave >= x.chave);
}

bool Registro::operator == (const Registro& x) const
{
        return (chave==x.chave);
}

bool Registro::operator != (const Registro& x) const
{
        return (chave!=x.chave);
}
