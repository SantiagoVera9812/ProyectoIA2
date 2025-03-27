#include "ProposicionesConConectores.h"
#include <vector>
#include "Relacion.h"
#include "manejoDeClausulas.h"


ProposicionesConConectores::ProposicionesConConectores(std::string conector, std::vector<Relacion> relaciones)
: conector(conector), relaciones(relaciones) {}
