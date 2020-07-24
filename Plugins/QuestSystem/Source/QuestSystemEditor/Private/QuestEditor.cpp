// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestEditor.h"
#include "Modules/ModuleManager.h"
#include "Editor.h"
#include "EditorStyleSet.h"
#include "PropertyEditorModule.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "QuestGraph.h"
#include "Quest.h"
#include "QuestSystemEditor.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Widgets/Docking/SDockTab.h"
#include "QuestEditorTabs.h"
#include "QuestEditorTabFactories.h"
#include "EdGraphSchema_Quest.h"


#define LOCTEXT_NAMESPACE "QuestEditor"

const FName FQuestEditor::ToolkitFName(TEXT("QuestEditor"));

FQuestEditor::FQuestEditor()
{
}

FQuestEditor::~FQuestEditor()
{
	PropertiesTab.Reset();
}

void FQuestEditor::InitQuestEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UQuest* InQuest)
{
	SetQuest(InQuest);

	TSharedPtr<FQuestEditor> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker);
		DocumentManager->Initialize(ThisPtr);

		// Register the document factories.
		{
			TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FQuestGraphEditorSummoner(ThisPtr,
				FQuestGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &FQuestEditor::CreateGraphEditorWidget)
				));

			// Also store off a reference to the grapheditor factory so we can find all the tabs spawned by it later.
			GraphEditorTabFactory = GraphEditorFactory;
			DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
		}
	}

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_QuestEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(FQuestEditorTabs::GraphEditorID, ETabState::ClosedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.3f)
					->AddTab(FQuestEditorTabs::GraphDetailsID, ETabState::OpenedTab)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, QuestEditorAppIdentifier,
		StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InQuest);

	RestoreQuestGraph();
}

void FQuestEditor::RestoreQuestGraph()
{
	UQuestGraph* Graph = Cast<UQuestGraph>(Quest->Graph);
	const bool bNewGraph = Graph == NULL;
	if (bNewGraph)
	{
		Quest->Graph = FBlueprintEditorUtils::CreateNewGraph(Quest, TEXT("Quest"), UQuestGraph::StaticClass(), UEdGraphSchema_Quest::StaticClass());
		Graph = Cast<UQuestGraph>(Quest->Graph);
		const UEdGraphSchema* Schema = Graph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*Graph);

		Graph->OnCreated();
	}
	else
	{
		Graph->OnLoaded();
	}

	Graph->Initialize();

	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(Graph);
	TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, FDocumentTracker::OpenNewDocument);
}

void FQuestEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	DocumentManager->SetTabManager(InTabManager);
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void FQuestEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

FName FQuestEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FQuestEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Quest Editor");
}

FText FQuestEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Quest Editor");
}

FString FQuestEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase").ToString();
}

FLinearColor FQuestEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

bool FQuestEditor::IsPrimaryEditor() const
{
	return true;
}

UQuest* FQuestEditor::GetQuest() const
{
	return Quest;
}

void FQuestEditor::SetQuest(UQuest* InQuest)
{
	Quest = InQuest;
}

TSharedRef<class SGraphEditor> FQuestEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("QuestGraphLabel", "Quest"))
			.TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
		]
		];

	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
		.TitleBar(TitleBarWidget)
		.GraphToEdit(InGraph);
}

TSharedRef<SDockTab> FQuestEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id.
	check(Args.GetTabId() == FQuestEditorTabs::GraphDetailsID);

	// Return a new slate dockable tab that contains our details view.
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Quest"))
		.TabColorScale(GetTabColorScale())
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Test", "Test"))
		];
}

#undef LOCTEXT_NAMESPACE
