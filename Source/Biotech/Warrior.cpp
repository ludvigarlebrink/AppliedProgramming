// Fill out your copyright notice in the Description page of Project Settings.

#include "Warrior.h"

AWarrior::AWarrior()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();
}
