// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidget_HUD.h"


UUserWidget_HUD::UUserWidget_HUD(const FObjectInitializer& objectInitializer) : Super(objectInitializer) {
    currentAmmo = FText::FromString("30");
    allAmmo = FText::FromString("60");
	killnemy = FText::FromString("0");
}


void UUserWidget_HUD::AddAmmo(const int32 nAmmo) {
    int32 nAllAmmo = FCString::Atoi(*allAmmo.ToString());
    nAllAmmo += nAmmo;
    allAmmo = FText::FromString(FString::FromInt(nAllAmmo));
}

void UUserWidget_HUD::Reload() {
    currentAmmo = FText::FromString("30");
}

void UUserWidget_HUD::Shoot() {
    int32 nCurrentAmmo = FCString::Atoi(*currentAmmo.ToString());
    nCurrentAmmo -= 1;
    currentAmmo = FText::FromString(FString::FromInt(nCurrentAmmo));
}
void UUserWidget_HUD::KillEnemy(const int32 nEnemy){
	int32 nkill = FCString::Atoi(*killnemy.ToString());
	nkill += nEnemy;
	killnemy = FText::FromString(FString::FromInt(nkill));
}