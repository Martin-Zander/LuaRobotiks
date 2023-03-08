// Fill out your copyright notice in the Description page of Project Settings.


#include "Robotiks_FunctionLibary.h"

FString URobotiks_FunctionLibary::AddLine(const FString& String, const FString& AddedLine)
{
	return String + AddedLine + "\n";
}

FVector URobotiks_FunctionLibary::GetEndOfLine(FVector StartPosition, FVector Direction, float LineLength)
{
	return StartPosition + (Direction * LineLength);
}

FHitResult URobotiks_FunctionLibary::LineTraceInDirection(UObject* WorldContextObject, FVector StartPosition, FVector Direction, float LineLength)
{
	FHitResult Result;
	AActor* Actor = Cast<AActor>(WorldContextObject);
	if (Actor)
	{
		if (Actor->GetWorld())
		{
			Actor->GetWorld()->LineTraceSingleByChannel(Result, StartPosition, GetEndOfLine(StartPosition, Direction, LineLength), ECC_Visibility, FCollisionQueryParams("", false, Actor));
		}
	}
	return Result;
}
