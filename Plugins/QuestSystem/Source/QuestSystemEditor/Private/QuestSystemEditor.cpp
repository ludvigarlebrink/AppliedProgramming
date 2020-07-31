// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestSystemEditor.h"
#include "QuestEditor.h"
#include "QuestNode.h"
#include "QuestGraphTypes.h"
#include "AssetTypeActions_Quest.h"

const FName QuestEditorAppIdentifier = FName(TEXT("StaticMeshEditorApp"));

#define LOCTEXT_NAMESPACE "QuestSystemEditor"

TSharedRef<IQuestEditor> FQuestSystemEditorModule::CreateQuestEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UQuest* Quest)
{
	if (!ClassCache.IsValid())
	{
		ClassCache = MakeShareable(new FQuestGraphNodeClassHelper(UQuestNode::StaticClass()));
		FQuestGraphNodeClassHelper::AddObservedBlueprintClasses(UQuestNode::StaticClass());
		ClassCache->UpdateAvailableBlueprintClasses();
	}

	TSharedRef<FQuestEditor> NewQuestEditor(new FQuestEditor());
	NewQuestEditor->InitQuestEditor(Mode, InitToolkitHost, Quest);
	return NewQuestEditor;
}

void FQuestSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

TSharedPtr<FExtensibilityManager> FQuestSystemEditorModule::GetMenuExtensibilityManager()
{
	return MenuExtensibilityManager;
}

TSharedPtr<FExtensibilityManager> FQuestSystemEditorModule::GetToolBarExtensibilityManager()
{
	return ToolBarExtensibilityManager;
}

void FQuestSystemEditorModule::StartupModule()
{
	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_Quest()));
}

void FQuestSystemEditorModule::ShutdownModule()
{
	MenuExtensibilityManager.Reset();
	ToolBarExtensibilityManager.Reset();
	ClassCache.Reset();

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		// Unregister our custom created assets from the AssetTools
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
		}
	}

	CreatedAssetTypeActions.Empty();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestSystemEditorModule, QuestSystemEditor)
