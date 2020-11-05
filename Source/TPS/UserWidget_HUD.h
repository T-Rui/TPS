// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_HUD.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UUserWidget_HUD(const FObjectInitializer& objectInitializer);

    UFUNCTION(BlueprintImplementableEvent)
    void Equip();
    UFUNCTION(BlueprintImplementableEvent)
    void UnEquip();

    void AddAmmo(const int32 nAmmo);
    void Reload();
    void Shoot();

	UFUNCTION(BlueprintCallable, Category = "KillEnemy,BlueprintFunc")
	void KillEnemy(const int32 nEnemy);

    UPROPERTY(BlueprintReadOnly)
    FText currentAmmo;
    UPROPERTY(BlueprintReadOnly)
    FText allAmmo;
	UPROPERTY(BlueprintReadOnly)
	FText killnemy;
};
