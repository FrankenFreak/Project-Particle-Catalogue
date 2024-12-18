// PHYS 30762 Programming in C++
// Project: Particle Catalogue
// Author: Clive Marvelous (10916086)
// Date: 

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<algorithm>
#include<utility>
#include<map>

using std::string;

#include "fourMomentum.h"
#include "particle.h"
#include "lepton.h"
#include "electron.h"
#include "muon.h"
#include "neutrino.h"
#include "tau.h"
#include "quark.h"
#include "boson.h"
#include "photon.h"
#include "gluon.h"
#include "Z.h"
#include "W.h"
#include "higgs.h"

// enum class
enum class ParticleCategory{LEPTON, QUARK, BOSON};

// Streamline catalogue type
using ParticleCatalogueMap = std::map<std::pair<ParticleCategory, ParticleType>, std::vector<std::shared_ptr<particle>>>;

// Functions
void print_particles_by_key(const ParticleCatalogueMap& catalogue, ParticleCategory category, ParticleType type); // Print all particles in the same category
void print_particles_by_name(const ParticleCatalogueMap& catalogue, const std::string& name); // Print particle data by name
int total_particles_in_catalog(const ParticleCatalogueMap& catalogue); // Count total particle in catalogue
int count_particles_by_type(const ParticleCatalogueMap& catalogue, ParticleType type); // Count particle by type
int count_particles_by_category(const ParticleCatalogueMap& catalogue, ParticleCategory category); // Count particle by category
std::vector<std::shared_ptr<particle>> get_particles_by_type(const ParticleCatalogueMap& catalogue, ParticleCategory category, ParticleType type); // Get sub-container 
fourMomentum sum_four_momentum(const ParticleCatalogueMap& catalogue); // Sum four momentum of all particles in the catalogue
void catalogue_summary(const ParticleCatalogueMap& catalogue); // Print catalogue report
void static_summary(); // Print class report

