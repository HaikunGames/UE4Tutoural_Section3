// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoorComponent.generated.h"


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

	// open door
	void OpenDoor();

	// close door
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// default rotator
	UPROPERTY(VisibleAnywhere)
		FRotator DefaultRotator;

	// open the door on Yaw by X degrees
	UPROPERTY(EditAnywhere)
		float OpenYaw = 70.0f;

	// door close delay
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;

	UPROPERTY(VisibleAnywhere)
		float LastDoorOpenTime;

	UPROPERTY(VisibleAnywhere)
		bool bDoorOpened = false;

	// the trigger volume that can launch the open door event
	UPROPERTY(EditInstanceOnly)
		ATriggerVolume* TriggerVolume;

	// target Pawn
	// who can launch the open door event
	UPROPERTY(VisibleAnywhere)
		APawn* TargetPawn;


};
