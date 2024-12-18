// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"

using std::string;

// Initialise lepton count
int lepton::lepton_count = 0;

// Default constructor
lepton::lepton() : particle(), lepton_number{} 
{

  particle_class = ParticleClass::FERMIONS;
  // Update count
  ++lepton_count;
}

// Parameterised constructor
lepton::lepton(string name_in, ParticleType particle_type_in, float charge_in, float spin_in, int lepton_number_in, double E, double px, double py, double pz) : 
  particle(name_in, particle_type_in, ParticleClass::FERMIONS, charge_in, spin_in, E, px, py, pz), lepton_number{lepton_number_in} {++lepton_count;}

// Destructor
lepton::~lepton() {--lepton_count;}

// Copy constructor 
lepton::lepton(const lepton& l) : particle{l}, lepton_number{l.lepton_number} {++lepton_count;}

// Copy assignment
lepton & lepton::operator=(const lepton& l)
{
  // Check for self-copy
  if(&l != this) 
  { 
    particle::operator=(l);
    lepton_number = l.lepton_number;
  }
  return *this;
}

// Move constructor 
lepton::lepton(lepton&& l) : particle{std::move(l)}, lepton_number{std::move(l.lepton_number)} {++lepton_count;}

// Move assignment
lepton & lepton::operator=(lepton&& l)
{
  // Prevent self-move
  if(&l != this) 
  {
    particle::operator=(std::move(l));
    lepton_number = std::move(l.lepton_number);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> lepton::clone() const {return std::make_shared<lepton>(*this);}

// Get functions 
const int lepton::get_lepton_number() {return lepton_number;}
int lepton::get_lepton_count() {return lepton_count;} 
const double lepton::get_EM1() {throw std::logic_error("get_EM1 is available only for electron class");} // Electron
const double lepton::get_EM2() {throw std::logic_error("get_EM1 is available only for electron class");}
const double lepton::get_HAD1() {throw std::logic_error("get_HAD1 is available only for electron class");}
const double lepton::get_HAD2() {throw std::logic_error("get_HAD2 is available only for electron class");}
const bool lepton::get_muon_isolation() {throw std::logic_error("get_muon_isolation is available only for muon class");} // Muon
const bool lepton::get_neutrino_interaction() {throw std::logic_error("get_neutrino_interaction is available only for neutrino class");} // Neutrino
const std::vector<std::shared_ptr<particle>> lepton::get_decay_products() {throw std::logic_error("get_decay_products is available only for tau class");} // Tau

// Quark get functions 
const string lepton::get_quark_particle() {throw std::logic_error("get_quark_particle is available only for quark class");}
const float lepton::get_baryon_number() {throw std::logic_error("get_baryon_number is available only for quark class");}
const string lepton::get_quark_colour() {throw std::logic_error("get_quark_colour is available only for quark class");}

// Boson get function
const ColourCharge lepton::get_colour() {throw std::logic_error("get_colour is available only for gluon class");} // Gluon
const ColourCharge lepton::get_anti_colour() {throw std::logic_error("get_anti_colour is available only for gluon class");}

// Set functions
void lepton::set_particle_type(ParticleType particle_type_in)  
{
  particle_type=particle_type_in;
  lepton_number = (particle_type == ParticleType::ANTIPARTICLE) ? -1 : 1;
}
void lepton::set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) {throw std::logic_error("set_energy_deposit is available only for electron class");} // Electron
void lepton::set_muon_isolation(bool isolation_in) {throw std::logic_error("set_muon_isolation is available only for muon class");} // Muon
void lepton::set_neutrino_interaction(bool has_interacted) {throw std::logic_error("set_neutrino_interaction is available only for neutrino class");} // Neutrino
void lepton::set_lepton_decay(Flavour product_flavour_in) {throw std::logic_error("set_decay is available only for tau class");} // Tau
void lepton::set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) 
  {throw std::logic_error("set_decay is available only for tau class");} 

// Quark set functions
void lepton::set_quark_colour(ColourCharge quark_colour_in) {throw std::logic_error("set_quark_colour is available only for quark class");}
void lepton::set_quark_particle(QuarkParticle quark_particle_in) {throw std::logic_error("set_quark_particle is available only for quark class");}

// Boson set functions
void lepton::set_boson_decay(Flavour neutrino_product_flavour_in) // Z
  {throw std::logic_error("set_boson_decay is available only for boson class");}
void lepton::set_boson_decay(LeptonParticle lepton_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Z & W
void lepton::set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) // W
  {throw std::logic_error("set_boson_decay is available only for boson class");}
void lepton::set_boson_decay(QuarkParticle quark_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Z & Higgs
void lepton::set_boson_decay(BosonParticle boson_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Higgs
void lepton::set_colour(ColourCharge colour_in) {throw std::logic_error("set_colour is available only for boson class");}
void lepton::set_anti_colour(ColourCharge anti_colour_in) {throw std::logic_error("set_anti_colour is available only for gluon class");}

// Print function
void lepton::print_data()
{
  // Prevent double printing
  particle::print_data();

  // Lepton specific info
  std::cout<<"Lepton Number: "<<lepton_number<<std::endl;
  return;
}

