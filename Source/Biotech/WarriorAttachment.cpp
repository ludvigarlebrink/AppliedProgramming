// Fill out your copyright notice in the Description page of Project Settings.

#include "WarriorAttachment.h"

AWarriorAttachment::AWarriorAttachment()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>((TEXT("Root"))));
}

void AWarriorAttachment::BeginPlay()
{
	Super::BeginPlay();
}
