#pragma once

#include "CoreMinimal.h"
#include "DetailLayoutBuilder.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"


class FReply;

class FAC_MyActorComponentDetails : public IDetailCustomization
{

	public :

		static TSharedRef<IDetailCustomization> MakeInstance();
		
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;
	
		FReply EditObjects();

		FMenuBuilder CreateMenuBuilder(TArray<FString> Array, TSharedRef<IPropertyHandle> MyHandleProp,TArray<TSharedRef<IPropertyHandle>> DependencyProps);
	
		void OnComboChanged(FString Arg, TSharedRef<IPropertyHandle> MyHandleProp, TArray<TSharedRef<IPropertyHandle>> DependencyProps);
	

	private:
		TArray<TWeakObjectPtr<UObject>> ObjectsToEdit;
		TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;
};
