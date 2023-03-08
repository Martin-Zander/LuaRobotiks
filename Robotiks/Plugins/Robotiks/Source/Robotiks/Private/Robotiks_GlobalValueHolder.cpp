// Fill out your copyright notice in the Description page of Project Settings.


#include "Robotiks_GlobalValueHolder.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ARobotiks_GlobalValueHolder::ARobotiks_GlobalValueHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CreateDefaultSubobject<USceneComponent>("Base")->SetupAttachment(RootComponent);
	ValueBank.SetNum(100);
}

// Called when the game starts or when spawned
void ARobotiks_GlobalValueHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARobotiks_GlobalValueHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobotiks_GlobalValueHolder::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ARobotiks_GlobalValueHolder, ValueBank);
}

FLuaValue ARobotiks_GlobalValueHolder::GetValue(int Index)
{
	if(Index >= ValueBank.Num()) return 0;
	return ValueBank[Index];
}

void ARobotiks_GlobalValueHolder::ServerSetValue_Implementation(FLuaValue Value, int Index)
{
	if(Index >= ValueBank.Num()) return;
	ValueBank[Index] = Value;
}

