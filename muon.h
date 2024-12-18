// Clive Marvelous

#ifndef MUON_H
#define MUON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"

// Muon derived class
class muon : public lepton
{
protected:
  // Data members
  bool isolated; // true if muon is isolated from other particles
  static int muon_count; 

public:
  // Constructor and destructor
  muon();
  muon(ParticleType particle_type_in, bool isolation_in, double E, double px, double py, double pz);
  ~muon();

  // Copy constructor and assignment
  muon(const muon&); 
  muon& operator=(const muon&); 

  // Move constructor and assignment
  muon(muon&&); 
  muon& operator=(muon&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions 
  const bool get_muon_isolation() override;
  static int get_muon_count();

  // Set functions
  void set_muon_isolation(bool isolation_in) override;
  void set_particle_type(ParticleType particle_type_in) override;

  // Print data function
  void print_data() override;
};

#endif