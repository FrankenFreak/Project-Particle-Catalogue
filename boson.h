// Clive Marvelous

#ifndef BOSON_H
#define BOSON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"

// Beginning of boson class 
class boson : public particle
{
protected:
  // Data members
  std::vector<std::shared_ptr<particle>> decay_products;
  static int boson_count; 

public:
  // Constructor and destructor
  boson();
  boson(string name_in, ParticleType particle_type_in, float charge_in, float spin_in, double E, double px, double py, double pz);
  virtual ~boson();

  // Copy constructor and assignment
  boson(const boson&);
  boson& operator=(const boson&);

  // Move constructor and assignment
  boson(boson&&);
  boson& operator=(boson&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions
  static int get_boson_count();
  const std::vector<std::shared_ptr<particle>> get_decay_products() override;
  const ColourCharge get_colour() override; // Gluon
  const ColourCharge get_anti_colour() override;

  // Set functions
  void set_particle_type(ParticleType particle_type_in) override;
  void set_boson_decay(Flavour neutrino_product_flavour_in) override; // Z
  void set_boson_decay(LeptonParticle lepton_decay_product_in) override; // Z & W
  void set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) override; // W
  void set_boson_decay(QuarkParticle quark_decay_product_in) override; // Z & Higgs
  void set_boson_decay(BosonParticle boson_decay_product_in) override; // Higgs
  void set_colour(ColourCharge colour_in) override; // Gluon
  void set_anti_colour(ColourCharge anti_colour_in) override;

  // Lepton get functions
  const int get_lepton_number() override;
  const double get_EM1() override; // Electron
  const double get_EM2() override;
  const double get_HAD1() override;
  const double get_HAD2() override;
  const bool get_muon_isolation() override; // Muon
  const bool get_neutrino_interaction() override; // Neutrino
  
  // Lepton set functions
  void set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) override; // Electron
  void set_muon_isolation(bool isolation_in) override; // Muon
  void set_neutrino_interaction(bool has_interacted) override; // Neutrino
  void set_lepton_decay(Flavour product_flavour_in) override; // Tau
  void set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) override;

  // Quark get functions
  const string get_quark_particle() override;
  const float get_baryon_number() override;
  const string get_quark_colour() override;

  // Quark set functions
  void set_quark_colour(ColourCharge quark_colour_in) override;
  void set_quark_particle(QuarkParticle quark_particle_in) override;

  // Print function
  virtual void print_data();
};



#endif