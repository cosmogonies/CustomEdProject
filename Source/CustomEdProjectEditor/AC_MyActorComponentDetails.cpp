// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_MyActorComponentDetails.h"

#include "../CustomEdProject/AC_MyActorComponent.h"
#include "../CustomEdProject/HelperLib.h"

#include "Editor/PropertyEditor//Public/DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/DetailCategoryBuilder.h"
#include "Editor/PropertyEditor/Public/DetailWidgetRow.h"

#include "Widgets/Input/SComboButton.h"

#define LOCTEXT_NAMESPACE "MyActorComponentDetails"


TSharedRef<IDetailCustomization> FAC_MyActorComponentDetails::MakeInstance()
{
	return MakeShareable((new FAC_MyActorComponentDetails));
}


void FAC_MyActorComponentDetails::CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder)
{
	// Intermediate CustomizeDetails to allow caching of DetailBuilder info (needed for refresh after callbacks (like OnComboChanged))
	CachedDetailBuilder = DetailBuilder;
	CustomizeDetails(*DetailBuilder);
}


void FAC_MyActorComponentDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	
	DetailBuilder.GetObjectsBeingCustomized(ObjectsToEdit);

	//Creation of the category Custom. Important category is pushed up at the top of details view
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Custom Selector", FText::GetEmpty(),ECategoryPriority::Important);

	// Geter of the component properties:
	TSharedRef<IPropertyHandle> MyAnimalTypeHandleProp =  DetailBuilder.GetProperty("SelectedAnimalType");
	TSharedRef<IPropertyHandle> MyAnimalHandleProp =  DetailBuilder.GetProperty("SelectedAnimal");

	
	//Animal-Type Custom Selector

		//Get possible choices:
		TArray<FString> AnimalTypeArray = UHelperLib::GetAnimalTypeArray();

		//Create dependencies : when a driver prop change, the driven prop must also be recomputed 
		TArray<TSharedRef<IPropertyHandle>> DependencyProps; 
		DependencyProps.Add(MyAnimalHandleProp);
		
		FMenuBuilder MenuBuilderAnimalType = CreateMenuBuilder(AnimalTypeArray, MyAnimalTypeHandleProp,DependencyProps);

		FText MyAnimalTypeValue;
		MyAnimalTypeHandleProp->GetValue(MyAnimalTypeValue);
	
		//Insert Sub Menu:
		Category.AddCustomRow(LOCTEXT("SComboButtonRow","SComboButton Row"))
			.NameContent()[SNew(STextBlock)
							.Text(LOCTEXT("Value", "Animal Type :"))
							.Font(IDetailLayoutBuilder::GetDetailFont())]
			.ValueContent()[
			SNew(SComboButton)
			.ButtonContent()[SNew(STextBlock).Text(MyAnimalTypeValue)]
			.MenuContent()[MenuBuilderAnimalType.MakeWidget()]
			];



	//Animal Custom Selector

		//Get possible choices:
		TArray<FString> AnimalArray = UHelperLib::GetAnimalArrayFromType(MyAnimalTypeValue.ToString());
	
		FMenuBuilder MenuBuilderAnimal = CreateMenuBuilder(AnimalArray, MyAnimalHandleProp, TArray<TSharedRef<IPropertyHandle>>());

		FText MyAnimalValue;
		MyAnimalHandleProp->GetValue(MyAnimalValue);

		Category.AddCustomRow(LOCTEXT("SComboButtonRow","SComboButton Row"))
			.NameContent()[SNew(STextBlock)
							.Text(LOCTEXT("Value", "Animal :"))
							.Font(IDetailLayoutBuilder::GetDetailFont())]
			.ValueContent()[
			SNew(SComboButton)
			.ButtonContent()[SNew(STextBlock).Text( MyAnimalValue)]
			.MenuContent()[MenuBuilderAnimal.MakeWidget()]
			];

	//Redraw of the details view.
	DetailBuilder.ForceRefreshDetails();
}


FMenuBuilder FAC_MyActorComponentDetails::CreateMenuBuilder(TArray<FString> Array, TSharedRef<IPropertyHandle> MyHandleProp, TArray<TSharedRef<IPropertyHandle>> DependencyProps)
{
	
	FMenuBuilder MenuBuilder(true, NULL);
	{
		for (FString MyData: Array)
		{
			if(MyData=="|")
			{
				MenuBuilder.AddMenuSeparator();
			}
			else
			{
				MenuBuilder.AddMenuEntry
				(
					FText::FromString(MyData),
				FText::FromString(MyData),
					FSlateIcon(FAppStyle::GetAppStyleSetName(),"OverridePropertiesWidget.AddEntry"),
					FUIAction(FExecuteAction::CreateSP( this, &FAC_MyActorComponentDetails::OnComboChanged, MyData, MyHandleProp, DependencyProps),FCanExecuteAction())
				);	
			}

		}
	}
	return MenuBuilder;
}


void FAC_MyActorComponentDetails::OnComboChanged(FString Arg, TSharedRef<IPropertyHandle> MyHandleProp, TArray<TSharedRef<IPropertyHandle>> DependencyProps)
{
	//The Prop has changed, we need to update it accordingly:
	MyHandleProp->SetValue(*FString(Arg));
	
	for(TSharedRef<IPropertyHandle> currentProp : DependencyProps)
	{
		//currentProp->SetValue(*FString(""));

		//We have a dependency prop, let's affect it with the very first available taksk:
		TArray<FString> MyNewAnimalArray = UHelperLib::GetAnimalArrayFromType(Arg);
		currentProp->SetValue(*FString(MyNewAnimalArray[0]));
	}

	//If we are on Blueprint Editor, we must redraw:
	if (IDetailLayoutBuilder* DetailBuilder = CachedDetailBuilder.Pin().Get())
	{
		DetailBuilder->ForceRefreshDetails();
	}
}


#undef LOCTEXT_NAMESPACE