// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"
#include "tau.h"

// Initialise tau count
int tau::tau_count = 0;

// Update functions
  // 1. Data member 
void tau::update_information()
{
  if(particle_type == ParticleType::ANTIPARTICLE)
  {
    particle_name = "antitau";
    charge = 1;
    lepton_number = -1;
  }
  else 
  {
    particle_name = "tau";
    charge = -1;
    lepton_number = 1;
  }
}
  // 2. Hadronic decay products
void tau::hadronic_products_update(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2)
{
  // Initialise quark products 
  decay_products.push_back(std::make_shared<quark>(product_1, product_type_1, ColourCharge::RED, 0, 0, 0, 0));
  decay_products.push_back(std::make_shared<quark>(product_2, product_type_2, ColourCharge::RED, 0, 0, 0, 0));

  // Total charge validation
  if(decay_products[0]->get_charge() + decay_products[1]->get_charge() != charge) 
    throw std::logic_error("Total final charge must be equal to initial charge");

  // Initialise tau neutrino product
  decay_products.push_back(std::make_shared<neutrino>(particle_type, Flavour::TAU, false, 0, 0, 0, 0));
}
  // 3. Leptonic decay products
void tau::leptonic_products_update(Flavour product_flavour_in)
{
  // Check for invalid input
  if(product_flavour_in == Flavour::TAU) throw std::invalid_argument("Tau particle cannot decay into tau");

  // Initialise lepton decay products
  ParticleType anti_particle_type = (particle_type == ParticleType::PARTICLE) ? ParticleType::ANTIPARTICLE : ParticleType::PARTICLE;
  switch(product_flavour_in)
  {
    case Flavour::ELECTRON:
      decay_products.push_back(std::make_shared<electron>(particle_type, 0, 0, 0, 0, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<neutrino>(anti_particle_type, product_flavour_in, false, 0, 0, 0, 0));
      break;
    case Flavour::MUON:
      decay_products.push_back(std::make_shared<muon>(particle_type, true, 0, 0, 0, 0));
      decay_products.push_back(std::make_shared<neutrino>(anti_particle_type, product_flavour_in, false, 0, 0, 0, 0));
      break;
  }
  // Initialise tau neutrino 
  decay_products.push_back(std::make_shared<neutrino>(particle_type, Flavour::TAU, false, 0, 0, 0, 0));
}
  

// Default constructor
tau::tau() : lepton("tau", ParticleType::PARTICLE, -1, 0.5, 1, 0, 0, 0, 0), decay_products{} 
{
  rest_mass = 1.776 * 1000; // MeV
  // Update count
  ++tau_count;}

// Parameterised constructor for decay to quark
tau::tau(ParticleType particle_type_in, QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2, double E, double px, double py, double pz) : 
  lepton("tau", particle_type_in, -1, 0.5, 1, E, px, py, pz), decay_products{} 
  {
    rest_mass = 1.776 * 1000; // MeV
    // Validate energy and momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Update count
    ++tau_count;
    // Update data members
    update_information();
    // Declare decay products
    hadronic_products_update(product_1, product_type_1, product_2, product_type_2);
  }

// Parameterised constructor for decay to lepton
tau::tau(ParticleType particle_type_in, Flavour product_flavour_in, double E, double px, double py, double pz) : 
  lepton("tau", particle_type_in, -1, 0.5, 1, E, px, py, pz), decay_products{} 
  {
    rest_mass = 1.776 * 1000; // MeV
    // Validate energy and momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Update count
    ++tau_count;
    // Update data members
    update_information();
    // Declare decay products
    leptonic_products_update(product_flavour_in);
  }

// Destructor
tau::~tau() {--tau_count;}

// Tau copy constructor 
tau::tau(const tau& t) : lepton(t)
{
  decay_products.reserve(t.decay_products.size()); // Optimise memory allocation
  // Deep copy decay products vector
  for (auto it = t.decay_products.begin(); it != t.decay_products.end(); ++it) 
    {decay_products.push_back(std::shared_ptr<particle>((*it)->clone()));}
  ++tau_count; // Update count
}

// Copy assignment
tau & tau::operator=(const tau& t) 
{
  // Check for self-copy
  if (&t != this) 
  { 
    lepton::operator=(t);
    decay_products.clear(); // Ensure empty vector
    decay_products.reserve(t.decay_products.size()); // Optimise memory allocation
    // Ensure empty decay products vector
    decay_products.clear(); 
    for (auto it = t.decay_products.begin(); it != t.decay_products.end(); ++it) 
      {decay_products.push_back(std::shared_ptr<particle>((*it)->clone()));}
  }
  return *this;
}

// Tau move constructor 
tau::tau(tau&& t) : lepton{std::move(t)}, decay_products{std::move(t.decay_products)} {++tau_count;}

// Tau assignment
tau & tau::operator=(tau&& t)  
{
  // Check for self move
  if(&t != this) 
  {
    lepton::operator=(std::move(t)); // Call lepton move assignment
    decay_products = std::move(t.decay_products);
  }
    return *this;
}

// Clone function
std::shared_ptr<particle> tau::clone() const {return std::make_shared<tau>(*this);}

// Get functions 
const std::vector<std::shared_ptr<particle>> tau::get_decay_products() const 
{
  // Check for empty vector
  if(decay_products.empty()) throw std::runtime_error("There are no decay products");
  return decay_products;
}
int tau::get_tau_count() {return tau_count;}

// Set functions
void tau::set_lepton_decay(Flavour product_flavour_in) // For leptonic decay
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Decay products
  leptonic_products_update(product_flavour_in);
}
void tau::set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) // For hadronic decay
{
  // Ensure empty decay products vector
  decay_products.clear();
  // Decay products
  hadronic_products_update(product_1, product_type_1, product_2, product_type_2);
}
void tau::set_particle_type(ParticleType particle_type_in)
{
  lepton::set_particle_type(particle_type_in);
  // Update data members
  update_information();
  // Clear decay products
  decay_products.clear();
}

// Tau print function
void tau::print_data() 
{
  std::cout<<std::endl;
  lepton::print_data();

  // Tau-specific information
  if(decay_products.empty()) 
  {
    std::cout<<"There are no decay products"<<std::endl;
    std::cout<<std::endl;
  } else 
  {
    std::cout<<"Decay products: "<<std::endl;
    int index{1}; // Declare numbering system
    for(auto it=decay_products.begin(); it!=decay_products.end(); ++it, ++index) 
    {
      std::cout<<index<<". "<<(*it)->get_name()<<std::endl;
    }
    std::cout<<std::endl;
  }
  
}
// End of tau class and associated member functions
