// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "photon.h"

using std::string;

// Initialise static count
int photon::photon_count = 0; 

// Default constructor
photon::photon() : boson("photon", ParticleType::PARTICLE, 0, 1, 0, 0, 0, 0) {++photon_count;}

// Parameterised constructor
photon::photon(double E, double px, double py, double pz) : boson("photon", ParticleType::PARTICLE, 0, 1, E, px, py, pz) 
{
  // Validate energy and momentum inputs
  validate_four_momentum_massless(E, px, py, pz);
  // Update count
  ++photon_count;
}

// Destructor
photon::~photon() {--photon_count;}

// Copy constructor
photon::photon(const photon& p) : boson(p) {++photon_count;}

// Copy assignment operator
photon & photon::operator=(const photon& p) 
{
  // Check for self-copy 
  if(&p != this) boson::operator=(p);
  return *this;
}

// Move constructor
photon::photon(photon&& p) : boson(std::move(p)) {++photon_count;}

// Move assignment operator
photon & photon::operator=(photon&& p) 
{
  // Check for self-move
  if(&p != this) boson::operator=(std::move(p));
  return *this;
}

// Clone function 
std::shared_ptr<particle> photon::clone() const {return std::make_shared<photon>(*this);}

// Get photon count
int photon::get_photon_count() {return photon_count;}

// Print function
void photon::print_data() 
{
  boson::print_data();
  std::cout<<std::endl;
}


