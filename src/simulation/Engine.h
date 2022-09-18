//
// Created by test on 2022-02-09.
//

#ifndef MPM_SOLVER_ENGINE_H
#define MPM_SOLVER_ENGINE_H

#include <Eigen/Dense>
#include <fmt/core.h>
#include "Particles.h"
#include "Entity.h"
#include "Types.h"
#include "Entity.h"
#include "Grid.h"
namespace mpm {

enum Device {
  CPU,
  GPU
};

enum TransferScheme {
  MLS,
  FLIP
};
enum GridBackendType {
  Dense,
  Sparse
};
enum IntegrationScheme {
  Explicit,
  Implicit
};

struct EngineConfig {

  bool m_useCflTimeStep;
  TransferScheme m_transferScheme;
  IntegrationScheme m_integrationScheme;
  GridBackendType m_gridBackend;
  Vec3i m_gridResolution;
  Scalar m_gridCellSize;
  unsigned int m_targetFrame;

};

class Engine {

 public:

  //constructor
  Engine(EngineConfig engine_config) :
  _engineConfig(engine_config),
  _grid(engine_config.m_gridResolution(0),engine_config.m_gridResolution(1),engine_config.m_gridResolution(2),engine_config.m_gridCellSize),
  _isCreated(true),
  _currentFrame(0)
  {

  };
  //destructor
  ~Engine() = default;

  //member functions
  //void create(EngineConfig engine_config);
//  void integrate();
  void integrate(Scalar dt);
  void setGravity(Vec3f gravity);
  float* getGravityFloatPtr();
  void addParticles(Particles& particles);
  unsigned int getParticleCount() const;
  inline unsigned long long getCurrentFrame() const{return _currentFrame;}

  EngineConfig getEngineConfig();

  //TODO: inheritance or functor?
  std::vector<Particle> m_sceneParticles;

 private:

  // important function
  void init();
  void p2g(Scalar dt);
  void updateGrid(Scalar dt);
  void g2p(Scalar dt);

  EngineConfig _engineConfig;
  Vec3f _gravity{0,0,0};
  Grid _grid;
  unsigned int bound =3;
  bool _isCreated = false;
  unsigned long long _currentFrame;


};

}

#endif //MPM_SOLVER_ENGINE_H
