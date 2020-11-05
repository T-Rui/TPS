// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Actor_PickUp.generated.h"

UCLASS()
class TPS_API AActor_PickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_PickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
    void onCharacterBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
    UFUNCTION()
    void onCharacterEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex);

    FTimerHandle timerHandle;
    void Timer_TextRender();

    class UCurveFloat* pCurve;
    FTimeline* pTimeline;
    FOnTimelineFloat timelineCallBack;

    UFUNCTION()
    void timelineCallBack_Function(float Value);

    FVector currentScale;
    FVector desiredScale;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    class UStaticMeshComponent* pMesh;
    class UBoxComponent* pBox;
    class UTextRenderComponent* pTextRender;
};
