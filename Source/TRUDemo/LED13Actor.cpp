// Fill out your copyright notice in the Description page of Project Settings.


#include "LED13Actor.h"

// Sets default values
ALED13Actor::ALED13Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Wanna give it a static mesh
	// UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LED13"));
	// const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Users/Shared/Epic Games/UE_5.4/Engine/Content/BasicShapes/Sphere.uasset"));
	// // MeshComponent->SetupAttachment();
	// MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// MeshComponent->SetStaticMesh(MeshObj.Object);
	// MeshComponent->RegisterComponent();




}

// Called when the game starts or when spawned
void ALED13Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALED13Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

