// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"

using std::string;

// Initialise boson count
int boson::boson_count = 0;

// Default constructor
boson::boson() : particle(), decay_products{} 
{
  // Update data members
  particle_class = ParticleClass::BOSONS;
  ++boson_count;
}

// Parameterised constructor
boson::boson(string name_in, ParticleType particle_type_in, float charge_in, float spin_in, double E, double px, double py, double pz) : 
  particle(name_in, particle_type_in, ParticleClass::BOSONS, charge_in, spin_in, E, px, py, pz), decay_products{} {++boson_count;}

// Destructor
boson::~boson() {--boson_count;}

// Copy constructor
boson::boson(const boson& b) : particle(b) 
{
  // Optimise memory allocation process
  decay_products.reserve(b.decay_products.size());
  // Deep copy decay products
  for (auto it = b.decay_products.begin(); it != b.decay_products.end(); ++it) 
    decay_products.push_back(std::shared_ptr<particle>((*it)->clone()));
  // Update count
  ++boson_count;
}

// Copy assignment
boson & boson::operator=(const boson& b) 
{
  // Check for self-copy
  if(&b != this) 
  {
    particle::operator=(b);
    // Ensure empty decay products vector
    decay_products.clear();
    // Optimise memory allocation process
    decay_products.reserve(b.decay_products.size());
    // Deep copy decay products
    for (auto it = b.decay_products.begin(); it != b.decay_products.end(); ++it) 
      decay_products.push_back(std::shared_ptr<particle>((*it)->clone()));
  }
  return *this;
}

// Move constructor
boson::boson(boson&& b) : particle(std::move(b)), decay_products(std::move(b.decay_products)) {++boson_count;}

// Move assignment
boson & boson::operator=(boson&& b) 
{
  // Prevent self-move
  if(&b != this) 
  {
    particle::operator=(std::move(b));
    decay_products = std::move(b.decay_products);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> boson::clone() const {return std::make_shared<boson>(*this);}

// Get functions
const std::vector<std::shared_ptr<particle>> boson::get_decay_products() 
{
  // Check for empty vector
  if(decay_products.empty()) throw std::runtime_error("There are no decay products");
  return decay_products;
}
const ColourCharge boson::get_colour() {throw std::logic_error("get_colour is available only for gluon class");}
const ColourCharge boson::get_anti_colour() {throw std::logic_error("get_anti_colour is available only for gluon class");}
int boson::get_boson_count() {return boson_count;} 

// Lepton get functions 
const int boson::get_lepton_number() {throw std::logic_error("get_lepton_number is available only for lepton class");}
const double boson::get_EM1() {throw std::logic_error("get_EM1 is available only for electron class");} // Electron
const double boson::get_EM2() {throw std::logic_error("get_EM1 is available only for electron class");}
const double boson::get_HAD1() {throw std::logic_error("get_HAD1 is available only for electron class");}
const double boson::get_HAD2() {throw std::logic_error("get_HAD2 is available only for electron class");}
const bool boson::get_muon_isolation() {throw std::logic_error("get_muon_isolation is available only for muon class");} // Muon
const bool boson::get_neutrino_interaction() {throw std::logic_error("get_neutrino_interaction is available only for neutrino class");} // Neutrino

// Quark get functions 
const string boson::get_quark_particle() {throw std::logic_error("get_quark_particle is available only for quark class");}
const float boson::get_baryon_number() {throw std::logic_error("get_baryon_number is available only for quark class");}
const string boson::get_quark_colour() {throw std::logic_error("get_quark_colour is available only for quark class");}

// Set functions
void boson::set_particle_type(ParticleType particle_type_in) {throw std::logic_error("set_particle_type is not available");}
void boson::set_boson_decay(Flavour neutrino_product_flavour_in) {throw std::logic_error("set_boson_decay is not available");} // Z
void boson::set_boson_decay(LeptonParticle lepton_decay_product_in) {throw std::logic_error("set_boson_decay is not available");} // Z & W
void boson::set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) 
  {throw std::logic_error("set_boson_decay is not available");} // W
void boson::set_boson_decay(QuarkParticle quark_decay_product_in) {throw std::logic_error("set_boson_decay is not available");} // Z & Higgs 
void boson::set_boson_decay(BosonParticle boson_decay_product_in) {throw std::logic_error("set_boson_decay is not available");} // Higgs
void boson::set_colour(ColourCharge colour_in) {throw std::logic_error("set_colour is available only for gluon class");} // Gluon
void boson::set_anti_colour(ColourCharge anti_colour_in) {throw std::logic_error("set_anti_colour is available only for gluon class");}

// Lepton set functions
void boson::set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) {throw std::logic_error("set_energy_deposit is available only for electron class");} // Electron
void boson::set_muon_isolation(bool isolation_in) {throw std::logic_error("set_muon_isolation is available only for muon class");} // Muon
void boson::set_neutrino_interaction(bool has_interacted) {throw std::logic_error("set_neutrino_interaction is available only for neutrino class");} // Neutrino
void boson::set_lepton_decay(Flavour product_flavour_in) {throw std::logic_error("set_decay is available only for tau class");} // Tau
void boson::set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) 
  {throw std::logic_error("set_decay is available only for tau class");} 

// Quark set functions
void boson::set_quark_colour(ColourCharge quark_colour_in) {throw std::logic_error("set_quark_colour is available only for quark class");}
void boson::set_quark_particle(QuarkParticle quark_particle_in) {throw std::logic_error("set_quark_particle is available only for quark class");}

// Print function
void boson::print_data() 
{
  particle::print_data();
  if(!decay_products.empty()) 
  {
    std::cout<<"Decay products: "<<std::endl;
    int index{1};
    for(auto it = decay_products.begin(); it != decay_products.end(); ++it, ++index) 
      std::cout<<index<<". "<<(*it)->get_name()<<std::endl;
    std::cout << std::endl;
  }
}

