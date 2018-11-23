// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION3_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InputSetup();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// grab 
	void Grab();
	// release
	void Release();

	// get the end point of the line trance
	FVector GetLineTranceEnd();

private:
	// how far ahead of the pawn can reach in cm
	UPROPERTY(EditAnywhere)
	float Reach = 200.0f;

 	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UPROPERTY(EditAnywhere)
	UInputComponent* InputComponent = nullptr;
};
