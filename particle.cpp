// Clive Marvelous, last updated 6/4/24

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<algorithm>

#include "fourMomentum.h"
#include "particle.h"

using std::string;

// Initialise particle count
int particle::particle_count = 0;

// Validation functions
void particle::validate_four_momentum_general(double E) // For all particles
{
  // Check for realistic energy input
  if(E < 0) throw std::logic_error("Energy >= 0 for particles");
}
void particle::validate_four_momentum_mass(double E, double px, double py, double pz) // For mass particles
{
  // Calculate magnitude of momentum square
  double magnitude{magnitude_square(px, px, py, py, pz, pz)};
  // Tolerance for comparison
  const double tolerance = rest_mass * 0.2; 
  // Check for realistic momentum inputs for mass particles
  if(!(std::sqrt(E*E - magnitude) <= rest_mass + tolerance)  || !(std::sqrt(E*E - magnitude) >= rest_mass - tolerance)) 
  {
    std::cout<<"Default values applied since input values not physically possible"<<std::endl;
    // Assign default values 
    four_momentum->set_E(rest_mass); 
    four_momentum->set_px(0);
    four_momentum->set_py(0);
    four_momentum->set_pz(0);
  }
}
void particle::validate_four_momentum_massless(double E, double px, double py, double pz) // For massless particles
{
  // Calculate magnitude of momentum square
  double magnitude{std::sqrt(magnitude_square(px, px, py, py, pz, pz))};
  // Tolerance for comparison
  const double tolerance = 0.1; 
  // Check for realistic momentum inputs for mass particles
  if(!(std::abs(E - magnitude) <= tolerance)) 
  {
    std::cout<<"Default values applied since energy must equal to the magnitude of momentum within tolerance of 0.1"<<std::endl;
    // Assign default values 
    four_momentum->set_E(0); 
    four_momentum->set_px(0);
    four_momentum->set_py(0);
    four_momentum->set_pz(0);
  }
}


// Default constructor
particle::particle() : particle_name{"unknown particle"}, particle_type{ParticleType::PARTICLE}, particle_class{}, charge{}, 
  spin{}, four_momentum{std::make_shared<fourMomentum>()}, rest_mass{} {++particle_count;}

// Parameterised constructor
particle::particle(string name_in, ParticleType particle_type_in, ParticleClass particle_class_in, float charge_in, float spin_in, double E, double px, double py, double pz) : 
  particle_name{name_in}, particle_type{particle_type_in}, particle_class{particle_class_in}, charge{charge_in}, spin{spin_in},
  four_momentum{std::make_shared<fourMomentum>(E, px, py, pz)}, rest_mass{} 
  {
    //Validate energy and momentum inputs
    validate_four_momentum_general(E);
    // Update count
    ++particle_count;}

// Destructor
particle::~particle() {--particle_count;}

// Copy constructor 
particle::particle(const particle& p) : particle_name{p.particle_name}, particle_type{p.particle_type}, 
  charge{p.charge}, spin{p.spin}, four_momentum{std::make_shared<fourMomentum>(*p.four_momentum)},
  rest_mass{p.rest_mass} {++particle_count;}

// Copy assignment
particle & particle::operator=(const particle& p)
{
  // Check for self-copy
  if(&p != this) 
  { 
    // Update data members
    particle_name = p.particle_name;
    particle_type = p.particle_type;
    charge = p.charge; 
    spin = p.spin;
    four_momentum = std::make_shared<fourMomentum>(*p.four_momentum);
    rest_mass = p.rest_mass;
  }
  return *this;
}

// Move constructor 
particle::particle(particle&& p) : particle_name{std::move(p.particle_name)}, particle_type{std::move(p.particle_type)}, 
  charge{std::move(p.charge)}, spin{std::move(p.spin)}, four_momentum{std::move(p.four_momentum)},
  rest_mass{std::move(p.rest_mass)} {++particle_count;}

