// Fill out your copyright notice in the Description page of Project Settings.


#include "Robotiks_Machine.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARobotiks_Machine::ARobotiks_Machine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = (true);

	for (int i = 0; i < 10; i++)
	{
		InputList.Add(0);
	}

}

// Called when the game starts or when spawned
void ARobotiks_Machine::BeginPlay()
{
	Super::BeginPlay();
	ValueBank = Cast<ARobotiks_GlobalValueHolder>(UGameplayStatics::GetActorOfClass(this, ARobotiks_GlobalValueHolder::StaticClass()));
}

// Called every frame
void ARobotiks_Machine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ARobotiks_Machine* ARobotiks_Machine::GetInputFromID(FLuaValue ID)
{
	int Index = ULuaBlueprintFunctionLibrary::Conv_LuaValueToInt(ID);

	if (InputList.Num() <= Index)
	{
		return 0;
	}
	
	return InputList[Index];
}

void ARobotiks_Machine::CallLua(FString Name)
{
	TArray<FLuaValue> Args;
	CallLuaAdvanced(Name, Args);
}

void ARobotiks_Machine::UpdateLua()
{
	ULuaBlueprintFunctionLibrary::LuaRunString(this, RobotiksLuaState, LuaCode);
}

void ARobotiks_Machine::UpdateLuaCode(FString NewCode)
{
	LuaCode = NewCode;
	UpdateLua();
}

void ARobotiks_Machine::ServerUpdateLuaCode_Implementation(const FString& NewCode)
{
	UpdateLuaCode(NewCode);
	UKismetSystemLibrary::PrintString(this, "Hello");
}

void ARobotiks_Machine::ServerOnInteraction_Implementation()
{
}

FString ARobotiks_Machine::GetLuaCode()
{
	return LuaCode;
}

void ARobotiks_Machine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARobotiks_Machine, LuaCode);
	DOREPLIFETIME(ARobotiks_Machine, InputList);
}

void ARobotiks_Machine::CallLuaAdvanced(FString Name, TArray<FLuaValue> ArgsIn, bool UpdateBeforeCall)
{
	TArray<FLuaValue> Args;
	Args.Add(FLuaValue(this));
	Args.Append(ArgsIn);

	if (UpdateBeforeCall)
	{
		ULuaBlueprintFunctionLibrary::LuaRunString(this, RobotiksLuaState, LuaCode);
	}
	
	ULuaBlueprintFunctionLibrary::LuaGlobalCall(this, RobotiksLuaState, Name, Args);
}

void ARobotiks_Machine::OnConnectInput_Implementation()
{
}

void ARobotiks_Machine::OnInteraction_Implementation()
{
}

void ARobotiks_Machine::ConnectInput(ARobotiks_Machine* Robotik, int Index)
{
	InputList[Index] = Robotik;
	OnConnectInput();
}

void ARobotiks_Machine::OnSignal_Implementation(const int Frequency)
{
	CallLua("OnSignal" + FString::FromInt(Frequency));
}

