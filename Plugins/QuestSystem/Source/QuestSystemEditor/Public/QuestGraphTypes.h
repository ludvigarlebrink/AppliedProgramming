// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/WeakObjectPtr.h"
#include "QuestGraphTypes.generated.h"

USTRUCT()
struct QUESTSYSTEMEDITOR_API FQuestGraphNodeClassData
{
	GENERATED_BODY()

public:

	FQuestGraphNodeClassData() {}
	FQuestGraphNodeClassData(UClass* InClass, const FString& InDeprecatedMessage);
	FQuestGraphNodeClassData(const FString& InAssetName, const FString& InGeneratedClassPackage, const FString& InClassName, UClass* InClass);

	FString ToString() const;
	FString GetClassName() const;
	FText GetCategory() const;
	FString GetDisplayName() const;
	UClass* GetClass(bool bSilent = false);
	bool IsAbstract() const;

	FORCEINLINE bool IsBlueprint() const { return AssetName.Len() > 0; }
	FORCEINLINE bool IsDeprecated() const { return DeprecatedMessage.Len() > 0; }
	FORCEINLINE FString GetDeprecatedMessage() const { return DeprecatedMessage; }
	FORCEINLINE FString GetPackageName() const { return GeneratedClassPackage; }

public:

	/** set when child class masked this one out (e.g. always use game specific class instead of engine one) */
	uint32 bIsHidden : 1;

	/** set when class wants to hide parent class from selection (just one class up hierarchy) */
	uint32 bHideParent : 1;

private:

	/** pointer to uclass */
	TWeakObjectPtr<UClass> Class;

	/** path to class if it's not loaded yet */
	UPROPERTY()
	FString AssetName;

	UPROPERTY()
	FString GeneratedClassPackage;

	/** resolved name of class from asset data */
	UPROPERTY()
	FString ClassName;

	/** User-defined category for this class */
	UPROPERTY()
	FText Category;

	/** message for deprecated class */
	FString DeprecatedMessage;
};

struct QUESTSYSTEMEDITOR_API FQuestGraphNodeClassNode
{
public:

	void AddUniqueSubNode(TSharedPtr<FQuestGraphNodeClassNode> SubNode);

	FQuestGraphNodeClassData Data;
	FString ParentClassName;

	TSharedPtr<FQuestGraphNodeClassNode> ParentNode;
	TArray<TSharedPtr<FQuestGraphNodeClassNode> > SubNodes;
};

struct QUESTSYSTEMEDITOR_API FQuestGraphNodeClassHelper
{
public:

	DECLARE_MULTICAST_DELEGATE(FOnPackageListUpdated);

public:

	FQuestGraphNodeClassHelper(UClass* InRootClass);
	~FQuestGraphNodeClassHelper();

	void GatherClasses(const UClass* BaseClass, TArray<FQuestGraphNodeClassData>& AvailableClasses);
	static FString GetDeprecationMessage(const UClass* Class);

	void OnAssetAdded(const struct FAssetData& AssetData);
	void OnAssetRemoved(const struct FAssetData& AssetData);
	void InvalidateCache();
	void OnHotReload(bool bWasTriggeredAutomatically);

	static void AddUnknownClass(const FQuestGraphNodeClassData& ClassData);
	static bool IsClassKnown(const FQuestGraphNodeClassData& ClassData);
	static FOnPackageListUpdated OnPackageListUpdated;

	static int32 GetObservedBlueprintClassCount(UClass* BaseNativeClass);
	static void AddObservedBlueprintClasses(UClass* BaseNativeClass);
	void UpdateAvailableBlueprintClasses();

private:

	UClass* RootNodeClass;
	TSharedPtr<FQuestGraphNodeClassNode> RootNode;
	static TArray<FName> UnknownPackages;
	static TMap<UClass*, int32> BlueprintClassCount;

	TSharedPtr<FQuestGraphNodeClassNode> CreateClassDataNode(const struct FAssetData& AssetData);
	TSharedPtr<FQuestGraphNodeClassNode> FindBaseClassNode(TSharedPtr<FQuestGraphNodeClassNode> Node, const FString& ClassName);
	void FindAllSubClasses(TSharedPtr<FQuestGraphNodeClassNode> Node, TArray<FQuestGraphNodeClassData>& AvailableClasses);

	UClass* FindAssetClass(const FString& GeneratedClassPackage, const FString& AssetName);
	void BuildClassGraph();
	void AddClassGraphChildren(TSharedPtr<FQuestGraphNodeClassNode> Node, TArray<TSharedPtr<FQuestGraphNodeClassNode> >& NodeList);

	bool IsHidingClass(UClass* Class);
	bool IsHidingParentClass(UClass* Class);
	bool IsPackageSaved(FName PackageName);
};
