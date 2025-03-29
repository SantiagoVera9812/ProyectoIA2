#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include "Relacion.h"
#include "ProposicionesConConectores.h"


void listarClausulas(std::vector<std::vector<std::string>> clausulas){

    std::cout << "\nClausulas ingresadas para encontrar una solucion:\n";
            for (const auto& entry : clausulas) {
                for (const auto& w : entry) {
                    std::cout << w << " ";
                    }
                    std::cout << std::endl;
                    }

};

Relacion procesarClausulasLogicas(std::vector<std::string> clausulaRelacion, std::vector<std::string> palabrasAcciones) {
    std::unordered_map<std::string, std::function<Relacion(size_t, const std::vector<std::string>&, bool)>> accionesConectores;

    // Acción para "es"
    accionesConectores["es"] = [](size_t i, const std::vector<std::string>& clausula, bool esNegacion) -> Relacion {
        if (i > 0 && i + 1 < clausula.size()) {
            return Relacion("definicion", clausula[i + 1], clausula[i - 1], false, "", esNegacion);
        }
        throw std::runtime_error("Invalid 'es' relationship: missing previous or next word.");
    };

    // Agregar las palabras de acciones como "ama", "odia", etc.
    for (const std::string& accion : palabrasAcciones) {
        accionesConectores[accion] = [accion](size_t i, const std::vector<std::string>& clausula, bool esNegacion) -> Relacion {
            if (i > 0 && i + 1 < clausula.size()) {
                return Relacion("accion", clausula[i], clausula[i + 1], true, clausula[i - 1], esNegacion);
            }
            throw std::runtime_error("Invalid action relationship: missing previous or next word.");
        };
    }

    bool esNegacion = false;

    for (size_t i = 0; i < clausulaRelacion.size(); ++i) {
        if (clausulaRelacion[i] == "no") {
            esNegacion = true;
            continue;  // Saltar al siguiente elemento
        }

        auto it = accionesConectores.find(clausulaRelacion[i]);
        if (it != accionesConectores.end()) {
            return it->second(i, clausulaRelacion, esNegacion);
        }
    }

    throw std::runtime_error("No valid relationship found in the clause.");
}


std::vector<ProposicionesConConectores> procesarConectoresLogicos(std::vector<std::vector<std::string>> clausulas, std::vector<std::string> palabrasAcciones) {
    std::vector<ProposicionesConConectores> proposiciones;
    std::vector<std::string> bufferProposicion;
    std::vector<Relacion> relacionesBuffer;
    std::string conectorActual = ""; // Guardará el conector que está separando las proposiciones

    for (const auto& clausula : clausulas) {
        bufferProposicion.clear();
        relacionesBuffer.clear();
        conectorActual = "";

        for (size_t i = 0; i < clausula.size(); ++i) {
            if (clausula[i] == "o") {
                // Si encontramos "o", procesamos lo que se acumuló antes
                if (!bufferProposicion.empty()) {
                    try {
                        Relacion relacion = procesarClausulasLogicas(bufferProposicion, palabrasAcciones);
                        relacionesBuffer.push_back(relacion);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    bufferProposicion.clear(); // Resetear el buffer
                }
                conectorActual = clausula[i]; // Asignamos "o" como conector
            } else {
                bufferProposicion.push_back(clausula[i]);
            }
        }

        // Procesar la última proposición de la cláusula si no termina en "o"
        if (!bufferProposicion.empty()) {
            try {
                Relacion relacion = procesarClausulasLogicas(bufferProposicion, palabrasAcciones);
                relacionesBuffer.push_back(relacion);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        // Guardar en `proposiciones`
        if (!relacionesBuffer.empty()) {
            proposiciones.emplace_back(conectorActual, relacionesBuffer);
        }
    }

    return proposiciones;

}

std::vector<std::string> consegirPalabrasAcciones(){

    bool escribiendoAcciones = true;

            std::vector<std::string> palabrasAcciones;

            while(escribiendoAcciones){

                std::string input;
                std::getline(std::cin, input);

                if(input == "aceptar_acciones"){
                    escribiendoAcciones = false;
                }

                palabrasAcciones.push_back(input);

            }

            return palabrasAcciones;
}


Relacion conseguirTeorema(std::vector<std::string> palabrasAcciones){


    std::cout << "Escribe una relacion valida que funcione como teorema: " << std::endl;
    std::vector<std::string> palabras;

    std::string input;
    std::getline(std::cin, input);

    std::istringstream iss(input);
            std::string word;

            while (iss >> word) {
                palabras.push_back(word);
            }

    return procesarClausulasLogicas(palabras, palabrasAcciones);

}

