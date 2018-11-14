// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get player viwe point
	FVector Location;
	FRotator Rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotator);

	FVector LineTranceEnd = Location + Rotator.Vector() * Reach;

	// draw a read trace in the world to visualize
	DrawDebugLine(GetWorld(), Location, LineTranceEnd,FColor(255,0,0),false, 0.0f, 0, 1.0f);

	// ray-cast out to reach distance

	// see what we hit

	
}

