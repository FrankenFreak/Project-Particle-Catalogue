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
#include "muon.h"

// Initialise muon count
int muon::muon_count = 0;

// Default constructor
muon::muon() : lepton("muon", ParticleType::PARTICLE, -1, 0.5, 1, 0, 0, 0, 0), isolated{false} 
{
  rest_mass = 105.6; // MeV/c^2
  // Update count
  ++muon_count;
}

// Parameterised constructor
muon::muon(ParticleType particle_type_in, bool isolation_in, double E, double px, double py, double pz) :
  lepton("muon", particle_type_in, -1, 0.5, 1, E, px, py, pz), isolated{isolation_in}
  {
    rest_mass = 105.6; // MeV/c^2
    // Validate energy and momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Update count
    ++muon_count; 
    // Check for antiparticle
    if(particle_type == ParticleType::ANTIPARTICLE)
    {
      // Update data members
      particle_name = "antimuon";
      charge = 1;
      lepton_number = -1;
    }
  }

// Destructor
muon::~muon() {--muon_count;};

// Copy constructor 
muon::muon(const muon& m) : lepton{m}, isolated{m.isolated} {++muon_count;}

// Copy assignment
muon & muon::operator=(const muon& m)
{
  // Prevent self-copy
  if(&m != this) 
  {
    lepton::operator=(m); 
    isolated = m.isolated;
  }
  return *this;
}

// Move constructor 
muon::muon(muon&& m) : lepton{std::move(m)}, isolated{std::move(m.isolated)} {++muon_count;}

// Move assignment
muon & muon::operator=(muon&& m)  
{
  // Prevent self-move
  if(&m != this) 
  {
    lepton::operator=(std::move(m)); 
    isolated = std::move(m.isolated);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> muon::clone() const {return std::make_shared<muon>(*this);}
  
// Get functions 
const bool muon::get_muon_isolation() {return isolated;}
int muon::get_muon_count() {return muon_count;}

// Set functions
void muon::set_muon_isolation(bool isolation_in) {isolated=isolation_in;}
void muon::set_particle_type(ParticleType particle_type_in) 
{
  // Update data members
  lepton::set_particle_type(particle_type_in);
  if(particle_type == ParticleType::ANTIPARTICLE)
  {
    particle_name = "antimuon";
    charge = 1;
  }
  else if(particle_type == ParticleType::PARTICLE)
  {
    particle_name = "muon";
    charge = -1;
  }
}

// Print function
void muon::print_data() 
{
  std::cout<<"Class: Muon"<<std::endl;
  lepton::print_data();

  // Muon-specific information
  if(isolated) std::cout<<particle_name<<" is isolated"<<std::endl;
  else std::cout<<particle_name<<" is not isolated"<<std::endl;
  std::cout<<std::endl;
}

