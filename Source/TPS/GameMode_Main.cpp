// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode_Main.h"
#include "TPSCharacter.h"
#include "Blueprint/UserWidget.h"

// Constructor
AGameMode_Main::AGameMode_Main() {
	DefaultPawnClass = ATPSCharacter::StaticClass();
}

void AGameMode_Main::BeginPlay() {
	Super::BeginPlay();

	TSubclassOf<UUserWidget_HUD> class_HUD = LoadClass<UUserWidget_HUD>(this, TEXT("WidgetBlueprint'/Game/UI/BPH_HUD.BPH_HUD_C'"));
	if (class_HUD) {
		pHUD = CreateWidget<UUserWidget_HUD>(GetWorld(), class_HUD);
		pHUD->AddToViewport();
	}
}

