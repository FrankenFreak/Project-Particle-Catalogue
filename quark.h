// Clive Marvelous

#ifndef QUARK_H
#define QUARK_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<utility>
#include<map>

using std::string;

#include "fourMomentum.h"
#include "particle.h"

// Beginning of quark class 
class quark : public particle
{
private: 
  // Simple struct to streamline information update
  struct quarkInformation 
  {
    // Data members
    std::string name;
    float charge;
    float baryon_n;
    double rest_mass_value; // MeV
    // Constructor
    quarkInformation(string n, float c, float b, double rm) : name{n}, charge{c}, baryon_n{b}, rest_mass_value{rm} {}
  };

  // Static map container to streamline data member update
  static const std::map<std::pair<QuarkParticle, ParticleType>, quarkInformation> information;
  // Update function
  void update_information();

protected:
  QuarkParticle quark_particle;
  float baryon_number;
  ColourCharge quark_colour;
  static int quark_count; // Count quark particle created

public:
  // Constructor and destructor
  quark();
  quark(QuarkParticle quark_particle_in, ParticleType particle_type_in, ColourCharge quark_colour_in, double E, double px, double py, double pz);
  ~quark();

  // Copy constructor and assignment
  quark(const quark&);
  quark& operator=(const quark&);

  // Move constructor and assignment
  quark(quark&&);
  quark& operator=(quark&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions 
  const string get_quark_particle() override;
  const float get_baryon_number() override;
  const string get_quark_colour() override;
  static int get_quark_count();

  // Set functions
  void set_quark_particle(QuarkParticle quark_particle_in) override;
  void set_quark_colour(ColourCharge quark_colour_in) override;
  void set_particle_type(ParticleType particle_type_in) override;

  // Lepton get functions
  const int get_lepton_number() override;
  const double get_EM1() override;
  const double get_EM2() override;
  const double get_HAD1() override;
  const double get_HAD2() override;
  const bool get_muon_isolation() override;
  const bool get_neutrino_interaction() override;
  const std::vector<std::shared_ptr<particle>> get_decay_products() override;

  // Lepton set functions
  void set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) override; // Electron
  void set_muon_isolation(bool isolation_in) override; // Muon
  void set_neutrino_interaction(bool has_interacted) override; // Neutrino
  void set_lepton_decay(Flavour product_flavour_in) override; // Tau
  void set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) override;

  // Boson get functions
  const ColourCharge get_colour() override;
  const ColourCharge get_anti_colour() override;

  // Boson set functions
  void set_colour(ColourCharge colour_in) override;
  void set_anti_colour(ColourCharge anti_colour_in) override;
  void set_boson_decay(Flavour neutrino_product_flavour_in) override; // Z
  void set_boson_decay(LeptonParticle lepton_decay_product_in) override; // Z & W
  void set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) override; // W
  void set_boson_decay(QuarkParticle quark_decay_product_in) override; // Z & Higgs
  void set_boson_decay(BosonParticle boson_decay_product_in) override; // Higgs

  // Print function
  virtual void print_data();
};



#endif