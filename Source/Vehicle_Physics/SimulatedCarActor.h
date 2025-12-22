// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../../Plugins/MyPhysicsCore/Source/MyPhysicsCore/Public/Simulation/VehicleSim.h"
#include "SimulatedCarActor.generated.h"

UCLASS()
class VEHICLE_PHYSICS_API ASimulatedCarActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulatedCarActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Componente visual (para vermos o carro)
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	// Inputs (podem ser chamados via Blueprint)
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float val);

	UFUNCTION(BlueprintCallable)
	void SetSteering(float val);

	//virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


private:
	VehicleCore PhysicsCore;
	SimInput CurrentInput;
};
