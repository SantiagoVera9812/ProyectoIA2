#include <string>
#include "Relacion.h"
#include <vector>
#pragma once

enum Conector{
    Y, O , SI, ENTONCES
};

class ProposicionesConConectores
{
private:

        std::vector<Relacion> relaciones;
        std::string conector;

    
public:
    
    ProposicionesConConectores(std::string conector, std::vector<Relacion> relaciones);

    void mostrar() const {
        std::cout << "Proposiciones con conector: " << conector << std::endl;
        for (const auto& relacion : relaciones) {
            relacion.mostrar();
        }
    }
};


