// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IQuestEditor.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class IDetailsView;

class QUESTSYSTEMEDITOR_API FQuestEditor : public IQuestEditor
{
public:

	FQuestEditor();

	virtual ~FQuestEditor();

	/** This method decides how the custom asset editor will be initialized. */
	void InitQuestEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UQuest* InQuest);

	/** Restores the quest graph we were editing or creates a new one if none is available */
	void RestoreQuestGraph();

	/** This function creates tab spawners on editor initialization. */
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	/** This function unregisters tab spawners on editor initialization. */
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	//~Begin IToolkit interface.
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override;
	//~End IToolkit interface.

	//~Begin IQuestEditor interface.
	virtual UQuest* GetQuest() const override;
	virtual void SetQuest(UQuest* LocalQuest) override;
	//~End IQuestEditor interface.

private:

	/** Create widget for graph editing. */
	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	
	/** Create the properties tab and its content. */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);

public:

	/** The name given to all instances of this type of editor. */
	static const FName ToolkitFName;

private:

	/** Dockable tab for properties. */
	TSharedPtr<SDockableTab> PropertiesTab;

	TSharedPtr<FDocumentTracker> DocumentManager;
	TWeakPtr<FDocumentTabFactory> GraphEditorTabFactory;

	/** The Custom Asset open within this editor. */
	UQuest* Quest;
};
