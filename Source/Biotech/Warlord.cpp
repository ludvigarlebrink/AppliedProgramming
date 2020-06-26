// Fill out your copyright notice in the Description page of Project Settings.

#include "Warlord.h"
#include "WarriorAttachment.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

AWarlord::AWarlord()
{
	PrimaryActorTick.bCanEverTick = true;

	ArmyHalfWidth = 1;
	ArmyHeight = 1;
}

void AWarlord::BeginPlay()
{
	Super::BeginPlay();
	
	// Minus one for for the warlord.
	ArmyAttachments.SetNum((ArmyHalfWidth * 2 + 1) * ArmyHeight - 1);
	for (int32 Count = 0; Count < ArmyAttachments.Num(); ++Count)
	{
		AWarriorAttachment* Actor = GetWorld()->SpawnActor<AWarriorAttachment>(AWarriorAttachment::StaticClass());
		Actor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		ArmyAttachments[Count] = Actor;
	}

	UpdateArmyAttachments();
}

void AWarlord::ExpandArmy()
{
	++ArmyHeight;
	int32 Begin = ArmyAttachments.Num();
	ArmyAttachments.SetNum((ArmyHalfWidth * 2 + 1) * ArmyHeight - 1);
	
	for (int32 Count = Begin; Count < ArmyAttachments.Num(); ++Count)
	{
		AWarriorAttachment* Actor = GetWorld()->SpawnActor<AWarriorAttachment>(AWarriorAttachment::StaticClass());
		Actor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		ArmyAttachments[Count] = Actor;
	}

	UpdateArmyAttachments();
}

void AWarlord::UpdateArmyAttachments()
{
	FVector2D Scale = FVector2D(200.0f, 200.0f);
	int32 ArmyWidth = ArmyHalfWidth * 2 + 1;

	for (int32 X = 0; X < ArmyHeight; ++X)
	{
		// Is not warlord.
		if (X != 0)
		{
			int32 Index = ArmyWidth * X - 1;
			ArmyAttachments[Index]->SetActorRelativeLocation(FVector(X * -1.0f * Scale.X, 0.0f, 0.0f));
		}

		for (int32 Y = 0, Count = 0; Y < ArmyHalfWidth; ++Y, Count += 2)
		{
			int32 Index0 = (ArmyWidth * X) + Count;
			int32 Index1 = (ArmyWidth * X) + Count + 1;
			ArmyAttachments[Index0]->SetActorRelativeLocation(FVector(X * -1.0f * Scale.X, (Y + 1) * Scale.Y, 0.0f));
			ArmyAttachments[Index1]->SetActorRelativeLocation(FVector(X * -1.0f * Scale.X, (Y + 1) * -1.0f * Scale.Y, 0.0f));
		}
	}
}

void AWarlord::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

AWarriorAttachment* AWarlord::JoinArmy(AWarrior* Warrior)
{
	if (Army.Num() >= ArmyAttachments.Num())
	{
		ExpandArmy();
	}

	AWarriorAttachment* ArmyAttachment = ArmyAttachments[Army.Num()];
	ArmyAttachment->Warrior = Warrior;
	Army.Add(Warrior);
	return ArmyAttachment;
}
