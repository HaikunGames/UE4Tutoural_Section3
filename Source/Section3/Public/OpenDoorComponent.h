// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION3_API UOpenDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// return total mass in KG
	float GetTotalMassOfActorsOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FOnActionRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FOnActionRequest OnCloseRequest;

protected:


	UPROPERTY(EditAnywhere)
		float TotalMassForOpening = 50.0f;

	// the trigger volume that can launch the open door event
	UPROPERTY(EditInstanceOnly)
		ATriggerVolume* PressurePlate = nullptr;

	// target Pawn
	// who can launch the open door event



};
