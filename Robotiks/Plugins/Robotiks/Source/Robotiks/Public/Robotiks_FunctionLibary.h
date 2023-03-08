// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Robotiks_FunctionLibary.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTIKS_API URobotiks_FunctionLibary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString AddLine(const FString& String, const FString& AddedLine);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetEndOfLine(FVector StartPosition, FVector Direction, float LineLength);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FHitResult LineTraceInDirection(UObject* WorldContextObject, FVector StartPosition, FVector Direction, float LineLength);
};
