// VehicleSim.h
#pragma once
#include <cmath>

// Estruturas de dados simples (Plain Old Data - POD)
struct SimInput {
    double Throttle = 0.0; // 0.0 a 1.0
    double Brake = 0.0;    // 0.0 a 1.0
    double Steering = 0.0; // -1.0 (esq) a 1.0 (dir)
};

struct SimState {
    // Posição no mundo (X, Y, Z)
    double PosX = 0.0, PosY = 0.0, PosZ = 0.0;

    // Velocidade linear
    double VelX = 0.0, VelY = 0.0, VelZ = 0.0;

    // Orientação (Yaw - rotação no eixo Z para simplificar o exemplo)
    double Yaw = 0.0;

    // Velocidade do motor (RPM)
    double EngineRPM = 800.0;
};

// Configuração do carro (constantes físicas)
struct VehicleConfig {
    double Mass = 1500.0;      // kg
    double EngineForce = 5000.0; // Newtons max
    double DragCoef = 0.42;    // Resistência do ar
    double WheelBase = 2.7;    // Distância entre eixos (metros)
};

class MYPHYSICSCORE_API VehicleCore {
public:
    VehicleCore();
    ~VehicleCore();

    void Initialize(double x, double y, double z, double yaw);
    void StepSimulation(double dt, const SimInput& input);

    SimState GetState() const { return CurrentState; }

private:
    SimState CurrentState;
    VehicleConfig Config;
};
