// Fill out your copyright notice in the Description page of Project Settings.


#include "Robotiks_PlayerInteraction.h"

#include "Robotiks_Machine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URobotiks_PlayerInteraction::URobotiks_PlayerInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void URobotiks_PlayerInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URobotiks_PlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ClientLookForRobotikInteractions();
}

FHitResult URobotiks_PlayerInteraction::LineTraceFromCamera()
{
	FHitResult OutHit;
	APlayerCameraManager* Camera = UGameplayStatics::GetPlayerCameraManager(this, 0);

	FVector CameraPosition = Camera->GetCameraLocation();
	FVector CameraForward = Camera->GetActorForwardVector();
	FVector TraceEndVector = CameraForward * InteractionLength + CameraPosition;

	GetWorld()->LineTraceSingleByChannel(OutHit, CameraPosition, TraceEndVector, ECC_Visibility, FCollisionQueryParams("", false, GetOwner()));

	return OutHit;
}

void URobotiks_PlayerInteraction::IsReplicatedCheck(AActor* Actor)
{
	if (Actor)
	{
		if (Actor->GetIsReplicated() == false)
		{
			//GEngine can be null so check to be save
			if (GEngine)
			{
				if (Debug)
				{
					FString Name = Actor->GetName();
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,FString::Printf(TEXT("Warning: This Actor is not Replicated. (%s)"), *Name));	
				}
			}
		}
	}
}

void URobotiks_PlayerInteraction::ClientServerRobotikInteract_Implementation()
{
	FHitResult Hit = LineTraceFromCamera();

	IsReplicatedCheck(Hit.GetActor());

	
	if (Hit.GetActor())
	{
		ARobotiks_Machine* Robotik = Cast<ARobotiks_Machine>(Hit.GetActor());
		if (Robotik)
		{
			Robotik->OnInteraction();
		}
		ServerRobotikInteract(Hit.GetActor());
	}
}

void URobotiks_PlayerInteraction::ServerRobotikInteract_Implementation(AActor* ActorHit)
{
	if (ActorHit)
	{
		ARobotiks_Machine* Robotik = Cast<ARobotiks_Machine>(ActorHit);
		if (Robotik)
		{
			Robotik->ServerOnInteraction();		
		}
	}
}

void URobotiks_PlayerInteraction::ClientLookForRobotikInteractions_Implementation()
{
	FHitResult OutHit = LineTraceFromCamera();
	IsReplicatedCheck(OutHit.GetActor());

	if (OutHit.GetActor())
	{
		//ServerLookForRobotikInteractions(OutHit.GetActor());	
	}
}

void URobotiks_PlayerInteraction::ServerLookForRobotikInteractions_Implementation(AActor* ActorHit)
{
	
}

