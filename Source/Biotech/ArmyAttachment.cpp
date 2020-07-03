// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyAttachment.h"

// Sets default values
AArmyAttachment::AArmyAttachment()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
}

