// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaValue.h"
#include "GameFramework/Actor.h"
#include "Robotiks_GlobalValueHolder.generated.h"

UCLASS()
class ROBOTIKS_API ARobotiks_GlobalValueHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobotiks_GlobalValueHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;
private:
	UPROPERTY(Replicated)
	TArray<FLuaValue> ValueBank;

public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerSetValue(FLuaValue Value, int Index);

	UFUNCTION(BlueprintCallable)
	FLuaValue GetValue(int Index);
};
