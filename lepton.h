// Clive Marvelous

#ifndef LEPTON_H
#define LEPTON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"

// Beginning of lepton class 
class lepton : public particle
{
protected:
  // Data members
  int lepton_number;
  static int lepton_count; 

public:
  // Constructor and destructor
  lepton();
  lepton(string name_in, ParticleType particle_type_in, float charge_in, float spin_in, int lepton_number_in, double E, double px, double py, double pz);
  virtual ~lepton();

  // Copy constructor and assignment
  lepton(const lepton&);
  lepton& operator=(const lepton&);

  // Move constructor and assignment
  lepton(lepton&&);
  lepton& operator=(lepton&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions
  const int get_lepton_number() override;
  static int get_lepton_count();
  const double get_EM1() override; // Electron
  const double get_EM2() override;
  const double get_HAD1() override;
  const double get_HAD2() override;
  const bool get_muon_isolation() override; // Muon
  const bool get_neutrino_interaction() override; // Neutrino
  const std::vector<std::shared_ptr<particle>> get_decay_products() override; // Tau

  // Set functions
  void set_particle_type(ParticleType particle_type_in) override;
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

  // Boson get functions
  const ColourCharge get_colour() override; // Gluon
  const ColourCharge get_anti_colour() override;

  // Boson set functions
  void set_boson_decay(Flavour neutrino_product_flavour_in) override; // Z
  void set_boson_decay(LeptonParticle lepton_decay_product_in) override; // Z & W
  void set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) override; // W
  void set_boson_decay(QuarkParticle quark_decay_product_in) override; // Z & Higgs
  void set_boson_decay(BosonParticle boson_decay_product_in) override; // Higgs
  void set_colour(ColourCharge colour_in) override; // Gluon
  void set_anti_colour(ColourCharge anti_colour_in) override;

  // Print function
  virtual void print_data();
};



#endif