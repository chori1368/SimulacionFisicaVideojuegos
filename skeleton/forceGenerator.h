#pragma once
#include <vector>
#include "Particle.h"

class forceGenerator
{
public:
	forceGenerator() : enabled(true) {}
	virtual ~forceGenerator() = default;

	void addAfeccted(Particle* particula);
	void removeAfeccted(Particle* particula);
	virtual void update(double t);

	// Control de activación
	void setEnabled(bool state) { enabled = state; }
	bool isEnabled() const { return enabled; }
	void toggleEnabled() { enabled = !enabled; }

	void clearAllReferences() { particulas.clear(); }

protected:
	virtual void applyForce(Particle* particula, double t) = 0;
	std::vector<Particle*> particulas;
	bool enabled;
};