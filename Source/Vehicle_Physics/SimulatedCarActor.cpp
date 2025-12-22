// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulatedCarActor.h"

// Sets default values
ASimulatedCarActor::ASimulatedCarActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	RootComponent = MeshComp;

	// Desligar física da Unreal para este ator, pois NÓS vamos controlar a posição
	MeshComp->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ASimulatedCarActor::BeginPlay()
{
	Super::BeginPlay();
	// Inicializa o core com a posição inicial do ator na Unreal
	FVector StartLoc = GetActorLocation();
	FRotator StartRot = GetActorRotation();

	// Conversão: Unreal usa cm, Física geralmente usa metros.
	// Unreal Units (cm) -> Metros: Dividir por 100
	PhysicsCore.Initialize(StartLoc.X / 100.0, StartLoc.Y / 100.0, StartLoc.Z / 100.0, FMath::DegreesToRadians(StartRot.Yaw));
}

// Called every frame
void ASimulatedCarActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//  Rodar a simulação PURA
	// Convertendo float (Unreal) para double (Core)
	PhysicsCore.StepSimulation((double)DeltaTime, CurrentInput);

	//  Ler o estado do Core e aplicar na Unreal
	SimState NewState = PhysicsCore.GetState();

	// Converter Metros -> Centímetros
	FVector NewPos(NewState.PosX * 100.0, NewState.PosY * 100.0, NewState.PosZ * 100.0);

	// Converter Radianos -> Graus
	FRotator NewRot(0, FMath::RadiansToDegrees(NewState.Yaw), 0);

	// Teletransportar o ator para onde a física matemática diz que ele está
	SetActorLocationAndRotation(NewPos, NewRot, false, nullptr, ETeleportType::None);
}

void ASimulatedCarActor::SetThrottle(float val)
{
	CurrentInput.Throttle = (double)FMath::Clamp(val, -1.0f, 1.0f);
}

void ASimulatedCarActor::SetSteering(float val)
{
	CurrentInput.Steering = (double)FMath::Clamp(val, -1.0f, 1.0f);
}

