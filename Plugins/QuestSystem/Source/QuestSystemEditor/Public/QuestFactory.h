// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "QuestFactory.generated.h"

UCLASS()
class QUESTSYSTEMEDITOR_API UQuestFactory : public UFactory
{
	GENERATED_BODY()
	
public:

	UQuestFactory();

	//~Begin UFactory Interface.
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	//~End UFactory Interface.
};
