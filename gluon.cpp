// Clive Marvelous

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "gluon.h"

using std::string;

// Initialise gluon count
int gluon::gluon_count = 0;

// Default constructor 
gluon::gluon() : boson("gluon", ParticleType::PARTICLE, 0, 1, 0, 0, 0, 0), colour_charge{ColourCharge::RED}, 
  anti_colour_charge{ColourCharge::RED} {++gluon_count;}

// Parameterised constructor
gluon::gluon(ColourCharge colour_in, ColourCharge anti_colour_in, double E, double px, double py, double pz) :
  boson("gluon", ParticleType::PARTICLE, 0, 1, E, px, py, pz), colour_charge{colour_in},
  anti_colour_charge{anti_colour_in} 
  {
    // Validate four momentum inputs
    validate_four_momentum_massless(E, px, py, pz);
    // Update count
    ++gluon_count; 
  }

// Destructor
gluon::~gluon() {--gluon_count;}

// Copy constructor 
gluon::gluon(const gluon& g) : boson{g}, colour_charge{g.colour_charge}, anti_colour_charge{g.anti_colour_charge} 
  {++gluon_count;}

// Copy assignment
gluon& gluon::operator=(const gluon& g) 
{
  // Prevent self-copy
  if(&g != this) 
  {
    boson::operator=(g);
    colour_charge = g.colour_charge;
    anti_colour_charge = g.anti_colour_charge;
  }
  return *this;
}

// Move constructor 
gluon::gluon(gluon&& g) : boson{std::move(g)}, colour_charge{std::move(g.colour_charge)}, 
  anti_colour_charge{std::move(g.anti_colour_charge)} {++gluon_count;}

// Move assignment
gluon& gluon::operator=(gluon&& g) 
{
  // Prevent self-move
  if(&g != this) 
  {
    boson::operator=(std::move(g));
    colour_charge = std::move(g.colour_charge);
    anti_colour_charge = std::move(g.anti_colour_charge);
  }
  return *this;
}

// Clone function
std::shared_ptr<particle> gluon::clone() const {return std::make_shared<gluon>(*this);}

// Get functions
const ColourCharge gluon::get_colour() {return colour_charge;}
const ColourCharge gluon::get_anti_colour() {return anti_colour_charge;}
int gluon::get_gluon_count() {return gluon_count;}

// Set functions
void gluon::set_colour(ColourCharge colour_in) {colour_charge = colour_in;}
void gluon::set_anti_colour(ColourCharge anti_colour_in) {anti_colour_charge = anti_colour_in;}

// Print data function
void gluon::print_data() 
{
  boson::print_data();
  // Gluon specific 
  std::cout<<"Colour charge: ";
  switch(colour_charge)
  {
    case ColourCharge::RED:
      std::cout<<"Red"<<std::endl;
      break;
    case ColourCharge::GREEN:
      std::cout<<"Green"<<std::endl;
      break;
    case ColourCharge::BLUE:
      std::cout<<"Blue"<<std::endl;
      break;
  }
  std::cout<<"Anti-Colour charge: ";
  switch(anti_colour_charge)
  {
    case ColourCharge::RED:
      std::cout<<"Anti-Red"<<std::endl;
      break;
    case ColourCharge::GREEN:
      std::cout<<"Anti-Green"<<std::endl;
      break;
    case ColourCharge::BLUE:
      std::cout<<"Anti-Blue"<<std::endl;
      break;
  }
  std::cout<<std::endl;
}

