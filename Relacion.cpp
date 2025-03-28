#include "Relacion.h"
#include<iostream>

// Constructor definition
Relacion::Relacion(std::string tipo_relacion, 
                   std::string nombreFuncion, 
                   std::string afectado, 
                   bool tieneAfectante, 
                   std::string afectante,
                    bool esNegacion)
    : tipo_relacion(tipo_relacion), 
      nombreFuncion(nombreFuncion), 
      afectado(afectado), 
      tieneAfectante(tieneAfectante), 
      afectante(afectante),
      esNegacion(esNegacion)
{
    if (tieneAfectante && afectante.empty()) {
        throw std::invalid_argument("Afectante no puede ser vacío cuando tieneAfectante es true");
    }
}

// Destructor definition
Relacion::~Relacion() {}

Relacion* Relacion::toggleNegacion(){

    esNegacion = !esNegacion;
    return this;

}

std::string Relacion::getTipoRelacion() const{
    return tipo_relacion;
}

std::string Relacion::getNombreFuncion() const{
    return nombreFuncion;
}

std::string Relacion::getAfectado() const{
    return afectado;
}

std::string Relacion::getAfectante() const{
    return afectante;
}

bool Relacion::getTieneAfectante() const{
    return tieneAfectante;
}

bool Relacion::getEsNegacion() const{
    return esNegacion;
}

