// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMover.h"

// Sets default values for this component's properties
UCameraMover::UCameraMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraMover::BeginPlay() {
	Super::BeginPlay();
	MoveToStateLocation(startPos);
	// ...	
}


// Called every frame
void UCameraMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//WasInputKeyJustPressed(EKeys::C)
	// ...
}

void UCameraMover::CycleAdjStateLocation(FString inputKey) {
	UCameraPosition* cameraPos = GetComponentByClass<UCameraPosition>(currentPos);

	UFunctions::Log("Blorp");
	if (IsValid(UFunctions::GetComponentByClass<UCameraPosition>(currentPos)))
	{
		if (UFunctions::GetComponentByClass<UCameraPosition>(currentPos)->connectionsList.Contains(inputKey))
		{
			UCameraPosition* loc = *(UFunctions::GetComponentByClass<UCameraPosition>(currentPos)->connectionsList.Find(inputKey));
			
			self->SetActorLocation(loc->GetOwner()->GetActorLocation());
			self->SetActorRotation(loc->GetOwner()->GetActorRotation());

			currentPos = loc->GetOwner();
		} else {
			UFunctions::Log("input key not found in cameraPosition %s connections list", *(UFunctions::GetComponentByClass<UCameraPosition>(currentPos)->stateLabel));
			UE_LOG(LogTemp, Warning, TEXT("input key not found in cameraPosition %s connections list"), *(UFunctions::GetComponentByClass<UCameraPosition>(currentPos)->stateLabel));
		}
	} 
	else {
		UFunctions::Log("Camera Position Component not found");
	}
}

void UCameraMover::MoveToStateLocation(AActor* loc) {
	if (IsValid(loc)) {
		
		self->SetActorLocation(loc->GetActorLocation());
		self->SetActorRotation(loc->GetActorRotation());

		currentPos = loc;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("state location does not exist"));
	}
	
}

// void UCameraMover::SetPlayerController(AActor* pc)
// {
// 	playerController = pc;
// }

