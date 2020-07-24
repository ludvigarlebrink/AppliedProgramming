// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestFactory.h"
#include "Quest.h"

UQuestFactory::UQuestFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UQuest::StaticClass();
}

UObject* UQuestFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	// Create and return a new instance of our MyCustomAsset object.
	UQuest* Quest = NewObject<UQuest>(InParent, Class, Name, Flags);
	return Quest;
}
