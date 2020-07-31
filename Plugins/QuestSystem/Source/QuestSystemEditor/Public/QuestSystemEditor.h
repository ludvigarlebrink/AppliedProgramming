// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AssetToolsModule.h"
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "IAssetTools.h"

extern const FName QuestEditorAppIdentifier;

class IQuestEditor;
class UQuest;
struct FQuestGraphNodeClassHelper;

class FQuestSystemEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:

	TSharedRef<IQuestEditor> CreateQuestEditor(const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost, UQuest* Quest);

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override;
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override;

	//~Begin IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~End IModuleInterface interface.

public:

	TSharedPtr<FQuestGraphNodeClassHelper> ClassCache;

private:

	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
