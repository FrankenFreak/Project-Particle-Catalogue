// Clive Marvelous

#ifndef TAU_H
#define TAU_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"
#include "electron.h"
#include "muon.h"
#include "neutrino.h"
#include "quark.h"

// Tau derived class
class tau : public lepton
{
protected:
  // Data members
  static int tau_count;
  std::vector<std::shared_ptr<particle>> decay_products;

  // Update functions
  void update_information();
  void hadronic_products_update(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2);
  void leptonic_products_update(Flavour product_flavour_in);
  
public:
  // Constructor and destructor
  tau();
  tau(ParticleType particle_type_in, QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2, double E, double px, double py, double pz);
  tau(ParticleType particle_type_in, Flavour product_flavour_in, double E, double px, double py, double pz);
  virtual ~tau();
  
  // Copy constructor and assignment
  tau(const tau&);
  tau& operator=(const tau&);

  // Move constructor and assignment
  tau(tau&&);
  tau& operator=(tau&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions
  const std::vector<std::shared_ptr<particle>> get_decay_products() const;
  static int get_tau_count();

  // Set functions
  void set_lepton_decay(Flavour product_flavour_in) override; // For leptonic decay
  void set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) override; // For hadronic decay
  void set_particle_type(ParticleType particle_type_in) override;
  
  // Print data function
  void print_data() override;

};

#endif