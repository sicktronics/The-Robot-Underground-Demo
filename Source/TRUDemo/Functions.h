// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Functions.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRUDEMO_API UFunctions : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFunctions();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	template<class T>
	static T* GetComponentByClass(AActor* Actor)
	{
		// Checks whether actor is valid before trying to get component
		return Actor ? Cast<T>(Actor->GetComponentByClass(T::StaticClass())) : nullptr;
	}

	static void Log(const char* msg, ...);
		
};