// Move assignment
particle & particle::operator=(particle&& p)
{
  // Prevent self-move
  if(&p != this) 
  {
    // Update data members
    particle_name = std::move(p.particle_name);
    particle_type = std::move(p.particle_type);
    charge = std::move(p.charge);
    spin = std::move(p.spin);
    four_momentum = std::move(p.four_momentum);
    rest_mass = std::move(p.rest_mass);
  }
  return *this;
}

// Rest mass function
double particle::restMass() {return four_momentum->invariant_mass();}

// Get functions 
const string particle::get_name() const {return particle_name;}
const ParticleType particle::get_particle_type() const {return particle_type;}
const ParticleClass particle::get_particle_class() const {return particle_class;}
const float particle::get_charge() const {return charge;}
const float particle::get_spin() const {return spin;}
const double particle::get_E() const {return four_momentum->get_E();}
const double particle::get_px() const {return four_momentum->get_px();}
const double particle::get_py() const {return four_momentum->get_py();}
const double particle::get_pz() const {return four_momentum->get_pz();}
const std::shared_ptr<fourMomentum>& particle::get_four_momentum() const {return four_momentum;}
int particle::get_particle_count() {return particle_count;} 

// Set functions
void particle::set_name(string name_in) {particle_name=name_in;}
void particle::set_particle_class(ParticleClass particle_class_in) {particle_class=particle_class_in;}
void particle::set_energy_momentum(double E, double px, double py, double pz) 
{
  std::vector<std::string> neutrino_names
  {
    "neutrino",
    "electron neutrino",
    "electron antineutrino",
    "muon neutrino",
    "muon antineutrino",
    "tau neutrino",
    "tau antineutrino"
  };
  // Validate energy and momentum inputs 
  validate_four_momentum_general(E);
  // Validate for massless particles
  if(particle_name == "photon" || particle_name == "gluon")
    validate_four_momentum_massless(E, px, py, pz);
  // Validate for mass particles (except neutrinos)
  else if(std::find(neutrino_names.begin(), neutrino_names.end(), particle_name) == neutrino_names.end())
    validate_four_momentum_mass(E, px, py, pz);
  
  // Set four momentum inputs
  four_momentum->set_E(E);
  four_momentum->set_px(px);
  four_momentum->set_py(py);
  four_momentum->set_pz(pz);
}

// Friend functions
fourMomentum sum(const particle& p1, const particle& p2) {return (*p1.four_momentum) + (*p2.four_momentum);} // Sum 
fourMomentum subtract(const particle& p1, const particle& p2) {return (*p1.four_momentum) - (*p2.four_momentum);} // Subtract
double dotProduct(const particle& p1, const particle& p2) // Dot product
{
  // Calculation
  double result_E{p1.four_momentum->get_E()*p2.four_momentum->get_E()};
  double magnitude{magnitude_square(p1.four_momentum->get_px(), p2.four_momentum->get_px(), 
    p1.four_momentum->get_py(), p2.four_momentum->get_py(), p1.four_momentum->get_pz(), p2.four_momentum->get_pz())}; // Momentum dot product
  return result_E - magnitude;
}

// Particle print function
void particle::print_data()
{
  std::cout<<"Particle Name: "<<particle_name<<std::endl;
  std::cout<<"Particle Class: ";
  switch(particle_class)
  {
    case ParticleClass::FERMIONS:
      std::cout<<"Fermions"<<std::endl;
      break;
    case ParticleClass::BOSONS:
      std::cout<<"Bosons"<<std::endl;
      break;
  }
  std::cout<<"Charge: "<<charge<<std::endl;
  std::cout<<"Spin: "<<spin<<std::endl;
  std::cout.precision(4);
  std::cout<<"Energy: "<<four_momentum->get_E()<<" MeV"<<std::endl;
  std::cout<<"Momentum (px): "<<four_momentum->get_px()<<" MeV/c"<<std::endl;
  std::cout<<"Momentum (py): "<<four_momentum->get_py()<<" MeV/c"<<std::endl;
  std::cout<<"Momentum (pz): "<<four_momentum->get_pz()<<" MeV/c"<<std::endl;
  return;
}
