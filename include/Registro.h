#ifndef REGISTRO_H
#define REGISTRO_H

#include <ostream>

class Registro
{
    public: // elementos que podem ser acessados externamente

        Registro(int c=0, int s=0); // construtor
        ~Registro(); // destrutor

        int getChave();
        int getDadoSatelite();

        // sobrecarrega operadores de comparacao para permitir comparacoes simples entre dois registros, tipo if(registro_a < registro_b)
        bool operator < (const Registro& x) const;
        bool operator <= (const Registro& x) const;
        bool operator == (const Registro& x) const;
        bool operator != (const Registro& x) const;
        bool operator >= (const Registro& x) const;
        bool operator > (const Registro& x) const;

        // sobrecarrega operador de escrita para permitir impressao via streams (i.e. std::cout << registro)
        friend std::ostream& operator<<(std::ostream& os, const Registro& reg);

    private: // elementos que somente podem ser acessados dentro da classe

        int chave;
        int dado_satelite;
};

#endif // REGISTRO_H
