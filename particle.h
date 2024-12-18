// Clive Marvelous

#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"

// enum classes:
enum class ParticleType{PARTICLE, ANTIPARTICLE}; // For all classes: Particle or antiparticle
enum class ParticleClass{FERMIONS, BOSONS}; // For all classes: Fermions or bosons
enum class ColourCharge{RED, GREEN, BLUE}; // For quark and boson classes: Colour charge 
enum class Flavour{ELECTRON, MUON, TAU}; // For lepton class: Particle flavours (Neutrino)
enum class QuarkParticle{UP, DOWN, CHARM, STRANGE, TOP, BOTTOM}; // For quark class: Quark particles
enum class LeptonParticle{ELECTRON, MUON, TAU, NEUTRINO}; // For boson class: Lepton particles
enum class BosonParticle{GLUON, PHOTON, Z, W, HIGGS}; // For boson class: Boson particles

// Beginning of particle abstract base class 
class particle
{
protected:
  // Data members
  string particle_name; 
  ParticleType particle_type;
  ParticleClass particle_class;
  float charge;
  float spin;
  double rest_mass; // MeV/c^2
  std::shared_ptr<fourMomentum> four_momentum; 
  static int particle_count; 

  // Validation functions
  virtual void validate_four_momentum_general(double E); // For all particles
  virtual void validate_four_momentum_mass(double E, double px, double py, double pz);  // For mass particles
  virtual void validate_four_momentum_massless(double E, double px, double py, double pz); // For massless particles

public:
  // Constructor and destructor
  particle();
  particle(string name_in, ParticleType particle_type_in, ParticleClass particle_class_in, float charge_in, float spin_in, double E, double px, double py, double pz);
  virtual ~particle();

  // Copy constructor and assignment
  particle(const particle&);
  particle& operator=(const particle&);

  // Move constructor and assignment
  particle(particle&&);
  particle& operator=(particle&&);

  // Clone function (Prevent abstract class initialisation)
  virtual std::shared_ptr<particle> clone() const = 0;

  // Rest mass function
  double restMass();

  // Get functions 
  const string get_name() const;
  const ParticleType get_particle_type() const;
  const ParticleClass get_particle_class() const;
  const float get_charge() const;
  const float get_spin() const;
  const double get_E() const;
  const double get_px() const;
  const double get_py() const;
  const double get_pz() const;
  const std::shared_ptr<fourMomentum>& get_four_momentum() const; 
  static int get_particle_count();

  // Set functions
  void set_name(string name_in);
  void set_particle_class(ParticleClass particle_class_in);
  virtual void set_energy_momentum(double E, double px, double py, double pz) ;

  // Virtual lepton get functions 
  virtual const int get_lepton_number() = 0;
  virtual const double get_EM1() = 0;
  virtual const double get_EM2() = 0;
  virtual const double get_HAD1() = 0;
  virtual const double get_HAD2() = 0;
  virtual const bool get_muon_isolation() = 0;
  virtual const bool get_neutrino_interaction() = 0;
  virtual const std::vector<std::shared_ptr<particle>> get_decay_products() = 0; // Tau and boson

  // Virtual lepton set functions
  virtual void set_particle_type(ParticleType particle_type_in) = 0; // For quark and boson class too
  virtual void set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) = 0; // Electron
  virtual void set_muon_isolation(bool isolation_in) = 0; // Muon
  virtual void set_neutrino_interaction(bool has_interacted) = 0; // Neutrino
  virtual void set_lepton_decay(Flavour product_flavour_in) = 0; // Tau 
  virtual void set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) = 0;

  // Virtual quark get functions
  virtual const string get_quark_particle() = 0;
  virtual const float get_baryon_number() = 0;
  virtual const string get_quark_colour() = 0;

  // Virtual quark set functions
  virtual void set_quark_particle(QuarkParticle quark_particle_in) = 0;
  virtual void set_quark_colour(ColourCharge quark_colour_in) = 0;

  // Virtual boson get functions
  virtual const ColourCharge get_colour() = 0;
  virtual const ColourCharge get_anti_colour() = 0;

  // Virtual boson set functions
  virtual void set_boson_decay(Flavour neutrino_product_flavour_in) = 0; // Z
  virtual void set_boson_decay(LeptonParticle lepton_decay_product_in) = 0; // Z & W
  virtual void set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) = 0; // W
  virtual void set_boson_decay(QuarkParticle quark_decay_product_in) = 0; // Z & Higgs
  virtual void set_boson_decay(BosonParticle boson_decay_product_in) = 0; // Higgs
  virtual void set_colour(ColourCharge colour_in) = 0; // Gluon
  virtual void set_anti_colour(ColourCharge anti_colour_in) = 0;

  // Friend functions
  friend fourMomentum sum(const particle& p1, const particle& p2);
  friend fourMomentum subtract(const particle& p1, const particle& p2);
  friend double dotProduct(const particle& p1, const particle& p2);

  // Print function
  virtual void print_data();
};



#endif