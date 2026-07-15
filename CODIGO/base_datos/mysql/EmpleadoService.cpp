#include "EmpleadoService.h"

EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio):cache(cache), repositorio(repositorio)
{
}

std::optional<Empleado> EmpleadoService::read(int id)
{

}


bool EmpleadoService::create(const Empleado& e)
{

}


EmpleadoService::~EmpleadoService()
{
}

