// Fill out your copyright notice in the Description page of Project Settings.

#include "Warlord.h"
#include "ArmyAttachment.h"
#include "Warrior.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

AWarlord::AWarlord()
{
	PrimaryActorTick.bCanEverTick = false;

	ArmyHalfWidth = 1;
	ArmyHeight = 1;
}

void AWarlord::JoinArmy(AWarrior* Warrior)
{
	if (Army.Num() >= ArmyAttachments.Num())
	{
		ExpandArmy();
	}

	AActor* ArmyAttachment = ArmyAttachments[Army.Num()];
	Warrior->ArmyAttachment = ArmyAttachment;
	Warrior->Warlord = this;
	Army.Add(Warrior);
}

AWarrior* AWarlord::SpawnWarrior()
{
	if (Army.Num() >= ArmyAttachments.Num())
	{
		ExpandArmy();
	}

	AActor* ArmyAttachment = ArmyAttachments[Army.Num()];
	FActorSpawnParameters Spawn = {};
	Spawn.SpawnCollisionHandlingOverride =	ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AWarrior* Warrior = GetWorld()->SpawnActor<AWarrior>(AWarrior::StaticClass(), FTransform(ArmyAttachment->GetActorLocation()), Spawn);
	Warrior->ArmyAttachment = ArmyAttachment;
	Warrior->Warlord = this;
	Army.Add(Warrior);

	return Warrior;
}

void AWarlord::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWarlord::BeginPlay()
{
	Super::BeginPlay();
	
	// Minus one for for the warlord.
	ArmyAttachments.SetNum((ArmyHalfWidth * 2 + 1) * ArmyHeight - 1);
	for (int32 Count = 0; Count < ArmyAttachments.Num(); ++Count)
	{
		AArmyAttachment* Actor = GetWorld()->SpawnActor<AArmyAttachment>(AArmyAttachment::StaticClass());
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
		AArmyAttachment* Actor = GetWorld()->SpawnActor<AArmyAttachment>(AArmyAttachment::StaticClass());
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
