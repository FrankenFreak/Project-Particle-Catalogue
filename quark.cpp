// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<utility>
#include<map>

#include "fourMomentum.h"
#include "particle.h"
#include "quark.h"

using std::string;

// Initialise static map container
const std::map<std::pair<QuarkParticle, ParticleType>, quark::quarkInformation> quark::information
{
  {{QuarkParticle::UP, ParticleType::PARTICLE}, {"Up", 2.0/3.0, 1.0/3.0, 2.2}},
  {{QuarkParticle::UP, ParticleType::ANTIPARTICLE}, {"Anti-Up", -2.0/3.0, -1.0/3.0, 2.2}},
  {{QuarkParticle::DOWN, ParticleType::PARTICLE}, {"Down", -1.0/3.0, 1.0/3.0, 4.7}},
  {{QuarkParticle::DOWN, ParticleType::ANTIPARTICLE}, {"Anti-Down", 1.0/3.0, -1.0/3.0, 4.7}},
  {{QuarkParticle::CHARM, ParticleType::PARTICLE}, {"Charm", 2.0/3.0, 1.0/3.0, 1.275 * 1000}},
  {{QuarkParticle::CHARM, ParticleType::ANTIPARTICLE}, {"Anti-Charm", -2.0/3.0, -1.0/3.0, 1.275 * 1000}},
  {{QuarkParticle::STRANGE, ParticleType::PARTICLE}, {"Strange", -1.0/3.0, 1.0/3.0, 95}},
  {{QuarkParticle::STRANGE, ParticleType::ANTIPARTICLE}, {"Anti-Strange", 1.0/3.0, -1.0/3.0, 95}},
  {{QuarkParticle::TOP, ParticleType::PARTICLE}, {"Top", 2.0/3.0, 1.0/3.0, 172.76 * 1000}},
  {{QuarkParticle::TOP, ParticleType::ANTIPARTICLE}, {"Anti-Top", -2.0/3.0, -1.0/3.0, 172.76 * 1000}},
  {{QuarkParticle::BOTTOM, ParticleType::PARTICLE}, {"Bottom",-1.0/3.0, 1.0/3.0, 4.18 * 1000}},
  {{QuarkParticle::BOTTOM, ParticleType::ANTIPARTICLE}, {"Anti-Bottom", 1.0/3.0, -1.0/3.0, 4.18 * 1000}}
};

// Update function
void quark::update_information() 
{
  // Find and update data 
  auto information_it = information.find({quark_particle, particle_type});
  if(information_it != information.end())
  {
    particle_name = information_it->second.name;
    charge = information_it->second.charge;
    baryon_number = information_it->second.baryon_n;
    rest_mass = information_it->second.rest_mass_value;
  }
};

// Initialise quark count
int quark::quark_count = 0;

// Default constructor 
quark::quark() : particle(), quark_colour{}, baryon_number{}
  {
    // Update quark number
    ++quark_count; 
    // Update particle_class
    particle_class = ParticleClass::BOSONS;
  }

// Parameterised constructor
quark::quark(QuarkParticle quark_particle_in, ParticleType particle_type_in, ColourCharge quark_colour_in, double E, double px, double py, double pz) : 
  particle("quark", particle_type_in, ParticleClass::FERMIONS, 0, 0.5, E, px, py, pz), quark_particle{quark_particle_in}, quark_colour{quark_colour_in} 
  {
    // Automatically update quark information
    update_information();
    // Validate energy and momentum inputs 
    validate_four_momentum_mass(E, px, py, pz);
    // Update quark number
    ++quark_count; 
  }

// Destructor
quark::~quark() {--quark_count;}

// Copy constructor 
quark::quark(const quark& q) : particle{q}, quark_particle{q.quark_particle}, 
  quark_colour{q.quark_colour}, baryon_number{q.baryon_number} {++quark_count;}

// Copy assignment
quark & quark::operator=(const quark& q)
{
  // Check for self-copy
  if(&q != this) 
  { 
    particle::operator=(q);
    quark_particle = q.quark_particle;
    baryon_number = q.baryon_number;
    quark_colour = q.quark_colour;
  }
  return *this;
}

// Move constructor 
quark::quark(quark&& q) : particle{std::move(q)}, quark_particle{std::move(q.quark_particle)}, 
quark_colour{std::move(q.quark_colour)}, baryon_number{std::move(q.baryon_number)} {++quark_count;}

