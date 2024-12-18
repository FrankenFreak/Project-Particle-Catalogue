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
#include "neutrino.h"

// Initialise neutrino count
int neutrino::neutrino_count = 0;

// Update name function
void neutrino::update_name() 
{
  switch(flavour)
  {
    case Flavour::ELECTRON:
      particle_name = (particle_type == ParticleType::ANTIPARTICLE) ? "electron antineutrino" : "electron neutrino";
      break;
    case Flavour::MUON:
      particle_name = (particle_type == ParticleType::ANTIPARTICLE) ? "muon antineutrino" : "muon neutrino";
      break;
    case Flavour::TAU:
      particle_name = (particle_type == ParticleType::ANTIPARTICLE) ? "tau antineutrino" : "tau neutrino";
      break;
  }
}

// Default constructor
neutrino::neutrino() : lepton("neutrino", ParticleType::PARTICLE, 0, 0.5, 1, 0, 0, 0, 0), hasInteracted{false} {++neutrino_count;}

// Parameterised constructor
neutrino::neutrino(ParticleType particle_type_in, Flavour flavour_in, bool interaction_in, double E, double px, double py, double pz) :
  lepton("neutrino", particle_type_in, 0, 0.5, 1, E, px, py, pz), flavour{flavour_in}, hasInteracted{interaction_in}
  {
    // Update count
    ++neutrino_count; 
    // Update data members
    lepton_number = (particle_type == ParticleType::ANTIPARTICLE) ? -1 : 1;
    update_name();
  }

// Destructor
neutrino::~neutrino() {--neutrino_count;}

// Copy constructor 
neutrino::neutrino(const neutrino& n) : lepton{n}, 
  flavour{n.flavour}, hasInteracted{n.hasInteracted} {++neutrino_count;}

// Copy assignment
neutrino & neutrino::operator=(const neutrino& n)
{
  // Prevent self-copy
  if(&n != this) 
  {
    lepton::operator=(n); 
    flavour = n.flavour;
    hasInteracted = n.hasInteracted;
  }
  return *this;
}

// Move constructor 
neutrino::neutrino(neutrino&& n) : lepton{std::move(n)}, hasInteracted{std::move(n.hasInteracted)}, 
  flavour{std::move(n.flavour)} {++neutrino_count;}

// Move assignment
neutrino & neutrino::operator=(neutrino&& n)  
{
  // Prevent self-move
  if(&n != this) 
  {
    lepton::operator=(std::move(n)); // Call lepton move assignment
    hasInteracted = std::move(n.hasInteracted);
    flavour = std::move(n.flavour);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> neutrino::clone() const {return std::make_shared<neutrino>(*this);}
  
// Get functions 
const bool neutrino::get_neutrino_interaction() {return hasInteracted;}
int neutrino::get_neutrino_count() {return neutrino_count;}

// Set functions
void neutrino::set_neutrino_interaction(bool has_interacted) {hasInteracted=has_interacted;}
void neutrino::set_particle_type(ParticleType particle_type_in)
{
  // Update particle_type
  lepton::set_particle_type(particle_type_in);
  // Update name
  update_name();
}

// Neutrino print function
void neutrino::print_data() 
{
  lepton::print_data();
  // Neutrino-specific information
  if(hasInteracted) std::cout<<particle_name<<" has interacted with detector"<<std::endl;
  else std::cout<<particle_name<<" has not interacted with detector"<<std::endl;
  std::cout<<std::endl;
}

