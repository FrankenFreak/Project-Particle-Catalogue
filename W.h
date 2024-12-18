// Clive Marvelous

#ifndef W_H
#define W_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "quark.h"
#include "electron.h"
#include "muon.h"
#include "tau.h"

using std::string;

// W derived class
class W : public boson 
{
protected:
  // Data members
  static int W_count; 

  // Update functions
  void update_information(ParticleType particle_type_in); 
  void update_lepton_decay(LeptonParticle lepton_decay_product_in); // For decay to lepton
  void update_quark_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in); // For decay to quark

public:
  // Constructor and destructor
  W();
    // Parameterised for decay to quark
  W(ParticleType particle_type_in, QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in, double E, double px, double py, double pz);
    // Parameterised for decay to lepton
  W(ParticleType particle_type_in, LeptonParticle lepton_decay_product_in, double E, double px, double py, double pz);
  ~W();

  // Copy constructor and assignment
  W(const W& w);
  W& operator=(const W& w);

  // Move constructor and assignment
  W(W&& w);
  W& operator=(W&& w);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get function
  static int get_W_count();

  // Set functions
  void set_boson_decay(LeptonParticle lepton_decay_product_in) override; // For decay to lepton
  void set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) override; // For decay to quark
  void set_particle_type(ParticleType particle_type_in) override; 

  // Print function
  void print_data() override;
};

#endif