// Move assignment
quark & quark::operator=(quark&& q)
{
  // Prevent self-move
  if(&q != this) 
  {
    particle::operator=(std::move(q));
    quark_particle = std::move(q.quark_particle);
    quark_colour = std::move(q.quark_colour);
    baryon_number = std::move(q.baryon_number);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> quark::clone() const {return std::make_shared<quark>(*this);}

// Get functions 
const string quark::get_quark_particle() 
{
  auto information_it = information.find({quark_particle, particle_type});
  if(information_it != information.end()) return information_it->second.name;
  return "Cannot find information"; // When information cannot be found
}
const float quark::get_baryon_number() {return baryon_number;}
const string quark::get_quark_colour() 
{
  if(quark_colour == ColourCharge::RED && particle_type == ParticleType::PARTICLE) return "Red";
  else if(quark_colour == ColourCharge::RED && particle_type == ParticleType::ANTIPARTICLE) return "Antired";
  else if(quark_colour == ColourCharge::GREEN && particle_type == ParticleType::PARTICLE) return "Green";
  else if(quark_colour == ColourCharge::GREEN && particle_type == ParticleType::ANTIPARTICLE) return "Antigreen";
  else if(quark_colour == ColourCharge::BLUE && particle_type == ParticleType::PARTICLE) return "Blue";
  else if(quark_colour == ColourCharge::BLUE && particle_type == ParticleType::ANTIPARTICLE) return "Antiblue";
  return "Cannot find colour charge"; 
}
int quark::get_quark_count() {return quark_count;} 

// Lepton get functions
const int quark::get_lepton_number() {throw std::logic_error("get_lepton_number is available only for lepton class");}
const double quark::get_EM1() {throw std::logic_error("get_EM1 is available only for electron class");} // Electron
const double quark::get_EM2() {throw std::logic_error("get_EM1 is available only for electron class");}
const double quark::get_HAD1() {throw std::logic_error("get_HAD1 is available only for electron class");}
const double quark::get_HAD2() {throw std::logic_error("get_HAD2 is available only for electron class");}
const bool quark::get_muon_isolation() {throw std::logic_error("get_muon_isolation is available only for muon class");} // Muon
const bool quark::get_neutrino_interaction() {throw std::logic_error("get_neutrino_interaction is available only for neutrino class");} // Neutrino
const std::vector<std::shared_ptr<particle>> quark::get_decay_products() {throw std::logic_error("get_decay_products is available only for tau class");} // Tau & Boson

// Boson get functions
const ColourCharge quark::get_colour() {throw std::logic_error("get_colour is available only for gluon class");}
const ColourCharge quark::get_anti_colour() {throw std::logic_error("get_anti_colour is available only for gluon class");}

// Set functions
void quark::set_quark_particle(QuarkParticle quark_particle_in) 
{
  quark_particle=quark_particle_in;
  // Automatically update quark information
  update_information();
}
void quark::set_quark_colour(ColourCharge quark_colour_in) {quark_colour=quark_colour_in;}
void quark::set_particle_type(ParticleType particle_type_in) 
{
  particle_type=particle_type_in;
  // Automatically update quark information
  update_information();
}

// Lepton set functions
void quark::set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) {throw std::logic_error("set_energy_deposit is available only for electron class");} // Electron
void quark::set_muon_isolation(bool isolation_in) {throw std::logic_error("set_muon_isolation is available only for muon class");} // Muon
void quark::set_neutrino_interaction(bool has_interacted) {throw std::logic_error("set_neutrino_interaction is available only for neutrino class");}  // Neutrino
void quark::set_lepton_decay(Flavour product_flavour_in) {throw std::logic_error("set_decay is available only for tau class");} // Tau
void quark::set_lepton_decay(QuarkParticle product_1, ParticleType product_type_1, QuarkParticle product_2, ParticleType product_type_2) 
  {throw std::logic_error("set_decay is available only for tau class");}  

// Boson set functions
void quark::set_colour(ColourCharge colour_in) {throw std::logic_error("set_colour is available only for boson class");}
void quark::set_anti_colour(ColourCharge anti_colour_in) {throw std::logic_error("set_anti_colour is available only for gluon class");}
void quark::set_boson_decay(Flavour neutrino_product_flavour_in) // Z
  {throw std::logic_error("set_boson_decay is available only for boson class");}
void quark::set_boson_decay(LeptonParticle lepton_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Z & W
void quark::set_boson_decay(QuarkParticle particle_quark_product_in, QuarkParticle antiparticle_quark_product_in) // W
  {throw std::logic_error("set_boson_decay is available only for boson class");}
void quark::set_boson_decay(QuarkParticle quark_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Z & Higgs
void quark::set_boson_decay(BosonParticle boson_decay_product_in) {throw std::logic_error("set_boson_decay is available only for boson class");} // Higgs

// Print function
void quark::print_data()
{
  // Prevent double printing
  particle::print_data();

  // Quark specific information
  std::cout<<"Baryon Number: "<<baryon_number<<std::endl;
  std::cout<<"Colour charge: ";
  if(quark_colour == ColourCharge::RED && particle_type == ParticleType::PARTICLE) std::cout<<"Red"<<std::endl;
  else if(quark_colour == ColourCharge::RED && particle_type == ParticleType::ANTIPARTICLE) std::cout<<"Antired"<<std::endl;
  else if(quark_colour == ColourCharge::GREEN && particle_type == ParticleType::PARTICLE) std::cout<<"Green"<<std::endl;
  else if(quark_colour == ColourCharge::GREEN && particle_type == ParticleType::ANTIPARTICLE) std::cout<<"Antigreen"<<std::endl;
  else if(quark_colour == ColourCharge::BLUE && particle_type == ParticleType::PARTICLE) std::cout<<"Blue"<<std::endl;
  else if(quark_colour == ColourCharge::BLUE && particle_type == ParticleType::ANTIPARTICLE) std::cout<<"Antiblue"<<std::endl;
  std::cout<<std::endl;
  return;
}

