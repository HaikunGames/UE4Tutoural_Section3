// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoorComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

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

	if (PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has Pressure Plate."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s needs a pressure plate."), *(Owner->GetName()));
	}
	
}


float UOpenDoorComponent::GetTotalMassOfActorsOnPlate()
{

	float TotalMass = 0.0f;

	if (PressurePlate) {
		// find all the overlapping actors
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OverlappingActors);

		// sum the mass of the actors.
		for (const AActor* Iter : OverlappingActors)
		{
			if (Iter->FindComponentByClass<UPrimitiveComponent>())
				TotalMass += Iter->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		}
		// UE_LOG(LogTemp, Warning, TEXT("%.2f KG in the Pressure Plate."), TotalMass);
	}
	
	return TotalMass;
}

// Called every frame
void UOpenDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// trigger 事件
	// 当目标Pawn与trigger发生重叠时，open door
	if (PressurePlate)
	{
		// if the total mass greater than X, open the door
		if (GetTotalMassOfActorsOnPlate() >= TotalMassForOpening) // TODO:: make a parameter
		{
			OnOpenRequest.Broadcast();
		}
		else
		{
			OnCloseRequest.Broadcast();
		}
	}
}

