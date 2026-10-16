#include "forceGenerator.h"

forceGenerator::forceGenerator(Force Fuerza) : fuerza(Fuerza){}

void forceGenerator::addAfeccted(Particle* particula) {
	particulas.push_back(particula);
}

void forceGenerator::removeAfeccted(Particle* particula) {
}

void forceGenerator::update(double t) {

}