// VehicleSim.cpp
#include "Simulation/VehicleSim.h"

VehicleCore::VehicleCore() {
    // Valores padrão
}

VehicleCore::~VehicleCore() {}

void VehicleCore::Initialize(double x, double y, double z, double yaw) {
    CurrentState.PosX = x;
    CurrentState.PosY = y;
    CurrentState.PosZ = z;
    CurrentState.Yaw = yaw;
}

void VehicleCore::StepSimulation(double dt, const SimInput& input) {
    // 1. Calcular Forças Locais
    // Força do motor (Simplificada: Apenas para frente)
    double tractionForce = input.Throttle * Config.EngineForce;

    // Resistência do ar (Drag equation: F = 0.5 * rho * v^2 * Cd * A)
    // Simplificado: F = -k * v
    double speed = std::sqrt(CurrentState.VelX * CurrentState.VelX + CurrentState.VelY * CurrentState.VelY);
    double dragForce = -Config.DragCoef * speed;

    // 2. Física Newtoniana (F = ma -> a = F/m)
    // Precisamos decompor a força na direção que o carro está apontando
    double totalForce = tractionForce + dragForce; // Simplificação escalar

    double accel = totalForce / Config.Mass;

    // Decompor aceleração nos eixos globais baseados no Yaw atual
    double ax = std::cos(CurrentState.Yaw) * accel;
    double ay = std::sin(CurrentState.Yaw) * accel;

    // 3. Integração de Euler (Integração numérica básica)
    // Atualiza velocidade
    CurrentState.VelX += ax * dt;
    CurrentState.VelY += ay * dt;

    // Atualiza posição
    CurrentState.PosX += CurrentState.VelX * dt;
    CurrentState.PosY += CurrentState.VelY * dt;

    // 4. Modelo de Bicicleta (Kinematic Bicycle Model) para curvas
    // Se houver velocidade, o carro gira baseado no steering
    if (std::abs(speed) > 0.1) {
        // Fórmula básica: YawRate = (Velocity / WheelBase) * tan(SteeringAngle)
        double maxSteerAngle = 0.5; // radianos (~30 graus)
        double steerAngle = input.Steering * maxSteerAngle;

        double yawRate = (speed / Config.WheelBase) * std::tan(steerAngle);
        CurrentState.Yaw += yawRate * dt;
    }
}
