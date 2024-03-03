// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Trigger componet is ALIVE"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr)
	{
		return;
	}

	AActor* ReturnActor = GetAcceptableActor();
	if (ReturnActor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(ReturnActor->GetRootComponent());

		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		const FAttachmentTransformRules Rules = FAttachmentTransformRules::KeepWorldTransform;
		ReturnActor->AttachToComponent(this, Rules);

		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		// Has Acceptable Tag and !Grabbed
		if (Actor->ActorHasTag(TriggerTag) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}
