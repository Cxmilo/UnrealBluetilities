// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/Selection.h"
#include "Engine/StaticMeshActor.h"
#include "UnrealEd.h"
#include "MyActorActionUtility.h"


/************************************************************************/
/* You Must include UnrealEd in PublicDependencyModuleNames.AddRange inside Project.Build.cs                                                                     */
/************************************************************************/
void UMyActorActionUtility::ChangeMaterial_FromCode(UMaterialInterface* NewMaterial)
{
	USelection* SelectedActors = GEditor->GetSelectedActors();

	if (nullptr == SelectedActors)
	{
		return;
	}

	TArray<UObject*> SelectedObjects;
	SelectedActors->GetSelectedObjects(AStaticMeshActor::StaticClass(), SelectedObjects);

	for (UObject* SelectedObject : SelectedObjects)
	{
		if (nullptr == SelectedObject)
		{
			continue;
		}

		AStaticMeshActor* StaticMeshActor = dynamic_cast<AStaticMeshActor*>(SelectedObject);

		if (nullptr != SelectedObject)
		{
			UStaticMeshComponent* StaticMeshComponet = StaticMeshActor->GetStaticMeshComponent();

			if (nullptr != StaticMeshComponet)
			{
				int32 NumMaterials = StaticMeshComponet->GetNumMaterials();
				for (size_t i = 0; i < NumMaterials; i++)
				{
					StaticMeshComponet->SetMaterial(i, NewMaterial);
				}
			}
		}
	}

}