// Main program
int main()
{
  // Map to store particles and antiparticles 
  std::map<std::pair<ParticleCategory, ParticleType>, std::vector<std::shared_ptr<particle>>> particle_catalogue 
  {
    {{ParticleCategory::LEPTON, ParticleType::PARTICLE}, 
    {
      std::make_shared<electron>(ParticleType::PARTICLE, 0.511, 0, 0, 0, 0, 0, 0, 0),
      std::make_shared<muon>(ParticleType::PARTICLE, true, 0, 0, 0, 0),
      std::make_shared<tau>(ParticleType::PARTICLE, QuarkParticle::DOWN, ParticleType::PARTICLE, QuarkParticle::UP, ParticleType::ANTIPARTICLE, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::PARTICLE, Flavour::ELECTRON, true, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::PARTICLE, Flavour::MUON, false, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::PARTICLE, Flavour::TAU, false, 0, 0, 0, 0)
    }},
    {{ParticleCategory::LEPTON, ParticleType::ANTIPARTICLE}, 
    {
      std::make_shared<electron>(ParticleType::ANTIPARTICLE, 0.511, 0, 0, 0, 0, 0, 0, 0),
      std::make_shared<muon>(ParticleType::ANTIPARTICLE, false, 0, 0, 0, 0),
      std::make_shared<tau>(ParticleType::ANTIPARTICLE, Flavour::ELECTRON, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::ANTIPARTICLE, Flavour::ELECTRON, false, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::ANTIPARTICLE, Flavour::MUON, true, 0, 0, 0, 0),
      std::make_shared<neutrino>(ParticleType::ANTIPARTICLE, Flavour::TAU, true, 0, 0, 0, 0)
    }},
    {{ParticleCategory::QUARK, ParticleType::PARTICLE}, 
    {
      std::make_shared<quark>(QuarkParticle::UP, ParticleType::PARTICLE, ColourCharge::RED, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::DOWN, ParticleType::PARTICLE, ColourCharge::BLUE, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::CHARM, ParticleType::PARTICLE, ColourCharge::GREEN, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::STRANGE, ParticleType::PARTICLE, ColourCharge::RED, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::TOP, ParticleType::PARTICLE, ColourCharge::BLUE, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::BOTTOM, ParticleType::PARTICLE, ColourCharge::GREEN, 0, 0, 0, 0)
    }},
    {{ParticleCategory::QUARK, ParticleType::ANTIPARTICLE}, 
    {
      std::make_shared<quark>(QuarkParticle::UP, ParticleType::ANTIPARTICLE, ColourCharge::RED, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::DOWN, ParticleType::ANTIPARTICLE, ColourCharge::BLUE, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::CHARM, ParticleType::ANTIPARTICLE, ColourCharge::GREEN, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::STRANGE, ParticleType::ANTIPARTICLE, ColourCharge::RED, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::TOP, ParticleType::ANTIPARTICLE, ColourCharge::BLUE, 0, 0, 0, 0),
      std::make_shared<quark>(QuarkParticle::BOTTOM, ParticleType::ANTIPARTICLE, ColourCharge::GREEN, 0, 0, 0, 0)
    }},
    {{ParticleCategory::BOSON, ParticleType::PARTICLE}, 
    {
      std::make_shared<photon>(0, 0, 0, 0),
      std::make_shared<gluon>(ColourCharge::BLUE, ColourCharge::RED, 0, 0, 0, 0),
      std::make_shared<Z>(LeptonParticle::ELECTRON, 0, 0, 0, 0),
      std::make_shared<Z>(QuarkParticle::DOWN, 0, 0, 0, 0),
      std::make_shared<Z>(Flavour::MUON, 0, 0, 0, 0),
      std::make_shared<W>(ParticleType::ANTIPARTICLE, QuarkParticle::BOTTOM, QuarkParticle::CHARM, 0, 0, 0, 0),
      std::make_shared<W>(ParticleType::PARTICLE, QuarkParticle::UP, QuarkParticle::STRANGE, 0, 0, 0, 0),
      std::make_shared<higgs>(QuarkParticle::STRANGE, 0, 0, 0, 0),
      std::make_shared<higgs>(BosonParticle::W, 0, 0, 0, 0)
    }},
    {{ParticleCategory::BOSON, ParticleType::ANTIPARTICLE}, 
    {
      std::make_shared<photon>(0, 0, 0, 0),
      std::make_shared<gluon>(ColourCharge::GREEN, ColourCharge::BLUE, 0, 0, 0, 0),
      std::make_shared<W>(ParticleType::ANTIPARTICLE, QuarkParticle::BOTTOM, QuarkParticle::CHARM, 0, 0, 0, 0),
    }}
  };

  // Input checking for four-momentum 
  try
  {
    std::make_shared<electron>(ParticleType::PARTICLE, -0.511, 0, 0, 0, 0, 0, 0, 0);
  } catch(std::logic_error& le)
  {
    std::cout<<"Logic error: "<<le.what()<<std::endl;
  } 

  // Print data from catalogue
  std::cout<<"Test print functions:"<<std::endl;
  print_particles_by_key(particle_catalogue, ParticleCategory::BOSON, ParticleType::ANTIPARTICLE); // By category and type
  print_particles_by_name(particle_catalogue, "tau"); // By name 

  // Get sub-container 
  std::vector<std::shared_ptr<particle>> boson_particle_subcontainer{get_particles_by_type(particle_catalogue, ParticleCategory::BOSON, ParticleType::PARTICLE)};
  std::cout<<"Sub-container element 1:"<<std::endl;
  std::cout<<std::endl;
  boson_particle_subcontainer[1]->print_data();

  // Print catalogue report
  std::cout<<"Report: "<<std::endl;
  catalogue_summary(particle_catalogue);
  static_summary();

  return 0;
}

// Function to print all particles inside the sub-container based on the category and type 
void print_particles_by_key(const ParticleCatalogueMap& catalogue, ParticleCategory category, ParticleType type) 
{
  std::cout<<std::endl;
  // Find the vector of particles that corresponds to the category and type
  auto it = catalogue.find({category, type});
  if(it != catalogue.end())
  {
    std::cout<<"Particles category: ";
    switch(category)
    {
      case ParticleCategory::LEPTON: 
        std::cout<<"Lepton"<<std::endl;
        break;
      case ParticleCategory::QUARK: 
        std::cout<<"Quark"<<std::endl;
        break;
      case ParticleCategory::BOSON: 
        std::cout<<"Boson"<<std::endl;
        break;
    }
    std::cout<<"Particles type: ";
    switch(type)
    {
      case ParticleType::PARTICLE: 
        std::cout<<"Particle"<<std::endl;
        break;
      case ParticleType::ANTIPARTICLE: 
        std::cout<<"Antiparticle"<<std::endl;
        break;
    }
    std::cout<<std::endl;
    for (const auto& part : it->second) part->print_data();
  } else std::cout<<"No particles found for the specified category and type"<<std::endl;
}

// Function to print particle by name
void print_particles_by_name(const ParticleCatalogueMap& catalogue, const std::string& name) 
{
  std::cout<<std::endl;
  // Iterate over all key in the catalogue
  for(const auto& key : catalogue) 
  {
    // Iterate over the vector
    for(const auto& part : key.second) 
      if(part->get_name() == name) part->print_data();
  }
  std::cout<<std::endl;
}

