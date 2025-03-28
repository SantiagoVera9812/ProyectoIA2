
#include <stack>
#include <vector>
#include "maquinaDeInferencia.h"
#include "ProposicionesConConectores.h"

/* void maquinaDeInferencia(std::vector<ProposicionesConConectores> clausulasProcesadas, Relacion* teorema) {
    std::cout << "Iniciando maquina de inferencia con el teorema:" << std::endl;
    

    ProposicionesConConectores nuevaPreposicionConConectores;
    nuevaPreposicionConConectores.agregarRelacion(teorema);

    nuevaPreposicionConConectores.mostrar();

    // Pila para el backtracking (cada estado es un conjunto de proposiciones)
    std::stack<std::vector<ProposicionesConConectores>> estados;

    estados.push(clausulasProcesadas);

    while (!estados.empty()) {
        std::vector<ProposicionesConConectores> estadoActual = estados.top();
        estados.pop();

        std::cout << "\n📢 Estado Actual de las Clausulas:" << std::endl;
        for (const auto& proposicion : estadoActual) {
            proposicion.mostrar();
        }

        for (size_t i = 0; i < estadoActual.size(); ++i) {
            ProposicionesConConectores& proposicion = estadoActual[i];

            const std::vector<Relacion>& relaciones = proposicion.getRelaciones();

            for (size_t j = 0; j < relaciones.size(); ++j) {
                 const Relacion& relacion = relaciones[j];

                // Verificamos si encontramos una relación que sea opuesta al teorema
                if (relacion.getNombreFuncion() == teorema->getNombreFuncion() &&
                    relacion.getAfectado() == teorema->getAfectado() &&
                    relacion.getAfectante() == teorema->getAfectante() &&
                    relacion.getEsNegacion() != teorema->getEsNegacion()) {

                    // 📌 Mostrar la relación que se eliminará
                    std::cout << "\n🔍 Relación encontrada que cancela el teorema:" << std::endl;
                    relacion.mostrar();

                    // Creamos un nuevo estado con la relación eliminada
                    std::vector<ProposicionesConConectores> nuevoEstado = estadoActual;
                    nuevoEstado[i].eliminarRelacion(j);  // 🔥 Ahora eliminamos SOLO la relación en lugar de toda la proposición

                    // 📌 Mostrar el estado después de eliminar
                    std::cout << "\n🛠️ Estado después de eliminar la proposición:\n";
                    for (const auto& proposicion : nuevoEstado) {
                        proposicion.mostrar();
                    }

                    if (nuevoEstado[i].getRelaciones().empty()) {
                        nuevoEstado.erase(nuevoEstado.begin() + i);
                    }

                    // Si no quedan más proposiciones, el teorema es válido
                    if (nuevoEstado.empty()) {
                        std::cout << "El teorema ha sido demostrado!" << std::endl;
                        
                    }

                    std::vector<ProposicionesConConectores> nuevoEstadoParcial;
                    nuevoEstadoParcial.push_back(nuevoEstado[i]);
                    

                    // Seguimos el proceso con el nuevo estado
                    estados.push(nuevoEstado);
                }
            }
        }
    }

    
    std::cout << "No se pudo demostrar el teorema con las clausulas dadas." << std::endl;
}
*/

void maquinaDeInferencia(std::vector<ProposicionesConConectores> clausulasProcesadas, Relacion* teorema) {
    std::cout << "Iniciando maquina de inferencia con el teorema:\n";
    
    // Crear la primera proposición con el teorema
    ProposicionesConConectores nuevaProposicionConConectores;
    nuevaProposicionConConectores.agregarRelacion(teorema);

    std::cout << "🔹 Teorema inicial convertido en proposición:\n";
    nuevaProposicionConConectores.mostrar();

    // Pila para el backtracking (ahora maneja pares: {estado, proposición actual})
    std::stack<std::pair<std::vector<ProposicionesConConectores>, ProposicionesConConectores>> estados;
    estados.push({clausulasProcesadas, nuevaProposicionConConectores});

    while (!estados.empty()) {
        // Desapilar estado y la proposición actual
        auto [estadoActual, proposicionActual] = estados.top();
        estados.pop();

        std::cout << "\n📢 Estado Actual de las Cláusulas:\n";
        for (const auto& proposicion : estadoActual) {
            proposicion.mostrar();
        }

        // Recorrer proposiciones del estado actual
        for (size_t i = 0; i < estadoActual.size(); ++i) {
            ProposicionesConConectores& proposicion = estadoActual[i];
            const std::vector<Relacion>& relaciones = proposicion.getRelaciones();
            
            // Revisamos todas las relaciones dentro de proposicionActual en lugar de teorema
            for (size_t k = 0; k < proposicionActual.getRelaciones().size(); ++k) {
                Relacion& relProposicionActual = proposicionActual.getRelaciones()[k];
                for (size_t j = 0; j < relaciones.size(); ++j) {
                    const Relacion& relacion = relaciones[j];

                    // 🔹 Comparar con cada relación en la proposición actual en vez de un solo teorema
                    if (relacion.getNombreFuncion() == relProposicionActual.getNombreFuncion() &&
                        relacion.getAfectado() == relProposicionActual.getAfectado() &&
                        relacion.getAfectante() == relProposicionActual.getAfectante() &&
                        relacion.getEsNegacion() != relProposicionActual.getEsNegacion()) {

                        // 📌 Mostrar la relación que se eliminará
                        std::cout << "\n🔍 Relación encontrada que cancela una en la proposición actual:\n";
                        relacion.mostrar();

                        // Crear un nuevo estado sin la relación eliminada
                        std::vector<ProposicionesConConectores> nuevoEstado = estadoActual;
                        std::cout << "\n🔍 Relación a eliminar\n";
                        nuevoEstado[i].getRelaciones()[j].mostrar(); 
                        
                         // También eliminamos la relación en proposicionActual
                        Relacion nuevaProposicion = relProposicionActual;

                        std::cout << "\n🔍 Proposicion actual\n" << std::endl;
                        proposicionActual.mostrar();

                        std::cout << "\n🔍 relacion actual\n" << std::endl;
                        relProposicionActual.mostrar();

                        std::cout << "\n🔍 Proposicion actual despues de eliminacion\n" << std::endl;
                        proposicionActual.mostrar();

                        proposicionActual.eliminarRelacion(j);
                        proposicionActual.eliminarRelacion(k);

                        nuevoEstado[i] = proposicionActual;

                            
                        
                        // 📌 Mostrar el estado después de eliminar
                        std::cout << "\n🛠️ Estado después de eliminar la relación:\n";
                        for (const auto& prop : nuevoEstado) {
                            prop.mostrar();
                        }

                        if (nuevoEstado[i].getRelaciones().empty()) {
                            nuevoEstado.erase(nuevoEstado.begin() + i);
                        }

                        

                        // Si no quedan más proposiciones, el teorema ha sido demostrado
                        if (nuevoEstado.empty()) {
                            std::cout << "✅ El teorema ha sido demostrado!\n";
                            return;
                        }

                        
                        // Push al stack con el nuevo estado y nueva proposición
                        estados.push({nuevoEstado, proposicionActual});
                    }
                }
            }
        }
    }

    std::cout << "❌ No se pudo demostrar el teorema con las cláusulas dadas.\n";
}



