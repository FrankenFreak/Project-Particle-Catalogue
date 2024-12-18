// Clive Marvelous, last updated 6/4/24

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"

// Neutrino derived class
class neutrino : public lepton
{
protected:
  // Data members
  Flavour flavour; // Neutrino flavour
  bool hasInteracted; // true if neutrino interacted with detector
  static int neutrino_count; 

  // Update name function
  void update_name();
public:
  // Constructor and destructor
  neutrino();
  neutrino(ParticleType particle_type_in, Flavour flavour_in, bool interaction_in, double E, double px, double py, double pz);
  ~neutrino();

  // Copy constructor and assignment
  neutrino(const neutrino&); 
  neutrino& operator=(const neutrino&); 

  // Move constructor and assignment
  neutrino(neutrino&&); 
  neutrino& operator=(neutrino&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions 
  const bool get_neutrino_interaction() override;
  static int get_neutrino_count();

  // Set functions
  void set_neutrino_interaction(bool has_interacted) override;
  void set_particle_type(ParticleType particle_type_in) override;
  
  // Print data function
  void print_data() override;
};

#endif