// Function to calculate the total number of particles in the container
int total_particles_in_catalog(const ParticleCatalogueMap& catalogue) {
    int count = 0;
    for(const auto& key : catalogue) count += key.second.size();
    return count;
}

// Function to count the particle by type
int count_particles_by_type(const ParticleCatalogueMap& catalogue, ParticleType type) 
{
  int count = 0;
  // Iterate over key
  for(const auto& key : catalogue) 
  {
    // Match the input type to second element of key
    if(key.first.second == type) count += key.second.size();
  }
  return count;
}

// Function to count the particle by classification
int count_particles_by_category(const ParticleCatalogueMap& catalogue, ParticleCategory category) 
{
  int count = 0;
  // Iterate over key
  for(const auto& key : catalogue) 
  {
    // Match the input type to second element of key
    if(key.first.first == category) count += key.second.size();
  }
  return count;
}

// Function to sum all the four momentum of all particles in the container
fourMomentum sum_four_momentum(const ParticleCatalogueMap& catalogue) 
{
  // Initialise four momentum class
  fourMomentum total_momentum; 
  for(const auto& key : catalogue) 
  {
    for(const auto& part : key.second) total_momentum = total_momentum + *(part->get_four_momentum()); 
  }
  return total_momentum;
}

// Function to return sub-container based on particle type 
std::vector<std::shared_ptr<particle>> get_particles_by_type(const ParticleCatalogueMap& catalogue, ParticleCategory category, ParticleType type) 
{
  // Iterate over the catalogue
  for(const auto& key : catalogue) 
  {
    // Match second element of key to type input
    if(key.first.first == category && key.first.second == type) return key.second;  // Return the vector directly if the type matches
  }
  // Return an empty vector if no match
  return {};
}

// Catalogue summary print function
void catalogue_summary(const ParticleCatalogueMap& catalogue) 
{
  std::cout<<std::endl;
  std::cout<<"Total number of particles in the container: "<<total_particles_in_catalog(catalogue)<<std::endl;
  std::cout<<"Total number of particles: "<<count_particles_by_type(catalogue, ParticleType::PARTICLE)<<std::endl;
  std::cout<<"Total number of antiparticles: "<<count_particles_by_type(catalogue, ParticleType::ANTIPARTICLE)<<std::endl;
  std::cout<<"Total number of lepton: "<<count_particles_by_category(catalogue, ParticleCategory::LEPTON)<<std::endl;
  std::cout<<"Total number of quark: "<<count_particles_by_category(catalogue, ParticleCategory::QUARK)<<std::endl;
  std::cout<<"Total number of boson: "<<count_particles_by_category(catalogue, ParticleCategory::BOSON)<<std::endl;
  fourMomentum total_four_momentum = sum_four_momentum(catalogue);
  std::cout<<"Sum of all four-momentum: ["<<total_four_momentum.get_E();
  std::cout<<", "<<total_four_momentum.get_px();
  std::cout<<", "<<total_four_momentum.get_py();
  std::cout<<", "<<total_four_momentum.get_pz()<<"] MeV (Taking c=1)"<<std::endl;
}

// Static summary
void static_summary()
{
  std::cout<<std::endl;
  std::cout<<"Total number of objects constructed:"<<std::endl;
  std::cout<<"1. Particle: "<<particle::get_particle_count()<<std::endl;
  std::cout<<"2. Lepton: "<<lepton::get_lepton_count()<<std::endl;
  std::cout<<"2.1 Electron: "<<electron::get_electron_count()<<std::endl;
  std::cout<<"2.2 Muon: "<<muon::get_muon_count()<<std::endl;
  std::cout<<"2.3 Tau: "<<tau::get_tau_count()<<std::endl;
  std::cout<<"2.4 Neutrino: "<<neutrino::get_neutrino_count()<<std::endl;
  std::cout<<"3. Quark: "<<quark::get_quark_count()<<std::endl;
  std::cout<<"4. Boson: "<<boson::get_boson_count()<<std::endl;
  std::cout<<"4.1 Photon: "<<photon::get_photon_count()<<std::endl;
  std::cout<<"4.2 Gluon: "<<gluon::get_gluon_count()<<std::endl;
  std::cout<<"4.3 Z: "<<Z::get_Z_count()<<std::endl;
  std::cout<<"4.4 W: "<<W::get_W_count()<<std::endl;
  std::cout<<"4.5 Higgs: "<<higgs::get_higgs_count()<<std::endl;
}