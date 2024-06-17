 #include "CustomEdProjectEditorModule.h"

#include "../CustomEdProject/AC_MyActorComponent.h"
#include "../CustomEdProjectEditor/AC_MyActorComponentDetails.h"


IMPLEMENT_GAME_MODULE(FCustomEdProjectEditorModule, CustomGameplayEditor);
 
void FCustomEdProjectEditorModule::StartupModule()
		  {
		   // Declaration of Customizations of properties:
		   FPropertyEditorModule& PropertyEdModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	       // We create a bound between the property and its custom detail slate code. 
		   PropertyEdModule.RegisterCustomClassLayout(UAC_MyActorComponent::StaticClass()->GetFName(),FOnGetDetailCustomizationInstance::CreateStatic(& FAC_MyActorComponentDetails::MakeInstance));
		  }
 
void FCustomEdProjectEditorModule::ShutdownModule()
    {
    }