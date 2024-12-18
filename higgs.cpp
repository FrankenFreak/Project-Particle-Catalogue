// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "higgs.h"

using std::string;

// Initialise static count
int higgs::higgs_count = 0;

// Update functions
  // For decay to boson
void higgs::update_boson_decay(BosonParticle boson_decay_product_in) 
{
  // Check for correct input
  if (boson_decay_product_in == BosonParticle::GLUON || boson_decay_product_in == BosonParticle::HIGGS) 
    {throw std::logic_error("Higgs boson cannot decay to Gluon or Higgs bosons");}
  // Ensure empty decay products vector
  decay_products.clear(); 
  // Declare products
  switch (boson_decay_product_in) 
  {
    case BosonParticle::Z:
      decay_products.push_back(std::make_shared<Z>());
      decay_products.push_back(std::make_shared<Z>());
      break;
    case BosonParticle::W:
      decay_products.push_back(std::make_shared<W>());
      decay_products.push_back(std::make_shared<W>());
      decay_products[1]->set_particle_type(ParticleType::ANTIPARTICLE);
      break;
    case BosonParticle::PHOTON:
      decay_products.push_back(std::make_shared<photon>());
      decay_products.push_back(std::make_shared<photon>());
      break;
  }
}
  // For decay to quark
void higgs::update_quark_decay(QuarkParticle quark_decay_product_in) 
{
  // Ensure empty decay products vector
  decay_products.clear(); 
  // Declare products
  decay_products.push_back(std::make_shared<quark>(quark_decay_product_in, ParticleType::PARTICLE, ColourCharge::RED, 0, 0, 0, 0));
  decay_products.push_back(std::make_shared<quark>(quark_decay_product_in, ParticleType::ANTIPARTICLE, ColourCharge::RED, 0, 0, 0, 0));
}

// Default constructor
higgs::higgs() : boson("higgs", ParticleType::PARTICLE, 0, 0, 0, 0, 0, 0) 
{
  rest_mass = 125.1 * 1000; // MeV/c^2
  // Update count
  ++higgs_count; 
}

// Parameterised constructor for decay to quark
higgs::higgs(QuarkParticle quark_decay_product_in, double E, double px, double py, double pz) : boson("higgs", ParticleType::PARTICLE, 0, 0, E, px, py, pz) 
{
  rest_mass = 125.1 * 1000; // MeV/c^2
  // Validate four momentum inputs
  validate_four_momentum_mass(E, px, py, pz);
  // Declare decay products
  update_quark_decay(quark_decay_product_in);
  // Update count
  ++higgs_count; 
}

// Parameterised constructor for decay to boson
higgs::higgs(BosonParticle boson_decay_product_in, double E, double px, double py, double pz) : boson("higgs", ParticleType::PARTICLE, 0, 0, E, px, py, pz) 
{
  rest_mass = 125.1 * 1000; // MeV/c^2
  // Validate four momentum inputs
  validate_four_momentum_mass(E, px, py, pz);
  // Declare decay products
  update_boson_decay(boson_decay_product_in);
  // Update count
  ++higgs_count;
}

// Destructor
higgs::~higgs() {--higgs_count;}

// Copy constructor
higgs::higgs(const higgs& h) : boson(h) {++higgs_count;}

// Copy assignment
higgs & higgs::operator=(const higgs& h) 
{
  if(&h != this) boson::operator=(h);
  return *this;
}

// Move constructor
higgs::higgs(higgs&& h) : boson(std::move(h)) {++higgs_count;}

// Move assignment
higgs & higgs::operator=(higgs&& h) 
{
  if (&h != this) boson::operator=(std::move(h));
  return *this;
}

// Clone function
std::shared_ptr<particle> higgs::clone() const {return std::make_shared<higgs>(*this);}

// Get functions
int higgs::get_higgs_count() {return higgs_count;}

// Set functions
void higgs::set_boson_decay(BosonParticle boson_decay_product_in) // Set decay to boson
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Declare decay products
  update_boson_decay(boson_decay_product_in);
}
void higgs::set_boson_decay(QuarkParticle quark_decay_product_in) // Set decay to quark
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Declare decay products
  update_quark_decay(quark_decay_product_in);
}

// Print function
void higgs::print_data() 
{
  boson::print_data();
  std::cout<<std::endl;
}



