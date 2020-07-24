// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetTypeActions_Quest.h"
#include "Quest.h"
#include "QuestSystemEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_Quest"

FText FAssetTypeActions_Quest::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_Quest", "AssetTypeActions_Quest", "Quest");
}

FColor FAssetTypeActions_Quest::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FAssetTypeActions_Quest::GetSupportedClass() const
{
	return UQuest::StaticClass();
}

void FAssetTypeActions_Quest::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Quest = Cast<UQuest>(*ObjIt);
		if (Quest)
		{
			FQuestSystemEditorModule* QuestSystemEditorModule = &FModuleManager::LoadModuleChecked<FQuestSystemEditorModule>("QuestSystemEditor");
			QuestSystemEditorModule->CreateQuestEditor(Mode, EditWithinLevelEditor, Quest);
		}
	}
}

uint32 FAssetTypeActions_Quest::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
