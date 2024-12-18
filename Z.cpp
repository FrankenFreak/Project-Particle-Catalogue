// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "Z.h"

using std::string;

// Initialise static count
int Z::Z_count = 0;

// Update functions
void Z::update_lepton_decay(LeptonParticle lepton_decay_product_in) // For decay to lepton (Other than neutrino)
{
  // Declare decay products
  ParticleType anti_particle_type = (particle_type == ParticleType::PARTICLE) ? ParticleType::ANTIPARTICLE : ParticleType::PARTICLE;
  switch(lepton_decay_product_in) 
  {
    case LeptonParticle::ELECTRON:
      decay_products.push_back(std::make_shared<electron>(particle_type, 0, 0, 0, 0, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<electron>(anti_particle_type, 0, 0, 0, 0, 0, 0, 0, 0));
      break;
    case LeptonParticle::MUON:
      decay_products.push_back(std::make_shared<muon>(particle_type, true, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<muon>(anti_particle_type, true, 0, 0, 0, 0));
      break;
    case LeptonParticle::TAU:
      decay_products.push_back(std::make_shared<tau>());
      decay_products.push_back(std::make_shared<tau>());
      decay_products[1]->set_particle_type(ParticleType::ANTIPARTICLE);
      break;
  }
}
void Z::update_neutrino_decay(Flavour neutrino_decay_product_in) // For decay to neutrino
{
  // Declare decay products
  ParticleType anti_particle_type = (particle_type == ParticleType::PARTICLE) ? ParticleType::ANTIPARTICLE : ParticleType::PARTICLE;
  decay_products.push_back(std::make_shared<neutrino>(particle_type, neutrino_decay_product_in, false, 0, 0, 0, 0));
  decay_products.push_back(std::make_shared<neutrino>(anti_particle_type, neutrino_decay_product_in, false, 0, 0, 0, 0));
}
void Z::update_quark_decay(QuarkParticle quark_decay_product_in) // For decay to quark
{
  // Declare decay products
  decay_products.push_back(std::make_shared<quark>(quark_decay_product_in, ParticleType::PARTICLE, ColourCharge::RED, 0, 0, 0, 0));
  decay_products.push_back(std::make_shared<quark>(quark_decay_product_in, ParticleType::ANTIPARTICLE, ColourCharge::RED, 0, 0, 0, 0));
}

// Default constructors
Z::Z() : boson("Z", ParticleType::PARTICLE, 0, 1, 0, 0, 0, 0) 
{
  rest_mass = 91.19 * 1000; // MeV/c^2
  // Update function
  ++Z_count;
}

// Parameterised constructor for decay to quark
Z::Z(QuarkParticle quark_decay_product_in, double E, double px, double py, double pz) : boson("Z", ParticleType::PARTICLE, 0, 1, E, px, py, pz) 
{
  rest_mass = 91.19 * 1000; // MeV/c^2
  // Validate four momentum inputs
  validate_four_momentum_mass(E, px, py, pz);
  // Update data members
  update_quark_decay(quark_decay_product_in);
  // Update count
  ++Z_count; 
}

// Parameterised constructor for decay to lepton (Other than neutrino)
Z::Z(LeptonParticle lepton_decay_product_in, double E, double px, double py, double pz) : boson("Z", ParticleType::PARTICLE, 0, 1, E, px, py, pz) 
{
  rest_mass = 91.19 * 1000; // MeV/c^2
  // Validate four momentum inputs
  validate_four_momentum_mass(E, px, py, pz);
  // Update data members
  update_lepton_decay(lepton_decay_product_in);
  // Update count
  ++Z_count;
}

// Parameterised constructor for decay to neutrino
Z::Z(Flavour neutrino_decay_product_in, double E, double px, double py, double pz) : boson("Z", ParticleType::PARTICLE, 0, 1, E, px, py, pz) 
{
  rest_mass = 91.19 * 1000; // MeV/c^2
  // Validate four momentum inputs
  validate_four_momentum_mass(E, px, py, pz);
  // Update data members
  update_neutrino_decay(neutrino_decay_product_in);
  // Update count
  ++Z_count;
}

// Destructor
Z::~Z() {--Z_count;}

// Copy constructors 
Z::Z(const Z& z) : boson(z) {++Z_count;}

// Copy assignment 
Z & Z::operator=(const Z& z) 
{
  // Check for self-copy 
  if(&z != this) boson::operator=(z);
  return *this;
}

// Move constructor
Z::Z(Z&& z) : boson(std::move(z)) {++Z_count;}

// Move assignment
Z & Z::operator=(Z&& z) 
{
  // Self for self-move
  if(&z != this) boson::operator=(std::move(z));
  return *this;
}

// Clone function
std::shared_ptr<particle> Z::clone() const {return std::make_shared<Z>(*this);}

// Get functions 
int Z::get_Z_count() {return Z_count;}

// Set functions
void Z::set_boson_decay(LeptonParticle lepton_decay_product_in) //For decay to lepton (Other than neutrino)
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Declare decay products
  update_lepton_decay(lepton_decay_product_in);
}
void Z::set_boson_decay(Flavour neutrino_product_flavour_in) // For decay to neutrino
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Declare decay products
  update_neutrino_decay(neutrino_product_flavour_in);
}
void Z::set_boson_decay(QuarkParticle quark_decay_product_in) // For decay to quark
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Declare decay products
  update_quark_decay(quark_decay_product_in);
}

// Print function
void Z::print_data() 
{
  boson::print_data();
  std::cout<<std::endl;
}
