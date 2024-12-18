// Clive Marvelous, last updated 6/4/24

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"
#include "electron.h"

// Initialise electron count
int electron::electron_count = 0;

// Validation function
void electron::validate_energy_deposit(double E, double& EM_1, double& EM_2, double& HAD_1, double& HAD_2) 
{
  double total_deposit = EM_1 + EM_2 + HAD_1 + HAD_2;
  // Ensure total_energy = energy of electron
  if(total_deposit != E) 
  {
    // Adjust the values
    double fraction = E/total_deposit;
    EM_1 *= fraction;
    EM_2 *= fraction;
    HAD_1 *= fraction;
    HAD_2 *= fraction;
  }
}

// Default constructor
electron::electron() : lepton("electron", ParticleType::PARTICLE, -1, 0.5, 1, 0, 0, 0, 0), energy_deposited_in_calorimeter(4) 
{
  rest_mass = 0.511; // MeV/c^2
  // Update count
  ++electron_count;
}

// Parameterised constructor
electron::electron(ParticleType particle_type_in, double E, double px, double py, double pz, double EM_1, double EM_2, double HAD_1, double HAD_2) :
  lepton("electron", particle_type_in, -1, 0.5, 1, E, px, py, pz)
  {
    rest_mass = 0.511; // MeV/c^2
    // Validate energy and momentum inputs
    validate_four_momentum_mass(E, px, py, pz);
    // Check for antiparticle
    if(particle_type == ParticleType::ANTIPARTICLE)
    {
      // Update data members
      particle_name = "antielectron";
      charge = 1;
      lepton_number = -1;
    }
    // Validate and store energy deposit values into vector
    validate_energy_deposit(E, EM_1, EM_2, HAD_1, HAD_2);
    energy_deposited_in_calorimeter = {EM_1, EM_2, HAD_1, HAD_2};
    // Update electron count
    ++electron_count;
  }
electron::~electron() {--electron_count;}

// Copy constructor 
electron::electron(const electron& e) : lepton{e}, 
  energy_deposited_in_calorimeter{e.energy_deposited_in_calorimeter} {++electron_count;}

// Copy assignment
electron & electron::operator=(const electron& e)
{
  // Prevent self-copy
  if(&e != this) 
  {
    lepton::operator=(e);
    energy_deposited_in_calorimeter = e.energy_deposited_in_calorimeter;
  }
  return *this;
}

// Move constructor 
electron::electron(electron&& e) : lepton{std::move(e)}, 
  energy_deposited_in_calorimeter{std::move(e.energy_deposited_in_calorimeter)} {++electron_count;}

// Move assignment
electron & electron::operator=(electron&& e)  
{
  // Prevent self-move
  if(&e != this) 
  {
    lepton::operator=(std::move(e)); 
    energy_deposited_in_calorimeter = std::move(e.energy_deposited_in_calorimeter); 
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> electron::clone() const {return std::make_shared<electron>(*this);}
  
// Get functions 
const double electron::get_EM1() {return energy_deposited_in_calorimeter.at(0);}
const double electron::get_EM2() {return energy_deposited_in_calorimeter.at(1);}
const double electron::get_HAD1() {return energy_deposited_in_calorimeter.at(2);}
const double electron::get_HAD2() {return energy_deposited_in_calorimeter.at(3);}
int electron::get_electron_count() {return electron_count;}

// Set functions
void electron::set_energy_deposit(double& EM_1, double& EM_2, double& HAD_1, double& HAD_2)
{
  validate_energy_deposit(four_momentum->get_E(), EM_1, EM_2, HAD_1, HAD_2);
  energy_deposited_in_calorimeter = {EM_1, EM_2, HAD_1, HAD_2};
}

void electron::set_particle_type(ParticleType particle_type_in)
{
  lepton::set_particle_type(particle_type_in);
  if(particle_type == ParticleType::ANTIPARTICLE)
  {
    particle_name = "antielectron";
    charge = 1;
  }
  else if(particle_type == ParticleType::PARTICLE)
  {
    particle_name = "electron";
    charge = -1;
  }
}

// Print function
void electron::print_data() 
{
  std::cout<<"Class: Electron"<<std::endl;
  lepton::print_data();

  // Electron-specific information
  std::cout<<"Deposited Energies in Calorimeter:"<<std::endl;
  std::cout<<"EM1: "<<energy_deposited_in_calorimeter[0]<<" MeV"<<std::endl;
  std::cout<<"EM2: "<<energy_deposited_in_calorimeter[1]<<" MeV"<<std::endl;
  std::cout<<"HAD1: "<<energy_deposited_in_calorimeter[2]<<" MeV"<<std::endl;
  std::cout<<"HAD2: "<<energy_deposited_in_calorimeter[3]<<" MeV"<<std::endl;
  std::cout<<std::endl;
}

