// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

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
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputSetup();
}


void UGrabber::InputSetup()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector LineTranceEnd = GetLineTranceEnd();

	// if grabbed sth. 
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTranceEnd);
	}

}

void UGrabber::Grab()
{

	UE_LOG(LogTemp, Warning, TEXT("Grab @ %.2f sec."), GetWorld()->GetTimeSeconds());

	// get player viwe point
	FVector Location;
	FRotator Rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotator);

	FVector LineTranceEnd = GetLineTranceEnd();

	// draw a read trace in the world to visualize
	DrawDebugLine(GetWorld(), Location, LineTranceEnd, FColor(255, 0, 0), false, 0.0f, 0, 1.0f);

	// ray-cast out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams QP;
	QP.AddIgnoredActor(GetOwner());
	QP.bTraceComplex = false;

	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Location,
		LineTranceEnd,
		ECollisionChannel::ECC_PhysicsBody,
		QP
	);

	// see what we hit
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab :%s. "), *HitResult.GetActor()->GetName());

		// attach physics handle
		if (PhysicsHandle) {
			PhysicsHandle->GrabComponent(
				HitResult.GetComponent(),
				NAME_None,
				HitResult.GetActor()->GetActorLocation(),
				true
			);
		}
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release @ %.2f sec."), GetWorld()->GetTimeSeconds());
	if (PhysicsHandle)
		PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetLineTranceEnd()
{
	// get player viwe point
	FVector Location;
	FRotator Rotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotator);

	return Location + Rotator.Vector() * Reach;
}

