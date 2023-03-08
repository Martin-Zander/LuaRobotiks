// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Robotiks_PlayerInteraction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROBOTIKS_API URobotiks_PlayerInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URobotiks_PlayerInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FHitResult LineTraceFromCamera();
	void IsReplicatedCheck(AActor* Actor);
	
	UFUNCTION(Client, Reliable)
	void ClientLookForRobotikInteractions();
	UFUNCTION(Server, Reliable)
	void ServerLookForRobotikInteractions(AActor* ActorHit);

	UFUNCTION(Server, Reliable)
	void ServerRobotikInteract(AActor* ActorHit);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractionLength = 5000.0f;

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientServerRobotikInteract();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Debug = false;
};
