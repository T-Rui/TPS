// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor_PickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "TPSCharacter.h"
#include "Public/TimerManager.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AActor_PickUp::AActor_PickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> object_Clip(TEXT("StaticMesh'/Game/Weapons/AssaultRifle/Meshes/SM_AssaultRifle_Clip.SM_AssaultRifle_Clip'"));
    pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    pMesh->SetupAttachment(RootComponent);
    if (object_Clip.Succeeded()) pMesh->SetStaticMesh(object_Clip.Object);

    pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    pBox->SetupAttachment(pMesh);
    pBox->OnComponentBeginOverlap.AddDynamic(this, &AActor_PickUp::onCharacterBeginOverlap);
    pBox->OnComponentEndOverlap.AddDynamic(this, &AActor_PickUp::onCharacterEndOverlap);

    pTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
    pTextRender->SetupAttachment(pMesh);
    pTextRender->SetText(FText::FromString("Clip"));
    pTextRender->SetWorldScale3D(FVector(0,0,0));

    static ConstructorHelpers::FObjectFinder<UCurveFloat> object_Curve(TEXT("CurveFloat'/Game/Blueprints/Curve_Camera.Curve_Camera'"));
    if (object_Curve.Succeeded()) pCurve = object_Curve.Object;
}

// Called when the game starts or when spawned
void AActor_PickUp::BeginPlay()
{
	Super::BeginPlay();
	
    pTimeline = new FTimeline();
    pTimeline->SetLooping(false);

    timelineCallBack.BindUFunction(this, TEXT("timelineCallBack_Function"));
    pTimeline->AddInterpFloat(pCurve, timelineCallBack);
}

// Called every frame
void AActor_PickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (pTimeline->IsPlaying()) pTimeline->TickTimeline(DeltaTime);
}

void AActor_PickUp::onCharacterBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) {
    if (Cast<ATPSCharacter>(otherActor)) {
        GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AActor_PickUp::Timer_TextRender, 0.01f, true);
        currentScale = pTextRender->RelativeScale3D;
        desiredScale = FVector(1.f,1.f,1.f);
        pTimeline->PlayFromStart();

        Cast<ATPSCharacter>(otherActor)->Array_PickUps.Add(this);
    }
}
void AActor_PickUp::onCharacterEndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex) {
    if (Cast<ATPSCharacter>(otherActor)) {
        currentScale = pTextRender->RelativeScale3D;
        desiredScale = FVector(0,0,0);
        pTimeline->PlayFromStart();
        GetWorld()->GetTimerManager().ClearTimer(timerHandle);

        Cast<ATPSCharacter>(otherActor)->Array_PickUps.Remove(this);
    }
}

void AActor_PickUp::Timer_TextRender() {
    FVector PickUpLocation = GetActorLocation();
    FVector CharacterLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

    pTextRender->SetWorldRotation((CharacterLocation - PickUpLocation).Rotation());
}
void AActor_PickUp::timelineCallBack_Function(float Value) {
    FVector scale = FMath::Lerp(currentScale, desiredScale, Value);
    pTextRender->SetWorldScale3D(scale);
}
