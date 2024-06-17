// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_MyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CUSTOMEDPROJECT_API UAC_MyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(HideInDetailPanel))
	FText SelectedAnimalType = FText::FromString("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(HideInDetailPanel))
	FText SelectedAnimal = FText::FromString("");

	// Sets default values for this component's properties
	UAC_MyActorComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
