// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "GameFramework/Actor.h"
#include "Robotiks_GlobalValueHolder.h"
#include "Robotiks_Machine.generated.h"

UCLASS()
class ROBOTIKS_API ARobotiks_Machine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobotiks_Machine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(Replicated)
	FString LuaCode;
	
public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<ARobotiks_Machine*> InputList;
	
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void OnSignal(int Frequency);

	UFUNCTION(BlueprintCallable)
	void ConnectInput(class ARobotiks_Machine* Robotik, int Index);

	UFUNCTION(BlueprintCallable)
	ARobotiks_Machine* GetInputFromID(FLuaValue ID);

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULuaState> RobotiksLuaState;

	UFUNCTION(BlueprintCallable)
	void CallLua(FString Name);

	UFUNCTION(BlueprintCallable)
	void UpdateLua();

	UFUNCTION(BlueprintCallable)
	void UpdateLuaCode(FString NewCode);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerUpdateLuaCode(const FString& NewCode);

	UFUNCTION(BlueprintNativeEvent)
	void OnInteraction();

	UFUNCTION(BlueprintNativeEvent)
	void ServerOnInteraction();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetLuaCode();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;

	UFUNCTION(BlueprintNativeEvent)
	void OnConnectInput();

	UPROPERTY(BlueprintReadOnly)
	ARobotiks_GlobalValueHolder* ValueBank;

	UFUNCTION(BlueprintCallable)
	void CallLuaAdvanced(FString Name, TArray<FLuaValue> Args, bool UpdateBeforeCall = true);
	
};
