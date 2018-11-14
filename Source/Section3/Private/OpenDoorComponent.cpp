// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorComponent.h"

// Sets default values for this component's properties
UOpenDoorComponent::UOpenDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// 记录默认的rotator
	AActor* Owner = GetOwner();
	DefaultRotator = Owner->GetTransform().Rotator();

	// 获得玩家控制的pawn
	if (GetWorld()->GetFirstPlayerController())
	{
		TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	

}

// open door
void UOpenDoorComponent::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator Rot = DefaultRotator;
	// open the door by X degrees
	Rot.Yaw += OpenYaw;
	Owner->SetActorRotation(Rot);
	bDoorOpened = true;
}

void UOpenDoorComponent::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator Rot = DefaultRotator;
	Owner->SetActorRotation(Rot);
	bDoorOpened = false;
}

// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// trigger 事件
	// 当目标Pawn与trigger发生重叠时，open door
	if (TriggerVolume)
	{
		if (TriggerVolume->IsOverlappingActor(TargetPawn))
		{
			OpenDoor();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
	}

	// Check if it is time to close
	if (bDoorOpened)
	{
		if (GetWorld()->GetTimeSeconds() > LastDoorOpenTime + DoorCloseDelay)
		{
			CloseDoor();
		}
	}
	

}

