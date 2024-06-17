// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperLib.generated.h"


UCLASS()
class CUSTOMEDPROJECT_API UHelperLib : public UObject
{
	GENERATED_BODY()
	
	public:
		static TArray<FString> GetAnimalTypeArray();
		static TArray<FString> GetAnimalArrayFromType(FString AnimalType);
};