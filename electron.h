// Clive Marvelous

#ifndef ELECTRON_H
#define ELECTRON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <memory>

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"

using std::string;

// Electron derived class
class electron : public lepton
{
protected:
  // Data members
  std::vector<double> energy_deposited_in_calorimeter;
  static int electron_count;

  // Validation function
  void validate_energy_deposit(double E, double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) ;

public:
  // Constructor and destructor
  electron();
  electron(ParticleType particle_type_in, double E, double px, double py, double pz, double EM_1, double EM_2, double HAD_1, double HAD_2);
  ~electron();

  // Copy constructor and assignment
  electron(const electron&); 
  electron& operator=(const electron&); 

  // Move constructor and assignment
  electron(electron&&); 
  electron& operator=(electron&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions 
  const double get_EM1() override;
  const double get_EM2() override;
  const double get_HAD1() override;
  const double get_HAD2() override;
  static int get_electron_count();

  // Set functions
  void set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) override;
  void set_particle_type(ParticleType particle_type_in) override;

  // Print data function
  void print_data() override;
};

#endif