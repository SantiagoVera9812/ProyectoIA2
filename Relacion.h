#include <string>
#include <stdexcept>
#include<iostream>
#pragma once

class Relacion {
private:
    std::string tipo_relacion;
    std::string nombreFuncion;
    std::string afectado;
    bool tieneAfectante;
    std::string afectante;
    bool esNegacion;

public:
    Relacion(std::string tipo_relacion, 
             std::string nombreFuncion, 
             std::string afectado, 
             bool tieneAfectante = false, 
             std::string afectante = "",
             bool esNegacion = false);

    Relacion();

    ~Relacion();

    Relacion* toggleNegacion();

    std::string getTipoRelacion() const;
    std::string getNombreFuncion() const;
    std::string getAfectado() const;
    std::string getAfectante() const;
    bool getTieneAfectante() const;
    bool getEsNegacion() const;

    void mostrar() const{
        std::cout << "Relacion -> Tipo: " << tipo_relacion
            << ", Funcion: " << nombreFuncion
            << ", Afectado: " << afectado;
            if (tieneAfectante) {
            std::cout << ", Afectante: " << afectante;
                }

                if(esNegacion){
                    std::cout << " es negado" << std::endl;
                }

                std::cout << std::endl;
                };
        };

            



