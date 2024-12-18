// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "W.h"

using std::string;

// Initialise count
int W::W_count = 0;

// Update functions
void W::update_information(ParticleType particle_type_in) 
{
  if(particle_type_in == ParticleType::PARTICLE) 
  {
    particle_name = "W+";
    charge = 1;
  } 
  else 
  {
    particle_name = "W-";
    charge = -1;
  }
  particle_type = particle_type_in; // Update particle type
}
   // For decay to lepton
void W::update_lepton_decay(LeptonParticle lepton_decay_product_in) 
{
  // Check for neutrino input
  if(lepton_decay_product_in == LeptonParticle::NEUTRINO) throw std::logic_error("W boson cannot decay to just neutrino");

  // Initialise lepton decay products
  ParticleType anti_particle_type = (particle_type == ParticleType::PARTICLE) ? ParticleType::ANTIPARTICLE : ParticleType::PARTICLE;
  switch(lepton_decay_product_in)
  {
    case LeptonParticle::ELECTRON:
      decay_products.push_back(std::make_shared<electron>(anti_particle_type, 0, 0, 0, 0, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<neutrino>(particle_type, Flavour::ELECTRON, false, 0, 0, 0, 0));
      break;
    case LeptonParticle::MUON:
      decay_products.push_back(std::make_shared<muon>(anti_particle_type, true, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<neutrino>(particle_type, Flavour::MUON, false, 0, 0, 0, 0));
      break;
    case LeptonParticle::TAU:
      decay_products.push_back(std::make_shared<tau>());
      if(particle_type == ParticleType::PARTICLE) decay_products[0]->set_particle_type(ParticleType::ANTIPARTICLE);
      decay_products.push_back(std::make_shared<neutrino>(particle_type, Flavour::TAU, false, 0, 0, 0, 0));
      break;
  }
}
  // For decay to quark
void W::update_quark_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) 
{
  // Initialise quark products 
  decay_products.push_back(std::make_shared<quark>(particle_quark_product_in, ParticleType::PARTICLE, ColourCharge::RED, 0, 0, 0, 0));
  decay_products.push_back(std::make_shared<quark>(antiparticle_quark_product_in, ParticleType::ANTIPARTICLE, ColourCharge::RED, 0, 0, 0, 0));

  // Total charge validation
  if(decay_products[0]->get_charge() + decay_products[1]->get_charge() != charge) 
    throw std::logic_error("Total final charge must be equal to initial charge");
}


// Default constructors
W::W() : boson("W+", ParticleType::PARTICLE, 1, 1, 0, 0, 0, 0) 
{
  rest_mass = 80.38 * 1000; // MeV
  // Update count
  ++W_count;
}

// Parameterised constructor for decay to quark
W::W(ParticleType particle_type_in, QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in, double E, double px, double py, double pz) : 
  boson("W+", ParticleType::PARTICLE, 1, 1, E, px, py, pz) 
  {
    rest_mass = 80.38 * 1000; // MeV/c^2
    // Validate four momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Check for antiparticle
    update_information(particle_type_in);
    // Declare decay products
    update_quark_decay(particle_quark_product_in, antiparticle_quark_product_in);
    // Update count
    ++W_count;
  }

// Parameterised constructor for decay to lepton
W::W(ParticleType particle_type_in, LeptonParticle lepton_decay_product_in, double E, double px, double py, double pz) : 
  boson("W+", ParticleType::PARTICLE, 1, 1, E, px, py, pz) 
  {
    rest_mass = 80.38 * 1000; // MeV/c^2
    // Validate four momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Check for antiparticle
    update_information(particle_type_in);
    // Declare decay products
    update_lepton_decay(lepton_decay_product_in);
    // Update count
    ++W_count;
  }

// Destructor
W::~W() {--W_count;}

// Copy constructors 
W::W(const W& w) : boson(w) {++W_count;}

// Copy assignment
W & W::operator=(const W& w) 
{
  // Check for self copy 
  if(&w != this) boson::operator=(w);
  return *this;
}

// Move constructor
W::W(W&& w) : boson(std::move(w)) {++W_count;}

// Move assignment
W & W::operator=(W&& w) 
{
  // Check for self-move
  if(&w != this) boson::operator=(std::move(w));
  return *this;
}

// Clone function
std::shared_ptr<particle> W::clone() const {return std::make_shared<W>(*this);}

// Get function
int W::get_W_count() {return W_count;}

// Set functions
  // 1. For decay to lepton
void W::set_boson_decay(LeptonParticle lepton_decay_product_in) 
{
  // Ensure empty decay product vector
  decay_products.clear();
  // Declare decay products
  update_lepton_decay(lepton_decay_product_in);
}
  // 2. For decay to quark
void W::set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) 
{
  // Ensure empty decay product vector
  decay_products.clear();
  // Declare decay products
  update_quark_decay(particle_quark_product_in, antiparticle_quark_product_in);
}
  // 3. Set particle type
void W::set_particle_type(ParticleType particle_type_in) 
{
  // Update data members
  update_information(particle_type_in);
  // Clear decay products
  decay_products.clear();
}

// Print function
void W::print_data() 
{
  boson::print_data();
  std::cout<<std::endl;
}

